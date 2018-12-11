/**
   Marlin 3D Printer Firmware
   Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]

   Based on Sprinter and grbl.
   Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Repetier.h"
#include "Configuration.h"

#define DELTA_AUTO_CALIBRATION

#if defined(DELTA_AUTO_CALIBRATION)

#define DEBUG_AUTO_CALIBRATION

#define degreesToRadians PI / 180.0
#define min(a,b) ((a)<(b)?(a):(b))


void MatrixSwapRows(float* matrix, int cols, int i, int j) {
  if (i != j) {
    for (int k = 0; k < cols; ++k) {
      float temp = matrix[i*cols + k];
      matrix[i*cols + k] = matrix[j*cols + k];
      matrix[j*cols + k] = temp;
    }
  }
}

// Perform Gauus-Jordan elimination on a matrix with numRows rows and (njumRows + 1) columns
void MatrixGaussJordan(float* matrix, int rows, int cols, float solution[]) {
  for (int i = 0; i < rows; ++i) {
    // Swap the rows around for stable Gauss-Jordan elimination
    float vmax = abs(matrix[i*cols + i]);
    for (int j = i + 1; j < rows; ++j) {
      float rmax = abs(matrix[j*cols + i]);
      if (rmax > vmax) {
        MatrixSwapRows(matrix, cols, i, j);
        vmax = rmax;
      }
    }

    // Use row i to eliminate the ith element from previous and subsequent rows
    float v = matrix[i*cols + i];
    for (int j = 0; j < i; ++j) {
      float factor = matrix[j*cols + i] / v;
      matrix[j*cols + i] = 0.0;
      for (int k = i + 1; k <= rows; ++k) {
        matrix[j*cols + k] -= matrix[i*cols + k] * factor;
      }
    }

    for (int j = i + 1; j < rows; ++j) {
      float factor = matrix[j*cols + i] / v;
      matrix[j*cols + i] = 0.0;
      for (int k = i + 1; k <= rows; ++k) {
        matrix[j*cols + k] -= matrix[i*cols + k] * factor;
      }
    }
  }

  for (int i = 0; i < rows; ++i) {
    solution[i] = (matrix[i*cols + rows] / matrix[i*cols + i]);
  }
}


class DeltaParameters {
  public:
    float diagonal;
    float radius;
    float homedHeight;
    float xStop;
    float yStop;
    float zStop;
    float xAdj;
    float yAdj;
    float zAdj;

    float towerX[3];
    float towerY[3];

    float Xbc;
    float Xca;
    float Xab;
    float Ybc;
    float Yca;
    float Yab;
    float coreFa;
    float coreFb;
    float coreFc;
    float Q;
    float Q2;
    float D2;

    float homedCarriageHeight;
  public:
    DeltaParameters(float aDiagonal, float aRadius, float aHeight, float aXStop, float aYStop, float aZStop, float aXAdj, float aYAdj, float aZAdj);

    void readFromEeprom();
    void writeToEeprom(bool aAngularCorr=true);

    void genProbePoints(int aNumPoints);

    void recalc();

    float transform(float machinePos[], int axis);
    float inverseTransform(float Ha, float Hb, float Hc);
    float computeDerivative(int deriv, float ha, float hb, float hc);
    void normaliseEndstopAdjustments();
    void adjust(int numFactors, float v[], bool norm);
};

DeltaParameters::DeltaParameters(float aDiagonal, float aRadius, float aHeight, float aXStop, float aYStop, float aZStop, float aXAdj, float aYAdj, float aZAdj) {
  diagonal = aDiagonal;
  radius = aRadius;
  homedHeight = aHeight;
  xStop = aXStop;
  yStop = aYStop;
  zStop = aZStop;
  xAdj = aXAdj;
  yAdj = aYAdj;
  zAdj = aZAdj;

  recalc();
}

void DeltaParameters::recalc() {
  towerX[0] = (-(radius * cos((30.0 + xAdj) * degreesToRadians)));
  towerY[0] = (-(radius * sin((30.0 + xAdj) * degreesToRadians)));
  towerX[1] = (+(radius * cos((30.0 - yAdj) * degreesToRadians)));
  towerY[1] = (-(radius * sin((30.0 - yAdj) * degreesToRadians)));
  towerX[2] = (-(radius * sin(zAdj * degreesToRadians)));
  towerY[2] = (+(radius * cos(zAdj * degreesToRadians)));

  Xbc = towerX[2] - towerX[1];
  Xca = towerX[0] - towerX[2];
  Xab = towerX[1] - towerX[0];
  Ybc = towerY[2] - towerY[1];
  Yca = towerY[0] - towerY[2];
  Yab = towerY[1] - towerY[0];
  coreFa = sq(towerX[0]) + sq(towerY[0]);
  coreFb = sq(towerX[1]) + sq(towerY[1]);
  coreFc = sq(towerX[2]) + sq(towerY[2]);
  Q = 2 * (Xca * Yab - Xab * Yca);
  Q2 = sq(Q);
  D2 = sq(diagonal);

  // Calculate the base carriage height when the printer is homed.
  float tempHeight = diagonal;   // any sensible height will do here, probably even zero
  homedCarriageHeight = homedHeight + tempHeight - inverseTransform(tempHeight, tempHeight, tempHeight);
}

float DeltaParameters::transform(float machinePos[], int axis) {
  return machinePos[2] + sqrt(D2 - sq(machinePos[0] - towerX[axis]) - sq(machinePos[1] - towerY[axis]));
}

// Inverse transform method, We only need the Z component of the result.
float DeltaParameters::inverseTransform(float Ha, float Hb, float Hc) {
  float Fa = coreFa + sq(Ha);
  float Fb = coreFb + sq(Hb);
  float Fc = coreFc + sq(Hc);

  // Setup PQRSU such that x = -(S - uz)/P, y = (P - Rz)/Q
  float P = (Xbc * Fa) + (Xca * Fb) + (Xab * Fc);
  float S = (Ybc * Fa) + (Yca * Fb) + (Yab * Fc);

  float R = 2 * ((Xbc * Ha) + (Xca * Hb) + (Xab * Hc));
  float U = 2 * ((Ybc * Ha) + (Yca * Hb) + (Yab * Hc));

  float R2 = sq(R);
  float U2 = sq(U);

  float A = U2 + R2 + Q2;
  float minusHalfB = S * U + P * R + Ha * Q2 + towerX[0] * U * Q - towerY[0] * R * Q;
  float C = sq(S + towerX[0] * Q) + sq(P - towerY[0] * Q) + (sq(Ha) - D2) * Q2;

  float rslt = (minusHalfB - sqrt(sq(minusHalfB) - A * C)) / A;
  return rslt;
}

float DeltaParameters::computeDerivative(int deriv, float ha, float hb, float hc) {
  float perturb = 0.2;      // perturbation amount in mm or degrees
  DeltaParameters hiParams(diagonal, radius, homedHeight, xStop, yStop, zStop, xAdj, yAdj, zAdj);
  DeltaParameters loParams(diagonal, radius, homedHeight, xStop, yStop, zStop, xAdj, yAdj, zAdj);
  switch (deriv)
  {
    case 0:
    case 1:
    case 2:
      break;

    case 3:
      hiParams.radius += perturb;
      loParams.radius -= perturb;
      break;

    case 4:
      hiParams.xAdj += perturb;
      loParams.xAdj -= perturb;
      break;

    case 5:
      hiParams.yAdj += perturb;
      loParams.yAdj -= perturb;
      break;

    case 6:
      hiParams.diagonal += perturb;
      loParams.diagonal -= perturb;
      break;
  }

  hiParams.recalc();
  loParams.recalc();

  float zHi = hiParams.inverseTransform((deriv == 0) ? ha + perturb : ha, (deriv == 1) ? hb + perturb : hb, (deriv == 2) ? hc + perturb : hc);
  float zLo = loParams.inverseTransform((deriv == 0) ? ha - perturb : ha, (deriv == 1) ? hb - perturb : hb, (deriv == 2) ? hc - perturb : hc);

  return (zHi - zLo) / (2.0 * perturb);
}

// Make the average of the endstop adjustments zero, or make all emndstop corrections negative, without changing the individual homed carriage heights
void DeltaParameters::normaliseEndstopAdjustments() {
  float eav = min(xStop, min(yStop, zStop));
  xStop -= eav;
  yStop -= eav;
  zStop -= eav;
  homedHeight += eav;
  homedCarriageHeight += eav;        // no need for a full recalc, this is sufficient
}

// Perform 3, 4, 6 or 7-factor adjustment.
// The input vector contains the following parameters in this order:
//  X, Y and Z endstop adjustments
//  If we are doing 4-factor adjustment, the next argument is the delta radius. Otherwise:
//  X tower X position adjustment
//  Y tower X position adjustment
//  Z tower Y position adjustment
//  Diagonal rod length adjustment
void DeltaParameters::adjust(int numFactors, float v[], bool norm) {
  float oldCarriageHeightA = homedCarriageHeight + xStop; // save for later

  // Update endstop adjustments
  xStop += v[0];
  yStop += v[1];
  zStop += v[2];

  if (norm) {
    normaliseEndstopAdjustments();
  }

  if (numFactors >= 4) {
    radius += v[3];

    if (numFactors >= 6) {
      xAdj += v[4];
      yAdj += v[5];

      if (numFactors == 7) {
        diagonal += v[6];
      }
    }

    recalc();
  }

  // Adjusting the diagonal and the tower positions affects the homed carriage height.
  // We need to adjust homedHeight to allow for this, to get the change that was requested in the endstop corrections.
  float heightError = homedCarriageHeight + xStop - oldCarriageHeightA - v[0];
  homedHeight -= heightError;
  homedCarriageHeight -= heightError;
}


class LeastSquaresCalibration {
  public:
    float bedRadius = 100;
    int numPoints = 10;
    int numFactors = 6;
    bool normalise = true;

    DeltaParameters deltaParameters;

    float probePoints[10][3];

    float expectedRmsError;
  public:
    LeastSquaresCalibration(int numPoints, int numFactors, bool normalise);

    void readFromEeprom();
    void writeToEeprom(bool aAngularCorr=true);

    void genProbePoints();

    void calcCalibration();
};

LeastSquaresCalibration::LeastSquaresCalibration(int aNumPoints, int aNumFactors, bool aNormalise): deltaParameters(299.5, 150.0, 300.0, 0, 0, 0, 0.0, 0.0, 0.0) {
  numPoints = aNumPoints;
  numFactors = aNumFactors;
  normalise = aNormalise;
}

void LeastSquaresCalibration::readFromEeprom() {
  deltaParameters.radius = EEPROM::deltaHorizontalRadius();

  deltaParameters.xStop = EEPROM::deltaTowerXOffsetSteps() / float(XAXIS_STEPS_PER_MM);
  deltaParameters.yStop = EEPROM::deltaTowerYOffsetSteps() / float(YAXIS_STEPS_PER_MM);
  deltaParameters.zStop = EEPROM::deltaTowerZOffsetSteps() / float(ZAXIS_STEPS_PER_MM);

  deltaParameters.xAdj = EEPROM::deltaAlphaA() - float(DELTA_ALPHA_A);
  deltaParameters.yAdj = EEPROM::deltaAlphaB() - float(DELTA_ALPHA_B);
  deltaParameters.zAdj = EEPROM::deltaAlphaC() - float(DELTA_ALPHA_C);

  deltaParameters.recalc();
}

void LeastSquaresCalibration::writeToEeprom(bool aAngularCorr) {
  EEPROM::setRodRadius(deltaParameters.radius);

  EEPROM::setDeltaTowerXOffsetSteps(deltaParameters.xStop * float(XAXIS_STEPS_PER_MM));
  EEPROM::setDeltaTowerYOffsetSteps(deltaParameters.yStop * float(YAXIS_STEPS_PER_MM));
  EEPROM::setDeltaTowerZOffsetSteps(deltaParameters.zStop * float(ZAXIS_STEPS_PER_MM));

  if (aAngularCorr) {
    EEPROM::setDeltaAlphaA(float(DELTA_ALPHA_A) + deltaParameters.xAdj);
    EEPROM::setDeltaAlphaB(float(DELTA_ALPHA_B) + deltaParameters.yAdj);
    EEPROM::setDeltaAlphaC(float(DELTA_ALPHA_C) + deltaParameters.zAdj);
  }
}

void LeastSquaresCalibration::genProbePoints() {
  if (numPoints == 4) {
    for (int i = 0; i < 3; ++i) {
      probePoints[i][0] = round(100.0 * bedRadius * sin((2.0 * PI * float(i)/3.0))) / 100.0;
      probePoints[i][1] = round(100.0 * bedRadius * cos((2.0 * PI * float(i)/3.0))) / 100.0;
    }
    probePoints[3][0] = 0.0;
    probePoints[3][1] = 0.0;
  }
  else {
    if (numPoints >= 7) {
      for (int i = 0; i < 6; ++i) {
        probePoints[i][0] = round(100.0 * bedRadius * sin((2.0 * PI * float(i)) / 6.0)) / 100.0;
        probePoints[i][1] = round(100.0 * bedRadius * cos((2.0 * PI * float(i)) / 6.0)) / 100.0;
      }
    }
    if (numPoints >= 10) {
      for (int i = 6; i < 9; ++i) {
        probePoints[i][0] = round(100.0 * bedRadius / 2.0 * sin((2.0 * PI * float(i - 6)) / 3.0)) / 100.0;
        probePoints[i][1] = round(100.0 * bedRadius / 2.0 * cos((2.0 * PI * float(i - 6)) / 3.0)) / 100.0;
      }
      probePoints[9][0] = 0.0;
      probePoints[9][1] = 0.0;
    }
    else {
      probePoints[6][0] = 0.0;
      probePoints[6][1] = 0.0;
    }
  } 
}

void LeastSquaresCalibration::calcCalibration() {
  if (numFactors != 3 && numFactors != 4 && numFactors != 6 && numFactors != 7) {
    Com::printErrorFLN(PSTR("Only 3, 4, 6 and 7 factors supported"));
    return;
  }
  if (numFactors > numPoints) {
    Com::printErrorFLN(PSTR("Need at least as many points as factors you want to calibrate"));
    return;
  }

  // // Transform the probing points to motor endpoints and store them in a matrix, so that we can do multiple iterations using the same data
  float probeMotorPositions[numPoints][3];
  float corrections[numPoints];
  float initialSumOfSquares = 0.0;
  for (int i = 0; i < numPoints; ++i) {
    corrections[i] = 0.0;
    float machinePos[3];
    machinePos[0] = probePoints[i][0];
    machinePos[1] = probePoints[i][1];
    machinePos[2] = 0.0;

    probeMotorPositions[i][0] = deltaParameters.transform(machinePos, 0);
    probeMotorPositions[i][1] = deltaParameters.transform(machinePos, 1);
    probeMotorPositions[i][2] = deltaParameters.transform(machinePos, 2);

    initialSumOfSquares += sq(probePoints[i][2]);
  }

  // Do 1 or more Newton-Raphson iterations
  int iteration = 0;
  for (;;) {
    // Build a Nx7 matrix of derivatives with respect to xa, xb, yc, za, zb, zc, diagonal.
    float derivativeMatrix[numPoints][numFactors];
    for (int i = 0; i < numPoints; ++i) {
      for (int j = 0; j < numFactors; ++j) {
        derivativeMatrix[i][j] = deltaParameters.computeDerivative(j, probeMotorPositions[i][0], probeMotorPositions[i][1], probeMotorPositions[i][2]);
      }
    }

    // Now build the normal equations for least squares fitting
    float normalMatrix[numFactors][numFactors + 1];
    for (int i = 0; i < numFactors; ++i) {
      for (int j = 0; j < numFactors; ++j) {
        float temp = derivativeMatrix[0][i] * derivativeMatrix[0][j];
        for (int k = 1; k < numPoints; ++k) {
          temp += derivativeMatrix[k][i] * derivativeMatrix[k][j];
        }
        normalMatrix[i][j] = temp;
      }
      float temp = derivativeMatrix[0][i] * -1.0 * (probePoints[0][2] + corrections[0]);
      for (int k = 1; k < numPoints; ++k) {
        temp += derivativeMatrix[k][i] * -1.0 * (probePoints[k][2] + corrections[k]);
      }
      normalMatrix[i][numFactors] = temp;
    }

    float solution[numFactors];
    MatrixGaussJordan(*normalMatrix, numFactors, numFactors + 1,solution);

    deltaParameters.adjust(numFactors, solution, normalise);

    // Calculate the expected probe heights using the new parameters
    {
      float expectedResiduals[numPoints];
      float sumOfSquares = 0.0;
      for (int i = 0; i < numPoints; ++i) {
        for (int axis = 0; axis < 3; ++axis) {
          probeMotorPositions[i][axis] += solution[axis];
        }
        float newZ = deltaParameters.inverseTransform(probeMotorPositions[i][0], probeMotorPositions[i][1], probeMotorPositions[i][2]);
        corrections[i] = newZ;
        expectedResiduals[i] = probePoints[i][2] + newZ;
        sumOfSquares += sq(expectedResiduals[i]);
      }

      expectedRmsError = sqrt(sumOfSquares / numPoints);
    }

    // Decide whether to do another iteration Two is slightly better than one, but three doesn't improve things.
    // Alternatively, we could stop when the expected RMS error is only slightly worse than the RMS of the residuals.
    ++iteration;
    if (iteration >= 2) {
      break;
    }
  }
}

void leastSquaresCalibration(float aTolerance, int aMaxIteration, bool aDisableSaveAngularCorr) {
  LeastSquaresCalibration calib(10, 6, true);

  Com::printFLN(PSTR("========== Least squares calibration =========="));
  for(int p=0; p<aMaxIteration; p++) {
    Com::printF(PSTR("===== "));
    Com::printF(PSTR("Pass "), p);
    Com::printFLN(PSTR(" ====="));

    Printer::homeAxis(true, true, true);
    Printer::resetTransformationMatrix(false);
    Printer::distortion.resetCorrection();

    calib.readFromEeprom();
    calib.genProbePoints();

    float zMin=999.9, zMax=-999.9;
    for (int i = 0; i < calib.numPoints; ++i) {
      Printer::moveToReal(calib.probePoints[i][0], calib.probePoints[i][1], 5.0, IGNORE_COORDINATE, 5000);

      float z = -1.0 * Printer::runZProbe(3 & 1, 3 & 2, Z_PROBE_REPETITIONS, true, false); 
      calib.probePoints[i][2] = z;

      if(z < zMin) {
        zMin = z;
      } 
      if (z > zMax) {
        zMax = z;
      }
    }

    float deviation = abs(zMax - zMin);
    if (deviation <= aTolerance) {
      Com::printFLN(PSTR("Calibration finished with tolerance: "), deviation, 3);
      break; 
    } 
    else {
      Com::printF(PSTR("Calibration out of tolerance - deviation: "), deviation, 3);
      Com::printF(PSTR(" (tolerance: "), aTolerance, 2);
      Com::printFLN(PSTR(")"));

      calib.calcCalibration();

      Com::printF(PSTR("New endstop corrections: "));
      Com::printF(PSTR("X="), calib.deltaParameters.xStop, 3);
      Com::printF(PSTR(" Y="), calib.deltaParameters.yStop, 3);
      Com::printFLN(PSTR(" Z="), calib.deltaParameters.zStop, 3);

      Com::printFLN(PSTR("New diagonal rod length: "), calib.deltaParameters.diagonal, 3);
      Com::printFLN(PSTR("New delta radius: "), calib.deltaParameters.radius, 3);
      Com::printFLN(PSTR("New homed height: "), calib.deltaParameters.homedHeight, 3);

      Com::printF(PSTR("New tower position angle corrections: "));
      Com::printF(PSTR("X="), calib.deltaParameters.xAdj, 3);
      Com::printF(PSTR(" Y="), calib.deltaParameters.yAdj, 3);
      Com::printFLN(PSTR(" Z="), calib.deltaParameters.zAdj, 3);

      calib.writeToEeprom(!aDisableSaveAngularCorr);
    }
  }

  Printer::homeAxis(true, true, true);
}

#endif // DELTA_AUTO_CALIBRATION

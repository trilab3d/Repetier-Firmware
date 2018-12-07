/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Repetier.h"
#include "Configuration.h"

#define DELTA_AUTO_CALIBRATION

#if defined(DELTA_AUTO_CALIBRATION)

#define DEBUG_AUTO_CALIBRATION

#define degreesToRadians PI / 180.0
#define min(a,b) ((a)<(b)?(a):(b))
#define num_Factors 6

void ArraySwapRows(float ar[][num_Factors + 1], int i, int j, int numCols) {
  if (i != j) {
    for (int k = 0; k < numCols; ++k) {
      float temp = ar[i][k];
      ar[i][k] = ar[j][k];
      ar[j][k] = temp;
    }
  }
}

// Perform Gauus-Jordan elimination on a matrix with numRows rows and (njumRows + 1) columns
void ArrayGaussJordan(float ar[][num_Factors + 1], float solution[], int numRows) {
  for (int i = 0; i < numRows; ++i) {
    // Swap the rows around for stable Gauss-Jordan elimination
    float vmax = abs(ar[i][i]);
    for (int j = i + 1; j < numRows; ++j) {
      float rmax = abs(ar[j][i]);
      if (rmax > vmax) {
        ArraySwapRows(ar, i, j, numRows + 1);
        vmax = rmax;
      }
    }

    Com::printFLN(PSTR("----- ArrayGaussJordan 1 -----"));
    for(int i=0; i < 6; ++i) {
      for(int j = 0; j < 7; ++j) {
        Com::printF(PSTR(", "), ar[i][j], 4);
      }
      Com::printFLN(PSTR(""));
    }

    // Use row i to eliminate the ith element from previous and subsequent rows
    float v = ar[i][i];
    for (int j = 0; j < i; ++j) {
      float factor = ar[j][i]/v;
      ar[j][i] = 0.0;
      for (int k = i + 1; k <= numRows; ++k) {
        ar[j][k] -= ar[i][k] * factor;
      }
    }

    Com::printFLN(PSTR("----- ArrayGaussJordan 2 -----"));
    for(int i=0; i < 6; ++i) {
      for(int j = 0; j < 7; ++j) {
        Com::printF(PSTR(", "), ar[i][j], 4);
      }
      Com::printFLN(PSTR(""));
    }

    for (int j = i + 1; j < numRows; ++j) {
      float factor = ar[j][i]/v;
      ar[j][i] = 0.0;
      for (int k = i + 1; k <= numRows; ++k) {
        ar[j][k] -= ar[i][k] * factor;
      }
    }

    Com::printFLN(PSTR("----- ArrayGaussJordan 3 -----"));
    for(int i=0; i < 6; ++i) {
      for(int j = 0; j < 7; ++j) {
        Com::printF(PSTR(", "), ar[i][j], 4);
      }
      Com::printFLN(PSTR(""));
    }
  }

  for (int i = 0; i < numRows; ++i) {
    solution[i] = (ar[i][numRows] / ar[i][i]);
  }
}

class DeltaParameters {
public:
  float diagonal;
  float radius;
  float homedHeight;
  float xstop;
  float ystop;
  float zstop;
  float xadj;
  float yadj;
  float zadj; 

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
  DeltaParameters(float adiagonal, float aradius, float aheight, float axstop, float aystop, float azstop, float axadj, float ayadj, float azadj);

  void Recalc();
  float Transform(float machinePos[], int axis);
  float InverseTransform(float Ha, float Hb, float Hc);
  float ComputeDerivative(int deriv, float ha, float hb, float hc);
  void NormaliseEndstopAdjustments();
  void Adjust(int numFactors, float v[], bool norm);
};

DeltaParameters::DeltaParameters(float adiagonal, float aradius, float aheight, float axstop, float aystop, float azstop, float axadj, float ayadj, float azadj) {
  diagonal = adiagonal;
  radius = aradius;
  homedHeight = aheight;
  xstop = axstop;
  ystop = aystop;
  zstop = azstop;
  xadj = axadj;
  yadj = ayadj;
  zadj = azadj;
  Recalc();
}

float DeltaParameters::Transform(float machinePos[], int axis) {
  return machinePos[2] + sqrt(D2 - sq(machinePos[0] - towerX[axis]) - sq(machinePos[1] - towerY[axis]));
}

// Inverse transform method, We only need the Z component of the result.
float DeltaParameters::InverseTransform(float Ha, float Hb, float Hc) {
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

void DeltaParameters::Recalc(){
  towerX[0] = (-(radius * cos((30.0 + xadj) * degreesToRadians)));
  towerY[0] = (-(radius * sin((30.0 + xadj) * degreesToRadians)));
  towerX[1] = (+(radius * cos((30.0 - yadj) * degreesToRadians)));
  towerY[1] = (-(radius * sin((30.0 - yadj) * degreesToRadians)));
  towerX[2] = (-(radius * sin(zadj * degreesToRadians)));
  towerY[2] = (+(radius * cos(zadj * degreesToRadians)));

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
  homedCarriageHeight = homedHeight + tempHeight - InverseTransform(tempHeight, tempHeight, tempHeight);
}

float DeltaParameters::ComputeDerivative(int deriv, float ha, float hb, float hc) {
  float perturb = 0.2;      // perturbation amount in mm or degrees
  DeltaParameters hiParams(diagonal, radius, homedHeight, xstop, ystop, zstop, xadj, yadj, zadj);
  DeltaParameters loParams(diagonal, radius, homedHeight, xstop, ystop, zstop, xadj, yadj, zadj);
  switch(deriv)
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
    hiParams.xadj += perturb;
    loParams.xadj -= perturb;
    break;

  case 5:
    hiParams.yadj += perturb;
    loParams.yadj -= perturb;
    break;

  case 6:
    hiParams.diagonal += perturb;
    loParams.diagonal -= perturb;
    break;
  }

  hiParams.Recalc();
  loParams.Recalc();

  float zHi = hiParams.InverseTransform((deriv == 0) ? ha + perturb : ha, (deriv == 1) ? hb + perturb : hb, (deriv == 2) ? hc + perturb : hc);
  float zLo = loParams.InverseTransform((deriv == 0) ? ha - perturb : ha, (deriv == 1) ? hb - perturb : hb, (deriv == 2) ? hc - perturb : hc);

  return (zHi - zLo)/(2 * perturb);
}

// Make the average of the endstop adjustments zero, or make all emndstop corrections negative, without changing the individual homed carriage heights
void DeltaParameters::NormaliseEndstopAdjustments() {
  float eav = min(xstop, min(ystop, zstop));
  xstop -= eav;
  ystop -= eav;
  zstop -= eav;
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
void DeltaParameters::Adjust(int numFactors, float v[], bool norm) {
  float oldCarriageHeightA = homedCarriageHeight + xstop; // save for later

  // Update endstop adjustments
  xstop += v[0];
  ystop += v[1];
  zstop += v[2];
  if (norm) {
    NormaliseEndstopAdjustments();
  }

  if (numFactors >= 4) {
    radius += v[3];

    if (numFactors >= 6) {
      xadj += v[4];
      yadj += v[5];

      if (numFactors == 7) {
        diagonal += v[6];
      }
    }

    Recalc();
  }

  // Adjusting the diagonal and the tower positions affects the homed carriage height.
  // We need to adjust homedHeight to allow for this, to get the change that was requested in the endstop corrections.
  float heightError = homedCarriageHeight + xstop - oldCarriageHeightA - v[0];
  homedHeight -= heightError;
  homedCarriageHeight -= heightError;
}

class Parameters {
public:
  // firmware = "Repetier";
  bool normalise = true;
  DeltaParameters deltaParams;
  float bedRadius = 100.0;
  int numPoints = 10;
  int numFactors = 6;
  float probePoints[10][3];
  int endstopFactor = 1.0/100; // Repetier

  Parameters();
};

Parameters::Parameters(): deltaParams(299.5, 150.0, 300.0, 50.0, 50.0, 50.0, 0.0, 0.0, 0.0) {
 
}

void calcProbePoints(Parameters *params) {
  if (params->numPoints >= 7) {
    for (int i = 0; i < 6; ++i) {
      params->probePoints[i][0] = round(100 * params->bedRadius * sin((2.0 * PI * float(i))/6.0))/100.0;
      params->probePoints[i][1] = round(100 * params->bedRadius * cos((2.0 * PI * float(i))/6.0))/100.0;
    }
  }
  if (params->numPoints >= 10) {
    for (int i = 6; i < 9; ++i) {
      params->probePoints[i][0] = round(100 * params->bedRadius/2.0 * sin((2.0 * PI * float(i - 6))/3.0))/100.0;
      params->probePoints[i][1] = round(100 * params->bedRadius/2.0 * cos((2.0 * PI * float(i - 6))/3.0))/100.0;
    }
    params->probePoints[9][0] = 0.0;
    params->probePoints[9][1] = 0.0;
  }
}

void convertIncomingEndstops(Parameters *params) {
  params->deltaParams.xstop *= params->endstopFactor;
  params->deltaParams.ystop *= params->endstopFactor;
  params->deltaParams.zstop *= params->endstopFactor;
}

void convertOutgoingEndstops(Parameters *params) {
  float endstopFactor = 100.0;
  params->deltaParams.xstop *= endstopFactor;
  params->deltaParams.ystop *= endstopFactor;
  params->deltaParams.zstop *= endstopFactor;
}



void DoDeltaCalibration(Parameters *params) {
  // if (numFactors != 3 && numFactors != 4 && numFactors != 6 && numFactors != 7) {
  //   return "Error: " + numFactors + " factors requested but only 3, 4, 6 and 7 supported";
  // }
  // if (numFactors > numPoints) {
  //   return "Error: need at least as many points as factors you want to calibrate";
  // }

  // // Transform the probing points to motor endpoints and store them in a matrix, so that we can do multiple iterations using the same data
  float probeMotorPositions[params->numPoints][3];
  float corrections[params->numPoints];
  float initialSumOfSquares = 0.0;
  for (int i = 0; i < params->numPoints; ++i) {
    corrections[i] = 0.0;
    float machinePos[3];
    machinePos[0] = params->probePoints[i][0];
    machinePos[1] = params->probePoints[i][1];
    machinePos[2] = 0.0;

    probeMotorPositions[i][0] = params->deltaParams.Transform(machinePos, 0);
    probeMotorPositions[i][1] = params->deltaParams.Transform(machinePos, 1);
    probeMotorPositions[i][2] = params->deltaParams.Transform(machinePos, 2);

    initialSumOfSquares += sq(params->probePoints[i][2]);
  }

  Com::printFLN(PSTR("----- probeMotorPositions -----"));
  for(int i=0; i < params->numPoints; ++i) {
    Com::printF(PSTR("X="), probeMotorPositions[i][0], 4);
    Com::printF(PSTR(", Y="), probeMotorPositions[i][1], 4);
    Com::printFLN(PSTR(", Z="), probeMotorPositions[i][2], 4);
  }
  Com::printFLN(PSTR("initialSumOfSquares"), initialSumOfSquares, 4);


  Com::printFLN(PSTR("---------- Newton-Raphson iterations ----------"));
  // // // Do 1 or more Newton-Raphson iterations
  int iteration = 0;
  bool expectedRmsError;
  for (;;) {
    Com::printFLN(PSTR("iteration "), iteration);

    // Build a Nx7 matrix of derivatives with respect to xa, xb, yc, za, zb, zc, diagonal.
    float derivativeMatrix[params->numPoints][params->numFactors];
    for (int i = 0; i < params->numPoints; ++i) {
      for (int j = 0; j < params->numFactors; ++j) {
        derivativeMatrix[i][j] = params->deltaParams.ComputeDerivative(j, probeMotorPositions[i][0], probeMotorPositions[i][1], probeMotorPositions[i][2]);
      }
    }

    Com::printFLN(PSTR("----- derivativeMatrix -----"));
    for(int i=0; i < params->numPoints; ++i) {
      for(int j = 0; j < params->numFactors; ++j) {
        Com::printF(PSTR(", "), derivativeMatrix[i][j], 4);
      }
      Com::printFLN(PSTR(""));
    }

    // Now build the normal equations for least squares fitting
    float normalMatrix[params->numFactors][num_Factors + 1];
    for (int i = 0; i < params->numFactors; ++i) {
      for (int j = 0; j < params->numFactors; ++j) {
        float temp = derivativeMatrix[0][i] * derivativeMatrix[0][j];
        for (int k = 1; k < params->numPoints; ++k) {
          temp += derivativeMatrix[k][i] * derivativeMatrix[k][j];
        }
        normalMatrix[i][j] = temp;
        Com::printFLN(PSTR("Temp1"), temp, 4);
      }
      float temp = derivativeMatrix[0][i] * -1.0 * (params->probePoints[0][2] + corrections[0]);
      for (int k = 1; k < params->numPoints; ++k) {
        temp += derivativeMatrix[k][i] * -1.0 * (params->probePoints[k][2] + corrections[k]);
      }
      Com::printFLN(PSTR("Temp2"), temp, 4);
      normalMatrix[i][params->numFactors] = temp;
    }

    Com::printFLN(PSTR("----- normalMatrix -----"));
    for(int i=0; i < params->numFactors; ++i) {
      for(int j = 0; j < params->numFactors + 1; ++j) {
        Com::printF(PSTR(", "), normalMatrix[i][j], 4);
      }
      Com::printFLN(PSTR(""));
    }

    float solution[params->numFactors];
    ArrayGaussJordan(normalMatrix, solution, params->numFactors);
    
    Com::printFLN(PSTR("----- ArrayGaussJordan -----"));
    for (int i = 0; i < params->numFactors; ++i) {
      Com::printFLN(PSTR("solution"), solution[i], 4);
    }

  //   if (debug) {
  //     DebugPrint(PrintVector("Solution", solution));

  //     // Calculate and display the residuals
  //     var residuals = [];
  //     for (var i = 0; i < numPoints; ++i) {
  //       var r = zBedProbePoints[i];
  //       for (var j = 0; j < numFactors; ++j) {
  //         r += solution[j] * derivativeMatrix.data[i][j];
  //       }
  //       residuals.push(r);
  //     }
  //     DebugPrint(PrintVector("Residuals", residuals));
  //   }

    params->deltaParams.Adjust(params->numFactors, solution, params->normalise);

    Com::printFLN(PSTR("----- Adjust -----"));
    for (int i = 0; i < params->numFactors; ++i) {
      Com::printFLN(PSTR("solution"), solution[i], 4);
    }

    // Calculate the expected probe heights using the new parameters
    {
      float expectedResiduals[params->numPoints];
      float sumOfSquares = 0.0;
      for (int i = 0; i < params->numPoints; ++i) {
        for (int axis = 0; axis < 3; ++axis) {
          probeMotorPositions[i][axis] += solution[axis];
        }
        float newZ = params->deltaParams.InverseTransform(probeMotorPositions[i][0], probeMotorPositions[i][1], probeMotorPositions[i][2]);
        corrections[i] = newZ;
        expectedResiduals[i] = params->probePoints[i][3] + newZ;
        sumOfSquares += sq(expectedResiduals[i]);
      }

      expectedRmsError = sqrt(sumOfSquares/params->numPoints);
      // DebugPrint(PrintVector("Expected probe error", expectedResiduals));
    }

    Com::printFLN(PSTR("----- expectedProbeHeights -----"));
    for (int i = 0; i < params->numPoints; ++i) {
      Com::printFLN(PSTR("corrections"), corrections[i], 4);
    }

    // Decide whether to do another iteration Two is slightly better than one, but three doesn't improve things.
    // Alternatively, we could stop when the expected RMS error is only slightly worse than the RMS of the residuals.
    ++iteration;
    if (iteration >= 2) { 
      break; 
    }
  }
}

void leastSquaresCalibration() {

  Parameters params;

  // Printer::homeAxis(true, true, true);
  // Printer::resetTransformationMatrix(false);
  // Printer::distortion.resetCorrection();

  calcProbePoints(&params);

  params.probePoints[0][2] = -0.02;
  params.probePoints[1][2] = 0.03;
  params.probePoints[2][2] = 0.0;
  params.probePoints[3][2] = -0.05;
  params.probePoints[4][2] = -0.08;
  params.probePoints[5][2] = -0.3;
  params.probePoints[6][2] = -0.08;
  params.probePoints[7][2] = -0.06;
  params.probePoints[8][2] = -0.11;
  params.probePoints[9][2] = -0.13;

  Com::printF(PSTR("Probe points:"));
  for (int i = 0; i <= 9; ++i) {
    Com::printF(PSTR("Point"), i);
    Com::printF(PSTR(": X="), params.probePoints[i][0]);
    Com::printF(PSTR(" Y="), params.probePoints[i][1]);
    Com::printFLN(PSTR(" zCorr="), params.probePoints[i][2]);
  }

  for (int i = 0; i <= 9; ++i) {
    params.probePoints[i][2] = -1.0 * params.probePoints[i][2];
  }

  //for (int i = 0; i <= 9; ++i) {
  //  Printer::moveToReal(params.probePoints[i][0], params.probePoints[i][1], 5.0, IGNORE_COORDINATE, 5000);

  //  GCode::executeFString(PSTR("G30"));
      
  //  params.probePoints[i][2] = Printer::distortion.correct(Printer::currentPositionSteps[X_AXIS], Printer::currentPositionSteps[Y_AXIS], Printer::zMinSteps) * Printer::invAxisStepsPerMM[Z_AXIS];
  //}

  convertIncomingEndstops(&params);
  DoDeltaCalibration(&params);
  convertOutgoingEndstops(&params);

  Com::printF(PSTR("New endstop corrections: "));
  Com::printF(PSTR("X="), params.deltaParams.xstop);
  Com::printF(PSTR(" Y="), params.deltaParams.ystop);
  Com::printFLN(PSTR(" Z="), params.deltaParams.zstop);

  Com::printFLN(PSTR("New diagonal rod length: "), params.deltaParams.diagonal);
  Com::printFLN(PSTR("New delta radius: "), params.deltaParams.radius);
  Com::printFLN(PSTR("New homed height: "), params.deltaParams.homedHeight);

  Com::printF(PSTR("New tower position angle corrections: "));
  Com::printF(PSTR("X="), params.deltaParams.xadj);
  Com::printF(PSTR(" Y="), params.deltaParams.yadj);
  Com::printFLN(PSTR(" Z="), params.deltaParams.zadj);

  // Printer::homeAxis(true, true, true);
}

#endif // DELTA_AUTO_CALIBRATION

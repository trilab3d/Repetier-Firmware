/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

//aaaa

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**************** READ FIRST ************************

   This configuration file was created with the configuration tool. For that
   reason, it does not contain the same informations as the original Configuration.h file.
   It misses the comments and unused parts. Open this file file in the config tool
   to see and change the data. You can also upload it to newer/older versions. The system
   will silently add new options, so compilation continues to work.

   This file is optimized for version 1.0.3
   generator: http://www.repetier.com/firmware/dev/

   If you are in doubt which named functions use which pins on your board, please check the
   pins.h for the used name->pin assignments and your board documentation to verify it is
   as you expect.

*/

#define NUM_EXTRUDER 2
#define MOTHERBOARD 33
#include "pins.h"

// ################## EDIT THESE SETTINGS MANUALLY ################
#define MICROSTEP_MODES { 16,16,16,16,16,16 } // [1,2,4,8,16]

// ################ END MANUAL SETTINGS ##########################

#undef FAN_BOARD_PIN
#define FAN_BOARD_PIN -1
#define BOARD_FAN_SPEED 255
#define BOARD_FAN_MIN_SPEED 0
#define FAN_THERMO_PIN -1
#define FAN_THERMO_MIN_PWM 128
#define FAN_THERMO_MAX_PWM 255
#define FAN_THERMO_MIN_TEMP 45
#define FAN_THERMO_MAX_TEMP 60
#define FAN_THERMO_THERMISTOR_PIN -1
#define FAN_THERMO_THERMISTOR_TYPE 1

//#define EXTERNALSERIAL  use Arduino serial library instead of build in. Requires more ram, has only 63 byte input buffer.
// Uncomment the following line if you are using Arduino compatible firmware made for Arduino version earlier then 1.0
// If it is incompatible you will get compiler errors about write functions not being compatible!
//#define COMPAT_PRE1
#define BLUETOOTH_SERIAL  -1
#define BLUETOOTH_BAUD  115200
#define MIXING_EXTRUDER 0

#define DRIVE_SYSTEM 3
#define XAXIS_STEPS_PER_MM 100
#define YAXIS_STEPS_PER_MM 100
#define ZAXIS_STEPS_PER_MM 100
#define EXTRUDER_FAN_COOL_TEMP 50
#define PDM_FOR_EXTRUDER 0
#define PDM_FOR_COOLER 0
#define DECOUPLING_TEST_MAX_HOLD_VARIANCE 30
#define DECOUPLING_TEST_MIN_TEMP_RISE 0.5
#define KILL_IF_SENSOR_DEFECT 0
#define RETRACT_ON_PAUSE 2
#define PAUSE_START_COMMANDS ""
#define PAUSE_END_COMMANDS ""
#define SHARED_EXTRUDER_HEATER 1
#define EXT0_X_OFFSET 0
#define EXT0_Y_OFFSET 0
#define EXT0_Z_OFFSET 0
#define EXT0_STEPS_PER_MM 400
#define EXT0_TEMPSENSOR_TYPE 8
#define EXT0_TEMPSENSOR_PIN TEMP_0_PIN
#define EXT0_HEATER_PIN HEATER_0_PIN
#define EXT0_STEP_PIN ORIG_E0_STEP_PIN
#define EXT0_DIR_PIN ORIG_E0_DIR_PIN
#define EXT0_INVERSE 1
#define EXT0_ENABLE_PIN ORIG_E0_ENABLE_PIN
#define EXT0_ENABLE_ON 0
#define EXT0_MIRROR_STEPPER 0
#define EXT0_STEP2_PIN ORIG_E0_STEP_PIN
#define EXT0_DIR2_PIN ORIG_E0_DIR_PIN
#define EXT0_INVERSE2 0
#define EXT0_ENABLE2_PIN ORIG_E0_ENABLE_PIN
#define EXT0_MAX_FEEDRATE 60
#define EXT0_MAX_START_FEEDRATE 20
#define EXT0_MAX_ACCELERATION 9000
#define EXT0_HEAT_MANAGER 1
#define EXT0_PREHEAT_TEMP 200
#define EXT0_WATCHPERIOD 1
#define EXT0_PID_INTEGRAL_DRIVE_MAX 230
#define EXT0_PID_INTEGRAL_DRIVE_MIN 40
#define EXT0_PID_PGAIN_OR_DEAD_TIME 7
#define EXT0_PID_I 1
#define EXT0_PID_D 32
#define EXT0_PID_MAX 230
#define EXT0_ADVANCE_K 0
#define EXT0_ADVANCE_L 0
#define EXT0_ADVANCE_BACKLASH_STEPS 0
#define EXT0_WAIT_RETRACT_TEMP 150
#define EXT0_WAIT_RETRACT_UNITS 0
#define EXT0_SELECT_COMMANDS ""
#define EXT0_DESELECT_COMMANDS ""
#define EXT0_EXTRUDER_COOLER_PIN HEATER_3_PIN
#define EXT0_EXTRUDER_COOLER_SPEED 255
#define EXT0_DECOUPLE_TEST_PERIOD 20000
#define EXT0_JAM_PIN ORIG_X_MIN_PIN
#define EXT0_JAM_PULLUP 1
#define EXT1_X_OFFSET 0
#define EXT1_Y_OFFSET 0
#define EXT1_Z_OFFSET 0
#define EXT1_STEPS_PER_MM 600
#define EXT1_TEMPSENSOR_TYPE 8
#define EXT1_TEMPSENSOR_PIN TEMP_0_PIN
#define EXT1_HEATER_PIN HEATER_0_PIN
#define EXT1_STEP_PIN ORIG_E1_STEP_PIN
#define EXT1_DIR_PIN ORIG_E1_DIR_PIN
#define EXT1_INVERSE 0
#define EXT1_ENABLE_PIN ORIG_E1_ENABLE_PIN
#define EXT1_ENABLE_ON 0
#define EXT1_MIRROR_STEPPER 0
#define EXT1_STEP2_PIN ORIG_E1_STEP_PIN
#define EXT1_DIR2_PIN ORIG_E1_DIR_PIN
#define EXT1_INVERSE2 0
#define EXT1_ENABLE2_PIN ORIG_E1_ENABLE_PIN
#define EXT1_MAX_FEEDRATE 50
#define EXT1_MAX_START_FEEDRATE 0.6
#define EXT1_MAX_ACCELERATION 120
#define EXT1_HEAT_MANAGER 1
#define EXT1_PREHEAT_TEMP 200
#define EXT1_WATCHPERIOD 1
#define EXT1_PID_INTEGRAL_DRIVE_MAX 230
#define EXT1_PID_INTEGRAL_DRIVE_MIN 40
#define EXT1_PID_PGAIN_OR_DEAD_TIME 7
#define EXT1_PID_I 1
#define EXT1_PID_D 32
#define EXT1_PID_MAX 230
#define EXT1_ADVANCE_K 0
#define EXT1_ADVANCE_L 0
#define EXT1_ADVANCE_BACKLASH_STEPS 0
#define EXT1_WAIT_RETRACT_TEMP 150
#define EXT1_WAIT_RETRACT_UNITS 0
#define EXT1_SELECT_COMMANDS ""
#define EXT1_DESELECT_COMMANDS ""
#define EXT1_EXTRUDER_COOLER_PIN HEATER_3_PIN
#define EXT1_EXTRUDER_COOLER_SPEED 255
#define EXT1_DECOUPLE_TEST_PERIOD 20000
#define EXT1_JAM_PIN -1
#define EXT1_JAM_PULLUP 0

#define FEATURE_RETRACTION 1
#define AUTORETRACT_ENABLED 0
#define RETRACTION_LENGTH 0
#define RETRACTION_LONG_LENGTH 0
#define RETRACTION_SPEED 30
#define RETRACTION_Z_LIFT 0
#define RETRACTION_UNDO_EXTRA_LENGTH 0
#define RETRACTION_UNDO_EXTRA_LONG_LENGTH 0
#define RETRACTION_UNDO_SPEED 20
#define FILAMENTCHANGE_X_POS 0
#define FILAMENTCHANGE_Y_POS 0
#define FILAMENTCHANGE_Z_ADD  50
#define FILAMENTCHANGE_REHOME 0
#define FILAMENTCHANGE_SHORTRETRACT 3
#define FILAMENTCHANGE_LONGRETRACT 100
#define JAM_METHOD 2
#define JAM_STEPS 220
#define JAM_SLOWDOWN_STEPS 320
#define JAM_SLOWDOWN_TO 70
#define JAM_ERROR_STEPS 500
#define JAM_MIN_STEPS 10
#define JAM_ACTION 1
#define JAM_DEBOUNCE 1000

#define RETRACT_DURING_HEATUP true
#define PID_CONTROL_RANGE 10
#define SKIP_M109_IF_WITHIN 1
#define SCALE_PID_TO_MAX 0
#define TEMP_HYSTERESIS 4
#define EXTRUDE_MAXLENGTH 1000
#define NUM_TEMPS_USERTHERMISTOR0 0
#define USER_THERMISTORTABLE0 {}
#define NUM_TEMPS_USERTHERMISTOR1 0
#define USER_THERMISTORTABLE1 {}
#define NUM_TEMPS_USERTHERMISTOR2 0
#define USER_THERMISTORTABLE2 {}
#define GENERIC_THERM_VREF 5
#define GENERIC_THERM_NUM_ENTRIES 33
#define HEATER_PWM_SPEED 0
#define COOLER_PWM_SPEED 0

// ############# Heated bed configuration ########################

#define HAVE_HEATED_BED 1
#define HEATED_BED_PREHEAT_TEMP 55
#define HEATED_BED_MAX_TEMP 105
#define SKIP_M190_IF_WITHIN 3
#define HEATED_BED_SENSOR_TYPE 14
#define HEATED_BED_SENSOR_PIN TEMP_1_PIN
#define HEATED_BED_HEATER_PIN HEATER_1_PIN
#define HEATED_BED_SET_INTERVAL 5000
#define HEATED_BED_HEAT_MANAGER 1
#define HEATED_BED_PID_INTEGRAL_DRIVE_MAX 120
#define HEATED_BED_PID_INTEGRAL_DRIVE_MIN 0
#define HEATED_BED_PID_PGAIN_OR_DEAD_TIME   80
#define HEATED_BED_PID_IGAIN   30
#define HEATED_BED_PID_DGAIN 70
#define HEATED_BED_PID_MAX 120
#define HEATED_BED_DECOUPLE_TEST_PERIOD 300000
#define MIN_EXTRUDER_TEMP 90
#define MAXTEMP 290
#define MIN_DEFECT_TEMPERATURE 5
#define MAX_DEFECT_TEMPERATURE 295
#define MILLISECONDS_PREHEAT_TIME 30000

// ##########################################################################################
// ##                             Laser configuration                                      ##
// ##########################################################################################

/*
If the firmware is in laser mode, it can control a laser output to cut or engrave materials.
Please use this feature only if you know about safety and required protection. Lasers are
dangerous and can hurt or make you blind!!!

The default laser driver only supports laser on and off. Here you control the intensity with
your feedrate. For exchangeable diode lasers this is normally enough. If you need more control
you can set the intensity in a range 0-255 with a custom extension to the driver. See driver.h
and comments on how to extend the functions non invasive with our event system.

If you have a laser - powder system you will like your E override. If moves contain a
increasing extruder position it will laser that move. With this trick you can
use existing fdm slicers to laser the output. Laser width is extrusion width.

Other tools may use M3 and M5 to enable/disable laser. Here G1/G2/G3 moves have laser enabled
and G0 moves have it disables.

In any case, laser only enables while moving. At the end of a move it gets
automatically disabled.
*/

#define SUPPORT_LASER 0
#define LASER_PIN -1
#define LASER_ON_HIGH 1
#define LASER_WARMUP_TIME 0
#define LASER_PWM_MAX 255
#define LASER_WATT 2

// ##                              CNC configuration                                       ##

/*
If the firmware is in CNC mode, it can control a mill with M3/M4/M5. It works
similar to laser mode, but mill keeps enabled during G0 moves and it allows
setting rpm (only with event extension that supports this) and milling direction.
It also can add a delay to wait for spindle to run on full speed.
*/

#define SUPPORT_CNC 0
#define CNC_WAIT_ON_ENABLE 300
#define CNC_WAIT_ON_DISABLE 0
#define CNC_ENABLE_PIN -1
#define CNC_ENABLE_WITH 1
#define CNC_DIRECTION_PIN -1
#define CNC_DIRECTION_CW 1
#define CNC_PWM_MAX 255
#define CNC_RPM_MAX 8000
#define CNC_SAFE_Z 150

#define DEFAULT_PRINTER_MODE 0

// ################ Endstop configuration #####################

#define MULTI_ZENDSTOP_HOMING 0
#define ENDSTOP_PULLUP_X_MIN true
#define ENDSTOP_X_MIN_INVERTING false
#define MIN_HARDWARE_ENDSTOP_X false
#define ENDSTOP_PULLUP_Y_MIN true
#define ENDSTOP_Y_MIN_INVERTING false
#define MIN_HARDWARE_ENDSTOP_Y false
#define ENDSTOP_PULLUP_Z_MIN true
#define ENDSTOP_Z_MIN_INVERTING true
#define MIN_HARDWARE_ENDSTOP_Z true
#define ENDSTOP_PULLUP_Z2_MINMAX true
#define ENDSTOP_Z2_MINMAX_INVERTING false
#define MINMAX_HARDWARE_ENDSTOP_Z2 false
#define ENDSTOP_PULLUP_X_MAX true
#define ENDSTOP_X_MAX_INVERTING false
#define MAX_HARDWARE_ENDSTOP_X true
#define ENDSTOP_PULLUP_Y_MAX true
#define ENDSTOP_Y_MAX_INVERTING false
#define MAX_HARDWARE_ENDSTOP_Y true
#define ENDSTOP_PULLUP_Z_MAX true
#define ENDSTOP_Z_MAX_INVERTING false
#define MAX_HARDWARE_ENDSTOP_Z true
#define ENDSTOP_PULLUP_X2_MIN true
#define ENDSTOP_PULLUP_Y2_MIN true
#define ENDSTOP_PULLUP_Z2_MINMAX true
#define ENDSTOP_PULLUP_X2_MAX true
#define ENDSTOP_PULLUP_Y2_MAX true
#define ENDSTOP_X2_MIN_INVERTING false
#define ENDSTOP_Y2_MIN_INVERTING false
#define ENDSTOP_X2_MAX_INVERTING false
#define ENDSTOP_Y2_MAX_INVERTING false
#define MIN_HARDWARE_ENDSTOP_X2 false
#define MIN_HARDWARE_ENDSTOP_Y2 false
#define MAX_HARDWARE_ENDSTOP_X2 false
#define MAX_HARDWARE_ENDSTOP_Y2 false
#define X2_MIN_PIN -1
#define X2_MAX_PIN -1
#define Y2_MIN_PIN -1
#define Y2_MAX_PIN -1
#define Z2_MINMAX_PIN -1



#define max_software_endstop_r true

#define min_software_endstop_x true
#define min_software_endstop_y true
#define min_software_endstop_z false
#define max_software_endstop_x false
#define max_software_endstop_y false
#define max_software_endstop_z false
#define DOOR_PIN -1
#define DOOR_PULLUP 1
#define DOOR_INVERTING 1
#define ENDSTOP_X_BACK_MOVE 5
#define ENDSTOP_Y_BACK_MOVE 5
#define ENDSTOP_Z_BACK_MOVE 5
#define ENDSTOP_X_RETEST_REDUCTION_FACTOR 3
#define ENDSTOP_Y_RETEST_REDUCTION_FACTOR 3
#define ENDSTOP_Z_RETEST_REDUCTION_FACTOR 3
#define ENDSTOP_X_BACK_ON_HOME 0
#define ENDSTOP_Y_BACK_ON_HOME 0
#define ENDSTOP_Z_BACK_ON_HOME 0
#define ALWAYS_CHECK_ENDSTOPS 0
#define MOVE_X_WHEN_HOMED 0
#define MOVE_Y_WHEN_HOMED 0
#define MOVE_Z_WHEN_HOMED 0

// ################# XYZ movements ###################

#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define DISABLE_X 0
#define DISABLE_Y 0
#define DISABLE_Z 0
#define DISABLE_E 0
#define INVERT_X_DIR 1
#define INVERT_X2_DIR 0
#define INVERT_Y_DIR 1
#define INVERT_Y2_DIR 0
#define INVERT_Z_DIR 1
#define INVERT_Z2_DIR 0
#define INVERT_Z3_DIR 0
#define INVERT_Z4_DIR 0
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR 1
#define X_MAX_LENGTH 200
#define Y_MAX_LENGTH 200
#define Z_MAX_LENGTH 220
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#define PARK_POSITION_X 0
#define PARK_POSITION_Y 10
#define PARK_POSITION_Z_RAISE 10


#define DISTORTION_CORRECTION 1
#define DISTORTION_CORRECTION_POINTS 5
#define DISTORTION_LIMIT_TO 2
#define DISTORTION_CORRECTION_R 60
#define DISTORTION_PERMANENT 1
#define DISTORTION_UPDATE_FREQUENCY 15
#define DISTORTION_START_DEGRADE 0.5
#define DISTORTION_END_HEIGHT 1
#define DISTORTION_EXTRAPOLATE_CORNERS 1
#define DISTORTION_XMIN 10
#define DISTORTION_YMIN 10
#define DISTORTION_XMAX 190
#define DISTORTION_YMAX 190

// ##########################################################################################
// ##                           Movement settings                                          ##
// ##########################################################################################

#define FEATURE_BABYSTEPPING 1
#define BABYSTEP_MULTIPLICATOR 1

#define DELTA_SEGMENTS_PER_SECOND_PRINT 100 // Move accurate setting for print moves
#define DELTA_SEGMENTS_PER_SECOND_MOVE 100 // Less accurate setting for other moves
#define EXACT_DELTA_MOVES 1

// Delta settings
#define DELTA_DIAGONAL_ROD 215 // mm
#define DELTA_ALPHA_A 210
#define DELTA_ALPHA_B 330
#define DELTA_ALPHA_C 90
#define DELTA_RADIUS_CORRECTION_A 0
#define DELTA_RADIUS_CORRECTION_B 0
#define DELTA_RADIUS_CORRECTION_C 0
#define DELTA_DIAGONAL_CORRECTION_A 0
#define DELTA_DIAGONAL_CORRECTION_B 0
#define DELTA_DIAGONAL_CORRECTION_C 0
#define END_EFFECTOR_HORIZONTAL_OFFSET 0
#define CARRIAGE_HORIZONTAL_OFFSET 0
#define DELTA_MAX_RADIUS 90
#define ROD_RADIUS 105
#define PRINTER_RADIUS 105
#define DELTA_HOME_ON_POWER 0
#define STEP_COUNTER
#define DELTA_X_ENDSTOP_OFFSET_STEPS 50
#define DELTA_Y_ENDSTOP_OFFSET_STEPS 50
#define DELTA_Z_ENDSTOP_OFFSET_STEPS 50
#define DELTA_FLOOR_SAFETY_MARGIN_MM 15
//#define SOFTWARE_LEVELING

#define DELTASEGMENTS_PER_PRINTLINE 12
#define STEPPER_INACTIVE_TIME 360L
#define MAX_INACTIVE_TIME 0L
#define MAX_FEEDRATE_X 200
#define MAX_FEEDRATE_Y 200
#define MAX_FEEDRATE_Z 200
#define HOMING_FEEDRATE_X 100
#define HOMING_FEEDRATE_Y 100
#define HOMING_FEEDRATE_Z 100
#define HOMING_ORDER HOME_ORDER_ZXY
#define ZHOME_PRE_RAISE 0
#define ZHOME_PRE_RAISE_DISTANCE 10
#define RAISE_Z_ON_TOOLCHANGE 0
#define ZHOME_MIN_TEMPERATURE 0
#define ZHOME_HEAT_ALL 1
#define ZHOME_HEAT_HEIGHT 0
#define ZHOME_X_POS 999999
#define ZHOME_Y_POS 999999
#define ENABLE_BACKLASH_COMPENSATION 0
#define X_BACKLASH 0
#define Y_BACKLASH 0
#define Z_BACKLASH 0
#define RAMP_ACCELERATION 1
#define STEPPER_HIGH_DELAY 0
#define DIRECTION_DELAY 0
#define STEP_DOUBLER_FREQUENCY 12000
#define ALLOW_QUADSTEPPING 1
#define DOUBLE_STEP_DELAY 0 // time in microseconds
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND_X 2000
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Y 2000
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Z 2000
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_X 3000
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Y 3000
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Z 3000
#define INTERPOLATE_ACCELERATION_WITH_Z 0
#define ACCELERATION_FACTOR_TOP 100
#define MAX_JERK 10
#define MAX_ZJERK 0.3
#define PRINTLINE_CACHE_SIZE 16
#define MOVE_CACHE_LOW 10
#define LOW_TICKS_PER_MOVE 250000
#define EXTRUDER_SWITCH_XY_SPEED 100
#define DUAL_X_AXIS 0
#define DUAL_X_RESOLUTION 0
#define X2AXIS_STEPS_PER_MM 100
#define FEATURE_TWO_XSTEPPER 0
#define X2_STEP_PIN   ORIG_E1_STEP_PIN
#define X2_DIR_PIN    ORIG_E1_DIR_PIN
#define X2_ENABLE_PIN ORIG_E1_ENABLE_PIN
#define FEATURE_TWO_YSTEPPER 0
#define Y2_STEP_PIN   ORIG_E1_STEP_PIN
#define Y2_DIR_PIN    ORIG_E1_DIR_PIN
#define Y2_ENABLE_PIN ORIG_E1_ENABLE_PIN
#define FEATURE_TWO_ZSTEPPER 0
#define Z2_STEP_PIN   ORIG_E1_STEP_PIN
#define Z2_DIR_PIN    ORIG_E1_DIR_PIN
#define Z2_ENABLE_PIN ORIG_E1_ENABLE_PIN
#define FEATURE_THREE_ZSTEPPER 0
#define Z3_STEP_PIN   ORIG_E2_STEP_PIN
#define Z3_DIR_PIN    ORIG_E2_DIR_PIN
#define Z3_ENABLE_PIN ORIG_E2_ENABLE_PIN
#define FEATURE_FOUR_ZSTEPPER 0
#define Z4_STEP_PIN   ORIG_E3_STEP_PIN
#define Z4_DIR_PIN    ORIG_E3_DIR_PIN
#define Z4_ENABLE_PIN ORIG_E3_ENABLE_PIN
#define FEATURE_DITTO_PRINTING 0
#define USE_ADVANCE 0
#define ENABLE_QUADRATIC_ADVANCE 0

#define DRV_TMC2130

// Uncomment if you use the stall guard for homing. Only for cartesian printers and xy direction

// The drivers with set CS pin will be used, all others are normal step/dir/enable drivers
#define TMC2130_X_CS_PIN 42
#define TMC2130_Y_CS_PIN 44
#define TMC2130_Z_CS_PIN 66
#define TMC2130_EXT0_CS_PIN 65
#define TMC2130_EXT1_CS_PIN -1
#define TMC2130_EXT2_CS_PIN -1

// Per-axis current setting in mA { X, Y, Z, E0, E1, E2}
#define MOTOR_CURRENT { 1000,1000,1000,1000,800,800 }

/**  Global settings - these apply to all configured drivers
Per-axis values will override these
*/
#define TMC2130_STEALTHCHOP         0  // Enable extremely quiet stepping
#define TMC2130_INTERPOLATE_256  1  // Enable internal driver microstep interpolation
#define TMC2130_STALLGUARD          0  // Sensorless homing sensitivity (between -63 and +64)

/** PWM values for chopper tuning
only change if you know what you're doing
*/
#define TMC2130_PWM_AMPL          255
#define TMC2130_PWM_GRAD            1
#define TMC2130_PWM_AUTOSCALE    1
#define TMC2130_PWM_FREQ            2

/**  Per-axis parameters

To define different values for certain parameters on each axis,
append either _X, _Y, _Z, _EXT0, _EXT1 or _EXT2
to the name of the global parameter.

Examples for the X axis:

#define TMC2130_STEALTHCHOP_X         1
#define TMC2130_INTERPOLATE_256_X  true
*/

/** Minimum speeds for stall detection.

These values may need to be adjusted if SENSORLESS_HOMING is enabled,
but endstops trigger prematurely or don't trigger at all.
The exact value is dependent on the duration of one microstep,
but good approximations can be determined by experimentation.
*/
#define TMC2130_TCOOLTHRS_X 300
#define TMC2130_TCOOLTHRS_Y 300
#define TMC2130_TCOOLTHRS_Z 300

// ################# Misc. settings ##################

#define BAUDRATE 250000
#define ENABLE_POWER_ON_STARTUP 1
#define POWER_INVERTING 0
#define AUTOMATIC_POWERUP 0
#define KILL_METHOD 1
#define ACK_WITH_LINENUMBER 1
#define KEEP_ALIVE_INTERVAL 2000
#define WAITING_IDENTIFIER "wait"
#define ECHO_ON_EXECUTE 1
#define EEPROM_MODE 1
#undef PS_ON_PIN
#define PS_ON_PIN ORIG_PS_ON_PIN
#define JSON_OUTPUT 0

/* ======== Servos =======
Control the servos with
M340 P<servoId> S<pulseInUS>   / ServoID = 0..3  pulseInUs = 500..2500
Servos are controlled by a pulse width normally between 500 and 2500 with 1500ms in center position. 0 turns servo off.
WARNING: Servos can draw a considerable amount of current. Make sure your system can handle this or you may risk your hardware!
*/
#define FEATURE_SERVO 0
#define SERVO0_PIN 11
#define SERVO1_PIN -1
#define SERVO2_PIN -1
#define SERVO3_PIN -1
#define SERVO0_NEUTRAL_POS  -1
#define SERVO1_NEUTRAL_POS  -1
#define SERVO2_NEUTRAL_POS  -1
#define SERVO3_NEUTRAL_POS  -1
#define UI_SERVO_CONTROL 0
#define FAN_KICKSTART_TIME  200
#define MAX_FAN_PWM 255

        #define FEATURE_WATCHDOG 0

// #################### Z-Probing #####################

#define Z_PROBE_Z_OFFSET 0
#define Z_PROBE_Z_OFFSET_MODE 0
#define UI_BED_COATING 1
#define FEATURE_Z_PROBE 1
#define EXTRUDER_IS_Z_PROBE 0
#define Z_PROBE_DISABLE_HEATERS 0
#define Z_PROBE_BED_DISTANCE 2
#define Z_PROBE_PIN ORIG_Z_MIN_PIN
#define Z_PROBE_PULLUP 0
#define Z_PROBE_ON_HIGH 0
#define Z_PROBE_X_OFFSET 20
#define Z_PROBE_Y_OFFSET 0
#define Z_PROBE_WAIT_BEFORE_TEST 0
#define Z_PROBE_SPEED 10
#define Z_PROBE_XY_SPEED 100
#define Z_PROBE_SWITCHING_DISTANCE 1
#define Z_PROBE_REPETITIONS 3
#define Z_PROBE_USE_MEDIAN 0
#define Z_PROBE_HEIGHT 0
#define Z_PROBE_DELAY 0
#define Z_PROBE_START_SCRIPT ""
#define Z_PROBE_FINISHED_SCRIPT ""
#define Z_PROBE_RUN_AFTER_EVERY_PROBE ""
#define Z_PROBE_REQUIRES_HEATING 0
#define Z_PROBE_MIN_TEMPERATURE 150
#define FEATURE_AUTOLEVEL 1
#define FEATURE_SOFTWARE_LEVELING 0
#define Z_PROBE_X1 -51.96
#define Z_PROBE_Y1 -30
#define Z_PROBE_X2 51.96
#define Z_PROBE_Y2 -30
#define Z_PROBE_X3 0
#define Z_PROBE_Y3 60
#define BED_LEVELING_METHOD 0
#define BED_CORRECTION_METHOD 0
#define BED_LEVELING_GRID_SIZE 5
#define BED_LEVELING_REPETITIONS 5
#define BED_MOTOR_1_X 0
#define BED_MOTOR_1_Y 0
#define BED_MOTOR_2_X 200
#define BED_MOTOR_2_Y 0
#define BED_MOTOR_3_X 100
#define BED_MOTOR_3_Y 200
#define BENDING_CORRECTION_A 0
#define BENDING_CORRECTION_B 0
#define BENDING_CORRECTION_C 0
#define FEATURE_AXISCOMP 0
#define AXISCOMP_TANXY 0
#define AXISCOMP_TANYZ 0
#define AXISCOMP_TANXZ 0

#ifndef SDSUPPORT  // Some boards have sd support on board. These define the values already in pins.h
#define SDSUPPORT 1
#undef SDCARDDETECT
#define SDCARDDETECT ORIG_SDCARDDETECT
#undef SDCARDDETECTINVERTED
#define SDCARDDETECTINVERTED 0
#endif
#define SD_EXTENDED_DIR 1 /** Show extended directory including file length. Don't use this with Pronterface! */
#define SD_RUN_ON_STOP ""
#define SD_STOP_HEATER_AND_MOTORS_ON_STOP 1
#define ARC_SUPPORT 1
#define FEATURE_MEMORY_POSITION 1
#define FEATURE_CHECKSUM_FORCED 0
#define FEATURE_FAN_CONTROL 1
#define FEATURE_FAN2_CONTROL 0
#define FEATURE_CONTROLLER 2
#define ADC_KEYPAD_PIN -1
#define LANGUAGE_EN_ACTIVE 1
#define LANGUAGE_DE_ACTIVE 0
#define LANGUAGE_NL_ACTIVE 0
#define LANGUAGE_PT_ACTIVE 0
#define LANGUAGE_IT_ACTIVE 0
#define LANGUAGE_ES_ACTIVE 0
#define LANGUAGE_FI_ACTIVE 0
#define LANGUAGE_SE_ACTIVE 0
#define LANGUAGE_FR_ACTIVE 0
#define LANGUAGE_CZ_ACTIVE 0
#define LANGUAGE_PL_ACTIVE 0
#define LANGUAGE_TR_ACTIVE 0
#define UI_PRINTER_NAME "DeltiQ_M"
#define UI_PRINTER_COMPANY "TRILAB"
#define UI_PAGES_DURATION 4000
#define UI_SPEEDDEPENDENT_POSITIONING 0
#define UI_DISABLE_AUTO_PAGESWITCH 1
#define UI_AUTORETURN_TO_MENU_AFTER 30000
#define FEATURE_UI_KEYS 0
#define UI_ENCODER_SPEED 2
#define UI_REVERSE_ENCODER 1
#define UI_KEY_BOUNCETIME 10
#define UI_KEY_FIRST_REPEAT 500
#define UI_KEY_REDUCE_REPEAT 50
#define UI_KEY_MIN_REPEAT 50
#define FEATURE_BEEPER 0
#define CASE_LIGHTS_PIN -1
#define CASE_LIGHT_DEFAULT_ON 1
#define UI_START_SCREEN_DELAY 1000
#define UI_DYNAMIC_ENCODER_SPEED 1
        /**
Beeper sound definitions for short beeps during key actions
and longer beeps for important actions.
Parameter is delay in microseconds and the secons is the number of repetitions.
Values must be in range 1..255
*/
#define BEEPER_SHORT_SEQUENCE 2,2
#define BEEPER_LONG_SEQUENCE 8,8
#define UI_SET_MIN_HEATED_BED_TEMP  30
#define UI_SET_MAX_HEATED_BED_TEMP 105
#define UI_SET_MIN_EXTRUDER_TEMP   90
#define UI_SET_MAX_EXTRUDER_TEMP   290
#define UI_SET_EXTRUDER_FEEDRATE 2
#define UI_SET_EXTRUDER_RETRACT_DISTANCE 3


#define NUM_MOTOR_DRIVERS 0

#define USER_QUICK_MENU_Z_PROBE_HEIGHT_USER_CHANGE
#define UI_Z_PROBE_HEIGHT_USER_CHANGE 1
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_1 "T0\n G28\n G92 E0\n G91\n M104 S210\n M116\n M117 Loading Filament\n G1 E300 F1000\n G1 E100 F500\n G1 E100 F100\n G90\n G92 E0\n M84"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_1_TEXT "Load Filament-Bowden Extr"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_2 "T0\nG28\n G92 E0\n G91\n M104 S210\n M116\n M117 Unloading Filament\n G1 E20 F200\n G1 E-100 F6000\n G90\n G92 E0\n M84"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_2_TEXT "Unload Filament-Bowden Extr"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_3 "T0\n G28\n G92 E0\n G91\n M104 S210\n M116\n M117 Purging Filament\n G1 E50 F100\n G90\n G92 E0\n M84"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_3_TEXT "Purge Filament-Bowden Extr"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_4 "T1\n G28\n G92 E0\n G91\n M104 S210\n M116\n M117 Purging Filament\n G1 E50 F50\n G90\n G92 E0\n M84"
#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_4_TEXT "Purge Filament-Direct Extr"

#define SERVICE_MENU
#define UI_TEXT_SERVICE_MENU_TEXT "Service menu"
#define UI_SERVICE_MENU_ITEM1 "G28\n M190 S55\n M322\n G33 R0\n G32 S2\n M322\n G33 R0\n G28"
#define SERVICE_MENU_ITEM1_TEXT "Z home calib"
#define UI_SERVICE_MENU_ITEM2 "G28\n M303 S205 C10 X10"
#define SERVICE_MENU_ITEM2_TEXT "PID tuning"
#define UI_SERVICE_MENU_ITEM3 "G28"
#define SERVICE_MENU_ITEM3_TEXT "Home"

// Filament change
#define FILAMENT_LOAD_UNLOAD_PURGE_TEMP 200

#define FILAMENT_LOAD_BOWDEN_LENGTH_FAST 400.0
#define FILAMENT_LOAD_BOWDEN_FEED_FAST 16.0
#define FILAMENT_LOAD_BOWDEN_LENGTH_SLOW 100.0
#define FILAMENT_LOAD_BOWDEN_FEED_SLOW 8.0
#define FILAMENT_UNLOAD_BOWDEN_LENGTH_PURGE 20.0
#define FILAMENT_UNLOAD_BOWDEN_FEED_PURGE 3.0
#define FILAMENT_UNLOAD_BOWDEN_LENGTH_RETRACT 100.0
#define FILAMENT_UNLOAD_BOWDEN_FEED_RETRACT 100.0
#define FILAMENT_PURGE_BOWDEN_LENGTH 20.0
#define FILAMENT_PURGE_BOWDEN_FEED 2.0

#define FILAMENT_LOAD_DIRECT_LENGTH 50.0
#define FILAMENT_LOAD_DIRECT_FEED 2.0
#define FILAMENT_UNLOAD_DIRECT_LENGTH_PURGE 20.0
#define FILAMENT_UNLOAD_DIRECT_FEED_PURGE 2.0
#define FILAMENT_UNLOAD_DIRECT_LENGTH_RETRACT 50.0
#define FILAMENT_UNLOAD_DIRECT_FEED_RETRACT 2.0
#define FILAMENT_PURGE_DIRECT_LENGTH 50.0
#define FILAMENT_PURGE_DIRECT_FEED 2.0

#endif

/* Below you will find the configuration string, that created this Configuration.h

========== Start configuration string ==========
{
    "editMode": 2,
    "processor": 0,
    "baudrate": 250000,
    "bluetoothSerial": -1,
    "bluetoothBaudrate": 115200,
    "xStepsPerMM": 100,
    "yStepsPerMM": 100,
    "zStepsPerMM": 100,
    "xInvert": "1",
    "x2Invert": 0,
    "xInvertEnable": 0,
    "eepromMode": 1,
    "yInvert": "1",
    "y2Invert": 0,
    "yInvertEnable": 0,
    "zInvert": "1",
    "z2Invert": 0,
    "z3Invert": 0,
    "z4Invert": 0,
    "zInvertEnable": 0,
    "extruder": [
        {
            "id": 0,
            "heatManager": 1,
            "pidDriveMin": 40,
            "pidDriveMax": 230,
            "pidMax": 230,
            "sensorType": 8,
            "sensorPin": "TEMP_0_PIN",
            "heaterPin": "HEATER_0_PIN",
            "maxFeedrate": 60,
            "startFeedrate": 20,
            "invert": "1",
            "invertEnable": "0",
            "acceleration": 9000,
            "watchPeriod": 1,
            "pidP": 7,
            "pidI": 1,
            "pidD": 32,
            "advanceK": 0,
            "advanceL": 0,
            "waitRetractTemp": 150,
            "waitRetractUnits": 0,
            "waitRetract": 0,
            "stepsPerMM": 400,
            "coolerPin": "HEATER_3_PIN",
            "coolerSpeed": 255,
            "selectCommands": "",
            "deselectCommands": "",
            "xOffset": 0,
            "yOffset": 0,
            "zOffset": 0,
            "xOffsetSteps": 0,
            "yOffsetSteps": 0,
            "zOffsetSteps": 0,
            "stepper": {
                "name": "Extruder 0",
                "step": "ORIG_E0_STEP_PIN",
                "dir": "ORIG_E0_DIR_PIN",
                "enable": "ORIG_E0_ENABLE_PIN"
            },
            "advanceBacklashSteps": 0,
            "decoupleTestPeriod": 20,
            "jamPin": "ORIG_X_MIN_PIN",
            "jamPullup": "1",
            "mirror": "0",
            "invert2": "0",
            "stepper2": {
                "name": "Extruder 0",
                "step": "ORIG_E0_STEP_PIN",
                "dir": "ORIG_E0_DIR_PIN",
                "enable": "ORIG_E0_ENABLE_PIN"
            },
            "preheat": 200
        },
        {
            "id": 1,
            "heatManager": 1,
            "pidDriveMin": 40,
            "pidDriveMax": 230,
            "pidMax": 230,
            "sensorType": 8,
            "sensorPin": "TEMP_0_PIN",
            "heaterPin": "HEATER_0_PIN",
            "maxFeedrate": 50,
            "startFeedrate": 0.6,
            "invert": "0",
            "invertEnable": "0",
            "acceleration": 120,
            "watchPeriod": 1,
            "pidP": 7,
            "pidI": 1,
            "pidD": 32,
            "advanceK": 0,
            "advanceL": 0,
            "waitRetractTemp": 150,
            "waitRetractUnits": 0,
            "waitRetract": 0,
            "stepsPerMM": 600,
            "coolerPin": "HEATER_3_PIN",
            "coolerSpeed": 255,
            "selectCommands": "",
            "deselectCommands": "",
            "xOffset": 0,
            "yOffset": 0,
            "zOffset": 0,
            "xOffsetSteps": 0,
            "yOffsetSteps": 0,
            "zOffsetSteps": 0,
            "stepper": {
                "name": "Extruder 1",
                "step": "ORIG_E1_STEP_PIN",
                "dir": "ORIG_E1_DIR_PIN",
                "enable": "ORIG_E1_ENABLE_PIN"
            },
            "advanceBacklashSteps": 0,
            "decoupleTestPeriod": 20,
            "jamPin": -1,
            "jamPullup": "0",
            "mirror": "0",
            "invert2": "0",
            "stepper2": {
                "name": "Extruder 1",
                "step": "ORIG_E1_STEP_PIN",
                "dir": "ORIG_E1_DIR_PIN",
                "enable": "ORIG_E1_ENABLE_PIN"
            },
            "preheat": 200
        }
    ],
    "uiLanguage": 0,
    "uiController": 0,
    "xMinEndstop": 0,
    "yMinEndstop": 0,
    "zMinEndstop": 1,
    "xMaxEndstop": 2,
    "yMaxEndstop": 2,
    "zMaxEndstop": 2,
    "x2MinEndstop": 0,
    "y2MinEndstop": 0,
    "x2MaxEndstop": 0,
    "y2MaxEndstop": 0,
    "motherboard": 33,
    "driveSystem": 3,
    "xMaxSpeed": 200,
    "xHomingSpeed": 100,
    "xTravelAcceleration": 3000,
    "xPrintAcceleration": 2000,
    "yMaxSpeed": 200,
    "yHomingSpeed": 100,
    "yTravelAcceleration": 3000,
    "yPrintAcceleration": 2000,
    "zMaxSpeed": 200,
    "zHomingSpeed": 100,
    "zTravelAcceleration": 3000,
    "zPrintAcceleration": 2000,
    "xMotor": {
        "name": "X motor",
        "step": "ORIG_X_STEP_PIN",
        "dir": "ORIG_X_DIR_PIN",
        "enable": "ORIG_X_ENABLE_PIN"
    },
    "yMotor": {
        "name": "Y motor",
        "step": "ORIG_Y_STEP_PIN",
        "dir": "ORIG_Y_DIR_PIN",
        "enable": "ORIG_Y_ENABLE_PIN"
    },
    "zMotor": {
        "name": "Z motor",
        "step": "ORIG_Z_STEP_PIN",
        "dir": "ORIG_Z_DIR_PIN",
        "enable": "ORIG_Z_ENABLE_PIN"
    },
    "enableBacklash": "0",
    "backlashX": 0,
    "backlashY": 0,
    "backlashZ": 0,
    "stepperInactiveTime": 360,
    "maxInactiveTime": 0,
    "xMinPos": 0,
    "yMinPos": 0,
    "zMinPos": 0,
    "xLength": 200,
    "yLength": 200,
    "zLength": 220,
    "alwaysCheckEndstops": "0",
    "disableX": "0",
    "disableY": "0",
    "disableZ": "0",
    "disableE": "0",
    "xHomeDir": "-1",
    "yHomeDir": "-1",
    "zHomeDir": 1,
    "xEndstopBack": 0,
    "yEndstopBack": 0,
    "zEndstopBack": 0,
    "deltaSegmentsPerSecondPrint": 100,
    "deltaSegmentsPerSecondTravel": 100,
    "deltaDiagonalRod": 215,
    "deltaHorizontalRadius": 105,
    "deltaAlphaA": 210,
    "deltaAlphaB": 330,
    "deltaAlphaC": 90,
    "deltaDiagonalCorrA": 0,
    "deltaDiagonalCorrB": 0,
    "deltaDiagonalCorrC": 0,
    "deltaMaxRadius": 90,
    "deltaFloorSafetyMarginMM": 15,
    "deltaRadiusCorrA": 0,
    "deltaRadiusCorrB": 0,
    "deltaRadiusCorrC": 0,
    "deltaXOffsetSteps": 0,
    "deltaYOffsetSteps": 0,
    "deltaZOffsetSteps": 0,
    "deltaSegmentsPerLine": 16,
    "stepperHighDelay": 0,
    "directionDelay": 0,
    "stepDoublerFrequency": 12000,
    "allowQuadstepping": "1",
    "doubleStepDelay": 0,
    "maxJerk": 10,
    "maxZJerk": 0.3,
    "moveCacheSize": 16,
    "moveCacheLow": 10,
    "lowTicksPerMove": 250000,
    "enablePowerOnStartup": "1",
    "echoOnExecute": "1",
    "sendWaits": "1",
    "ackWithLineNumber": "1",
    "killMethod": 1,
    "useAdvance": "0",
    "useQuadraticAdvance": "0",
    "powerInverting": 0,
    "mirrorX": 0,
    "mirrorXMotor": {
        "name": "Extruder 1",
        "step": "ORIG_E1_STEP_PIN",
        "dir": "ORIG_E1_DIR_PIN",
        "enable": "ORIG_E1_ENABLE_PIN"
    },
    "mirrorY": 0,
    "mirrorYMotor": {
        "name": "Extruder 1",
        "step": "ORIG_E1_STEP_PIN",
        "dir": "ORIG_E1_DIR_PIN",
        "enable": "ORIG_E1_ENABLE_PIN"
    },
    "mirrorZ": "0",
    "mirrorZMotor": {
        "name": "Extruder 1",
        "step": "ORIG_E1_STEP_PIN",
        "dir": "ORIG_E1_DIR_PIN",
        "enable": "ORIG_E1_ENABLE_PIN"
    },
    "mirrorZ3": "0",
    "mirrorZ3Motor": {
        "name": "Extruder 2",
        "step": "ORIG_E2_STEP_PIN",
        "dir": "ORIG_E2_DIR_PIN",
        "enable": "ORIG_E2_ENABLE_PIN"
    },
    "mirrorZ4": "0",
    "mirrorZ4Motor": {
        "name": "Extruder 3",
        "step": "ORIG_E3_STEP_PIN",
        "dir": "ORIG_E3_DIR_PIN",
        "enable": "ORIG_E3_ENABLE_PIN"
    },
    "dittoPrinting": "0",
    "featureServos": "0",
    "servo0Pin": 11,
    "servo1Pin": -1,
    "servo2Pin": -1,
    "servo3Pin": -1,
    "featureWatchdog": "0",
    "hasHeatedBed": "1",
    "enableZProbing": "1",
    "extrudeMaxLength": 1000,
    "homeOrder": "HOME_ORDER_ZXY",
    "featureController": 2,
    "uiPrinterName": "DeltiQ_M",
    "uiPrinterCompany": "TRILAB",
    "uiPagesDuration": 4000,
    "uiHeadline": "",
    "uiDisablePageswitch": "1",
    "uiAutoReturnAfter": 30000,
    "featureKeys": "0",
    "uiEncoderSpeed": 2,
    "uiReverseEncoder": "1",
    "uiKeyBouncetime": 10,
    "uiKeyFirstRepeat": 500,
    "uiKeyReduceRepeat": 50,
    "uiKeyMinRepeat": 50,
    "featureBeeper": "0",
    "uiMinHeatedBed": 30,
    "uiMaxHeatedBed": 105,
    "uiMinEtxruderTemp": 90,
    "uiMaxExtruderTemp": 290,
    "uiExtruderFeedrate": 2,
    "uiExtruderRetractDistance": 3,
    "uiSpeeddependentPositioning": "0",
    "maxBedTemperature": 105,
    "bedSensorType": 14,
    "bedSensorPin": "TEMP_1_PIN",
    "bedHeaterPin": "HEATER_1_PIN",
    "bedHeatManager": 1,
    "bedPreheat": 55,
    "bedUpdateInterval": 5000,
    "bedPidDriveMin": 0,
    "bedPidDriveMax": 120,
    "bedPidP": 80,
    "bedPidI": 30,
    "bedPidD": 70,
    "bedPidMax": 120,
    "bedDecoupleTestPeriod": 300,
    "caseLightPin": -1,
    "caseLightDefaultOn": "1",
    "bedSkipIfWithin": 3,
    "gen1T0": 25,
    "gen1R0": 100000,
    "gen1Beta": 4036,
    "gen1MinTemp": -20,
    "gen1MaxTemp": 300,
    "gen1R1": 0,
    "gen1R2": 4700,
    "gen2T0": 25,
    "gen2R0": 100000,
    "gen2Beta": 4036,
    "gen2MinTemp": -20,
    "gen2MaxTemp": 300,
    "gen2R1": 0,
    "gen2R2": 4700,
    "gen3T0": 25,
    "gen3R0": 100000,
    "gen3Beta": 4036,
    "gen3MinTemp": -20,
    "gen3MaxTemp": 300,
    "gen3R1": 0,
    "gen3R2": 4700,
    "userTable0": {
        "r1": 0,
        "r2": 4700,
        "temps": [],
        "numEntries": 0
    },
    "userTable1": {
        "r1": 0,
        "r2": 4700,
        "temps": [],
        "numEntries": 0
    },
    "userTable2": {
        "r1": 0,
        "r2": 4700,
        "temps": [],
        "numEntries": 0
    },
    "tempHysteresis": 4,
    "pidControlRange": 10,
    "skipM109Within": 1,
    "extruderFanCoolTemp": 50,
    "minTemp": 90,
    "maxTemp": 290,
    "minDefectTemp": 5,
    "maxDefectTemp": 295,
    "arcSupport": "1",
    "featureMemoryPositionWatchdog": "1",
    "forceChecksum": "0",
    "sdExtendedDir": "1",
    "featureFanControl": "1",
    "fanPin": "ORIG_FAN_PIN",
    "featureFan2Control": "0",
    "fan2Pin": "ORIG_FAN2_PIN",
    "fanThermoPin": -1,
    "fanThermoMinPWM": 128,
    "fanThermoMaxPWM": 255,
    "fanThermoMinTemp": 45,
    "fanThermoMaxTemp": 60,
    "fanThermoThermistorPin": -1,
    "fanThermoThermistorType": 1,
    "scalePidToMax": 0,
    "zProbePin": "ORIG_Z_MIN_PIN",
    "zProbeBedDistance": 2,
    "zProbeDisableHeaters": "0",
    "zProbePullup": "0",
    "zProbeOnHigh": "0",
    "zProbeXOffset": 20,
    "zProbeYOffset": 0,
    "zProbeWaitBeforeTest": "0",
    "zProbeSpeed": 10,
    "zProbeXYSpeed": 100,
    "zProbeHeight": 0,
    "zProbeStartScript": "",
    "zProbeFinishedScript": "",
    "featureAutolevel": "1",
    "zProbeX1": -51.96,
    "zProbeY1": -30,
    "zProbeX2": 51.96,
    "zProbeY2": -30,
    "zProbeX3": 0,
    "zProbeY3": 60,
    "zProbeSwitchingDistance": 1,
    "zProbeRepetitions": 3,
    "zProbeMedian": "0",
    "zProbeEveryPoint": "",
    "sdSupport": "1",
    "sdCardDetectPin": "ORIG_SDCARDDETECT",
    "sdCardDetectInverted": "0",
    "uiStartScreenDelay": 1000,
    "xEndstopBackMove": 5,
    "yEndstopBackMove": 5,
    "zEndstopBackMove": 5,
    "xEndstopRetestFactor": 3,
    "yEndstopRetestFactor": 3,
    "zEndstopRetestFactor": 3,
    "xMinPin": "ORIG_X_MIN_PIN",
    "yMinPin": "ORIG_Y_MIN_PIN",
    "zMinPin": "ORIG_Z_MIN_PIN",
    "xMaxPin": "ORIG_X_MAX_PIN",
    "yMaxPin": "ORIG_Y_MAX_PIN",
    "zMaxPin": "ORIG_Z_MAX_PIN",
    "x2MinPin": -1,
    "y2MinPin": -1,
    "x2MaxPin": -1,
    "y2MaxPin": -1,
    "deltaHomeOnPower": "0",
    "fanBoardPin": -1,
    "heaterPWMSpeed": 0,
    "featureBabystepping": "1",
    "babystepMultiplicator": 1,
    "pdmForHeater": "0",
    "pdmForCooler": "0",
    "psOn": "ORIG_PS_ON_PIN",
    "mixingExtruder": "0",
    "decouplingTestMaxHoldVariance": 30,
    "decouplingTestMinTempRise": 0.5,
    "featureAxisComp": "0",
    "axisCompTanXY": 0,
    "axisCompTanXZ": 0,
    "axisCompTanYZ": 0,
    "retractOnPause": 2,
    "pauseStartCommands": "G91\\n G1 Z10\\n G90\\n",
    "pauseEndCommands": "G91\\n G1 Z-10\\n G90\\n",
    "distortionCorrection": "1",
    "distortionCorrectionPoints": 5,
    "distortionCorrectionR": 60,
    "distortionPermanent": "1",
    "distortionUpdateFrequency": 15,
    "distortionStartDegrade": 0.5,
    "distortionEndDegrade": 1,
    "distortionExtrapolateCorners": "1",
    "distortionXMin": 10,
    "distortionXMax": 190,
    "distortionYMin": 10,
    "distortionYMax": 190,
    "sdRunOnStop": "",
    "sdStopHeaterMotorsOnStop": "1",
    "featureRetraction": "1",
    "autoretractEnabled": "0",
    "retractionLength": 0,
    "retractionLongLength": 0,
    "retractionSpeed": 30,
    "retractionZLift": 0,
    "retractionUndoExtraLength": 0,
    "retractionUndoExtraLongLength": 0,
    "retractionUndoSpeed": 20,
    "filamentChangeXPos": 0,
    "filamentChangeYPos": 0,
    "filamentChangeZAdd": 50,
    "filamentChangeRehome": 0,
    "filamentChangeShortRetract": 3,
    "filamentChangeLongRetract": 100,
    "fanKickstart": 200,
    "servo0StartPos": -1,
    "servo1StartPos": -1,
    "servo2StartPos": -1,
    "servo3StartPos": -1,
    "uiDynamicEncoderSpeed": "1",
    "uiServoControl": 0,
    "killIfSensorDefect": "0",
    "jamSteps": 220,
    "jamSlowdownSteps": 320,
    "jamSlowdownTo": 70,
    "jamErrorSteps": 500,
    "jamMinSteps": 10,
    "jamAction": 1,
    "jamMethod": 2,
    "primaryPort": 0,
    "numMotorDrivers": 0,
    "motorDrivers": [
        {
            "t": "None",
            "s": "",
            "invertEnable": "0",
            "invertDirection": "0",
            "stepsPerMM": 100,
            "speed": 10,
            "dirPin": -1,
            "stepPin": -1,
            "enablePin": -1,
            "endstopPin": -1,
            "invertEndstop": "0",
            "minEndstop": "1",
            "endstopPullup": "1",
            "maxDistance": 20
        },
        {
            "t": "None",
            "s": "",
            "invertEnable": "0",
            "invertDirection": "0",
            "stepsPerMM": 100,
            "speed": 10,
            "dirPin": -1,
            "stepPin": -1,
            "enablePin": -1,
            "endstopPin": -1,
            "invertEndstop": "0",
            "minEndstop": "1",
            "endstopPullup": "1",
            "maxDistance": 20
        },
        {
            "t": "None",
            "s": "",
            "invertEnable": "0",
            "invertDirection": "0",
            "stepsPerMM": 100,
            "speed": 10,
            "dirPin": -1,
            "stepPin": -1,
            "enablePin": -1,
            "endstopPin": -1,
            "invertEndstop": "0",
            "minEndstop": "1",
            "endstopPullup": "1",
            "maxDistance": 20
        },
        {
            "t": "None",
            "s": "",
            "invertEnable": "0",
            "invertDirection": "0",
            "stepsPerMM": 100,
            "speed": 10,
            "dirPin": -1,
            "stepPin": -1,
            "enablePin": -1,
            "endstopPin": -1,
            "invertEndstop": "0",
            "minEndstop": "1",
            "endstopPullup": "1",
            "maxDistance": 20
        },
        {
            "t": "None",
            "s": "",
            "invertEnable": "0",
            "invertDirection": "0",
            "stepsPerMM": 100,
            "speed": 10,
            "dirPin": -1,
            "stepPin": -1,
            "enablePin": -1,
            "endstopPin": -1,
            "invertEndstop": "0",
            "minEndstop": "1",
            "endstopPullup": "1",
            "maxDistance": 20
        },
        {
            "t": "None",
            "s": "",
            "invertEnable": "0",
            "invertDirection": "0",
            "stepsPerMM": 100,
            "speed": 10,
            "dirPin": -1,
            "stepPin": -1,
            "enablePin": -1,
            "endstopPin": -1,
            "invertEndstop": "0",
            "minEndstop": "1",
            "endstopPullup": "1",
            "maxDistance": 20
        }
    ],
    "manualConfig": "#define USER_QUICK_MENU_Z_PROBE_HEIGHT_USER_CHANGE\n#define UI_Z_PROBE_HEIGHT_USER_CHANGE 1\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_1 \"T0\\n G28\\n G92 E0\\n G91\\n M104 S210\\n M116\\n M117 Loading Filament\\n G1 E300 F1000\\n G1 E100 F500\\n G1 E100 F100\\n G90\\n G92 E0\\n M84\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_1_TEXT \"Load Filament-Bowden Extr\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_2 \"T0\\nG28\\n G92 E0\\n G91\\n M104 S210\\n M116\\n M117 Unloading Filament\\n G1 E20 F200\\n G1 E-100 F6000\\n G90\\n G92 E0\\n M84\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_2_TEXT \"Unload Filament-Bowden Extr\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_3 \"T0\\n G28\\n G92 E0\\n G91\\n M104 S210\\n M116\\n M117 Purging Filament\\n G1 E50 F100\\n G90\\n G92 E0\\n M84\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_3_TEXT \"Purge Filament-Bowden Extr\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_4 \"T1\\n G28\\n G92 E0\\n G91\\n M104 S210\\n M116\\n M117 Purging Filament\\n G1 E50 F50\\n G90\\n G92 E0\\n M84\"\n#define USER_QUICK_MENU_ITEM_CUSTOM_SCRIPT_4_TEXT \"Purge Filament-Direct Extr\"\n\n#define SERVICE_MENU\n#define UI_TEXT_SERVICE_MENU_TEXT \"Service menu\"\n#define UI_SERVICE_MENU_ITEM1 \"G28\\n M190 S55\\n M322\\n G33 R0\\n G32 S2\\n M322\\n G33 R0\\n G28\"\n#define SERVICE_MENU_ITEM1_TEXT \"Z home calib\"\n#define UI_SERVICE_MENU_ITEM2 \"G28\\n M303 S205 C10 X10\"\n#define SERVICE_MENU_ITEM2_TEXT \"PID tuning\"\n#define UI_SERVICE_MENU_ITEM3 \"G28\"\n#define SERVICE_MENU_ITEM3_TEXT \"Home\"",
    "zHomeMinTemperature": 0,
    "zHomeXPos": 999999,
    "zHomeYPos": 999999,
    "zHomeHeatHeight": 20,
    "zHomeHeatAll": "1",
    "zProbeZOffsetMode": 0,
    "zProbeZOffset": 0,
    "zProbeDelay": 0,
    "uiBedCoating": "1",
    "langEN": "1",
    "langDE": "0",
    "langNL": "0",
    "langPT": "0",
    "langIT": "0",
    "langES": "0",
    "langFI": "0",
    "langSE": "0",
    "langFR": "0",
    "langCZ": "0",
    "langPL": "0",
    "langTR": "0",
    "interpolateAccelerationWithZ": 0,
    "accelerationFactorTop": 100,
    "bendingCorrectionA": 0,
    "bendingCorrectionB": 0,
    "bendingCorrectionC": 0,
    "preventZDisableOnStepperTimeout": "0",
    "supportLaser": "0",
    "laserPin": -1,
    "laserOnHigh": "1",
    "laserWarmupTime": 0,
    "defaultPrinterMode": 0,
    "laserPwmMax": 255,
    "laserWatt": 2,
    "supportCNC": "0",
    "cncWaitOnEnable": 300,
    "cncWaitOnDisable": 0,
    "cncEnablePin": -1,
    "cncEnableWith": "1",
    "cncDirectionPin": -1,
    "cncDirectionCW": "1",
    "cncPwmMax": 255,
    "cncRpmMax": 8000,
    "cncSafeZ": 150,
    "startupGCode": "",
    "jsonOutput": "0",
    "bedLevelingMethod": 0,
    "bedCorrectionMethod": 0,
    "bedLevelingGridSize": 5,
    "bedLevelingRepetitions": 5,
    "bedMotor1X": 0,
    "bedMotor1Y": 0,
    "bedMotor2X": 200,
    "bedMotor2Y": 0,
    "bedMotor3X": 100,
    "bedMotor3Y": 200,
    "zProbeRequiresHeating": "0",
    "zProbeMinTemperature": 150,
    "adcKeypadPin": -1,
    "sharedExtruderHeater": "1",
    "extruderSwitchXYSpeed": 100,
    "dualXAxis": "0",
    "boardFanSpeed": 255,
    "keepAliveInterval": 2000,
    "moveXWhenHomed": "0",
    "moveYWhenHomed": "0",
    "moveZWhenHomed": "0",
    "preheatTime": 30000,
    "multiZEndstopHoming": "0",
    "z2MinMaxPin": -1,
    "z2MinMaxEndstop": 0,
    "extruderIsZProbe": "0",
    "boardFanMinSpeed": 0,
    "doorPin": -1,
    "doorEndstop": 1,
    "zhomePreRaise": 0,
    "zhomePreRaiseDistance": 10,
    "dualXResolution": "0",
    "x2axisStepsPerMM": 100,
    "coolerPWMSpeed": 0,
    "maxFanPWM": 255,
    "raiseZOnToolchange": 0,
    "distortionLimitTo": 2,
    "automaticPowerup": 0,
    "hasTMC2130": "1",
    "TMC2130Sensorless": "0",
    "TMC2130Steathchop": "0",
    "TMC2130Interpolate256": "1",
    "TMC2130StallguardSensitivity": 0,
    "TMC2130PWMAmpl": 255,
    "TMC2130PWMGrad": 1,
    "TMC2130PWMAutoscale": "1",
    "TMC2130PWMFreq": 2,
    "TMC2130CSX": 42,
    "TMC2130CSY": 44,
    "TMC2130CSZ": 66,
    "TMC2130CSE0": 65,
    "TMC2130CSE1": -1,
    "TMC2130CSE2": -1,
    "TMC2130CurrentX": 1000,
    "TMC2130CurrentY": 1000,
    "TMC2130CurrentZ": 1000,
    "TMC2130CurrentE0": 1000,
    "TMC2130CurrentE1": 800,
    "TMC2130CurrentE2": 800,
    "TMC2130CoolstepTresholdX": 300,
    "TMC2130CoolstepTresholdY": 300,
    "TMC2130CoolstepTresholdZ": 300,
    "microstepX": 16,
    "microstepY": 16,
    "microstepZ": 16,
    "microstepE0": 16,
    "microstepE1": 16,
    "microstepE2": 16,
    "parkPosX": 0,
    "parkPosY": 0,
    "parkPosZ": 10,
    "uiAnimation": "0",
    "uiPresetBedTempPLA": 55,
    "uiPresetBedABS": 100,
    "uiPresetExtruderPLA": 210,
    "uiPresetExtruderABS": 230,
    "hasMAX6675": false,
    "hasMAX31855": false,
    "hasGeneric1": false,
    "hasGeneric2": false,
    "hasGeneric3": false,
    "hasUser0": false,
    "hasUser1": false,
    "hasUser2": false,
    "numExtruder": 2,
    "version": 100.2,
    "primaryPortName": ""
}
========== End configuration string ==========

*/

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

/**
 * power_loss_recovery.cpp - Resume an SD print after power-loss
 */

#include "Repetier.h"
#include "Configuration.h"

#ifdef POWER_LOSS_RECOVERY

#include "power_loss_recovery.h"

PrintJobRecovery recovery;

/**
 * Clear the recovery info
 */
void PrintJobRecovery::init() { memset(&info, 0, sizeof(info)); }


/**
 * Delete the recovery file and clear the recovery data
 */
void PrintJobRecovery::purge() {
  init();
}

/**
 * Load the recovery data, if it exists
 */
void PrintJobRecovery::load() {

}

/**
 * Save the current machine state to the power-loss recovery file
 */
void PrintJobRecovery::save() {

  // info.feedrate = uint16_t(feedrate_mm_s * 60.0f);

  //info.active_hotend = active_extruder;

  //info.target_temperature_extruder = thermalManager.target_temperature;
  //info.target_temperature_bed = thermalManager.target_temperature_bed;

  //info.fan_speed = thermalManager.fan_speed

  // Elapsed print job time
  // info.print_job_elapsed = print_job_timer.duration();

  // SD file position
  // sd.getAbsFilename(info.sd_filename);
  //info.sdpos = sd.sdpos;
}


/**
 * Resume the saved print job
 */
/**
void PrintJobRecovery::resume() {

  #define RECOVERY_ZRAISE 2

  #if HAS_LEVELING
    // Make sure leveling is off before any G92 and G28
    gcode.process_subcommands_now_P(PSTR("M420 S0 Z0"));
  #endif

  // Set Z to 0, raise Z by 2mm, and Home (XY only for Cartesian) with no raise
  // (Only do simulated homing in Marlin Dev Mode.)
  gcode.process_subcommands_now_P(PSTR("G92.0 Z0\nG1 Z" STRINGIFY(RECOVERY_ZRAISE) "\nG28 R0"
    #ifdef MARLIN_DEV_MODE
      " S"
    #elif !IS_KINEMATIC
      " X Y"
    #endif
  ));

  // Pretend that all axes are homed
  axis_homed = axis_known_position = xyz_bits;

  char cmd[40], str_1[16], str_2[16];

  // Select the previously active tool (with no_move)
  #if EXTRUDERS > 1
    sprintf_P(cmd, PSTR("T%i S"), info.active_hotend);
    gcode.process_subcommands_now(cmd);
  #endif

  #if HAS_HEATED_BED
    const int16_t bt = info.target_temperature_bed;
    if (bt) {
      // Restore the bed temperature
      sprintf_P(cmd, PSTR("M190 S%i"), bt);
      gcode.process_subcommands_now(cmd);
    }
  #endif

  // Restore all hotend temperatures
  HOTEND_LOOP() {
    const int16_t et = info.target_temperature[e];
    if (et) {
      #if HOTENDS > 1
        sprintf_P(cmd, PSTR("T%i"), e);
        gcode.process_subcommands_now(cmd);
      #endif
      sprintf_P(cmd, PSTR("M109 S%i"), et);
      gcode.process_subcommands_now(cmd);
    }
  }

  // Restore print cooling fan speeds
  FANS_LOOP(i) {
    uint8_t f = info.fan_speed[i];
    if (f) {
      sprintf_P(cmd, PSTR("M106 P%i S%i"), i, f);
      gcode.process_subcommands_now(cmd);
    }
  }

  #if HAS_LEVELING
    // Restore leveling state before 'G92 Z' to ensure
    // the Z stepper count corresponds to the native Z.
    if (info.fade || info.leveling) {
      dtostrf(info.fade, 1, 1, str_1);
      sprintf_P(cmd, PSTR("M420 S%i Z%s"), int(info.leveling), str_1);
      gcode.process_subcommands_now(cmd);
    }
  #endif

  // Restore Z (plus raise) and E positions with G92.0
  dtostrf(info.current_position[Z_AXIS] + RECOVERY_ZRAISE, 1, 3, str_1);
  dtostrf(info.current_position[E_AXIS]
    #ifdef SAVE_EACH_CMD_MODE
      - 5 // Extra extrusion on restart
    #endif
    , 1, 3, str_2
  );
  sprintf_P(cmd, PSTR("G92.0 Z%s E%s"), str_1, str_2);
  gcode.process_subcommands_now(cmd);

  // Move back to the saved XY
  dtostrf(info.current_position[X_AXIS], 1, 3, str_1);
  dtostrf(info.current_position[Y_AXIS], 1, 3, str_2);
  sprintf_P(cmd, PSTR("G1 X%s Y%s F3000"), str_1, str_2);
  gcode.process_subcommands_now(cmd);

  // Move back to the saved Z
  dtostrf(info.current_position[Z_AXIS], 1, 3, str_1);
  sprintf_P(cmd, PSTR("G1 Z%s F200"), str_1);
  gcode.process_subcommands_now(cmd);

  // Restore the feedrate
  sprintf_P(cmd, PSTR("G1 F%d"), info.feedrate);
  gcode.process_subcommands_now(cmd);

  // Process commands from the old pending queue
  uint8_t c = info.commands_in_queue, r = info.cmd_queue_index_r;
  for (; c--; r = (r + 1) % BUFSIZE)
    gcode.process_subcommands_now(info.command_queue[r]);

  // Resume the SD file from the last position
  char *fn = info.sd_filename;
  while (*fn == '/') fn++;
  sprintf_P(cmd, PSTR("M23 %s"), fn);
  gcode.process_subcommands_now(cmd);
  sprintf_P(cmd, PSTR("M24 S%ld T%ld"), info.sdpos, info.print_job_elapsed);
  gcode.process_subcommands_now(cmd);
}
*/

#endif // POWER_LOSS_RECOVERY

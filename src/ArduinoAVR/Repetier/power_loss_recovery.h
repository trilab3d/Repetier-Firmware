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
#pragma once

/**
 * power_loss_recovery.h - Resume an SD print after power-loss
 */

#include <stdint.h>
#include "Repetier.h"
#include "Configuration.h"


typedef struct {
  uint8_t active_hotend;

  uint8_t target_temperature_extruder;

  uint8_t target_temperature_bed;

  uint8_t fan_speed;

  // SD Filename and position
  char sd_filename[64];
  uint32_t sdpos;
} job_recovery_info_t;


class PrintJobRecovery {
  public:
    static job_recovery_info_t info;

    static void init();

    //static void check();
    //static void resume();

    static void purge();
    static void load();
    static void save();
};

extern PrintJobRecovery recovery;

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
#if !defined(_UI_MENU_H)
#define _UI_MENU_H

/* ============= PAGES DEFINITION =============

  If you are not inside a menu, the firmware displays pages with information.
  Especially if you have only a small display it is convenient to have
  more then one information page.
*/

UI_PAGE4_T(ui_page1, UI_TEXT_MAINPAGE_TEMP_BED_ID, UI_TEXT_MAINPAGE_Z_BUF_ID, UI_TEXT_MAINPAGE_MUL_EUSAGE_ID, UI_TEXT_STATUS_ID)
UI_PAGE4_T(ui_page2, UI_TEXT_ACTION_XPOSITION4A_ID, UI_TEXT_ACTION_YPOSITION4A_ID, UI_TEXT_ACTION_ZPOSITION4A_ID, UI_TEXT_STATUS_ID)
UI_PAGE4_T(ui_page3, UI_TEXT_PAGE_EXTRUDER1_ID, UI_TEXT_PAGE_EXTRUDER2_ID, UI_TEXT_BED_TEMP_ID, UI_TEXT_STATUS_ID)
UI_PAGE4_T(ui_page4, UI_TEXT_PRINT_TIME_ID, UI_TEXT_PRINT_TIME_VALUE_ID, UI_TEXT_PRINT_FILAMENT_ID, UI_TEXT_PRINT_FILAMENT_VALUE_ID)

/*
  Merge pages together. Use the following pattern:
  #define UI_PAGES {&name1,&name2,&name3}
*/
#define UI_PAGES {&ui_page1, &ui_page2, &ui_page3, &ui_page4}
#define UI_NUM_PAGES 4


/* ============ MENU definition ================

  The menu works the same as pages. In additon you need to define what the lines do
  or where to jump to. For that reason, the menu structure needs to be entered in
  reverse order. Starting from the leaves, the menu structure is defined.
*/

// Helper
UI_MENU_ACTIONCOMMAND_T(ui_menu_back, UI_TEXT_BACK_ID, UI_ACTION_BACK)
UI_MENU_HEADLINE_T(ui_menu_empty,UI_TEXT_EMPTY_ID)
UI_MENU_HEADLINE_T(ui_menu_please_wait, UI_TEXT_PLEASE_WAIT_ID)

// Error menu
UI_MENU_ACTION2_T(ui_menu_error, UI_ACTION_DUMMY, UI_TEXT_ERROR_ID, UI_TEXT_ERRORMSG_ID)

// Messages
UI_WIZARD4_T(ui_msg_decoupled, UI_ACTION_MESSAGE,  UI_TEXT_NOTIFICATION_ID, UI_TEXT_HEATER_DECOUPLED_ID, UI_TEXT_EMPTY_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_defectsensor, UI_ACTION_MESSAGE, UI_TEXT_NOTIFICATION_ID, UI_TEXT_TEMPSENSOR_DEFECT_ID, UI_TEXT_EMPTY_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_slipping, UI_ACTION_MESSAGE,  UI_TEXT_NOTIFICATION_ID, UI_TEXT_SLIPPING_ID, UI_TEXT_EMPTY_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_leveling_error, UI_ACTION_MESSAGE, UI_TEXT_NOTIFICATION_ID, UI_TEXT_LEVELING_ERROR_ID, UI_TEXT_EMPTY_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_calibration_error, UI_ACTION_MESSAGE, UI_TEXT_NOTIFICATION_ID, UI_TEXT_CALIBRATION_ERROR_ID, UI_TEXT_EMPTY_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_clearbed1, UI_ACTION_AUTOLEVEL2, UI_TEXT_CLEARBED1_ID, UI_TEXT_CLEARBED2_ID, UI_TEXT_CLEARBED3_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_clearbed2, UI_ACTION_MEASURE_DISTORTION2, UI_TEXT_CLEARBED1_ID, UI_TEXT_CLEARBED2_ID, UI_TEXT_CLEARBED3_ID, UI_TEXT_OK_ID)
UI_WIZARD4_T(ui_msg_calibrating_bed, UI_ACTION_STATE,UI_TEXT_EMPTY_ID, UI_TEXT_CALIBRATING_ID, UI_TEXT_EMPTY_ID, UI_TEXT_PLEASE_WAIT_ID)
UI_WIZARD4_T(ui_msg_homing, UI_ACTION_STATE,UI_TEXT_EMPTY_ID, UI_TEXT_HOMING_ID, UI_TEXT_EMPTY_ID, UI_TEXT_PLEASE_WAIT_ID)

// Filament change wizard
UI_WIZARD4_T(ui_wiz_filamentchange, UI_ACTION_WIZARD_FILAMENTCHANGE, UI_TEXT_WIZ_CH_FILAMENT1_ID, UI_TEXT_WIZ_CH_FILAMENT2_ID, UI_TEXT_WIZ_CH_FILAMENT3_ID, UI_TEXT_CLICK_DONE_ID)
UI_WIZARD4_T(ui_wiz_jamwaitheat, UI_ACTION_WIZARD_JAM_WAITHEAT, UI_TEXT_WIZ_WAITTEMP1_ID, UI_TEXT_WIZ_WAITTEMP2_ID, UI_TEXT_EMPTY_ID, UI_TEXT_TEMP_SET_ID)
UI_WIZARD4_T(ui_wiz_jamreheat, UI_ACTION_WIZARD_JAM_REHEAT, UI_TEXT_WIZ_REHEAT1_ID, UI_TEXT_WIZ_REHEAT2_ID, UI_TEXT_EMPTY_ID, UI_TEXT_CURRENT_TEMP_ID)

// Home all
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_home_all, UI_TEXT_HOME_ALL_ID, UI_ACTION_HOME_ALL, 0, MENU_MODE_PRINTING + MENU_MODE_PAUSED)

// Print file
#define UI_MENU_SD_FILESELECTOR {&ui_menu_back}
UI_MENU_FILESELECT(ui_menu_sd_fileselector, UI_MENU_SD_FILESELECTOR, 1)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_sd_printfile, UI_TEXT_PRINT_FILE_ID,     UI_ACTION_SD_PRINT,    MENU_MODE_SD_MOUNTED,  MENU_MODE_SD_PRINTING)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_sd_pause,     UI_TEXT_PAUSE_PRINT_ID,    UI_ACTION_SD_PAUSE,    MENU_MODE_SD_PRINTING, MENU_MODE_PAUSED)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_sd_continue,  UI_TEXT_CONTINUE_PRINT_ID, UI_ACTION_SD_CONTINUE, MENU_MODE_SD_PRINTING + MENU_MODE_PAUSED,   0)
UI_MENU_HEADLINE_T(ui_menu_askstop_head, UI_TEXT_STOP_PRINT_ID)
UI_MENU_ACTIONCOMMAND_T(ui_menu_sd_askstop_no, UI_TEXT_NO_ID, UI_ACTION_BACK)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_sd_askstop_yes, UI_TEXT_YES_ID, UI_ACTION_STOP_CONFIRMED | UI_ACTION_TOPMENU, MENU_MODE_PRINTING, 0)
#define UI_MENU_ASKSTOP {&ui_menu_askstop_head,&ui_menu_empty,&ui_menu_sd_askstop_no,&ui_menu_sd_askstop_yes}
UI_MENU(ui_menu_askstop, UI_MENU_ASKSTOP, 4)
UI_MENU_SUBMENU_FILTER_T(ui_menu_sd_stop, UI_TEXT_STOP_PRINT_ID, ui_menu_askstop, MENU_MODE_SD_PRINTING, 0 )

// Load filament
UI_MENU_ACTIONCOMMAND_T(ui_menu_load_filament_bowden, UI_TEXT_BOWDEN_EXTRUDER_ID, UI_ACTION_LOAD_FILAMENT_BOWDEN)
UI_MENU_ACTIONCOMMAND_T(ui_menu_load_filament_direct, UI_TEXT_DIRECT_EXTRUDER_ID, UI_ACTION_LOAD_FILAMENT_DIRECT)
#define UI_MENU_LOAD_FILAMENT {&ui_menu_back, &ui_menu_load_filament_bowden, &ui_menu_load_filament_direct}
UI_MENU(ui_menu_load_filament_sel_ext, UI_MENU_LOAD_FILAMENT, 3)
UI_MENU_SUBMENU_FILTER_T(ui_menu_load_filament, UI_TEXT_LOAD_FILAMENT_ID, ui_menu_load_filament_sel_ext,0,MENU_MODE_PRINTING)

UI_MENU_HEADLINE_T(ui_menu_loading_filament_1, UI_TEXT_LOADING_FILAMENT_ID)
#define UI_MENU_LOADING_FILAMENT {&ui_menu_please_wait, &ui_menu_empty, &ui_menu_loading_filament_1, &ui_menu_empty}
UI_MENU(ui_menu_loading_filament, UI_MENU_LOADING_FILAMENT, 4)

// Unload filament
UI_MENU_ACTIONCOMMAND_T(ui_menu_unload_filament_bowden, UI_TEXT_BOWDEN_EXTRUDER_ID, UI_ACTION_UNLOAD_FILAMENT_BOWDEN)
UI_MENU_ACTIONCOMMAND_T(ui_menu_unload_filament_direct, UI_TEXT_DIRECT_EXTRUDER_ID, UI_ACTION_UNLOAD_FILAMENT_DIRECT)
#define UI_MENU_UNLOAD_FILAMENT {&ui_menu_back, &ui_menu_unload_filament_bowden, &ui_menu_unload_filament_direct}
UI_MENU(ui_menu_unload_filament_sel_ext, UI_MENU_UNLOAD_FILAMENT, 3)
UI_MENU_SUBMENU_FILTER_T(ui_menu_unload_filament, UI_TEXT_UNLOAD_FILAMENT_ID, ui_menu_unload_filament_sel_ext,0,MENU_MODE_PRINTING)

UI_MENU_HEADLINE_T(ui_menu_unloading_filament_1, UI_TEXT_UNLOADING_FILAMENT_ID)
#define UI_MENU_UNLOADING_FILAMENT {&ui_menu_please_wait, &ui_menu_empty, &ui_menu_unloading_filament_1, &ui_menu_empty}
UI_MENU(ui_menu_unloading_filament, UI_MENU_UNLOADING_FILAMENT, 4)

// Purge filament
UI_MENU_ACTIONCOMMAND_T(ui_menu_purge_filament_bowden, UI_TEXT_BOWDEN_EXTRUDER_ID, UI_ACTION_PURGE_FILAMENT_BOWDEN)
UI_MENU_ACTIONCOMMAND_T(ui_menu_purge_filament_direct, UI_TEXT_DIRECT_EXTRUDER_ID, UI_ACTION_PURGE_FILAMENT_DIRECT)
#define UI_MENU_PURGE_FILAMENT {&ui_menu_back, &ui_menu_purge_filament_bowden, &ui_menu_purge_filament_direct}
UI_MENU(ui_menu_purge_filament_sel_ext, UI_MENU_PURGE_FILAMENT, 3)
UI_MENU_SUBMENU_FILTER_T(ui_menu_purge_filament, UI_TEXT_PURGE_FILAMENT_ID, ui_menu_purge_filament_sel_ext,0,MENU_MODE_PRINTING)

UI_MENU_HEADLINE_T(ui_menu_purging_filament_1, UI_TEXT_PURGING_FILAMENT_ID)
#define UI_MENU_PURGING_FILAMENT {&ui_menu_please_wait, &ui_menu_empty, &ui_menu_purging_filament_1, &ui_menu_empty}
UI_MENU(ui_menu_purging_filament, UI_MENU_PURGING_FILAMENT, 4)


// Move
UI_MENU_ACTION4_T(ui_menu_xpos, UI_ACTION_XPOSITION, UI_TEXT_ACTION_XPOSITION4A_ID, UI_TEXT_ACTION_XPOSITION4B_ID, UI_TEXT_ACTION_XPOSITION4C_ID, UI_TEXT_ACTION_XPOSITION4D_ID)
UI_MENU_ACTION4_T(ui_menu_ypos, UI_ACTION_YPOSITION, UI_TEXT_ACTION_YPOSITION4A_ID, UI_TEXT_ACTION_YPOSITION4B_ID, UI_TEXT_ACTION_YPOSITION4C_ID, UI_TEXT_ACTION_YPOSITION4D_ID)
UI_MENU_ACTION4_T(ui_menu_zpos, UI_ACTION_ZPOSITION, UI_TEXT_ACTION_ZPOSITION4A_ID, UI_TEXT_ACTION_ZPOSITION4B_ID, UI_TEXT_ACTION_ZPOSITION4C_ID, UI_TEXT_ACTION_ZPOSITION4D_ID)
UI_MENU_ACTION4_T(ui_menu_zpos_notest, UI_ACTION_ZPOSITION_NOTEST, UI_TEXT_ACTION_ZPOSITION4A_ID, UI_TEXT_ACTION_ZPOSITION4B_ID, UI_TEXT_ACTION_ZPOSITION4C_ID, UI_TEXT_ACTION_ZPOSITION4D_ID)
UI_MENU_ACTION4_T(ui_menu_xpos_fast, UI_ACTION_XPOSITION_FAST, UI_TEXT_ACTION_XPOSITION_FAST4A_ID, UI_TEXT_ACTION_XPOSITION_FAST4B_ID, UI_TEXT_ACTION_XPOSITION_FAST4C_ID, UI_TEXT_ACTION_XPOSITION_FAST4D_ID)
UI_MENU_ACTION4_T(ui_menu_ypos_fast, UI_ACTION_YPOSITION_FAST, UI_TEXT_ACTION_YPOSITION_FAST4A_ID, UI_TEXT_ACTION_YPOSITION_FAST4B_ID, UI_TEXT_ACTION_YPOSITION_FAST4C_ID, UI_TEXT_ACTION_YPOSITION_FAST4D_ID)
UI_MENU_ACTION4_T(ui_menu_zpos_fast, UI_ACTION_ZPOSITION_FAST, UI_TEXT_ACTION_ZPOSITION_FAST4A_ID, UI_TEXT_ACTION_ZPOSITION_FAST4B_ID, UI_TEXT_ACTION_ZPOSITION_FAST4C_ID, UI_TEXT_ACTION_ZPOSITION_FAST4D_ID)
UI_MENU_ACTION4_T(ui_menu_zpos_fast_notest, UI_ACTION_ZPOSITION_FAST_NOTEST, UI_TEXT_ACTION_ZPOSITION_FAST4A_ID, UI_TEXT_ACTION_ZPOSITION_FAST4B_ID, UI_TEXT_ACTION_ZPOSITION_FAST4C_ID, UI_TEXT_ACTION_ZPOSITION_FAST4D_ID)
UI_MENU_ACTION4_T(ui_menu_epos, UI_ACTION_EPOSITION, UI_TEXT_ACTION_EPOSITION_FAST2A_ID, UI_TEXT_ACTION_EPOSITION_FAST2B_ID, UI_TEXT_PAGE_EXTRUDER_ID, UI_TEXT_METER_PRINTED_ID)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_xpos, UI_TEXT_X_POSITION_ID, ui_menu_xpos)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_ypos, UI_TEXT_Y_POSITION_ID, ui_menu_ypos)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_zpos, UI_TEXT_Z_POSITION_ID, ui_menu_zpos)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_epos, UI_TEXT_E_POSITION_ID, ui_menu_epos)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_xfast, UI_TEXT_X_POS_FAST_ID, ui_menu_xpos_fast)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_yfast, UI_TEXT_Y_POS_FAST_ID, ui_menu_ypos_fast)
UI_MENU_ACTIONSELECTOR_T(ui_menu_go_zfast, UI_TEXT_Z_POS_FAST_ID, ui_menu_zpos_fast)

#define UI_MENU_POSITIONS {&ui_menu_back, &ui_menu_home_all, &ui_menu_go_xfast, &ui_menu_go_xpos, &ui_menu_go_yfast, &ui_menu_go_ypos, &ui_menu_go_zfast, &ui_menu_go_zpos}
UI_MENU(ui_menu_positions, UI_MENU_POSITIONS, 7)
UI_MENU_SUBMENU_FILTER_T(ui_menu_move, UI_TEXT_POSITION_ID, ui_menu_positions,0,MENU_MODE_PRINTING + MENU_MODE_PAUSED)


// Extruder
UI_MENU_ACTIONCOMMAND_T(ui_menu_quick_cooldown, UI_TEXT_COOLDOWN_ID, UI_ACTION_COOLDOWN)
UI_MENU_CHANGEACTION_T(ui_menu_bed_temp, UI_TEXT_BED_TEMP_ID, UI_ACTION_HEATED_BED_TEMP)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_bed_temp_printing, UI_TEXT_BED_TEMP_ID, UI_ACTION_HEATED_BED_TEMP,MENU_MODE_PRINTING,0)
UI_MENU_CHANGEACTION_T(ui_menu_ext_temp0, UI_TEXT_EXTR0_TEMP_ID, UI_ACTION_EXTRUDER0_TEMP)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_ext_temp0_printing, UI_TEXT_EXTR0_TEMP_ID, UI_ACTION_EXTRUDER0_TEMP,MENU_MODE_PRINTING,0)
UI_MENU_CHANGEACTION_T(ui_menu_ext_temp1, UI_TEXT_EXTR1_TEMP_ID, UI_ACTION_EXTRUDER1_TEMP)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_ext_temp1_printing, UI_TEXT_EXTR1_TEMP_ID, UI_ACTION_EXTRUDER1_TEMP,MENU_MODE_PRINTING,0)
UI_MENU_ACTIONCOMMAND_T(ui_menu_ext_sel0, UI_TEXT_EXTR0_SELECT_ID, UI_ACTION_SELECT_EXTRUDER0)
UI_MENU_ACTIONCOMMAND_T(ui_menu_ext_sel1, UI_TEXT_EXTR1_SELECT_ID, UI_ACTION_SELECT_EXTRUDER1)
UI_MENU_ACTIONCOMMAND_T(ui_menu_ext_off0, UI_TEXT_EXTR0_OFF_ID, UI_ACTION_EXTRUDER0_OFF)
UI_MENU_ACTIONCOMMAND_T(ui_menu_ext_off1, UI_TEXT_EXTR1_OFF_ID, UI_ACTION_EXTRUDER1_OFF)
UI_MENU_CHANGEACTION_T(ui_menu_fan_fanspeed, UI_TEXT_ACTION_FANSPEED_ID, UI_ACTION_FANSPEED)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_fan_fanspeed_printing, UI_TEXT_ACTION_FANSPEED_ID, UI_ACTION_FANSPEED,MENU_MODE_PRINTING,0)

#define UI_MENU_EXTRUDER {&ui_menu_back, &ui_menu_quick_cooldown, &ui_menu_bed_temp, &ui_menu_ext_temp0, &ui_menu_ext_temp1, &ui_menu_ext_off0, &ui_menu_ext_off1, &ui_menu_ext_sel0, &ui_menu_ext_sel1 , &ui_menu_go_epos, &ui_menu_fan_fanspeed}
UI_MENU(ui_menu_extruder, UI_MENU_EXTRUDER, 11)
UI_MENU_SUBMENU_FILTER_T(ui_menu_extrudercontrol, UI_TEXT_EXTRUDER_ID, ui_menu_extruder,0,MENU_MODE_PRINTING + MENU_MODE_PAUSED)

// Settings
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_z_home_cal,UI_TEXT_Z_HOME_CALIB_ID,UI_ACTION_SERVICE_MENU_ITEM1,0,MENU_MODE_PRINTING + MENU_MODE_PAUSED)
UI_MENU_ACTION2_T(ui_menu_z_offset_change, UI_ACTION_DUMMY, UI_TEXT_BED_COATING_SET1_ID, UI_TEXT_COATING_THICKNESS_ID)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_adjust_z_offset_change, UI_TEXT_ZPROBE_HEIGHT_ID, UI_ACTION_Z_OFFSET_CHANGE, 0, MENU_MODE_PRINTING + MENU_MODE_PAUSED)
UI_MENU_ACTIONCOMMAND_T(ui_fil_sensor_on_off, UI_TEXT_JAMCONTROL_ID, UI_ACTION_TOGGLE_JAMCONTROL)

#define UI_MENU_CONFIGURATION {&ui_menu_back, &ui_menu_z_home_cal, &ui_menu_adjust_z_offset_change, &ui_fil_sensor_on_off}
UI_MENU(ui_menu_configuration, UI_MENU_CONFIGURATION, 4)
UI_MENU_SUBMENU_FILTER_T(ui_menu_settings, UI_TEXT_CONFIGURATION_ID, ui_menu_configuration,0,MENU_MODE_PRINTING)

// Calibration
UI_MENU_HEADLINE_T(ui_menu_cal_ask_use_tower_angle_corr_1, UI_TEXT_CAL_USE_TOWER_ANGLE_CORR_1_ID)
UI_MENU_HEADLINE_T(ui_menu_cal_ask_use_tower_angle_corr_2, UI_TEXT_CAL_USE_TOWER_ANGLE_CORR_2_ID)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_ask_use_tower_angle_corr_yes, UI_TEXT_YES_ID, UI_ACTION_CAL_RUN_FULL_CALIBRATION_WITH_TOWER_ANGLE_CORR)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_ask_use_tower_angle_corr_no, UI_TEXT_NO_ID, UI_ACTION_CAL_RUN_FULL_CALIBRATION_WITHOUT_TOWER_ANGLE_CORR)
#define UI_MENU_CAL_ASK_USE_TOWER_ANGLE_CORR {&ui_menu_cal_ask_use_tower_angle_corr_1,&ui_menu_cal_ask_use_tower_angle_corr_2,&ui_menu_cal_ask_use_tower_angle_corr_yes,&ui_menu_cal_ask_use_tower_angle_corr_no}
UI_MENU(ui_menu_cal_ask_use_tower_angle_corr, UI_MENU_CAL_ASK_USE_TOWER_ANGLE_CORR, 4)

UI_MENU_CHANGEACTION_T(ui_menu_cal_x_endstop_offset, UI_TEXT_CAL_X_ENDSTOP_OFFSET_ID, UI_ACTION_CAL_X_ENDSTOP_OFFSET)
UI_MENU_CHANGEACTION_T(ui_menu_cal_y_endstop_offset, UI_TEXT_CAL_Y_ENDSTOP_OFFSET_ID, UI_ACTION_CAL_Y_ENDSTOP_OFFSET)
UI_MENU_CHANGEACTION_T(ui_menu_cal_z_endstop_offset, UI_TEXT_CAL_Z_ENDSTOP_OFFSET_ID, UI_ACTION_CAL_Z_ENDSTOP_OFFSET)
UI_MENU_CHANGEACTION_T(ui_menu_cal_delta_radius, UI_TEXT_CAL_DELTA_RADIUS_ID, UI_ACTION_CAL_DELTA_RADIUS)
UI_MENU_CHANGEACTION_T(ui_menu_cal_x_tower_angle, UI_TEXT_CAL_X_TOWER_ANGLE_ID, UI_ACTION_CAL_X_TOWER_ANGLE)
UI_MENU_CHANGEACTION_T(ui_menu_cal_y_tower_angle, UI_TEXT_CAL_Y_TOWER_ANGLE_ID, UI_ACTION_CAL_Y_TOWER_ANGLE)
UI_MENU_CHANGEACTION_T(ui_menu_cal_z_tower_angle, UI_TEXT_CAL_Z_TOWER_ANGLE_ID, UI_ACTION_CAL_Z_TOWER_ANGLE)
UI_MENU_CHANGEACTION_T(ui_menu_cal_diagonal_rod_length, UI_TEXT_CAL_DIAGONAL_ROD_LENGTH_ID, UI_ACTION_CAL_DIAGONAL_ROD_LENGTH)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_reset_to_defaults, UI_TEXT_CAL_RESET_TO_DEFAULTS_ID, UI_ACTION_CAL_CONFIRM_RESET_TO_DEFAULTS)

UI_MENU_HEADLINE_T(ui_menu_cal_confirm_reset_to_defaults_1, UI_TEXT_CAL_CONFIRM_RESET_TO_DEFAULTS_ID)
UI_MENU_HEADLINE_T(ui_menu_cal_confirm_reset_to_defaults_2, UI_TEXT_EMPTY_ID)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_confirm_reset_to_defaults_yes, UI_TEXT_YES_ID, UI_ACTION_CAL_RESET_TO_DEFAULTS)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_confirm_reset_to_defaults_no, UI_TEXT_NO_ID, UI_ACTION_BACK)
#define UI_MENU_CAL_CONFIRM_RESET_TO_DEFAULTS {&ui_menu_cal_confirm_reset_to_defaults_1,&ui_menu_cal_confirm_reset_to_defaults_2,&ui_menu_cal_confirm_reset_to_defaults_yes,&ui_menu_cal_confirm_reset_to_defaults_no}
UI_MENU(ui_menu_cal_confirm_reset_to_defaults, UI_MENU_CAL_CONFIRM_RESET_TO_DEFAULTS, 4)

#define UI_MENU_CAL_MANUAL_ADJUST {&ui_menu_back, &ui_menu_cal_x_endstop_offset, &ui_menu_cal_y_endstop_offset, &ui_menu_cal_z_endstop_offset, &ui_menu_cal_delta_radius, &ui_menu_cal_x_tower_angle, &ui_menu_cal_y_tower_angle, &ui_menu_cal_z_tower_angle, &ui_menu_cal_diagonal_rod_length, &ui_menu_cal_reset_to_defaults}
UI_MENU(ui_menu_cal_manual_adjust, UI_MENU_CAL_MANUAL_ADJUST, 10)
UI_MENU_SUBMENU_T(ui_menu_cal_manual_adjust_sub, UI_TEXT_CAL_MANUAL_ADJUST_ID , ui_menu_cal_manual_adjust)

UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_plain_probing, UI_TEXT_CAL_PLAIN_PROBING_ID, UI_ACTION_CAL_PLAIN_PROBING)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_autolevel_probing, UI_TEXT_CAL_AUTOLEVEL_PROBING_ID, UI_ACTION_CAL_AUTOLEVEL_PROBING)
UI_MENU_ACTIONCOMMAND_T(ui_menu_cal_run_full_calibration, UI_TEXT_CAL_RUN_FULL_CALIBRATION_ID, UI_ACTION_CAL_RUN_FULL_CALIBRATION)
#define UI_MENU_SERVICE_CAL {&ui_menu_back, &ui_menu_cal_plain_probing, &ui_menu_cal_autolevel_probing, &ui_menu_cal_run_full_calibration, &ui_menu_cal_manual_adjust_sub}
UI_MENU(ui_menu_service_cal, UI_MENU_SERVICE_CAL, 5)
UI_MENU_SUBMENU_T(ui_menu_service_cal_sub, UI_TEXT_SERVICE_CAL_ID , ui_menu_service_cal)

UI_WIZARD4_T(ui_msg_cal_plain_probing_result, UI_ACTION_MESSAGE,  UI_TEXT_CAL_PLAIN_PROBING_ID, UI_TEXT_CAL_PROBE_HEIGHT_L1_ID, UI_TEXT_CAL_PROBE_HEIGHT_L2_ID, UI_TEXT_CAL_PROBE_HEIGHT_L3_ID)
UI_WIZARD4_T(ui_msg_cal_autolevel_probing_result, UI_ACTION_MESSAGE,  UI_TEXT_CAL_AUTOLEVEL_PROBING_ID, UI_TEXT_CAL_PROBE_HEIGHT_L1_ID, UI_TEXT_CAL_PROBE_HEIGHT_L2_ID, UI_TEXT_CAL_PROBE_HEIGHT_L3_ID)
UI_WIZARD4_T(ui_msg_cal_full_calibration_probing_result, UI_ACTION_CAL_RESULT, UI_TEXT_CAL_RUN_FULL_CALIBRATION_ID, UI_TEXT_CAL_PROBE_HEIGHT_L1_ID, UI_TEXT_CAL_PROBE_HEIGHT_L2_ID, UI_TEXT_CAL_PROBE_HEIGHT_L3_ID)
UI_WIZARD4_T(ui_msg_cal_full_calibration_result, UI_ACTION_MESSAGE, UI_TEXT_CAL_RESULT_1_ID, UI_TEXT_CAL_RESULT_2_ID, UI_TEXT_CAL_RESULT_3_ID, UI_TEXT_CAL_RESULT_4_ID)

UI_MENU_ACTION2_T(ui_menu_stepper2, UI_ACTION_STEPPER_INACTIVE, UI_TEXT_STEPPER_INACTIVE2A_ID, UI_TEXT_STEPPER_INACTIVE2B_ID)
UI_MENU_ACTION2_T(ui_menu_maxinactive2, UI_ACTION_MAX_INACTIVE, UI_TEXT_POWER_INACTIVE2A_ID, UI_TEXT_POWER_INACTIVE2B_ID)
UI_MENU_CHANGEACTION_T(ui_menu_general_baud, UI_TEXT_BAUDRATE_ID, UI_ACTION_BAUDRATE)
UI_MENU_ACTIONSELECTOR_T(ui_menu_general_stepper_inactive, UI_TEXT_STEPPER_INACTIVE_ID, ui_menu_stepper2)
UI_MENU_ACTIONSELECTOR_T(ui_menu_general_max_inactive, UI_TEXT_POWER_INACTIVE_ID, ui_menu_maxinactive2)

UI_MENU_CHANGEACTION_T(ui_menu_accel_printz, UI_TEXT_PRINT_Z_DELTA_ID, UI_ACTION_PRINT_ACCEL_Z)
UI_MENU_CHANGEACTION_T(ui_menu_accel_travelz, UI_TEXT_MOVE_Z_DELTA_ID, UI_ACTION_MOVE_ACCEL_Z)
UI_MENU_CHANGEACTION_T(ui_menu_accel_jerk, UI_TEXT_JERK_ID, UI_ACTION_MAX_JERK)
#define UI_MENU_ACCEL {&ui_menu_back, &ui_menu_accel_printz,&ui_menu_accel_travelz,&ui_menu_accel_jerk}
UI_MENU(ui_menu_accel, UI_MENU_ACCEL, 4)
UI_MENU_SUBMENU_T(ui_menu_conf_accel,   UI_TEXT_ACCELERATION_ID, ui_menu_accel)

// **** Feedrates
UI_MENU_CHANGEACTION_T(ui_menu_feedrate_maxz, UI_TEXT_FEED_MAX_Z_DELTA_ID, UI_ACTION_MAX_FEEDRATE_Z)
UI_MENU_CHANGEACTION_T(ui_menu_feedrate_homez, UI_TEXT_FEED_HOME_Z_DELTA_ID, UI_ACTION_HOMING_FEEDRATE_Z)
#define UI_MENU_FEEDRATE {&ui_menu_back, &ui_menu_feedrate_maxz,&ui_menu_feedrate_homez}
UI_MENU(ui_menu_feedrate, UI_MENU_FEEDRATE, 3)
UI_MENU_SUBMENU_T(ui_menu_conf_feed,    UI_TEXT_FEEDRATE_ID,     ui_menu_feedrate)

UI_MENU_CHANGEACTION_T(ui_menu_cext_steps,          UI_TEXT_EXTR_STEPS_ID,              UI_ACTION_EXTR_STEPS)
UI_MENU_CHANGEACTION_T(ui_menu_cext_start_feedrate, UI_TEXT_EXTR_START_FEED_ID,         UI_ACTION_EXTR_START_FEEDRATE)
UI_MENU_CHANGEACTION_T(ui_menu_cext_max_feedrate,   UI_TEXT_EXTR_MAX_FEED_ID,           UI_ACTION_EXTR_MAX_FEEDRATE)
UI_MENU_CHANGEACTION_T(ui_menu_cext_acceleration,   UI_TEXT_EXTR_ACCEL_ID,              UI_ACTION_EXTR_ACCELERATION)
UI_MENU_CHANGEACTION_T(ui_menu_cext_watch_period,   UI_TEXT_EXTR_WATCH_ID,              UI_ACTION_EXTR_WATCH_PERIOD)
UI_MENU_CHANGEACTION_T(ui_menu_ext_wait_temp,       UI_TEXT_EXTR_WAIT_RETRACT_TEMP_ID,  UI_ACTION_EXTR_WAIT_RETRACT_TEMP)
UI_MENU_CHANGEACTION_T(ui_menu_ext_wait_units,      UI_TEXT_EXTR_WAIT_RETRACT_UNITS_ID, UI_ACTION_EXTR_WAIT_RETRACT_UNITS)
UI_MENU_CHANGEACTION_T(ui_menu_cext_manager, UI_TEXT_EXTR_MANAGER_ID, UI_ACTION_EXTR_HEATMANAGER)
UI_MENU_CHANGEACTION_T(ui_menu_cext_pmax,    UI_TEXT_EXTR_PMAX_ID,    UI_ACTION_PID_MAX)
// PID
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_pgain,   UI_TEXT_EXTR_PGAIN_ID,   UI_ACTION_PID_PGAIN, MENU_MODE_FULL_PID, 0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_igain,   UI_TEXT_EXTR_IGAIN_ID,   UI_ACTION_PID_IGAIN,  MENU_MODE_FULL_PID, 0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_dgain,   UI_TEXT_EXTR_DGAIN_ID,   UI_ACTION_PID_DGAIN,  MENU_MODE_FULL_PID, 0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_dmin,    UI_TEXT_EXTR_DMIN_ID,    UI_ACTION_DRIVE_MIN,  MENU_MODE_FULL_PID, 0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_dmax,    UI_TEXT_EXTR_DMAX_ID,    UI_ACTION_DRIVE_MAX,  MENU_MODE_FULL_PID, 0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_pgain_dt,   UI_TEXT_EXTR_DEADTIME_ID,   UI_ACTION_PID_PGAIN, MENU_MODE_DEADTIME, 0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_cext_dmax_dt,    UI_TEXT_EXTR_DMAX_DT_ID,    UI_ACTION_DRIVE_MAX,  MENU_MODE_DEADTIME, 0)
#define UI_MENU_CEXTR {&ui_menu_back, &ui_menu_cext_steps,&ui_menu_cext_start_feedrate,&ui_menu_cext_max_feedrate,&ui_menu_cext_acceleration,&ui_menu_cext_watch_period,&ui_menu_ext_wait_units,&ui_menu_ext_wait_temp,&ui_menu_cext_manager,&ui_menu_cext_pgain,&ui_menu_cext_igain,&ui_menu_cext_dgain,&ui_menu_cext_dmin,&ui_menu_cext_dmax, &ui_menu_cext_pgain_dt,&ui_menu_cext_dmax_dt,&ui_menu_cext_pmax}
UI_MENU(ui_menu_cextr, UI_MENU_CEXTR, 17)
UI_MENU_SUBMENU_T(ui_menu_conf_extr,    UI_TEXT_EXTRUDER_ID,     ui_menu_cextr)

#define UI_MENU_BEDCONF {&ui_menu_back, &ui_menu_cext_manager,&ui_menu_cext_pgain,&ui_menu_cext_igain,&ui_menu_cext_dgain,&ui_menu_cext_dmin,&ui_menu_cext_dmax,&ui_menu_cext_pgain_dt,&ui_menu_cext_pmax}
UI_MENU(ui_menu_bedconf, UI_MENU_BEDCONF, 9)
UI_MENU_SUBMENU_T(ui_menu_conf_bed,    UI_TEXT_HEATING_BED_ID,  ui_menu_bedconf)

// EEprom
UI_MENU_ACTIONCOMMAND_T(ui_menu_conf_to_eeprom, UI_TEXT_STORE_TO_EEPROM_ID, UI_ACTION_STORE_EEPROM)
UI_MENU_ACTIONCOMMAND_T(ui_menu_conf_from_eeprom, UI_TEXT_LOAD_EEPROM_ID, UI_ACTION_LOAD_EEPROM)
UI_MENU_ACTION2_T(ui_menu_eeprom_saved,  UI_ACTION_DUMMY, UI_TEXT_EEPROM_STOREDA_ID, UI_TEXT_EEPROM_STOREDB_ID)
UI_MENU_ACTION2_T(ui_menu_eeprom_loaded, UI_ACTION_DUMMY, UI_TEXT_EEPROM_LOADEDA_ID, UI_TEXT_EEPROM_LOADEDB_ID)

UI_MENU_ACTIONCOMMAND_T(ui_menu_factory_reset, UI_TEXT_FACTORY_RESET_ID, UI_ACTION_FACTORY_RESET_CONFIRM)

UI_MENU_HEADLINE_T(ui_menu_factory_reset_ask, UI_TEXT_FACTORY_RESET_CONFIRM_ID)
UI_MENU_ACTIONCOMMAND_T(ui_menu_factory_reset_confirm_yes, UI_TEXT_YES_ID, UI_ACTION_FACTORY_RESET)
UI_MENU_ACTIONCOMMAND_T(ui_menu_factory_reset_confirm_no, UI_TEXT_NO_ID, UI_ACTION_BACK)
#define UI_MENU_FACTORY_RESET_CONFIRM {&ui_menu_factory_reset_ask,&ui_menu_empty,&ui_menu_factory_reset_confirm_yes,&ui_menu_factory_reset_confirm_no}
UI_MENU(ui_menu_factory_reset_confirm, UI_MENU_FACTORY_RESET_CONFIRM, 4)

UI_MENU_ACTIONCOMMAND_T(ui_menu_service_only, UI_TEXT_SERVICE_ONLY_ID, UI_ACTION_DUMMY)
UI_MENU_ACTIONCOMMAND_T(ui_menu_service_only_separator, UI_TEXT_LINE_SEPARATOR_ID, UI_ACTION_DUMMY)

// Service menu
#define UI_MENU_SERVICE {&ui_menu_back, &ui_menu_service_only_separator, &ui_menu_service_only, &ui_menu_service_only_separator, &ui_menu_general_baud, &ui_menu_general_stepper_inactive, &ui_menu_general_max_inactive, &ui_menu_conf_accel, &ui_menu_conf_feed, &ui_menu_conf_extr, &ui_menu_conf_bed, &ui_menu_service_cal_sub, &ui_menu_conf_to_eeprom, &ui_menu_conf_from_eeprom, &ui_menu_factory_reset}
UI_MENU(ui_menu_service, UI_MENU_SERVICE, 15)
UI_MENU_SUBMENU_FILTER_T(ui_menu_service_sub, UI_TEXT_NA_ID , ui_menu_service, 0, MENU_MODE_PRINTING + MENU_MODE_PAUSED)

// Printing menu - stop/pause/continue...
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_pause,UI_TEXT_PAUSE_PRINT_ID,UI_ACTION_PAUSE,MENU_MODE_PRINTING,MENU_MODE_PAUSED)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_continue,UI_TEXT_CONTINUE_PRINT_ID,UI_ACTION_CONTINUE,MENU_MODE_PAUSED,0)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_stop,UI_TEXT_STOP_PRINT_ID,UI_ACTION_STOP,MENU_MODE_PRINTING,MENU_MODE_PAUSED)

UI_MENU_CHANGEACTION_T(ui_menu_quick_zbaby, UI_TEXT_Z_BABYSTEPPING_ID, UI_ACTION_Z_BABYSTEPS)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_quick_zbaby_printing, UI_TEXT_Z_BABYSTEPPING_ID, UI_ACTION_Z_BABYSTEPS,MENU_MODE_PRINTING,0)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_quick_speedmultiply_printing, UI_TEXT_SPEED_MULTIPLY_ID, UI_ACTION_FEEDRATE_MULTIPLY,MENU_MODE_PRINTING,0)
UI_MENU_CHANGEACTION_T(ui_menu_quick_flowmultiply, UI_TEXT_FLOW_MULTIPLY_ID, UI_ACTION_FLOWRATE_MULTIPLY)
UI_MENU_CHANGEACTION_FILTER_T(ui_menu_quick_flowmultiply_printing, UI_TEXT_FLOW_MULTIPLY_ID, UI_ACTION_FLOWRATE_MULTIPLY,MENU_MODE_PRINTING,0)
UI_MENU_ACTIONCOMMAND_T(ui_menu_fan_ignoreM106, UI_TEXT_IGNORE_M106_ID, UI_ACTION_IGNORE_M106)
UI_MENU_ACTIONCOMMAND_FILTER_T(ui_menu_fan_ignoreM106_printing, UI_TEXT_IGNORE_M106_ID, UI_ACTION_IGNORE_M106,MENU_MODE_PRINTING,0)

// Main menu
#define UI_MENU_MAIN {&ui_menu_back, &ui_stop, &ui_pause, &ui_continue, &ui_menu_home_all, &ui_menu_sd_printfile, &ui_menu_load_filament, &ui_menu_unload_filament, &ui_menu_purge_filament, &ui_menu_move, &ui_menu_extrudercontrol, &ui_menu_settings, &ui_menu_service_sub, &ui_menu_ext_temp0_printing, &ui_menu_ext_temp1_printing, &ui_menu_bed_temp_printing, &ui_menu_quick_zbaby_printing, &ui_menu_quick_speedmultiply_printing, &ui_menu_quick_flowmultiply_printing, &ui_menu_fan_fanspeed_printing, &ui_menu_fan_ignoreM106_printing} 
UI_MENU(ui_menu_main, UI_MENU_MAIN, 21)


/* Define menus accessible by action commands

  You can create up to 10 user menus which are accessible by the action commands UI_ACTION_SHOW_USERMENU1 until UI_ACTION_SHOW_USERMENU10
  You this the same way as with the menus above or you use one of the above menus. Then add a define like

  #define UI_USERMENU1 ui_menu_conf_feed

  which assigns the menu stored in ui_menu_conf_feed to the action UI_ACTION_SHOW_USERMENU1. Make sure only to change the numbers and not the name of the define.

  When do you need this? You might want a fast button to change the temperature. In the default menu you have no menu
  to change the temperature and view it the same time. So you need to make an action menu for this like:
  UI_MENU_ACTION4C(ui_menu_extrtemp,UI_ACTION_EXTRUDER0_TEMP,"Temp. 0  :%E0" cDEG,"","","");
  Then you assign this menu to a user menu:
  #define UI_USERMENU2 ui_menu_extrtemp

  Now you can assign the action  UI_ACTION_SHOW_USERMENU2+UI_ACTION_TOPMENU to a key and that will now show the temperature screen and allows
  the change of temperature with the next/previous buttons.

*/

#endif // __UI_MENU_H

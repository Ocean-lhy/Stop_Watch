/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

int screen_time_analog_clock_1_hour_value = 10;
int screen_time_analog_clock_1_min_value = 10;
int screen_time_analog_clock_1_sec_value = 15;
void setup_scr_screen_time(lv_ui *ui)
{
    //Write codes screen_time
    ui->screen_time = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_time, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_time, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->screen_time, &_StopWATCHUI2modified_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->screen_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->screen_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_bar_battery
    ui->screen_time_bar_battery = lv_bar_create(ui->screen_time);
    lv_obj_set_style_anim_time(ui->screen_time_bar_battery, 500, 0);
    lv_bar_set_mode(ui->screen_time_bar_battery, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_time_bar_battery, 0, 100);
    lv_bar_set_value(ui->screen_time_bar_battery, 100, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_time_bar_battery, 176, 357);
    lv_obj_set_size(ui->screen_time_bar_battery, 115, 20);

    //Write style for screen_time_bar_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_bar_battery, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_bar_battery, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_bar_battery, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_bar_battery, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_bar_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_time_bar_battery, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_bar_battery, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_bar_battery, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_bar_battery, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_bar_battery, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_time_label_battery
    ui->screen_time_label_battery = lv_label_create(ui->screen_time);
    lv_label_set_text(ui->screen_time_label_battery, "");
    lv_label_set_long_mode(ui->screen_time_label_battery, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_battery, 181, 359);
    lv_obj_set_size(ui->screen_time_label_battery, 109, 16);

    //Write style for screen_time_label_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_battery, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_battery, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_battery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_tabview_1
    ui->screen_time_tabview_1 = lv_tabview_create(ui->screen_time, LV_DIR_TOP, 0);
    lv_obj_set_pos(ui->screen_time_tabview_1, 0, 0);
    lv_obj_set_size(ui->screen_time_tabview_1, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_time_tabview_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_time_tabview_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_time_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_tabview_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_time_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_time_tabview_1_extra_btnm_main_default
    static lv_style_t style_screen_time_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_screen_time_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_screen_time_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_screen_time_tabview_1_extra_btnm_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_time_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_time_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_screen_time_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_time_tabview_1), &style_screen_time_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_time_tabview_1_extra_btnm_items_default
    static lv_style_t style_screen_time_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_screen_time_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_screen_time_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_screen_time_tabview_1_extra_btnm_items_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_time_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_time_tabview_1), &style_screen_time_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_time_tabview_1_extra_btnm_items_checked
    static lv_style_t style_screen_time_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_screen_time_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_screen_time_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_text_font(&style_screen_time_tabview_1_extra_btnm_items_checked, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_time_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_screen_time_tabview_1_extra_btnm_items_checked, 4);
    lv_style_set_border_opa(&style_screen_time_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_color(&style_screen_time_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_border_side(&style_screen_time_tabview_1_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_screen_time_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_screen_time_tabview_1_extra_btnm_items_checked, 60);
    lv_style_set_bg_color(&style_screen_time_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_time_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->screen_time_tabview_1), &style_screen_time_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes time
    ui->screen_time_tabview_1_tab_1 = lv_tabview_add_tab(ui->screen_time_tabview_1,"time");
    lv_obj_t * screen_time_tabview_1_tab_1_label = lv_label_create(ui->screen_time_tabview_1_tab_1);
    lv_label_set_text(screen_time_tabview_1_tab_1_label, "");

    //Write codes info
    ui->screen_time_tabview_1_tab_2 = lv_tabview_add_tab(ui->screen_time_tabview_1,"info");
    lv_obj_t * screen_time_tabview_1_tab_2_label = lv_label_create(ui->screen_time_tabview_1_tab_2);
    lv_label_set_text(screen_time_tabview_1_tab_2_label, "");

    //Write codes screen_time_cont_info
    ui->screen_time_cont_info = lv_obj_create(ui->screen_time_tabview_1_tab_2);
    lv_obj_set_pos(ui->screen_time_cont_info, -20, -20);
    lv_obj_set_size(ui->screen_time_cont_info, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_time_cont_info, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_time_cont_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_cont_info, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_time_cont_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_time_cont_info, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_time_cont_info, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_cont_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_touch
    ui->screen_time_label_touch = lv_label_create(ui->screen_time_cont_info);
    lv_label_set_text(ui->screen_time_label_touch, "Touch: x: -1, y: -1");
    lv_label_set_long_mode(ui->screen_time_label_touch, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_touch, 104, 233);
    lv_obj_set_size(ui->screen_time_label_touch, 255, 22);

    //Write style for screen_time_label_touch, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_touch, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_touch, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_touch, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_touch, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_touch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_charge
    ui->screen_time_label_charge = lv_label_create(ui->screen_time_cont_info);
    lv_label_set_text(ui->screen_time_label_charge, "bat charging");
    lv_label_set_long_mode(ui->screen_time_label_charge, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_charge, 173, 304);
    lv_obj_set_size(ui->screen_time_label_charge, 121, 18);

    //Write style for screen_time_label_charge, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_charge, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_charge, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_charge, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_charge, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_accel
    ui->screen_time_label_accel = lv_label_create(ui->screen_time_cont_info);
    lv_label_set_text(ui->screen_time_label_accel, "Accel: x: -2520, y: 7341, z: 14396");
    lv_label_set_long_mode(ui->screen_time_label_accel, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_accel, 85, 200);
    lv_obj_set_size(ui->screen_time_label_accel, 293, 25);

    //Write style for screen_time_label_accel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_accel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_accel, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_accel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_accel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_gyro
    ui->screen_time_label_gyro = lv_label_create(ui->screen_time_cont_info);
    lv_label_set_text(ui->screen_time_label_gyro, "Gyro: x: 3, y: -1, z: 0");
    lv_label_set_long_mode(ui->screen_time_label_gyro, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_gyro, 101, 168);
    lv_obj_set_size(ui->screen_time_label_gyro, 255, 22);

    //Write style for screen_time_label_gyro, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_gyro, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_gyro, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_gyro, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_gyro, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_current
    ui->screen_time_label_current = lv_label_create(ui->screen_time_cont_info);
    lv_label_set_text(ui->screen_time_label_current, "current: 0mA");
    lv_label_set_long_mode(ui->screen_time_label_current, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_current, 173, 333);
    lv_obj_set_size(ui->screen_time_label_current, 121, 18);

    //Write style for screen_time_label_current, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_current, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_current, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_current, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_current, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes vibra
    ui->screen_time_tabview_1_tab_3 = lv_tabview_add_tab(ui->screen_time_tabview_1,"vibra");
    lv_obj_t * screen_time_tabview_1_tab_3_label = lv_label_create(ui->screen_time_tabview_1_tab_3);
    lv_label_set_text(screen_time_tabview_1_tab_3_label, "");

    //Write codes screen_time_cont_vibra
    ui->screen_time_cont_vibra = lv_obj_create(ui->screen_time_tabview_1_tab_3);
    lv_obj_set_pos(ui->screen_time_cont_vibra, -20, -20);
    lv_obj_set_size(ui->screen_time_cont_vibra, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_time_cont_vibra, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_time_cont_vibra, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_cont_vibra, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_time_cont_vibra, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_time_cont_vibra, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_time_cont_vibra, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_cont_vibra, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_slider_time
    ui->screen_time_slider_time = lv_slider_create(ui->screen_time_cont_vibra);
    lv_slider_set_range(ui->screen_time_slider_time, 0, 100);
    lv_slider_set_mode(ui->screen_time_slider_time, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_time_slider_time, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_time_slider_time, 204, 94);
    lv_obj_set_size(ui->screen_time_slider_time, 12, 250);

    //Write style for screen_time_slider_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_slider_time, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_slider_time, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_slider_time, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_slider_time, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_time_slider_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_slider_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_time_slider_time, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_slider_time, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_slider_time, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_slider_time, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_slider_time, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_time_slider_time, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_slider_time, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_slider_time, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_slider_time, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_slider_time, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_time_slider_intensity
    ui->screen_time_slider_intensity = lv_slider_create(ui->screen_time_cont_vibra);
    lv_slider_set_range(ui->screen_time_slider_intensity, 0, 100);
    lv_slider_set_mode(ui->screen_time_slider_intensity, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_time_slider_intensity, 100, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_time_slider_intensity, 247, 94);
    lv_obj_set_size(ui->screen_time_slider_intensity, 12, 250);

    //Write style for screen_time_slider_intensity, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_slider_intensity, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_slider_intensity, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_slider_intensity, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_slider_intensity, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_time_slider_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_slider_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_time_slider_intensity, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_slider_intensity, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_slider_intensity, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_slider_intensity, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_slider_intensity, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_time_slider_intensity, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_slider_intensity, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_slider_intensity, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_slider_intensity, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_slider_intensity, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_time_label_time
    ui->screen_time_label_time = lv_label_create(ui->screen_time_cont_vibra);
    lv_label_set_text(ui->screen_time_label_time, "vibration time\n50ms");
    lv_label_set_long_mode(ui->screen_time_label_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_time, 69, 224);
    lv_obj_set_size(ui->screen_time_label_time, 132, 40);

    //Write style for screen_time_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_intensity
    ui->screen_time_label_intensity = lv_label_create(ui->screen_time_cont_vibra);
    lv_label_set_text(ui->screen_time_label_intensity, "vibration intensity\n100%");
    lv_label_set_long_mode(ui->screen_time_label_intensity, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_intensity, 266, 224);
    lv_obj_set_size(ui->screen_time_label_intensity, 155, 37);

    //Write style for screen_time_label_intensity, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_intensity, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_intensity, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_intensity, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_intensity, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_intensity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes voice
    ui->screen_time_tabview_1_tab_4 = lv_tabview_add_tab(ui->screen_time_tabview_1,"voice");
    lv_obj_t * screen_time_tabview_1_tab_4_label = lv_label_create(ui->screen_time_tabview_1_tab_4);
    lv_label_set_text(screen_time_tabview_1_tab_4_label, "");

    //Write codes screen_time_cont_voice
    ui->screen_time_cont_voice = lv_obj_create(ui->screen_time_tabview_1_tab_4);
    lv_obj_set_pos(ui->screen_time_cont_voice, -20, -20);
    lv_obj_set_size(ui->screen_time_cont_voice, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_time_cont_voice, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_time_cont_voice, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_cont_voice, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_time_cont_voice, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_time_cont_voice, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_time_cont_voice, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_cont_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_btn_record
    ui->screen_time_btn_record = lv_btn_create(ui->screen_time_cont_voice);
    ui->screen_time_btn_record_label = lv_label_create(ui->screen_time_btn_record);
    lv_label_set_text(ui->screen_time_btn_record_label, "record");
    lv_label_set_long_mode(ui->screen_time_btn_record_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_time_btn_record_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_time_btn_record, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_time_btn_record_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_time_btn_record, 158, 153);
    lv_obj_set_size(ui->screen_time_btn_record, 148, 50);

    //Write style for screen_time_btn_record, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_btn_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_btn_record, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_btn_record, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_time_btn_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_btn_record, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_btn_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_btn_record, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_btn_record, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_btn_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_btn_record, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_record
    ui->screen_time_label_record = lv_label_create(ui->screen_time_cont_voice);
    lv_label_set_text(ui->screen_time_label_record, "0.0s");
    lv_label_set_long_mode(ui->screen_time_label_record, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_record, 158, 120);
    lv_obj_set_size(ui->screen_time_label_record, 159, 20);

    //Write style for screen_time_label_record, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_record, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_record, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_record, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_label_play
    ui->screen_time_label_play = lv_label_create(ui->screen_time_cont_voice);
    lv_label_set_text(ui->screen_time_label_play, "0.0s");
    lv_label_set_long_mode(ui->screen_time_label_play, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_time_label_play, 158, 228);
    lv_obj_set_size(ui->screen_time_label_play, 159, 20);

    //Write style for screen_time_label_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_label_play, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_label_play, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_label_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_label_play, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_btn_play
    ui->screen_time_btn_play = lv_btn_create(ui->screen_time_cont_voice);
    ui->screen_time_btn_play_label = lv_label_create(ui->screen_time_btn_play);
    lv_label_set_text(ui->screen_time_btn_play_label, "play");
    lv_label_set_long_mode(ui->screen_time_btn_play_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_time_btn_play_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_time_btn_play, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_time_btn_play_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_time_btn_play, 158, 265);
    lv_obj_set_size(ui->screen_time_btn_play, 148, 50);

    //Write style for screen_time_btn_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_btn_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_btn_play, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_btn_play, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_time_btn_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_time_btn_play, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_btn_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_time_btn_play, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_btn_play, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_btn_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_time_btn_play, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_time_analog_clock_1
    static bool screen_time_analog_clock_1_timer_enabled = false;
    ui->screen_time_analog_clock_1 = lv_analogclock_create(ui->screen_time);
    lv_analogclock_hide_digits(ui->screen_time_analog_clock_1, true);
    lv_analogclock_set_major_ticks(ui->screen_time_analog_clock_1, 2, 8, lv_color_hex(0x555555), 10);
    lv_analogclock_set_ticks(ui->screen_time_analog_clock_1, 2, 5, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_img(ui->screen_time_analog_clock_1, &_img_clockwise_hour_alpha_18x98, 6, 0);
    lv_analogclock_set_min_needle_img(ui->screen_time_analog_clock_1, &_img_clockwise_min_alpha_18x157, 10, 0);
    lv_analogclock_set_sec_needle_img(ui->screen_time_analog_clock_1, &_img_clockwise_sec_alpha_31x180, 15, 24);
    lv_analogclock_set_time(ui->screen_time_analog_clock_1, screen_time_analog_clock_1_hour_value, screen_time_analog_clock_1_min_value,screen_time_analog_clock_1_sec_value);
    // create timer
    if (!screen_time_analog_clock_1_timer_enabled) {
        lv_timer_create(screen_time_analog_clock_1_timer, 1000, NULL);
        screen_time_analog_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->screen_time_analog_clock_1, 0, 0);
    lv_obj_set_size(ui->screen_time_analog_clock_1, 466, 466);

    //Write style for screen_time_analog_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_time_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_time_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_time_analog_clock_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_time_analog_clock_1, lv_color_hex(0x4f4f4f), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_time_analog_clock_1, &lv_font_Acme_Regular_22, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_time_analog_clock_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for screen_time_analog_clock_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_time_analog_clock_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_time_analog_clock_1, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_time_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //The custom code of screen_time.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_time);

    //Init events for screen.
    events_init_screen_time(ui);
}

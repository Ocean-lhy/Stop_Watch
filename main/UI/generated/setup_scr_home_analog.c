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



int home_analog_analog_clock_1_hour_value = 9;
int home_analog_analog_clock_1_min_value = 37;
int home_analog_analog_clock_1_sec_value = 10;
void setup_scr_home_analog(lv_ui *ui)
{
    //Write codes home_analog
    ui->home_analog = lv_obj_create(NULL);
    lv_obj_set_size(ui->home_analog, 466, 466);
    lv_obj_set_scrollbar_mode(ui->home_analog, LV_SCROLLBAR_MODE_OFF);

    //Write style for home_analog, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->home_analog, &_img_bg_analog_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->home_analog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->home_analog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_battery_arc
    ui->home_analog_battery_arc = lv_arc_create(ui->home_analog);
    lv_arc_set_mode(ui->home_analog_battery_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->home_analog_battery_arc, 0, 100);
    lv_arc_set_bg_angles(ui->home_analog_battery_arc, 238, 300);
    lv_arc_set_value(ui->home_analog_battery_arc, 70);
    lv_arc_set_rotation(ui->home_analog_battery_arc, 0);
    lv_obj_set_pos(ui->home_analog_battery_arc, 58, 5);
    lv_obj_set_size(ui->home_analog_battery_arc, 388, 356);

    //Write style for home_analog_battery_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog_battery_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_analog_battery_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->home_analog_battery_arc, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_analog_battery_arc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_analog_battery_arc, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_battery_arc, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_battery_arc, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_battery_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_battery_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_battery_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_battery_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_analog_battery_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->home_analog_battery_arc, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_analog_battery_arc, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_analog_battery_arc, lv_color_hex(0x1000ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for home_analog_battery_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog_battery_arc, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_analog_battery_arc, lv_color_hex(0x1000ff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_analog_battery_arc, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->home_analog_battery_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes home_analog_step_arc
    ui->home_analog_step_arc = lv_arc_create(ui->home_analog);
    lv_arc_set_mode(ui->home_analog_step_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->home_analog_step_arc, 0, 100);
    lv_arc_set_bg_angles(ui->home_analog_step_arc, 60, 120);
    lv_arc_set_value(ui->home_analog_step_arc, 70);
    lv_arc_set_rotation(ui->home_analog_step_arc, 0);
    lv_obj_set_pos(ui->home_analog_step_arc, 55, 99);
    lv_obj_set_size(ui->home_analog_step_arc, 383, 356);

    //Write style for home_analog_step_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->home_analog_step_arc, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_analog_step_arc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_analog_step_arc, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_step_arc, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_step_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_analog_step_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->home_analog_step_arc, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_analog_step_arc, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_analog_step_arc, lv_color_hex(0xFF4818), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for home_analog_step_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog_step_arc, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_analog_step_arc, lv_color_hex(0xFF4818), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_analog_step_arc, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->home_analog_step_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes home_analog_analog_clock_1
    static bool home_analog_analog_clock_1_timer_enabled = false;
    ui->home_analog_analog_clock_1 = lv_analogclock_create(ui->home_analog);
    lv_analogclock_hide_digits(ui->home_analog_analog_clock_1, true);
    lv_analogclock_set_major_ticks(ui->home_analog_analog_clock_1, 2, 0, lv_color_hex(0x555555), 10);
    lv_analogclock_set_ticks(ui->home_analog_analog_clock_1, 6, 0, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_img(ui->home_analog_analog_clock_1, &_img_clockwise_hour_alpha_18x98, 6, 0);
    lv_analogclock_set_min_needle_img(ui->home_analog_analog_clock_1, &_img_clockwise_min_alpha_18x157, 10, 0);
    lv_analogclock_set_sec_needle_img(ui->home_analog_analog_clock_1, &_img_clockwise_sec_alpha_31x180, 15, 24);
    lv_analogclock_set_time(ui->home_analog_analog_clock_1, home_analog_analog_clock_1_hour_value, home_analog_analog_clock_1_min_value,home_analog_analog_clock_1_sec_value);
    // create timer
    if (!home_analog_analog_clock_1_timer_enabled) {
        lv_timer_create(home_analog_analog_clock_1_timer, 1000, NULL);
        home_analog_analog_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->home_analog_analog_clock_1, 0, 0);
    lv_obj_set_size(ui->home_analog_analog_clock_1, 466, 466);

    //Write style for home_analog_analog_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog_analog_clock_1, 39, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_analog_analog_clock_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_analog_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_analog_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_analog_analog_clock_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->home_analog_analog_clock_1, lv_color_hex(0xff0000), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_analog_analog_clock_1, &lv_font_montserratMedium_14, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_analog_analog_clock_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for home_analog_analog_clock_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_analog_analog_clock_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_analog_analog_clock_1, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_analog_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes home_analog_sport_icon
    ui->home_analog_sport_icon = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_sport_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_sport_icon, &_icn_sport_alpha_14x28);
    lv_img_set_pivot(ui->home_analog_sport_icon, 50,50);
    lv_img_set_angle(ui->home_analog_sport_icon, 0);
    lv_obj_set_pos(ui->home_analog_sport_icon, 376, 121);
    lv_obj_set_size(ui->home_analog_sport_icon, 14, 28);

    //Write style for home_analog_sport_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_sport_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_sport_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_sport_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_sport_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_nxp_log
    ui->home_analog_nxp_log = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_nxp_log, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_nxp_log, &_img_nxp_alpha_77x23);
    lv_img_set_pivot(ui->home_analog_nxp_log, 50,50);
    lv_img_set_angle(ui->home_analog_nxp_log, 0);
    lv_obj_set_pos(ui->home_analog_nxp_log, 479, 221);
    lv_obj_set_size(ui->home_analog_nxp_log, 77, 23);

    //Write style for home_analog_nxp_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_nxp_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_nxp_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_nxp_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_nxp_log, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_step_icon
    ui->home_analog_step_icon = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_step_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_step_icon, &_icn_step_red_alpha_20x24);
    lv_img_set_pivot(ui->home_analog_step_icon, 50,50);
    lv_img_set_angle(ui->home_analog_step_icon, 0);
    lv_obj_set_pos(ui->home_analog_step_icon, 185, 401);
    lv_obj_set_size(ui->home_analog_step_icon, 20, 24);

    //Write style for home_analog_step_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_step_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_step_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_step_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_step_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_step_text
    ui->home_analog_step_text = lv_label_create(ui->home_analog);
    lv_label_set_text(ui->home_analog_step_text, "1526");
    lv_label_set_long_mode(ui->home_analog_step_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_analog_step_text, 221, 401);
    lv_obj_set_size(ui->home_analog_step_text, 70, 24);

    //Write style for home_analog_step_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_analog_step_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_analog_step_text, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_analog_step_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_analog_step_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_analog_step_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_step_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_temp_text
    ui->home_analog_temp_text = lv_label_create(ui->home_analog);
    lv_label_set_text(ui->home_analog_temp_text, "26°");
    lv_label_set_long_mode(ui->home_analog_temp_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_analog_temp_text, 77, 294);
    lv_obj_set_size(ui->home_analog_temp_text, 55, 24);

    //Write style for home_analog_temp_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_analog_temp_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_analog_temp_text, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_analog_temp_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_analog_temp_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_analog_temp_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_temp_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_weather_icon
    ui->home_analog_weather_icon = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_weather_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_weather_icon, &_icn_weather_1_alpha_48x39);
    lv_img_set_pivot(ui->home_analog_weather_icon, 50,50);
    lv_img_set_angle(ui->home_analog_weather_icon, 0);
    lv_obj_set_pos(ui->home_analog_weather_icon, 67, 247);
    lv_obj_set_size(ui->home_analog_weather_icon, 48, 39);

    //Write style for home_analog_weather_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_weather_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_analog_weather_icon, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_weather_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_weather_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_weather_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_week_day
    ui->home_analog_week_day = lv_label_create(ui->home_analog);
    lv_label_set_text(ui->home_analog_week_day, "WED");
    lv_label_set_long_mode(ui->home_analog_week_day, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_analog_week_day, 40, 169);
    lv_obj_set_size(ui->home_analog_week_day, 79, 29);

    //Write style for home_analog_week_day, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_analog_week_day, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_analog_week_day, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_analog_week_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_analog_week_day, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_analog_week_day, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_week_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_date_text
    ui->home_analog_date_text = lv_label_create(ui->home_analog);
    lv_label_set_text(ui->home_analog_date_text, "05/15");
    lv_label_set_long_mode(ui->home_analog_date_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_analog_date_text, 40, 131);
    lv_obj_set_size(ui->home_analog_date_text, 87, 24);

    //Write style for home_analog_date_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_analog_date_text, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_analog_date_text, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_analog_date_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_analog_date_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_analog_date_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_sport_text
    ui->home_analog_sport_text = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_sport_text, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_sport_text, &_text_sport_alpha_59x59);
    lv_img_set_pivot(ui->home_analog_sport_text, 50,50);
    lv_img_set_angle(ui->home_analog_sport_text, 30);
    lv_obj_set_pos(ui->home_analog_sport_text, 381, 90);
    lv_obj_set_size(ui->home_analog_sport_text, 59, 59);

    //Write style for home_analog_sport_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_sport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_sport_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_sport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_sport_text, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_message_icon
    ui->home_analog_message_icon = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_message_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_message_icon, &_icn_message_alpha_29x29);
    lv_img_set_pivot(ui->home_analog_message_icon, 50,50);
    lv_img_set_angle(ui->home_analog_message_icon, 0);
    lv_obj_set_pos(ui->home_analog_message_icon, 354, 319);
    lv_obj_set_size(ui->home_analog_message_icon, 29, 29);

    //Write style for home_analog_message_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_message_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_message_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_message_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_message_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_battery_icon
    ui->home_analog_battery_icon = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_battery_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_battery_icon, &_icn_flash_blue_alpha_20x24);
    lv_img_set_pivot(ui->home_analog_battery_icon, 50,50);
    lv_img_set_angle(ui->home_analog_battery_icon, 0);
    lv_obj_set_pos(ui->home_analog_battery_icon, 185, 41);
    lv_obj_set_size(ui->home_analog_battery_icon, 20, 24);

    //Write style for home_analog_battery_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_battery_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_battery_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_battery_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_battery_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_battery_text
    ui->home_analog_battery_text = lv_label_create(ui->home_analog);
    lv_label_set_text(ui->home_analog_battery_text, "86%");
    lv_label_set_long_mode(ui->home_analog_battery_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_analog_battery_text, 221, 41);
    lv_obj_set_size(ui->home_analog_battery_text, 70, 24);
    lv_obj_add_flag(ui->home_analog_battery_text, LV_OBJ_FLAG_CLICKABLE);

    //Write style for home_analog_battery_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_analog_battery_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_analog_battery_text, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_analog_battery_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_analog_battery_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_analog_battery_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_analog_battery_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_dot_list
    ui->home_analog_dot_list = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_dot_list, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_dot_list, &_img_menu_alpha_13x139);
    lv_img_set_pivot(ui->home_analog_dot_list, 50,50);
    lv_img_set_angle(ui->home_analog_dot_list, 0);
    lv_obj_set_pos(ui->home_analog_dot_list, 433, 166);
    lv_obj_set_size(ui->home_analog_dot_list, 13, 139);

    //Write style for home_analog_dot_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_dot_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_dot_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_dot_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_dot_list, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_message_text
    ui->home_analog_message_text = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_message_text, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_message_text, &_text_message_alpha_83x83);
    lv_img_set_pivot(ui->home_analog_message_text, 50,50);
    lv_img_set_angle(ui->home_analog_message_text, -50);
    lv_obj_set_pos(ui->home_analog_message_text, 350, 319);
    lv_obj_set_size(ui->home_analog_message_text, 83, 83);

    //Write style for home_analog_message_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_message_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_message_text, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_analog_img_dot
    ui->home_analog_img_dot = lv_img_create(ui->home_analog);
    lv_obj_add_flag(ui->home_analog_img_dot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_analog_img_dot, &_dot_alpha_9x9);
    lv_img_set_pivot(ui->home_analog_img_dot, 50,50);
    lv_img_set_angle(ui->home_analog_img_dot, 0);
    lv_obj_set_pos(ui->home_analog_img_dot, 433, 166);
    lv_obj_set_size(ui->home_analog_img_dot, 9, 9);

    //Write style for home_analog_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_analog_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_analog_img_dot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_analog_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_analog_img_dot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of home_analog.


    //Update current screen layout.
    lv_obj_update_layout(ui->home_analog);

    //Init events for screen.
    events_init_home_analog(ui);
}

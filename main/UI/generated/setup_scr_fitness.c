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



void setup_scr_fitness(lv_ui *ui)
{
    //Write codes fitness
    ui->fitness = lv_obj_create(NULL);
    lv_obj_set_size(ui->fitness, 466, 466);
    lv_obj_set_scrollbar_mode(ui->fitness, LV_SCROLLBAR_MODE_OFF);

    //Write style for fitness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->fitness, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->fitness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->fitness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_home
    ui->fitness_home = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->fitness_home, 50,50);
    lv_img_set_angle(ui->fitness_home, 0);
    lv_obj_set_pos(ui->fitness_home, 391, 307);
    lv_obj_set_size(ui->fitness_home, 42, 57);
    lv_obj_add_flag(ui->fitness_home, LV_OBJ_FLAG_FLOATING);

    //Write style for fitness_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_start_icon
    ui->fitness_start_icon = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_start_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_start_icon, &_text_start_stop_alpha_51x67);
    lv_img_set_pivot(ui->fitness_start_icon, 50,50);
    lv_img_set_angle(ui->fitness_start_icon, 80);
    lv_obj_set_pos(ui->fitness_start_icon, 386, 87);
    lv_obj_set_size(ui->fitness_start_icon, 51, 67);
    lv_obj_add_flag(ui->fitness_start_icon, LV_OBJ_FLAG_FLOATING);

    //Write style for fitness_start_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_start_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_start_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_start_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_start_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_title
    ui->fitness_title = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_title, "Fitness");
    lv_label_set_long_mode(ui->fitness_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_title, 0, -97);
    lv_obj_set_size(ui->fitness_title, 466, 89);
    lv_obj_add_flag(ui->fitness_title, LV_OBJ_FLAG_FLOATING);

    //Write style for fitness_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->fitness_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->fitness_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->fitness_title, lv_color_hex(0x109d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->fitness_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_calorie_arc
    ui->fitness_calorie_arc = lv_arc_create(ui->fitness);
    lv_arc_set_mode(ui->fitness_calorie_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->fitness_calorie_arc, 0, 125);
    lv_arc_set_bg_angles(ui->fitness_calorie_arc, 90, 230);
    lv_arc_set_value(ui->fitness_calorie_arc, 70);
    lv_arc_set_rotation(ui->fitness_calorie_arc, 0);
    lv_obj_set_pos(ui->fitness_calorie_arc, -217, 58);
    lv_obj_set_size(ui->fitness_calorie_arc, 380, 380);

    //Write style for fitness_calorie_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_calorie_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->fitness_calorie_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->fitness_calorie_arc, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_calorie_arc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_calorie_arc, lv_color_hex(0x6c6967), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_calorie_arc, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_calorie_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_calorie_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_calorie_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_calorie_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_calorie_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for fitness_calorie_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->fitness_calorie_arc, 16, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_calorie_arc, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_calorie_arc, lv_color_hex(0xEEC200), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for fitness_calorie_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_calorie_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->fitness_calorie_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes fitness_distance_arc
    ui->fitness_distance_arc = lv_arc_create(ui->fitness);
    lv_arc_set_mode(ui->fitness_distance_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->fitness_distance_arc, 0, 125);
    lv_arc_set_bg_angles(ui->fitness_distance_arc, 90, 230);
    lv_arc_set_value(ui->fitness_distance_arc, 70);
    lv_arc_set_rotation(ui->fitness_distance_arc, 0);
    lv_obj_set_pos(ui->fitness_distance_arc, -187, 86);
    lv_obj_set_size(ui->fitness_distance_arc, 320, 320);

    //Write style for fitness_distance_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_distance_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->fitness_distance_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->fitness_distance_arc, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_distance_arc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_distance_arc, lv_color_hex(0x6c6967), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_distance_arc, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_distance_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_distance_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_distance_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_distance_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_distance_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for fitness_distance_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->fitness_distance_arc, 16, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_distance_arc, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_distance_arc, lv_color_hex(0x00ce10), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for fitness_distance_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_distance_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->fitness_distance_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes fitness_duration_arc
    ui->fitness_duration_arc = lv_arc_create(ui->fitness);
    lv_arc_set_mode(ui->fitness_duration_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->fitness_duration_arc, 0, 125);
    lv_arc_set_bg_angles(ui->fitness_duration_arc, 97, 229);
    lv_arc_set_value(ui->fitness_duration_arc, 70);
    lv_arc_set_rotation(ui->fitness_duration_arc, 0);
    lv_obj_set_pos(ui->fitness_duration_arc, -150, 117);
    lv_obj_set_size(ui->fitness_duration_arc, 261, 261);

    //Write style for fitness_duration_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_duration_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->fitness_duration_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->fitness_duration_arc, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_duration_arc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_duration_arc, lv_color_hex(0x6c6967), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_duration_arc, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_duration_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_duration_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_duration_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_duration_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_duration_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for fitness_duration_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->fitness_duration_arc, 15, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_duration_arc, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_duration_arc, lv_color_hex(0x0a74b1), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for fitness_duration_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_duration_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->fitness_duration_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes fitness_pluse_arc
    ui->fitness_pluse_arc = lv_arc_create(ui->fitness);
    lv_arc_set_mode(ui->fitness_pluse_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->fitness_pluse_arc, 0, 125);
    lv_arc_set_bg_angles(ui->fitness_pluse_arc, 90, 228);
    lv_arc_set_value(ui->fitness_pluse_arc, 70);
    lv_arc_set_rotation(ui->fitness_pluse_arc, 0);
    lv_obj_set_pos(ui->fitness_pluse_arc, -121, 147);
    lv_obj_set_size(ui->fitness_pluse_arc, 202, 202);

    //Write style for fitness_pluse_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_pluse_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->fitness_pluse_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->fitness_pluse_arc, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_pluse_arc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_pluse_arc, lv_color_hex(0x6c6967), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_pluse_arc, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_pluse_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_pluse_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_pluse_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_pluse_arc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_pluse_arc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for fitness_pluse_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->fitness_pluse_arc, 15, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->fitness_pluse_arc, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->fitness_pluse_arc, lv_color_hex(0xed0b6d), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for fitness_pluse_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->fitness_pluse_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->fitness_pluse_arc, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes fitness_pluse_icon
    ui->fitness_pluse_icon = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_pluse_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_pluse_icon, &_icn_small_pulse_alpha_29x26);
    lv_img_set_pivot(ui->fitness_pluse_icon, 50,50);
    lv_img_set_angle(ui->fitness_pluse_icon, 0);
    lv_obj_set_pos(ui->fitness_pluse_icon, 233, 131);
    lv_obj_set_size(ui->fitness_pluse_icon, 29, 26);

    //Write style for fitness_pluse_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_pluse_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_pluse_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_pluse_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_pluse_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_pulse_text
    ui->fitness_pulse_text = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_pulse_text, "PULSE");
    lv_label_set_long_mode(ui->fitness_pulse_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_pulse_text, 280, 111);
    lv_obj_set_size(ui->fitness_pulse_text, 98, 20);

    //Write style for fitness_pulse_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_pulse_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_pulse_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_pulse_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_pulse_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_pulse_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_pulse_value
    ui->fitness_pulse_value = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_pulse_value, "128");
    lv_label_set_long_mode(ui->fitness_pulse_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_pulse_value, 280, 131);
    lv_obj_set_size(ui->fitness_pulse_value, 76, 36);

    //Write style for fitness_pulse_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_pulse_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_pulse_value, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_pulse_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_pulse_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_pulse_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_pulse_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_duration_icon
    ui->fitness_duration_icon = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_duration_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_duration_icon, &_icn_small_time_alpha_29x29);
    lv_img_set_pivot(ui->fitness_duration_icon, 50,50);
    lv_img_set_angle(ui->fitness_duration_icon, 0);
    lv_obj_set_pos(ui->fitness_duration_icon, 233, 215);
    lv_obj_set_size(ui->fitness_duration_icon, 29, 29);

    //Write style for fitness_duration_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_duration_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_duration_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_duration_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_duration_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_distance_value
    ui->fitness_distance_value = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_distance_value, "1223");
    lv_label_set_long_mode(ui->fitness_distance_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_distance_value, 280, 294);
    lv_obj_set_size(ui->fitness_distance_value, 99, 36);

    //Write style for fitness_distance_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_distance_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_distance_value, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_distance_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_distance_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_distance_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_duration_text
    ui->fitness_duration_text = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_duration_text, "DURATION");
    lv_label_set_long_mode(ui->fitness_duration_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_duration_text, 280, 190);
    lv_obj_set_size(ui->fitness_duration_text, 127, 20);

    //Write style for fitness_duration_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_duration_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_duration_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_duration_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_duration_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_duration_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_distance_icon
    ui->fitness_distance_icon = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_distance_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_distance_icon, &_icn_small_pos_alpha_22x29);
    lv_img_set_pivot(ui->fitness_distance_icon, 50,50);
    lv_img_set_angle(ui->fitness_distance_icon, 0);
    lv_obj_set_pos(ui->fitness_distance_icon, 233, 294);
    lv_obj_set_size(ui->fitness_distance_icon, 22, 29);

    //Write style for fitness_distance_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_distance_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_distance_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_distance_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_distance_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_duration_value
    ui->fitness_duration_value = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_duration_value, "02:53");
    lv_label_set_long_mode(ui->fitness_duration_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_duration_value, 280, 211);
    lv_obj_set_size(ui->fitness_duration_value, 111, 36);

    //Write style for fitness_duration_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_duration_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_duration_value, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_duration_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_duration_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_duration_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_distance_text
    ui->fitness_distance_text = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_distance_text, "DISTANCE");
    lv_label_set_long_mode(ui->fitness_distance_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_distance_text, 280, 274);
    lv_obj_set_size(ui->fitness_distance_text, 128, 20);

    //Write style for fitness_distance_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_distance_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_distance_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_distance_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_distance_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_calorie_icon
    ui->fitness_calorie_icon = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_calorie_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_calorie_icon, &_icn_small_burn_alpha_24x28);
    lv_img_set_pivot(ui->fitness_calorie_icon, 50,50);
    lv_img_set_angle(ui->fitness_calorie_icon, 0);
    lv_obj_set_pos(ui->fitness_calorie_icon, 233, 379);
    lv_obj_set_size(ui->fitness_calorie_icon, 24, 28);

    //Write style for fitness_calorie_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_calorie_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_calorie_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_calorie_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_calorie_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_calorie_value
    ui->fitness_calorie_value = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_calorie_value, "235");
    lv_label_set_long_mode(ui->fitness_calorie_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_calorie_value, 280, 379);
    lv_obj_set_size(ui->fitness_calorie_value, 76, 36);

    //Write style for fitness_calorie_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_calorie_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_calorie_value, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_calorie_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_calorie_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_calorie_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_calorie_text
    ui->fitness_calorie_text = lv_label_create(ui->fitness);
    lv_label_set_text(ui->fitness_calorie_text, "CALORIE");
    lv_label_set_long_mode(ui->fitness_calorie_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->fitness_calorie_text, 280, 359);
    lv_obj_set_size(ui->fitness_calorie_text, 108, 20);

    //Write style for fitness_calorie_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->fitness_calorie_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->fitness_calorie_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->fitness_calorie_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->fitness_calorie_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->fitness_calorie_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_img_menu
    ui->fitness_img_menu = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_img_menu, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_img_menu, &_img_menu_alpha_13x118);
    lv_img_set_pivot(ui->fitness_img_menu, 50,50);
    lv_img_set_angle(ui->fitness_img_menu, 0);
    lv_obj_set_pos(ui->fitness_img_menu, 433, 173);
    lv_obj_set_size(ui->fitness_img_menu, 13, 118);

    //Write style for fitness_img_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_img_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_img_menu, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes fitness_img_dot
    ui->fitness_img_dot = lv_img_create(ui->fitness);
    lv_obj_add_flag(ui->fitness_img_dot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->fitness_img_dot, &_dot_alpha_9x9);
    lv_img_set_pivot(ui->fitness_img_dot, 50,50);
    lv_img_set_angle(ui->fitness_img_dot, 0);
    lv_obj_set_pos(ui->fitness_img_dot, 437, 197);
    lv_obj_set_size(ui->fitness_img_dot, 9, 9);

    //Write style for fitness_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->fitness_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->fitness_img_dot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->fitness_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->fitness_img_dot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of fitness.


    //Update current screen layout.
    lv_obj_update_layout(ui->fitness);

    //Init events for screen.
    events_init_fitness(ui);
}

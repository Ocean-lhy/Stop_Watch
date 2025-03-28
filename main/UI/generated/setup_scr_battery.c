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



void setup_scr_battery(lv_ui *ui)
{
    //Write codes battery
    ui->battery = lv_obj_create(NULL);
    lv_obj_set_size(ui->battery, 466, 466);
    lv_obj_set_scrollbar_mode(ui->battery, LV_SCROLLBAR_MODE_OFF);

    //Write style for battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->battery, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_title
    ui->battery_title = lv_label_create(ui->battery);
    lv_label_set_text(ui->battery_title, "Battery\n");
    lv_label_set_long_mode(ui->battery_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_title, 0, -101);
    lv_obj_set_size(ui->battery_title, 466, 89);
    lv_obj_add_flag(ui->battery_title, LV_OBJ_FLAG_FLOATING);

    //Write style for battery_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->battery_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->battery_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->battery_title, lv_color_hex(0xD5D2D5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->battery_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_setting_info
    ui->battery_setting_info = lv_obj_create(ui->battery);
    lv_obj_set_pos(ui->battery_setting_info, 28, 242);
    lv_obj_set_size(ui->battery_setting_info, 410, 388);
    lv_obj_set_scrollbar_mode(ui->battery_setting_info, LV_SCROLLBAR_MODE_OFF);

    //Write style for battery_setting_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_setting_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_label_10
    ui->battery_label_10 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_10, "Battery usage\n");
    lv_label_set_long_mode(ui->battery_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_10, 80, 7);
    lv_obj_set_size(ui->battery_label_10, 225, 22);

    //Write style for battery_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_10, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_label_11
    ui->battery_label_11 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_11, "Battery level\n");
    lv_label_set_long_mode(ui->battery_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_11, 9, 47);
    lv_obj_set_size(ui->battery_label_11, 146, 21);

    //Write style for battery_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_11, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_11, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_img_1
    ui->battery_img_1 = lv_img_create(ui->battery_setting_info);
    lv_obj_add_flag(ui->battery_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->battery_img_1, &_img_chart_battery_alpha_383x98);
    lv_img_set_pivot(ui->battery_img_1, 50,50);
    lv_img_set_angle(ui->battery_img_1, 0);
    lv_obj_set_pos(ui->battery_img_1, 10, 78);
    lv_obj_set_size(ui->battery_img_1, 383, 98);

    //Write style for battery_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->battery_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->battery_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->battery_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_label_12
    ui->battery_label_12 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_12, "Battery usage by app\n");
    lv_label_set_long_mode(ui->battery_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_12, 84, 205);
    lv_obj_set_size(ui->battery_label_12, 225, 27);

    //Write style for battery_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_12, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_img_2
    ui->battery_img_2 = lv_img_create(ui->battery_setting_info);
    lv_obj_add_flag(ui->battery_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->battery_img_2, &_icn_fitness_alpha_47x47);
    lv_img_set_pivot(ui->battery_img_2, 50,50);
    lv_img_set_angle(ui->battery_img_2, 0);
    lv_obj_set_pos(ui->battery_img_2, 91, 257);
    lv_obj_set_size(ui->battery_img_2, 47, 47);

    //Write style for battery_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->battery_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->battery_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->battery_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_bar_1
    ui->battery_bar_1 = lv_bar_create(ui->battery_setting_info);
    lv_obj_set_style_anim_time(ui->battery_bar_1, 1000, 0);
    lv_bar_set_mode(ui->battery_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->battery_bar_1, 0, 100);
    lv_bar_set_value(ui->battery_bar_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->battery_bar_1, 153, 291);
    lv_obj_set_size(ui->battery_bar_1, 154, 8);

    //Write style for battery_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->battery_bar_1, 254, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->battery_bar_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->battery_bar_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_bar_1, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for battery_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->battery_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->battery_bar_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->battery_bar_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_bar_1, 11, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes battery_label_13
    ui->battery_label_13 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_13, "Fitness");
    lv_label_set_long_mode(ui->battery_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_13, 155, 256);
    lv_obj_set_size(ui->battery_label_13, 78, 26);

    //Write style for battery_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_13, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_13, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_img_3
    ui->battery_img_3 = lv_img_create(ui->battery_setting_info);
    lv_obj_add_flag(ui->battery_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->battery_img_3, &_icn_travel_alpha_47x47);
    lv_img_set_pivot(ui->battery_img_3, 50,50);
    lv_img_set_angle(ui->battery_img_3, 0);
    lv_obj_set_pos(ui->battery_img_3, 91, 325);
    lv_obj_set_size(ui->battery_img_3, 47, 47);

    //Write style for battery_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->battery_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->battery_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->battery_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_bar_2
    ui->battery_bar_2 = lv_bar_create(ui->battery_setting_info);
    lv_obj_set_style_anim_time(ui->battery_bar_2, 1000, 0);
    lv_bar_set_mode(ui->battery_bar_2, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->battery_bar_2, 0, 100);
    lv_bar_set_value(ui->battery_bar_2, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->battery_bar_2, 152, 361);
    lv_obj_set_size(ui->battery_bar_2, 154, 8);

    //Write style for battery_bar_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->battery_bar_2, 254, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->battery_bar_2, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->battery_bar_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_bar_2, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_bar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for battery_bar_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->battery_bar_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->battery_bar_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->battery_bar_2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_bar_2, 11, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes battery_label_14
    ui->battery_label_14 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_14, "Travel");
    lv_label_set_long_mode(ui->battery_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_14, 155, 324);
    lv_obj_set_size(ui->battery_label_14, 78, 26);

    //Write style for battery_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_14, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_14, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_label_15
    ui->battery_label_15 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_15, "18%");
    lv_label_set_long_mode(ui->battery_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_15, 255, 250);
    lv_obj_set_size(ui->battery_label_15, 66, 33);

    //Write style for battery_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_15, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_15, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_15, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_label_16
    ui->battery_label_16 = lv_label_create(ui->battery_setting_info);
    lv_label_set_text(ui->battery_label_16, "12%");
    lv_label_set_long_mode(ui->battery_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->battery_label_16, 255, 320);
    lv_obj_set_size(ui->battery_label_16, 66, 33);

    //Write style for battery_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->battery_label_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->battery_label_16, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->battery_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->battery_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->battery_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_right
    ui->battery_right = lv_img_create(ui->battery);
    lv_obj_add_flag(ui->battery_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->battery_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->battery_right, 50,50);
    lv_img_set_angle(ui->battery_right, 0);
    lv_obj_set_pos(ui->battery_right, 437, 204);
    lv_obj_set_size(ui->battery_right, 10, 38);
    lv_obj_add_flag(ui->battery_right, LV_OBJ_FLAG_FLOATING);

    //Write style for battery_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->battery_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->battery_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_left
    ui->battery_left = lv_img_create(ui->battery);
    lv_obj_add_flag(ui->battery_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->battery_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->battery_left, 50,50);
    lv_img_set_angle(ui->battery_left, 0);
    lv_obj_set_pos(ui->battery_left, 11, 204);
    lv_obj_set_size(ui->battery_left, 10, 38);
    lv_obj_add_flag(ui->battery_left, LV_OBJ_FLAG_FLOATING);

    //Write style for battery_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->battery_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->battery_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes battery_home
    ui->battery_home = lv_img_create(ui->battery);
    lv_obj_add_flag(ui->battery_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->battery_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->battery_home, 50,50);
    lv_img_set_angle(ui->battery_home, 0);
    lv_obj_set_pos(ui->battery_home, 387, 309);
    lv_obj_set_size(ui->battery_home, 42, 57);
    lv_obj_add_flag(ui->battery_home, LV_OBJ_FLAG_FLOATING);

    //Write style for battery_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->battery_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->battery_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->battery_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->battery_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of battery.


    //Update current screen layout.
    lv_obj_update_layout(ui->battery);

    //Init events for screen.
    events_init_battery(ui);
}

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



void setup_scr_weather_week(lv_ui *ui)
{
    //Write codes weather_week
    ui->weather_week = lv_obj_create(NULL);
    lv_obj_set_size(ui->weather_week, 466, 466);
    lv_obj_set_scrollbar_mode(ui->weather_week, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weather_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->weather_week, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->weather_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->weather_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_week_list
    ui->weather_week_week_list = lv_obj_create(ui->weather_week);
    lv_obj_set_pos(ui->weather_week_week_list, 54, 89);
    lv_obj_set_size(ui->weather_week_week_list, 356, 567);
    lv_obj_set_scrollbar_mode(ui->weather_week_week_list, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_week_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_week_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_cont_14
    ui->weather_week_cont_14 = lv_obj_create(ui->weather_week_week_list);
    lv_obj_set_pos(ui->weather_week_cont_14, 2, 40);
    lv_obj_set_size(ui->weather_week_cont_14, 339, 53);
    lv_obj_set_scrollbar_mode(ui->weather_week_cont_14, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_cont_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_cont_14, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_33
    ui->weather_week_img_33 = lv_img_create(ui->weather_week_cont_14);
    lv_obj_add_flag(ui->weather_week_img_33, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_33, &_icn_small_weather_3_alpha_35x38);
    lv_img_set_pivot(ui->weather_week_img_33, 50,50);
    lv_img_set_angle(ui->weather_week_img_33, 0);
    lv_obj_set_pos(ui->weather_week_img_33, 118, 0);
    lv_obj_set_size(ui->weather_week_img_33, 35, 38);

    //Write style for weather_week_img_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_33, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_27
    ui->weather_week_label_27 = lv_label_create(ui->weather_week_cont_14);
    lv_label_set_text(ui->weather_week_label_27, "Today");
    lv_label_set_long_mode(ui->weather_week_label_27, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_27, 11, 5);
    lv_obj_set_size(ui->weather_week_label_27, 91, 38);

    //Write style for weather_week_label_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_27, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_27, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_27, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_26
    ui->weather_week_label_26 = lv_label_create(ui->weather_week_cont_14);
    lv_label_set_text(ui->weather_week_label_26, "28°-30°");
    lv_label_set_long_mode(ui->weather_week_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_26, 193, 2);
    lv_obj_set_size(ui->weather_week_label_26, 131, 38);

    //Write style for weather_week_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_26, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_26, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_26, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_26, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_32
    ui->weather_week_img_32 = lv_img_create(ui->weather_week_week_list);
    lv_obj_add_flag(ui->weather_week_img_32, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_32, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_week_img_32, 50,50);
    lv_img_set_angle(ui->weather_week_img_32, 0);
    lv_obj_set_pos(ui->weather_week_img_32, 13, 99);
    lv_obj_set_size(ui->weather_week_img_32, 331, 2);

    //Write style for weather_week_img_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_32, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_cont_13
    ui->weather_week_cont_13 = lv_obj_create(ui->weather_week_week_list);
    lv_obj_set_pos(ui->weather_week_cont_13, 2, 117);
    lv_obj_set_size(ui->weather_week_cont_13, 339, 54);
    lv_obj_set_scrollbar_mode(ui->weather_week_cont_13, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_cont_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_cont_13, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_31
    ui->weather_week_img_31 = lv_img_create(ui->weather_week_cont_13);
    lv_obj_add_flag(ui->weather_week_img_31, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_31, &_icn_small_weather_1_alpha_49x38);
    lv_img_set_pivot(ui->weather_week_img_31, 50,50);
    lv_img_set_angle(ui->weather_week_img_31, 0);
    lv_obj_set_pos(ui->weather_week_img_31, 118, 0);
    lv_obj_set_size(ui->weather_week_img_31, 49, 38);

    //Write style for weather_week_img_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_31, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_25
    ui->weather_week_label_25 = lv_label_create(ui->weather_week_cont_13);
    lv_label_set_text(ui->weather_week_label_25, "Friday");
    lv_label_set_long_mode(ui->weather_week_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_25, 11, 5);
    lv_obj_set_size(ui->weather_week_label_25, 111, 38);

    //Write style for weather_week_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_25, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_25, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_25, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_24
    ui->weather_week_label_24 = lv_label_create(ui->weather_week_cont_13);
    lv_label_set_text(ui->weather_week_label_24, "28°-32°");
    lv_label_set_long_mode(ui->weather_week_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_24, 193, 2);
    lv_obj_set_size(ui->weather_week_label_24, 131, 38);

    //Write style for weather_week_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_24, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_24, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_24, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_24, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_cont_12
    ui->weather_week_cont_12 = lv_obj_create(ui->weather_week_week_list);
    lv_obj_set_pos(ui->weather_week_cont_12, 3, 274);
    lv_obj_set_size(ui->weather_week_cont_12, 339, 53);
    lv_obj_set_scrollbar_mode(ui->weather_week_cont_12, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_cont_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_30
    ui->weather_week_img_30 = lv_img_create(ui->weather_week_cont_12);
    lv_obj_add_flag(ui->weather_week_img_30, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_30, &_icn_small_weather_2_alpha_48x45);
    lv_img_set_pivot(ui->weather_week_img_30, 50,50);
    lv_img_set_angle(ui->weather_week_img_30, 0);
    lv_obj_set_pos(ui->weather_week_img_30, 118, 1);
    lv_obj_set_size(ui->weather_week_img_30, 48, 45);

    //Write style for weather_week_img_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_30, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_30, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_23
    ui->weather_week_label_23 = lv_label_create(ui->weather_week_cont_12);
    lv_label_set_text(ui->weather_week_label_23, "Sunday");
    lv_label_set_long_mode(ui->weather_week_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_23, 11, 5);
    lv_obj_set_size(ui->weather_week_label_23, 112, 38);

    //Write style for weather_week_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_23, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_23, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_22
    ui->weather_week_label_22 = lv_label_create(ui->weather_week_cont_12);
    lv_label_set_text(ui->weather_week_label_22, "22°-25°");
    lv_label_set_long_mode(ui->weather_week_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_22, 193, 2);
    lv_obj_set_size(ui->weather_week_label_22, 131, 38);

    //Write style for weather_week_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_22, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_22, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_cont_11
    ui->weather_week_cont_11 = lv_obj_create(ui->weather_week_week_list);
    lv_obj_set_pos(ui->weather_week_cont_11, 3, 193);
    lv_obj_set_size(ui->weather_week_cont_11, 339, 53);
    lv_obj_set_scrollbar_mode(ui->weather_week_cont_11, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_cont_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_cont_11, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_29
    ui->weather_week_img_29 = lv_img_create(ui->weather_week_cont_11);
    lv_obj_add_flag(ui->weather_week_img_29, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_29, &_icn_small_weather_1_alpha_49x38);
    lv_img_set_pivot(ui->weather_week_img_29, 50,50);
    lv_img_set_angle(ui->weather_week_img_29, 0);
    lv_obj_set_pos(ui->weather_week_img_29, 118, 0);
    lv_obj_set_size(ui->weather_week_img_29, 49, 38);

    //Write style for weather_week_img_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_29, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_21
    ui->weather_week_label_21 = lv_label_create(ui->weather_week_cont_11);
    lv_label_set_text(ui->weather_week_label_21, "Saturday");
    lv_label_set_long_mode(ui->weather_week_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_21, 11, 5);
    lv_obj_set_size(ui->weather_week_label_21, 111, 38);

    //Write style for weather_week_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_21, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_21, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_21, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_20
    ui->weather_week_label_20 = lv_label_create(ui->weather_week_cont_11);
    lv_label_set_text(ui->weather_week_label_20, "26°-30°");
    lv_label_set_long_mode(ui->weather_week_label_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_20, 193, 2);
    lv_obj_set_size(ui->weather_week_label_20, 131, 38);

    //Write style for weather_week_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_20, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_20, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_20, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_20, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_28
    ui->weather_week_img_28 = lv_img_create(ui->weather_week_week_list);
    lv_obj_add_flag(ui->weather_week_img_28, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_28, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_week_img_28, 50,50);
    lv_img_set_angle(ui->weather_week_img_28, 0);
    lv_obj_set_pos(ui->weather_week_img_28, 3, 256);
    lv_obj_set_size(ui->weather_week_img_28, 331, 2);

    //Write style for weather_week_img_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_28, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_28, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_27
    ui->weather_week_img_27 = lv_img_create(ui->weather_week_week_list);
    lv_obj_add_flag(ui->weather_week_img_27, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_27, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_week_img_27, 50,50);
    lv_img_set_angle(ui->weather_week_img_27, 0);
    lv_obj_set_pos(ui->weather_week_img_27, 7, 180);
    lv_obj_set_size(ui->weather_week_img_27, 331, 2);

    //Write style for weather_week_img_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_27, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_cont_10
    ui->weather_week_cont_10 = lv_obj_create(ui->weather_week_week_list);
    lv_obj_set_pos(ui->weather_week_cont_10, 3, 422);
    lv_obj_set_size(ui->weather_week_cont_10, 339, 53);
    lv_obj_set_scrollbar_mode(ui->weather_week_cont_10, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_cont_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_cont_10, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_26
    ui->weather_week_img_26 = lv_img_create(ui->weather_week_cont_10);
    lv_obj_add_flag(ui->weather_week_img_26, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_26, &_icn_small_weather_3_alpha_35x38);
    lv_img_set_pivot(ui->weather_week_img_26, 50,50);
    lv_img_set_angle(ui->weather_week_img_26, 0);
    lv_obj_set_pos(ui->weather_week_img_26, 118, 3);
    lv_obj_set_size(ui->weather_week_img_26, 35, 38);

    //Write style for weather_week_img_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_26, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_19
    ui->weather_week_label_19 = lv_label_create(ui->weather_week_cont_10);
    lv_label_set_text(ui->weather_week_label_19, "Tuesday");
    lv_label_set_long_mode(ui->weather_week_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_19, 11, 5);
    lv_obj_set_size(ui->weather_week_label_19, 112, 38);

    //Write style for weather_week_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_19, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_19, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_19, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_18
    ui->weather_week_label_18 = lv_label_create(ui->weather_week_cont_10);
    lv_label_set_text(ui->weather_week_label_18, "30°-35°");
    lv_label_set_long_mode(ui->weather_week_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_18, 193, 2);
    lv_obj_set_size(ui->weather_week_label_18, 131, 38);

    //Write style for weather_week_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_18, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_18, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_18, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_cont_9
    ui->weather_week_cont_9 = lv_obj_create(ui->weather_week_week_list);
    lv_obj_set_pos(ui->weather_week_cont_9, 3, 354);
    lv_obj_set_size(ui->weather_week_cont_9, 339, 53);
    lv_obj_set_scrollbar_mode(ui->weather_week_cont_9, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_week_cont_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_25
    ui->weather_week_img_25 = lv_img_create(ui->weather_week_cont_9);
    lv_obj_add_flag(ui->weather_week_img_25, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_25, &_icn_small_weather_1_alpha_49x38);
    lv_img_set_pivot(ui->weather_week_img_25, 50,50);
    lv_img_set_angle(ui->weather_week_img_25, 0);
    lv_obj_set_pos(ui->weather_week_img_25, 118, 0);
    lv_obj_set_size(ui->weather_week_img_25, 49, 38);

    //Write style for weather_week_img_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_25, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_17
    ui->weather_week_label_17 = lv_label_create(ui->weather_week_cont_9);
    lv_label_set_text(ui->weather_week_label_17, "Mayday");
    lv_label_set_long_mode(ui->weather_week_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_17, 11, 5);
    lv_obj_set_size(ui->weather_week_label_17, 112, 38);

    //Write style for weather_week_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_17, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_17, &lv_font_montserratMedium_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_label_16
    ui->weather_week_label_16 = lv_label_create(ui->weather_week_cont_9);
    lv_label_set_text(ui->weather_week_label_16, "22°-27°");
    lv_label_set_long_mode(ui->weather_week_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_label_16, 193, 2);
    lv_obj_set_size(ui->weather_week_label_16, 131, 38);

    //Write style for weather_week_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_label_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_label_16, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_label_16, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_24
    ui->weather_week_img_24 = lv_img_create(ui->weather_week_week_list);
    lv_obj_add_flag(ui->weather_week_img_24, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_24, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_week_img_24, 50,50);
    lv_img_set_angle(ui->weather_week_img_24, 0);
    lv_obj_set_pos(ui->weather_week_img_24, 3, 335);
    lv_obj_set_size(ui->weather_week_img_24, 331, 2);

    //Write style for weather_week_img_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_24, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_img_23
    ui->weather_week_img_23 = lv_img_create(ui->weather_week_week_list);
    lv_obj_add_flag(ui->weather_week_img_23, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_img_23, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_week_img_23, 50,50);
    lv_img_set_angle(ui->weather_week_img_23, 0);
    lv_obj_set_pos(ui->weather_week_img_23, 3, 410);
    lv_obj_set_size(ui->weather_week_img_23, 331, 2);

    //Write style for weather_week_img_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_img_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_img_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_home
    ui->weather_week_home = lv_img_create(ui->weather_week);
    lv_obj_add_flag(ui->weather_week_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->weather_week_home, 50,50);
    lv_img_set_angle(ui->weather_week_home, 0);
    lv_obj_set_pos(ui->weather_week_home, 379, 307);
    lv_obj_set_size(ui->weather_week_home, 42, 57);
    lv_obj_add_flag(ui->weather_week_home, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_week_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_select_icon
    ui->weather_week_select_icon = lv_img_create(ui->weather_week);
    lv_obj_add_flag(ui->weather_week_select_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_select_icon, &_text_select_alpha_51x67);
    lv_img_set_pivot(ui->weather_week_select_icon, 50,50);
    lv_img_set_angle(ui->weather_week_select_icon, 80);
    lv_obj_set_pos(ui->weather_week_select_icon, 381, 90);
    lv_obj_set_size(ui->weather_week_select_icon, 51, 67);
    lv_obj_add_flag(ui->weather_week_select_icon, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_week_select_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_select_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_select_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_select_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_select_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_week_title
    ui->weather_week_week_title = lv_label_create(ui->weather_week);
    lv_label_set_text(ui->weather_week_week_title, "Week forecast");
    lv_label_set_long_mode(ui->weather_week_week_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_week_week_title, 0, -89);
    lv_obj_set_size(ui->weather_week_week_title, 466, 89);
    lv_obj_add_flag(ui->weather_week_week_title, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_week_week_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_week_week_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_week_week_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_week_week_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_week_week_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_week_week_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_week_week_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->weather_week_week_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->weather_week_week_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->weather_week_week_title, lv_color_hex(0x1099e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->weather_week_week_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_week_week_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_left
    ui->weather_week_left = lv_img_create(ui->weather_week);
    lv_obj_add_flag(ui->weather_week_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->weather_week_left, 50,50);
    lv_img_set_angle(ui->weather_week_left, 0);
    lv_obj_set_pos(ui->weather_week_left, 11, 204);
    lv_obj_set_size(ui->weather_week_left, 10, 38);
    lv_obj_add_flag(ui->weather_week_left, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_week_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_week_right
    ui->weather_week_right = lv_img_create(ui->weather_week);
    lv_obj_add_flag(ui->weather_week_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_week_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->weather_week_right, 50,50);
    lv_img_set_angle(ui->weather_week_right, 0);
    lv_obj_set_pos(ui->weather_week_right, 437, 204);
    lv_obj_set_size(ui->weather_week_right, 10, 38);
    lv_obj_add_flag(ui->weather_week_right, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_week_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_week_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_week_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_week_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_week_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of weather_week.


    //Update current screen layout.
    lv_obj_update_layout(ui->weather_week);

    //Init events for screen.
    events_init_weather_week(ui);
}

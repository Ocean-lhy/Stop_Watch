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



void setup_scr_weather_hour(lv_ui *ui)
{
    //Write codes weather_hour
    ui->weather_hour = lv_obj_create(NULL);
    lv_obj_set_size(ui->weather_hour, 466, 466);
    lv_obj_set_scrollbar_mode(ui->weather_hour, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weather_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->weather_hour, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->weather_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->weather_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_hour_list
    ui->weather_hour_hour_list = lv_obj_create(ui->weather_hour);
    lv_obj_set_pos(ui->weather_hour_hour_list, 54, 89);
    lv_obj_set_size(ui->weather_hour_hour_list, 356, 567);
    lv_obj_set_scrollbar_mode(ui->weather_hour_hour_list, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_hour_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_hour_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_cont_14
    ui->weather_hour_cont_14 = lv_obj_create(ui->weather_hour_hour_list);
    lv_obj_set_pos(ui->weather_hour_cont_14, 2, 40);
    lv_obj_set_size(ui->weather_hour_cont_14, 316, 53);
    lv_obj_set_scrollbar_mode(ui->weather_hour_cont_14, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_cont_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_cont_14, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_33
    ui->weather_hour_img_33 = lv_img_create(ui->weather_hour_cont_14);
    lv_obj_add_flag(ui->weather_hour_img_33, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_33, &_icn_small_weather_1_alpha_49x38);
    lv_img_set_pivot(ui->weather_hour_img_33, 50,50);
    lv_img_set_angle(ui->weather_hour_img_33, 0);
    lv_obj_set_pos(ui->weather_hour_img_33, 247, 3);
    lv_obj_set_size(ui->weather_hour_img_33, 49, 38);

    //Write style for weather_hour_img_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_33, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_27
    ui->weather_hour_label_27 = lv_label_create(ui->weather_hour_cont_14);
    lv_label_set_text(ui->weather_hour_label_27, "Now");
    lv_label_set_long_mode(ui->weather_hour_label_27, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_27, 29, 5);
    lv_obj_set_size(ui->weather_hour_label_27, 91, 38);

    //Write style for weather_hour_label_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_27, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_27, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_27, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_27, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_26
    ui->weather_hour_label_26 = lv_label_create(ui->weather_hour_cont_14);
    lv_label_set_text(ui->weather_hour_label_26, "28°");
    lv_label_set_long_mode(ui->weather_hour_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_26, 145, 4);
    lv_obj_set_size(ui->weather_hour_label_26, 79, 38);

    //Write style for weather_hour_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_26, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_26, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_26, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_26, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_32
    ui->weather_hour_img_32 = lv_img_create(ui->weather_hour_hour_list);
    lv_obj_add_flag(ui->weather_hour_img_32, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_32, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_hour_img_32, 50,50);
    lv_img_set_angle(ui->weather_hour_img_32, 0);
    lv_obj_set_pos(ui->weather_hour_img_32, 13, 99);
    lv_obj_set_size(ui->weather_hour_img_32, 331, 2);

    //Write style for weather_hour_img_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_32, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_cont_13
    ui->weather_hour_cont_13 = lv_obj_create(ui->weather_hour_hour_list);
    lv_obj_set_pos(ui->weather_hour_cont_13, 2, 117);
    lv_obj_set_size(ui->weather_hour_cont_13, 316, 54);
    lv_obj_set_scrollbar_mode(ui->weather_hour_cont_13, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_cont_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_cont_13, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_31
    ui->weather_hour_img_31 = lv_img_create(ui->weather_hour_cont_13);
    lv_obj_add_flag(ui->weather_hour_img_31, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_31, &_icn_small_weather_2_alpha_48x45);
    lv_img_set_pivot(ui->weather_hour_img_31, 50,50);
    lv_img_set_angle(ui->weather_hour_img_31, 0);
    lv_obj_set_pos(ui->weather_hour_img_31, 247, 3);
    lv_obj_set_size(ui->weather_hour_img_31, 48, 45);

    //Write style for weather_hour_img_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_31, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_25
    ui->weather_hour_label_25 = lv_label_create(ui->weather_hour_cont_13);
    lv_label_set_text(ui->weather_hour_label_25, "17:00");
    lv_label_set_long_mode(ui->weather_hour_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_25, 29, 5);
    lv_obj_set_size(ui->weather_hour_label_25, 91, 38);

    //Write style for weather_hour_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_25, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_25, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_25, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_25, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_24
    ui->weather_hour_label_24 = lv_label_create(ui->weather_hour_cont_13);
    lv_label_set_text(ui->weather_hour_label_24, "27°");
    lv_label_set_long_mode(ui->weather_hour_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_24, 145, 4);
    lv_obj_set_size(ui->weather_hour_label_24, 79, 38);

    //Write style for weather_hour_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_24, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_24, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_24, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_24, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_cont_12
    ui->weather_hour_cont_12 = lv_obj_create(ui->weather_hour_hour_list);
    lv_obj_set_pos(ui->weather_hour_cont_12, 3, 274);
    lv_obj_set_size(ui->weather_hour_cont_12, 316, 53);
    lv_obj_set_scrollbar_mode(ui->weather_hour_cont_12, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_cont_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_30
    ui->weather_hour_img_30 = lv_img_create(ui->weather_hour_cont_12);
    lv_obj_add_flag(ui->weather_hour_img_30, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_30, &_icn_small_weather_2_alpha_48x45);
    lv_img_set_pivot(ui->weather_hour_img_30, 50,50);
    lv_img_set_angle(ui->weather_hour_img_30, 0);
    lv_obj_set_pos(ui->weather_hour_img_30, 247, 3);
    lv_obj_set_size(ui->weather_hour_img_30, 48, 45);

    //Write style for weather_hour_img_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_30, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_30, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_23
    ui->weather_hour_label_23 = lv_label_create(ui->weather_hour_cont_12);
    lv_label_set_text(ui->weather_hour_label_23, "19:00");
    lv_label_set_long_mode(ui->weather_hour_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_23, 29, 5);
    lv_obj_set_size(ui->weather_hour_label_23, 91, 38);

    //Write style for weather_hour_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_23, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_23, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_23, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_22
    ui->weather_hour_label_22 = lv_label_create(ui->weather_hour_cont_12);
    lv_label_set_text(ui->weather_hour_label_22, "22°");
    lv_label_set_long_mode(ui->weather_hour_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_22, 145, 4);
    lv_obj_set_size(ui->weather_hour_label_22, 79, 38);

    //Write style for weather_hour_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_22, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_22, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_cont_11
    ui->weather_hour_cont_11 = lv_obj_create(ui->weather_hour_hour_list);
    lv_obj_set_pos(ui->weather_hour_cont_11, 3, 193);
    lv_obj_set_size(ui->weather_hour_cont_11, 316, 53);
    lv_obj_set_scrollbar_mode(ui->weather_hour_cont_11, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_cont_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_cont_11, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_29
    ui->weather_hour_img_29 = lv_img_create(ui->weather_hour_cont_11);
    lv_obj_add_flag(ui->weather_hour_img_29, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_29, &_icn_small_weather_2_alpha_48x45);
    lv_img_set_pivot(ui->weather_hour_img_29, 50,50);
    lv_img_set_angle(ui->weather_hour_img_29, 0);
    lv_obj_set_pos(ui->weather_hour_img_29, 247, 3);
    lv_obj_set_size(ui->weather_hour_img_29, 48, 45);

    //Write style for weather_hour_img_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_29, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_21
    ui->weather_hour_label_21 = lv_label_create(ui->weather_hour_cont_11);
    lv_label_set_text(ui->weather_hour_label_21, "18:00");
    lv_label_set_long_mode(ui->weather_hour_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_21, 29, 5);
    lv_obj_set_size(ui->weather_hour_label_21, 91, 38);

    //Write style for weather_hour_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_21, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_21, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_21, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_21, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_20
    ui->weather_hour_label_20 = lv_label_create(ui->weather_hour_cont_11);
    lv_label_set_text(ui->weather_hour_label_20, "26°");
    lv_label_set_long_mode(ui->weather_hour_label_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_20, 145, 4);
    lv_obj_set_size(ui->weather_hour_label_20, 79, 38);

    //Write style for weather_hour_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_20, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_20, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_20, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_20, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_28
    ui->weather_hour_img_28 = lv_img_create(ui->weather_hour_hour_list);
    lv_obj_add_flag(ui->weather_hour_img_28, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_28, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_hour_img_28, 50,50);
    lv_img_set_angle(ui->weather_hour_img_28, 0);
    lv_obj_set_pos(ui->weather_hour_img_28, 3, 256);
    lv_obj_set_size(ui->weather_hour_img_28, 331, 2);

    //Write style for weather_hour_img_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_28, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_28, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_27
    ui->weather_hour_img_27 = lv_img_create(ui->weather_hour_hour_list);
    lv_obj_add_flag(ui->weather_hour_img_27, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_27, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_hour_img_27, 50,50);
    lv_img_set_angle(ui->weather_hour_img_27, 0);
    lv_obj_set_pos(ui->weather_hour_img_27, 7, 180);
    lv_obj_set_size(ui->weather_hour_img_27, 331, 2);

    //Write style for weather_hour_img_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_27, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_cont_10
    ui->weather_hour_cont_10 = lv_obj_create(ui->weather_hour_hour_list);
    lv_obj_set_pos(ui->weather_hour_cont_10, 3, 422);
    lv_obj_set_size(ui->weather_hour_cont_10, 316, 53);
    lv_obj_set_scrollbar_mode(ui->weather_hour_cont_10, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_cont_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_cont_10, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_26
    ui->weather_hour_img_26 = lv_img_create(ui->weather_hour_cont_10);
    lv_obj_add_flag(ui->weather_hour_img_26, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_26, &_icn_small_weather_1_alpha_49x38);
    lv_img_set_pivot(ui->weather_hour_img_26, 50,50);
    lv_img_set_angle(ui->weather_hour_img_26, 0);
    lv_obj_set_pos(ui->weather_hour_img_26, 247, 3);
    lv_obj_set_size(ui->weather_hour_img_26, 49, 38);

    //Write style for weather_hour_img_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_26, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_19
    ui->weather_hour_label_19 = lv_label_create(ui->weather_hour_cont_10);
    lv_label_set_text(ui->weather_hour_label_19, "21:00");
    lv_label_set_long_mode(ui->weather_hour_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_19, 29, 5);
    lv_obj_set_size(ui->weather_hour_label_19, 91, 38);

    //Write style for weather_hour_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_19, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_19, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_19, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_19, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_18
    ui->weather_hour_label_18 = lv_label_create(ui->weather_hour_cont_10);
    lv_label_set_text(ui->weather_hour_label_18, "20°");
    lv_label_set_long_mode(ui->weather_hour_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_18, 145, 4);
    lv_obj_set_size(ui->weather_hour_label_18, 79, 38);

    //Write style for weather_hour_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_18, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_18, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_18, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_cont_9
    ui->weather_hour_cont_9 = lv_obj_create(ui->weather_hour_hour_list);
    lv_obj_set_pos(ui->weather_hour_cont_9, 3, 354);
    lv_obj_set_size(ui->weather_hour_cont_9, 316, 53);
    lv_obj_set_scrollbar_mode(ui->weather_hour_cont_9, LV_SCROLLBAR_MODE_OFF);

    //Write style for weather_hour_cont_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_25
    ui->weather_hour_img_25 = lv_img_create(ui->weather_hour_cont_9);
    lv_obj_add_flag(ui->weather_hour_img_25, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_25, &_icn_small_weather_1_alpha_49x38);
    lv_img_set_pivot(ui->weather_hour_img_25, 50,50);
    lv_img_set_angle(ui->weather_hour_img_25, 0);
    lv_obj_set_pos(ui->weather_hour_img_25, 247, 3);
    lv_obj_set_size(ui->weather_hour_img_25, 49, 38);

    //Write style for weather_hour_img_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_25, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_17
    ui->weather_hour_label_17 = lv_label_create(ui->weather_hour_cont_9);
    lv_label_set_text(ui->weather_hour_label_17, "20:00");
    lv_label_set_long_mode(ui->weather_hour_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_17, 29, 5);
    lv_obj_set_size(ui->weather_hour_label_17, 97, 38);

    //Write style for weather_hour_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_17, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_17, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_17, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_label_16
    ui->weather_hour_label_16 = lv_label_create(ui->weather_hour_cont_9);
    lv_label_set_text(ui->weather_hour_label_16, "22°");
    lv_label_set_long_mode(ui->weather_hour_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_label_16, 145, 4);
    lv_obj_set_size(ui->weather_hour_label_16, 79, 38);

    //Write style for weather_hour_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_label_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_label_16, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_label_16, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_24
    ui->weather_hour_img_24 = lv_img_create(ui->weather_hour_hour_list);
    lv_obj_add_flag(ui->weather_hour_img_24, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_24, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_hour_img_24, 50,50);
    lv_img_set_angle(ui->weather_hour_img_24, 0);
    lv_obj_set_pos(ui->weather_hour_img_24, 3, 335);
    lv_obj_set_size(ui->weather_hour_img_24, 331, 2);

    //Write style for weather_hour_img_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_24, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_img_23
    ui->weather_hour_img_23 = lv_img_create(ui->weather_hour_hour_list);
    lv_obj_add_flag(ui->weather_hour_img_23, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_img_23, &_img_line_2_alpha_331x2);
    lv_img_set_pivot(ui->weather_hour_img_23, 50,50);
    lv_img_set_angle(ui->weather_hour_img_23, 0);
    lv_obj_set_pos(ui->weather_hour_img_23, 3, 410);
    lv_obj_set_size(ui->weather_hour_img_23, 331, 2);

    //Write style for weather_hour_img_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_img_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_img_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_home
    ui->weather_hour_home = lv_img_create(ui->weather_hour);
    lv_obj_add_flag(ui->weather_hour_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->weather_hour_home, 50,50);
    lv_img_set_angle(ui->weather_hour_home, 0);
    lv_obj_set_pos(ui->weather_hour_home, 379, 307);
    lv_obj_set_size(ui->weather_hour_home, 42, 57);
    lv_obj_add_flag(ui->weather_hour_home, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_hour_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_select_icon
    ui->weather_hour_select_icon = lv_img_create(ui->weather_hour);
    lv_obj_add_flag(ui->weather_hour_select_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_select_icon, &_text_select_alpha_51x67);
    lv_img_set_pivot(ui->weather_hour_select_icon, 50,50);
    lv_img_set_angle(ui->weather_hour_select_icon, 80);
    lv_obj_set_pos(ui->weather_hour_select_icon, 381, 90);
    lv_obj_set_size(ui->weather_hour_select_icon, 51, 67);
    lv_obj_add_flag(ui->weather_hour_select_icon, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_hour_select_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_select_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_select_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_select_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_select_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_title
    ui->weather_hour_title = lv_label_create(ui->weather_hour);
    lv_label_set_text(ui->weather_hour_title, "Hour forecast");
    lv_label_set_long_mode(ui->weather_hour_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weather_hour_title, 0, -89);
    lv_obj_set_size(ui->weather_hour_title, 466, 89);
    lv_obj_add_flag(ui->weather_hour_title, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_hour_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weather_hour_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weather_hour_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weather_hour_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weather_hour_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weather_hour_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weather_hour_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->weather_hour_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->weather_hour_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->weather_hour_title, lv_color_hex(0x1099e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->weather_hour_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weather_hour_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_left
    ui->weather_hour_left = lv_img_create(ui->weather_hour);
    lv_obj_add_flag(ui->weather_hour_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->weather_hour_left, 50,50);
    lv_img_set_angle(ui->weather_hour_left, 0);
    lv_obj_set_pos(ui->weather_hour_left, 11, 204);
    lv_obj_set_size(ui->weather_hour_left, 10, 38);
    lv_obj_add_flag(ui->weather_hour_left, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_hour_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weather_hour_right
    ui->weather_hour_right = lv_img_create(ui->weather_hour);
    lv_obj_add_flag(ui->weather_hour_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->weather_hour_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->weather_hour_right, 50,50);
    lv_img_set_angle(ui->weather_hour_right, 0);
    lv_obj_set_pos(ui->weather_hour_right, 437, 204);
    lv_obj_set_size(ui->weather_hour_right, 10, 38);
    lv_obj_add_flag(ui->weather_hour_right, LV_OBJ_FLAG_FLOATING);

    //Write style for weather_hour_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->weather_hour_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->weather_hour_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weather_hour_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->weather_hour_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of weather_hour.


    //Update current screen layout.
    lv_obj_update_layout(ui->weather_hour);

    //Init events for screen.
    events_init_weather_hour(ui);
}

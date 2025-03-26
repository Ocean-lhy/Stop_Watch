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



void setup_scr_air_quality(lv_ui *ui)
{
    //Write codes air_quality
    ui->air_quality = lv_obj_create(NULL);
    lv_obj_set_size(ui->air_quality, 466, 466);
    lv_obj_set_scrollbar_mode(ui->air_quality, LV_SCROLLBAR_MODE_OFF);

    //Write style for air_quality, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->air_quality, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->air_quality, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->air_quality, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->air_quality, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_home
    ui->air_quality_home = lv_img_create(ui->air_quality);
    lv_obj_add_flag(ui->air_quality_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->air_quality_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->air_quality_home, 50,50);
    lv_img_set_angle(ui->air_quality_home, 0);
    lv_obj_set_pos(ui->air_quality_home, 379, 307);
    lv_obj_set_size(ui->air_quality_home, 42, 57);
    lv_obj_add_flag(ui->air_quality_home, LV_OBJ_FLAG_FLOATING);

    //Write style for air_quality_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->air_quality_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->air_quality_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->air_quality_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_select_icon
    ui->air_quality_select_icon = lv_img_create(ui->air_quality);
    lv_obj_add_flag(ui->air_quality_select_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->air_quality_select_icon, &_text_select_alpha_51x67);
    lv_img_set_pivot(ui->air_quality_select_icon, 50,50);
    lv_img_set_angle(ui->air_quality_select_icon, 80);
    lv_obj_set_pos(ui->air_quality_select_icon, 381, 90);
    lv_obj_set_size(ui->air_quality_select_icon, 51, 67);
    lv_obj_add_flag(ui->air_quality_select_icon, LV_OBJ_FLAG_FLOATING);

    //Write style for air_quality_select_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->air_quality_select_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->air_quality_select_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_select_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->air_quality_select_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_air_title
    ui->air_quality_air_title = lv_label_create(ui->air_quality);
    lv_label_set_text(ui->air_quality_air_title, "Air quality");
    lv_label_set_long_mode(ui->air_quality_air_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_air_title, 0, -89);
    lv_obj_set_size(ui->air_quality_air_title, 466, 89);
    lv_obj_add_flag(ui->air_quality_air_title, LV_OBJ_FLAG_FLOATING);

    //Write style for air_quality_air_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_air_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_air_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_air_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_air_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_air_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_air_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->air_quality_air_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->air_quality_air_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->air_quality_air_title, lv_color_hex(0x1099e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->air_quality_air_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_air_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_left
    ui->air_quality_left = lv_img_create(ui->air_quality);
    lv_obj_add_flag(ui->air_quality_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->air_quality_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->air_quality_left, 50,50);
    lv_img_set_angle(ui->air_quality_left, 0);
    lv_obj_set_pos(ui->air_quality_left, 11, 204);
    lv_obj_set_size(ui->air_quality_left, 10, 38);
    lv_obj_add_flag(ui->air_quality_left, LV_OBJ_FLAG_FLOATING);

    //Write style for air_quality_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->air_quality_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->air_quality_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->air_quality_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_airList_2
    ui->air_quality_airList_2 = lv_obj_create(ui->air_quality);
    lv_obj_set_pos(ui->air_quality_airList_2, 42, 97);
    lv_obj_set_size(ui->air_quality_airList_2, 356, 106);
    lv_obj_set_scrollbar_mode(ui->air_quality_airList_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for air_quality_airList_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_airList_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_line_12
    ui->air_quality_line_12 = lv_line_create(ui->air_quality_airList_2);
    static lv_point_t air_quality_line_12[] = {{0, 0},{0, 83},};
    lv_line_set_points(ui->air_quality_line_12, air_quality_line_12, 2);
    lv_obj_set_pos(ui->air_quality_line_12, 23, 17);
    lv_obj_set_size(ui->air_quality_line_12, 11, 83);

    //Write style for air_quality_line_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->air_quality_line_12, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->air_quality_line_12, lv_color_hex(0xBDD631), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->air_quality_line_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->air_quality_line_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_line_11
    ui->air_quality_line_11 = lv_line_create(ui->air_quality_airList_2);
    static lv_point_t air_quality_line_11[] = {{0, 0},{0, 83},};
    lv_line_set_points(ui->air_quality_line_11, air_quality_line_11, 2);
    lv_obj_set_pos(ui->air_quality_line_11, 143, 17);
    lv_obj_set_size(ui->air_quality_line_11, 11, 83);

    //Write style for air_quality_line_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->air_quality_line_11, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->air_quality_line_11, lv_color_hex(0xFF7D10), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->air_quality_line_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->air_quality_line_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_line_10
    ui->air_quality_line_10 = lv_line_create(ui->air_quality_airList_2);
    static lv_point_t air_quality_line_10[] = {{0, 0},{0, 83},};
    lv_line_set_points(ui->air_quality_line_10, air_quality_line_10, 2);
    lv_obj_set_pos(ui->air_quality_line_10, 255, 17);
    lv_obj_set_size(ui->air_quality_line_10, 11, 83);

    //Write style for air_quality_line_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->air_quality_line_10, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->air_quality_line_10, lv_color_hex(0xFF4818), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->air_quality_line_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->air_quality_line_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_38
    ui->air_quality_label_38 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_38, "PM2.5");
    lv_label_set_long_mode(ui->air_quality_label_38, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_38, 36, 14);
    lv_obj_set_size(ui->air_quality_label_38, 78, 20);

    //Write style for air_quality_label_38, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_38, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_38, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_38, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_38, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_38, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_37
    ui->air_quality_label_37 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_37, "16");
    lv_label_set_long_mode(ui->air_quality_label_37, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_37, 38, 40);
    lv_obj_set_size(ui->air_quality_label_37, 78, 34);

    //Write style for air_quality_label_37, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_37, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_37, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_37, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_37, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_37, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_36
    ui->air_quality_label_36 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_36, "μg/m3");
    lv_label_set_long_mode(ui->air_quality_label_36, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_36, 36, 80);
    lv_obj_set_size(ui->air_quality_label_36, 78, 20);

    //Write style for air_quality_label_36, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_36, lv_color_hex(0xEFEFEF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_36, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_36, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_36, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_36, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_35
    ui->air_quality_label_35 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_35, "PM10");
    lv_label_set_long_mode(ui->air_quality_label_35, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_35, 158, 14);
    lv_obj_set_size(ui->air_quality_label_35, 78, 20);

    //Write style for air_quality_label_35, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_35, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_35, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_35, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_35, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_35, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_34
    ui->air_quality_label_34 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_34, "O3");
    lv_label_set_long_mode(ui->air_quality_label_34, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_34, 268, 14);
    lv_obj_set_size(ui->air_quality_label_34, 78, 20);

    //Write style for air_quality_label_34, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_34, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_34, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_34, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_34, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_34, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_33
    ui->air_quality_label_33 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_33, "150");
    lv_label_set_long_mode(ui->air_quality_label_33, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_33, 156, 42);
    lv_obj_set_size(ui->air_quality_label_33, 78, 34);

    //Write style for air_quality_label_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_33, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_33, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_33, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_33, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_32
    ui->air_quality_label_32 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_32, "125");
    lv_label_set_long_mode(ui->air_quality_label_32, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_32, 268, 42);
    lv_obj_set_size(ui->air_quality_label_32, 78, 34);

    //Write style for air_quality_label_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_32, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_32, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_32, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_32, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_31
    ui->air_quality_label_31 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_31, "μg/m3");
    lv_label_set_long_mode(ui->air_quality_label_31, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_31, 268, 80);
    lv_obj_set_size(ui->air_quality_label_31, 78, 20);

    //Write style for air_quality_label_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_31, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_31, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_31, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_31, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_30
    ui->air_quality_label_30 = lv_label_create(ui->air_quality_airList_2);
    lv_label_set_text(ui->air_quality_label_30, "μg/m3");
    lv_label_set_long_mode(ui->air_quality_label_30, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_30, 160, 80);
    lv_obj_set_size(ui->air_quality_label_30, 78, 20);

    //Write style for air_quality_label_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_30, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_30, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_30, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_30, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_30, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_airList_1
    ui->air_quality_airList_1 = lv_obj_create(ui->air_quality);
    lv_obj_set_pos(ui->air_quality_airList_1, 42, 222);
    lv_obj_set_size(ui->air_quality_airList_1, 356, 106);
    lv_obj_set_scrollbar_mode(ui->air_quality_airList_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for air_quality_airList_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_airList_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_line_9
    ui->air_quality_line_9 = lv_line_create(ui->air_quality_airList_1);
    static lv_point_t air_quality_line_9[] = {{0, 0},{0, 83},};
    lv_line_set_points(ui->air_quality_line_9, air_quality_line_9, 2);
    lv_obj_set_pos(ui->air_quality_line_9, 23, 17);
    lv_obj_set_size(ui->air_quality_line_9, 11, 83);

    //Write style for air_quality_line_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->air_quality_line_9, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->air_quality_line_9, lv_color_hex(0xBDD631), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->air_quality_line_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->air_quality_line_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_line_8
    ui->air_quality_line_8 = lv_line_create(ui->air_quality_airList_1);
    static lv_point_t air_quality_line_8[] = {{0, 0},{0, 83},};
    lv_line_set_points(ui->air_quality_line_8, air_quality_line_8, 2);
    lv_obj_set_pos(ui->air_quality_line_8, 143, 17);
    lv_obj_set_size(ui->air_quality_line_8, 11, 83);

    //Write style for air_quality_line_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->air_quality_line_8, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->air_quality_line_8, lv_color_hex(0x29C239), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->air_quality_line_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->air_quality_line_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_line_7
    ui->air_quality_line_7 = lv_line_create(ui->air_quality_airList_1);
    static lv_point_t air_quality_line_7[] = {{0, 0},{0, 83},};
    lv_line_set_points(ui->air_quality_line_7, air_quality_line_7, 2);
    lv_obj_set_pos(ui->air_quality_line_7, 255, 17);
    lv_obj_set_size(ui->air_quality_line_7, 11, 83);

    //Write style for air_quality_line_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->air_quality_line_7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->air_quality_line_7, lv_color_hex(0xBDD631), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->air_quality_line_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->air_quality_line_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_29
    ui->air_quality_label_29 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_29, "NO2");
    lv_label_set_long_mode(ui->air_quality_label_29, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_29, 36, 14);
    lv_obj_set_size(ui->air_quality_label_29, 78, 20);

    //Write style for air_quality_label_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_29, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_29, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_29, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_29, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_28
    ui->air_quality_label_28 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_28, "280");
    lv_label_set_long_mode(ui->air_quality_label_28, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_28, 38, 40);
    lv_obj_set_size(ui->air_quality_label_28, 78, 34);

    //Write style for air_quality_label_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_28, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_28, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_28, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_28, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_28, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_27
    ui->air_quality_label_27 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_27, "μg/m3");
    lv_label_set_long_mode(ui->air_quality_label_27, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_27, 36, 80);
    lv_obj_set_size(ui->air_quality_label_27, 78, 20);

    //Write style for air_quality_label_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_27, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_27, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_27, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_27, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_26
    ui->air_quality_label_26 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_26, "SO2");
    lv_label_set_long_mode(ui->air_quality_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_26, 158, 14);
    lv_obj_set_size(ui->air_quality_label_26, 78, 20);

    //Write style for air_quality_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_26, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_26, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_26, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_26, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_25
    ui->air_quality_label_25 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_25, "CO");
    lv_label_set_long_mode(ui->air_quality_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_25, 268, 14);
    lv_obj_set_size(ui->air_quality_label_25, 78, 20);

    //Write style for air_quality_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_25, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_25, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_25, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_25, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_24
    ui->air_quality_label_24 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_24, "1583");
    lv_label_set_long_mode(ui->air_quality_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_24, 154, 42);
    lv_obj_set_size(ui->air_quality_label_24, 86, 34);

    //Write style for air_quality_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_24, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_24, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_24, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_24, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_23
    ui->air_quality_label_23 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_23, "60");
    lv_label_set_long_mode(ui->air_quality_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_23, 268, 42);
    lv_obj_set_size(ui->air_quality_label_23, 78, 34);

    //Write style for air_quality_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_23, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_23, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_23, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_22
    ui->air_quality_label_22 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_22, "μg/m3");
    lv_label_set_long_mode(ui->air_quality_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_22, 268, 80);
    lv_obj_set_size(ui->air_quality_label_22, 78, 20);

    //Write style for air_quality_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_22, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_22, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_22, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_label_21
    ui->air_quality_label_21 = lv_label_create(ui->air_quality_airList_1);
    lv_label_set_text(ui->air_quality_label_21, "μg/m3");
    lv_label_set_long_mode(ui->air_quality_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_label_21, 156, 80);
    lv_obj_set_size(ui->air_quality_label_21, 78, 20);

    //Write style for air_quality_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_label_21, lv_color_hex(0xdad9d9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_label_21, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_label_21, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_label_21, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes air_quality_ade_text
    ui->air_quality_ade_text = lv_label_create(ui->air_quality);
    lv_label_set_text(ui->air_quality_ade_text, "Adequate");
    lv_label_set_long_mode(ui->air_quality_ade_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->air_quality_ade_text, 133, 492);
    lv_obj_set_size(ui->air_quality_ade_text, 200, 46);

    //Write style for air_quality_ade_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->air_quality_ade_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->air_quality_ade_text, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->air_quality_ade_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->air_quality_ade_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->air_quality_ade_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->air_quality_ade_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of air_quality.


    //Update current screen layout.
    lv_obj_update_layout(ui->air_quality);

    //Init events for screen.
    events_init_air_quality(ui);
}

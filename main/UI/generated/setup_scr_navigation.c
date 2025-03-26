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



void setup_scr_navigation(lv_ui *ui)
{
    //Write codes navigation
    ui->navigation = lv_obj_create(NULL);
    lv_obj_set_size(ui->navigation, 466, 466);
    lv_obj_set_scrollbar_mode(ui->navigation, LV_SCROLLBAR_MODE_OFF);

    //Write style for navigation, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->navigation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->navigation, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->navigation, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->navigation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_home
    ui->navigation_home = lv_img_create(ui->navigation);
    lv_obj_add_flag(ui->navigation_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->navigation_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->navigation_home, 50,50);
    lv_img_set_angle(ui->navigation_home, 0);
    lv_obj_set_pos(ui->navigation_home, 387, 307);
    lv_obj_set_size(ui->navigation_home, 42, 57);
    lv_obj_add_flag(ui->navigation_home, LV_OBJ_FLAG_FLOATING);

    //Write style for navigation_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->navigation_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->navigation_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->navigation_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_title
    ui->navigation_title = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_title, "Navigation\n");
    lv_label_set_long_mode(ui->navigation_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_title, -3, -99);
    lv_obj_set_size(ui->navigation_title, 466, 89);
    lv_obj_add_flag(ui->navigation_title, LV_OBJ_FLAG_FLOATING);

    //Write style for navigation_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->navigation_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->navigation_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->navigation_title, lv_color_hex(0x3155EE), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->navigation_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_next_roadName
    ui->navigation_next_roadName = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_next_roadName, "Next: West Higgins Rd.");
    lv_label_set_long_mode(ui->navigation_next_roadName, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_next_roadName, 115, 48);
    lv_obj_set_size(ui->navigation_next_roadName, 235, 20);

    //Write style for navigation_next_roadName, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_next_roadName, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_next_roadName, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_next_roadName, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_next_roadName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_next_roadName, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_road_name
    ui->navigation_road_name = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_road_name, "Ed Bluestein Blvd");
    lv_label_set_long_mode(ui->navigation_road_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_road_name, 89, 11);
    lv_obj_set_size(ui->navigation_road_name, 268, 36);

    //Write style for navigation_road_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_road_name, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_road_name, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_road_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_road_name, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_road_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_distance
    ui->navigation_distance = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_distance, "1.8");
    lv_label_set_long_mode(ui->navigation_distance, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_distance, 36, 222);
    lv_obj_set_size(ui->navigation_distance, 45, 36);

    //Write style for navigation_distance, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_distance, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_distance, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_distance, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_distance, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_distance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_distance_text
    ui->navigation_distance_text = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_distance_text, "DISTANCE");
    lv_label_set_long_mode(ui->navigation_distance_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_distance_text, 29, 194);
    lv_obj_set_size(ui->navigation_distance_text, 101, 24);

    //Write style for navigation_distance_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_distance_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_distance_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_distance_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_distance_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_distance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_take_time_text
    ui->navigation_take_time_text = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_take_time_text, "TAKE TIME");
    lv_label_set_long_mode(ui->navigation_take_time_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_take_time_text, 319, 194);
    lv_obj_set_size(ui->navigation_take_time_text, 111, 20);

    //Write style for navigation_take_time_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_take_time_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_take_time_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_take_time_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_take_time_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_take_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_nav_icon
    ui->navigation_nav_icon = lv_img_create(ui->navigation);
    lv_obj_add_flag(ui->navigation_nav_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->navigation_nav_icon, &_img_nav_1_alpha_127x145);
    lv_img_set_pivot(ui->navigation_nav_icon, 50,50);
    lv_img_set_angle(ui->navigation_nav_icon, 0);
    lv_obj_set_pos(ui->navigation_nav_icon, 165, 183);
    lv_obj_set_size(ui->navigation_nav_icon, 127, 145);

    //Write style for navigation_nav_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->navigation_nav_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->navigation_nav_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_nav_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->navigation_nav_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_km_text
    ui->navigation_km_text = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_km_text, "km");
    lv_label_set_long_mode(ui->navigation_km_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_km_text, 82, 231);
    lv_obj_set_size(ui->navigation_km_text, 38, 17);

    //Write style for navigation_km_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_km_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_km_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_km_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_km_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_km_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_take_time
    ui->navigation_take_time = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_take_time, "45");
    lv_label_set_long_mode(ui->navigation_take_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_take_time, 319, 222);
    lv_obj_set_size(ui->navigation_take_time, 45, 36);

    //Write style for navigation_take_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_take_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_take_time, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_take_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_take_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_take_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_mins_text
    ui->navigation_mins_text = lv_label_create(ui->navigation);
    lv_label_set_text(ui->navigation_mins_text, "mins");
    lv_label_set_long_mode(ui->navigation_mins_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_mins_text, 364, 230);
    lv_obj_set_size(ui->navigation_mins_text, 57, 24);

    //Write style for navigation_mins_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_mins_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_mins_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_mins_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_mins_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_mins_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_indicator
    ui->navigation_indicator = lv_obj_create(ui->navigation);
    lv_obj_set_pos(ui->navigation_indicator, 109, 485);
    lv_obj_set_size(ui->navigation_indicator, 248, 104);
    lv_obj_set_scrollbar_mode(ui->navigation_indicator, LV_SCROLLBAR_MODE_OFF);

    //Write style for navigation_indicator, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_indicator, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_label_4
    ui->navigation_label_4 = lv_label_create(ui->navigation_indicator);
    lv_label_set_text(ui->navigation_label_4, "200m");
    lv_label_set_long_mode(ui->navigation_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_label_4, 65, 9);
    lv_obj_set_size(ui->navigation_label_4, 118, 36);

    //Write style for navigation_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_label_4, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_label_5
    ui->navigation_label_5 = lv_label_create(ui->navigation_indicator);
    lv_label_set_text(ui->navigation_label_5, "Turn Right");
    lv_label_set_long_mode(ui->navigation_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->navigation_label_5, 47, 52);
    lv_obj_set_size(ui->navigation_label_5, 158, 28);

    //Write style for navigation_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->navigation_label_5, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->navigation_label_5, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->navigation_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->navigation_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->navigation_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_img_dot
    ui->navigation_img_dot = lv_img_create(ui->navigation);
    lv_obj_add_flag(ui->navigation_img_dot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->navigation_img_dot, &_dot_alpha_9x9);
    lv_img_set_pivot(ui->navigation_img_dot, 50,50);
    lv_img_set_angle(ui->navigation_img_dot, 0);
    lv_obj_set_pos(ui->navigation_img_dot, 439, 240);
    lv_obj_set_size(ui->navigation_img_dot, 9, 9);

    //Write style for navigation_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->navigation_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->navigation_img_dot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->navigation_img_dot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes navigation_img_menu
    ui->navigation_img_menu = lv_img_create(ui->navigation);
    lv_obj_add_flag(ui->navigation_img_menu, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->navigation_img_menu, &_img_menu_alpha_13x118);
    lv_img_set_pivot(ui->navigation_img_menu, 50,50);
    lv_img_set_angle(ui->navigation_img_menu, 0);
    lv_obj_set_pos(ui->navigation_img_menu, 433, 173);
    lv_obj_set_size(ui->navigation_img_menu, 13, 118);

    //Write style for navigation_img_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->navigation_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->navigation_img_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->navigation_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->navigation_img_menu, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of navigation.


    //Update current screen layout.
    lv_obj_update_layout(ui->navigation);

    //Init events for screen.
    events_init_navigation(ui);
}

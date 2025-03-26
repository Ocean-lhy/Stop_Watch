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



void setup_scr_flight(lv_ui *ui)
{
    //Write codes flight
    ui->flight = lv_obj_create(NULL);
    lv_obj_set_size(ui->flight, 466, 466);
    lv_obj_set_scrollbar_mode(ui->flight, LV_SCROLLBAR_MODE_OFF);

    //Write style for flight, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->flight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->flight, &_img_bg_travel_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->flight, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->flight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_home
    ui->flight_home = lv_img_create(ui->flight);
    lv_obj_add_flag(ui->flight_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->flight_home, 50,50);
    lv_img_set_angle(ui->flight_home, 0);
    lv_obj_set_pos(ui->flight_home, 386, 307);
    lv_obj_set_size(ui->flight_home, 42, 57);
    lv_obj_add_flag(ui->flight_home, LV_OBJ_FLAG_FLOATING);

    //Write style for flight_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_title
    ui->flight_title = lv_label_create(ui->flight);
    lv_label_set_text(ui->flight_title, "Your Flight");
    lv_label_set_long_mode(ui->flight_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_title, 0, -98);
    lv_obj_set_size(ui->flight_title, 466, 89);
    lv_obj_add_flag(ui->flight_title, LV_OBJ_FLAG_FLOATING);

    //Write style for flight_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->flight_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->flight_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->flight_title, lv_color_hex(0xFFAA10), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->flight_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_flight_icon
    ui->flight_flight_icon = lv_img_create(ui->flight);
    lv_obj_add_flag(ui->flight_flight_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_flight_icon, &_img_plane_2_alpha_398x57);
    lv_img_set_pivot(ui->flight_flight_icon, 50,50);
    lv_img_set_angle(ui->flight_flight_icon, 0);
    lv_obj_set_pos(ui->flight_flight_icon, 34, 193);
    lv_obj_set_size(ui->flight_flight_icon, 398, 57);

    //Write style for flight_flight_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_flight_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_flight_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_flight_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_flight_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_departure_time
    ui->flight_departure_time = lv_label_create(ui->flight);
    lv_label_set_text(ui->flight_departure_time, "18:03");
    lv_label_set_long_mode(ui->flight_departure_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_departure_time, 64, 260);
    lv_obj_set_size(ui->flight_departure_time, 112, 36);

    //Write style for flight_departure_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_departure_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_departure_time, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_departure_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_departure_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_departure_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_departure_date
    ui->flight_departure_date = lv_label_create(ui->flight);
    lv_label_set_text(ui->flight_departure_date, "23.12.2022");
    lv_label_set_long_mode(ui->flight_departure_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_departure_date, 59, 307);
    lv_obj_set_size(ui->flight_departure_date, 149, 20);

    //Write style for flight_departure_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_departure_date, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_departure_date, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_departure_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_departure_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_departure_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_arrival_time
    ui->flight_arrival_time = lv_label_create(ui->flight);
    lv_label_set_text(ui->flight_arrival_time, "05:25");
    lv_label_set_long_mode(ui->flight_arrival_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_arrival_time, 288, 260);
    lv_obj_set_size(ui->flight_arrival_time, 112, 36);

    //Write style for flight_arrival_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_arrival_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_arrival_time, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_arrival_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_arrival_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_arrival_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_flight_number
    ui->flight_flight_number = lv_label_create(ui->flight);
    lv_label_set_text(ui->flight_flight_number, "LH 2547");
    lv_label_set_long_mode(ui->flight_flight_number, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_flight_number, 185, 269);
    lv_obj_set_size(ui->flight_flight_number, 96, 27);

    //Write style for flight_flight_number, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_flight_number, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_flight_number, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_flight_number, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_flight_number, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_arrival_date
    ui->flight_arrival_date = lv_label_create(ui->flight);
    lv_label_set_text(ui->flight_arrival_date, "24.12.2022");
    lv_label_set_long_mode(ui->flight_arrival_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_arrival_date, 281, 307);
    lv_obj_set_size(ui->flight_arrival_date, 99, 20);

    //Write style for flight_arrival_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_arrival_date, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_arrival_date, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_arrival_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_arrival_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_arrival_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_flight_seat
    ui->flight_flight_seat = lv_obj_create(ui->flight);
    lv_obj_set_pos(ui->flight_flight_seat, 72, 469);
    lv_obj_set_size(ui->flight_flight_seat, 298, 103);
    lv_obj_set_scrollbar_mode(ui->flight_flight_seat, LV_SCROLLBAR_MODE_OFF);

    //Write style for flight_flight_seat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_flight_seat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_13
    ui->flight_label_13 = lv_label_create(ui->flight_flight_seat);
    lv_label_set_text(ui->flight_label_13, "GATE");
    lv_label_set_long_mode(ui->flight_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_13, 45, 21);
    lv_obj_set_size(ui->flight_label_13, 68, 20);

    //Write style for flight_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_13, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_13, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_11
    ui->flight_label_11 = lv_label_create(ui->flight_flight_seat);
    lv_label_set_text(ui->flight_label_11, "A32");
    lv_label_set_long_mode(ui->flight_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_11, 35, 43);
    lv_obj_set_size(ui->flight_label_11, 84, 36);

    //Write style for flight_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_11, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_img_2
    ui->flight_img_2 = lv_img_create(ui->flight_flight_seat);
    lv_obj_add_flag(ui->flight_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_img_2, &_img_line_3_alpha_2x103);
    lv_img_set_pivot(ui->flight_img_2, 50,50);
    lv_img_set_angle(ui->flight_img_2, 0);
    lv_obj_set_pos(ui->flight_img_2, 147, 0);
    lv_obj_set_size(ui->flight_img_2, 2, 103);

    //Write style for flight_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_14
    ui->flight_label_14 = lv_label_create(ui->flight_flight_seat);
    lv_label_set_text(ui->flight_label_14, "SEAT");
    lv_label_set_long_mode(ui->flight_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_14, 196, 19);
    lv_obj_set_size(ui->flight_label_14, 68, 20);

    //Write style for flight_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_14, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_14, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_12
    ui->flight_label_12 = lv_label_create(ui->flight_flight_seat);
    lv_label_set_text(ui->flight_label_12, "16B");
    lv_label_set_long_mode(ui->flight_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_12, 190, 42);
    lv_obj_set_size(ui->flight_label_12, 84, 36);

    //Write style for flight_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_12, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_flight_location
    ui->flight_flight_location = lv_obj_create(ui->flight);
    lv_obj_set_pos(ui->flight_flight_location, 42, 9);
    lv_obj_set_size(ui->flight_flight_location, 381, 91);
    lv_obj_set_scrollbar_mode(ui->flight_flight_location, LV_SCROLLBAR_MODE_OFF);

    //Write style for flight_flight_location, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_flight_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_3
    ui->flight_label_3 = lv_label_create(ui->flight_flight_location);
    lv_label_set_text(ui->flight_label_3, "MUC");
    lv_label_set_long_mode(ui->flight_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_3, 26, 11);
    lv_obj_set_size(ui->flight_label_3, 110, 36);

    //Write style for flight_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_3, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_1
    ui->flight_label_1 = lv_label_create(ui->flight_flight_location);
    lv_label_set_text(ui->flight_label_1, "Munich");
    lv_label_set_long_mode(ui->flight_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_1, 30, 54);
    lv_obj_set_size(ui->flight_label_1, 98, 20);

    //Write style for flight_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_1, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_5
    ui->flight_label_5 = lv_label_create(ui->flight_flight_location);
    lv_label_set_text(ui->flight_label_5, "KLAX");
    lv_label_set_long_mode(ui->flight_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_5, 240, 13);
    lv_obj_set_size(ui->flight_label_5, 110, 36);

    //Write style for flight_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_5, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_label_4
    ui->flight_label_4 = lv_label_create(ui->flight_flight_location);
    lv_label_set_text(ui->flight_label_4, "Los Angeles");
    lv_label_set_long_mode(ui->flight_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_label_4, 235, 52);
    lv_obj_set_size(ui->flight_label_4, 129, 20);

    //Write style for flight_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_label_4, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_label_4, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_label_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_img_dot
    ui->flight_img_dot = lv_img_create(ui->flight);
    lv_obj_add_flag(ui->flight_img_dot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_img_dot, &_dot_alpha_9x9);
    lv_img_set_pivot(ui->flight_img_dot, 50,50);
    lv_img_set_angle(ui->flight_img_dot, 0);
    lv_obj_set_pos(ui->flight_img_dot, 439, 227);
    lv_obj_set_size(ui->flight_img_dot, 9, 9);

    //Write style for flight_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_img_dot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_img_dot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_img_menu
    ui->flight_img_menu = lv_img_create(ui->flight);
    lv_obj_add_flag(ui->flight_img_menu, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_img_menu, &_img_menu_alpha_13x118);
    lv_img_set_pivot(ui->flight_img_menu, 50,50);
    lv_img_set_angle(ui->flight_img_menu, 0);
    lv_obj_set_pos(ui->flight_img_menu, 433, 173);
    lv_obj_set_size(ui->flight_img_menu, 13, 118);

    //Write style for flight_img_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_img_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_img_menu, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of flight.


    //Update current screen layout.
    lv_obj_update_layout(ui->flight);

    //Init events for screen.
    events_init_flight(ui);
}

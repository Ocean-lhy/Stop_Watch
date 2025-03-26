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



void setup_scr_flight_info(lv_ui *ui)
{
    //Write codes flight_info
    ui->flight_info = lv_obj_create(NULL);
    lv_obj_set_size(ui->flight_info, 466, 466);
    lv_obj_set_scrollbar_mode(ui->flight_info, LV_SCROLLBAR_MODE_OFF);

    //Write style for flight_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->flight_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->flight_info, &_img_bg_travel_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->flight_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->flight_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_home
    ui->flight_info_home = lv_img_create(ui->flight_info);
    lv_obj_add_flag(ui->flight_info_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_info_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->flight_info_home, 50,50);
    lv_img_set_angle(ui->flight_info_home, 0);
    lv_obj_set_pos(ui->flight_info_home, 379, 307);
    lv_obj_set_size(ui->flight_info_home, 42, 57);
    lv_obj_add_flag(ui->flight_info_home, LV_OBJ_FLAG_FLOATING);

    //Write style for flight_info_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_info_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_info_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_info_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_title
    ui->flight_info_title = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_title, "Your Flight");
    lv_label_set_long_mode(ui->flight_info_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_title, 0, -96);
    lv_obj_set_size(ui->flight_info_title, 466, 89);
    lv_obj_add_flag(ui->flight_info_title, LV_OBJ_FLAG_FLOATING);

    //Write style for flight_info_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->flight_info_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->flight_info_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->flight_info_title, lv_color_hex(0xFFAA10), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->flight_info_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_number_text
    ui->flight_info_number_text = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_number_text, "FLIGHT NUMBER");
    lv_label_set_long_mode(ui->flight_info_number_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_number_text, 142, 11);
    lv_obj_set_size(ui->flight_info_number_text, 181, 20);

    //Write style for flight_info_number_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_number_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_number_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_number_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_number_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_number_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_flight_number
    ui->flight_info_flight_number = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_flight_number, "LH 2547");
    lv_label_set_long_mode(ui->flight_info_flight_number, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_flight_number, 153, 32);
    lv_obj_set_size(ui->flight_info_flight_number, 160, 36);

    //Write style for flight_info_flight_number, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_flight_number, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_flight_number, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_flight_number, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_flight_number, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_flight_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_left
    ui->flight_info_left = lv_img_create(ui->flight_info);
    lv_obj_add_flag(ui->flight_info_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_info_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->flight_info_left, 50,50);
    lv_img_set_angle(ui->flight_info_left, 0);
    lv_obj_set_pos(ui->flight_info_left, 11, 204);
    lv_obj_set_size(ui->flight_info_left, 10, 38);
    lv_obj_add_flag(ui->flight_info_left, LV_OBJ_FLAG_FLOATING);

    //Write style for flight_info_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_info_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_info_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_info_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_right
    ui->flight_info_right = lv_img_create(ui->flight_info);
    lv_obj_add_flag(ui->flight_info_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_info_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->flight_info_right, 50,50);
    lv_img_set_angle(ui->flight_info_right, 0);
    lv_obj_set_pos(ui->flight_info_right, 437, 204);
    lv_obj_set_size(ui->flight_info_right, 10, 38);
    lv_obj_add_flag(ui->flight_info_right, LV_OBJ_FLAG_FLOATING);

    //Write style for flight_info_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_info_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_info_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_info_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_gate_number
    ui->flight_info_gate_number = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_gate_number, "A32");
    lv_label_set_long_mode(ui->flight_info_gate_number, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_gate_number, 22, 222);
    lv_obj_set_size(ui->flight_info_gate_number, 84, 36);

    //Write style for flight_info_gate_number, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_gate_number, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_gate_number, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_gate_number, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_gate_number, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_gate_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_gate_text
    ui->flight_info_gate_text = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_gate_text, "GATE");
    lv_label_set_long_mode(ui->flight_info_gate_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_gate_text, 29, 194);
    lv_obj_set_size(ui->flight_info_gate_text, 68, 20);

    //Write style for flight_info_gate_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_gate_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_gate_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_gate_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_gate_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_gate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_seat_text
    ui->flight_info_seat_text = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_seat_text, "SEAT");
    lv_label_set_long_mode(ui->flight_info_seat_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_seat_text, 385, 194);
    lv_obj_set_size(ui->flight_info_seat_text, 52, 20);

    //Write style for flight_info_seat_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_seat_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_seat_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_seat_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_seat_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_seat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_seat_number
    ui->flight_info_seat_number = lv_label_create(ui->flight_info);
    lv_label_set_text(ui->flight_info_seat_number, "16B");
    lv_label_set_long_mode(ui->flight_info_seat_number, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->flight_info_seat_number, 370, 222);
    lv_obj_set_size(ui->flight_info_seat_number, 84, 36);

    //Write style for flight_info_seat_number, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->flight_info_seat_number, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->flight_info_seat_number, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->flight_info_seat_number, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->flight_info_seat_number, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->flight_info_seat_number, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes flight_info_qrcode
    ui->flight_info_qrcode = lv_img_create(ui->flight_info);
    lv_obj_add_flag(ui->flight_info_qrcode, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->flight_info_qrcode, &_img_qr_code_alpha_246x288);
    lv_img_set_pivot(ui->flight_info_qrcode, 50,50);
    lv_img_set_angle(ui->flight_info_qrcode, 0);
    lv_obj_set_pos(ui->flight_info_qrcode, 110, 474);
    lv_obj_set_size(ui->flight_info_qrcode, 246, 288);

    //Write style for flight_info_qrcode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->flight_info_qrcode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->flight_info_qrcode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->flight_info_qrcode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->flight_info_qrcode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of flight_info.


    //Update current screen layout.
    lv_obj_update_layout(ui->flight_info);

    //Init events for screen.
    events_init_flight_info(ui);
}

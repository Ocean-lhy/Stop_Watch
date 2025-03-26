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



void setup_scr_ekg(lv_ui *ui)
{
    //Write codes ekg
    ui->ekg = lv_obj_create(NULL);
    lv_obj_set_size(ui->ekg, 466, 466);
    lv_obj_set_scrollbar_mode(ui->ekg, LV_SCROLLBAR_MODE_OFF);

    //Write style for ekg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ekg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->ekg, &_img_bg_health_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->ekg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->ekg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_home
    ui->ekg_home = lv_img_create(ui->ekg);
    lv_obj_add_flag(ui->ekg_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ekg_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->ekg_home, 50,50);
    lv_img_set_angle(ui->ekg_home, 0);
    lv_obj_set_pos(ui->ekg_home, 387, 309);
    lv_obj_set_size(ui->ekg_home, 42, 57);
    lv_obj_add_flag(ui->ekg_home, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ekg_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ekg_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ekg_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_title
    ui->ekg_title = lv_label_create(ui->ekg);
    lv_label_set_text(ui->ekg_title, "ECG");
    lv_label_set_long_mode(ui->ekg_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_title, 0, -97);
    lv_obj_set_size(ui->ekg_title, 466, 89);
    lv_obj_add_flag(ui->ekg_title, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->ekg_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->ekg_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->ekg_title, lv_color_hex(0xBD1C39), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->ekg_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_cont_1
    ui->ekg_cont_1 = lv_obj_create(ui->ekg);
    lv_obj_set_pos(ui->ekg_cont_1, 126, 439);
    lv_obj_set_size(ui->ekg_cont_1, 213, 109);
    lv_obj_set_scrollbar_mode(ui->ekg_cont_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->ekg_cont_1, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_label_bmp
    ui->ekg_label_bmp = lv_label_create(ui->ekg_cont_1);
    lv_label_set_text(ui->ekg_label_bmp, "67\nbpm\n\n\n\n\n");
    lv_label_set_long_mode(ui->ekg_label_bmp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_label_bmp, 127, 39);
    lv_obj_set_size(ui->ekg_label_bmp, 63, 57);

    //Write style for ekg_label_bmp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_label_bmp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_label_bmp, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_label_bmp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_label_bmp, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_label_bmp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_label_pulse
    ui->ekg_label_pulse = lv_label_create(ui->ekg_cont_1);
    lv_label_set_text(ui->ekg_label_pulse, "PULSE");
    lv_label_set_long_mode(ui->ekg_label_pulse, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_label_pulse, 123, 9);
    lv_obj_set_size(ui->ekg_label_pulse, 68, 22);

    //Write style for ekg_label_pulse, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_label_pulse, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_label_pulse, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_label_pulse, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_label_pulse, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_label_pulse, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_img_healthy
    ui->ekg_img_healthy = lv_img_create(ui->ekg_cont_1);
    lv_obj_add_flag(ui->ekg_img_healthy, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ekg_img_healthy, &_img_heart_alpha_60x51);
    lv_img_set_pivot(ui->ekg_img_healthy, 25,22);
    lv_img_set_angle(ui->ekg_img_healthy, 0);
    lv_obj_set_pos(ui->ekg_img_healthy, 36, 28);
    lv_obj_set_size(ui->ekg_img_healthy, 60, 51);

    //Write style for ekg_img_healthy, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ekg_img_healthy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ekg_img_healthy, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_img_healthy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ekg_img_healthy, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_cont_2
    ui->ekg_cont_2 = lv_obj_create(ui->ekg);
    lv_obj_set_pos(ui->ekg_cont_2, 0, 160);
    lv_obj_set_size(ui->ekg_cont_2, 605, 135);
    lv_obj_set_scrollbar_mode(ui->ekg_cont_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->ekg_cont_2, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_img_2
    ui->ekg_img_2 = lv_img_create(ui->ekg_cont_2);
    lv_obj_add_flag(ui->ekg_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ekg_img_2, &_img_ekg_alpha_152x134);
    lv_img_set_pivot(ui->ekg_img_2, 50,50);
    lv_img_set_angle(ui->ekg_img_2, 0);
    lv_obj_set_pos(ui->ekg_img_2, 0, 0);
    lv_obj_set_size(ui->ekg_img_2, 152, 134);

    //Write style for ekg_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ekg_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ekg_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ekg_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_img_3
    ui->ekg_img_3 = lv_img_create(ui->ekg_cont_2);
    lv_obj_add_flag(ui->ekg_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ekg_img_3, &_img_ekg_alpha_152x134);
    lv_img_set_pivot(ui->ekg_img_3, 50,50);
    lv_img_set_angle(ui->ekg_img_3, 0);
    lv_obj_set_pos(ui->ekg_img_3, 152, 0);
    lv_obj_set_size(ui->ekg_img_3, 152, 134);

    //Write style for ekg_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ekg_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ekg_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ekg_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_img_4
    ui->ekg_img_4 = lv_img_create(ui->ekg_cont_2);
    lv_obj_add_flag(ui->ekg_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ekg_img_4, &_img_ekg_alpha_152x134);
    lv_img_set_pivot(ui->ekg_img_4, 50,50);
    lv_img_set_angle(ui->ekg_img_4, 0);
    lv_obj_set_pos(ui->ekg_img_4, 304, 0);
    lv_obj_set_size(ui->ekg_img_4, 152, 134);

    //Write style for ekg_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ekg_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ekg_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ekg_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_img_5
    ui->ekg_img_5 = lv_img_create(ui->ekg_cont_2);
    lv_obj_add_flag(ui->ekg_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ekg_img_5, &_img_ekg_alpha_152x134);
    lv_img_set_pivot(ui->ekg_img_5, 50,50);
    lv_img_set_angle(ui->ekg_img_5, 0);
    lv_obj_set_pos(ui->ekg_img_5, 456, 0);
    lv_obj_set_size(ui->ekg_img_5, 152, 134);

    //Write style for ekg_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ekg_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ekg_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ekg_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_label_RR_text
    ui->ekg_label_RR_text = lv_label_create(ui->ekg);
    lv_label_set_text(ui->ekg_label_RR_text, "R-R INTERVAL");
    lv_label_set_long_mode(ui->ekg_label_RR_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_label_RR_text, 28, 87);
    lv_obj_set_size(ui->ekg_label_RR_text, 149, 26);
    lv_obj_add_flag(ui->ekg_label_RR_text, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_label_RR_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_label_RR_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_label_RR_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_label_RR_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_label_RR_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_label_RR_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_label_count_text
    ui->ekg_label_count_text = lv_label_create(ui->ekg);
    lv_label_set_text(ui->ekg_label_count_text, "BEAT COUNT");
    lv_label_set_long_mode(ui->ekg_label_count_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_label_count_text, 304, 87);
    lv_obj_set_size(ui->ekg_label_count_text, 149, 26);
    lv_obj_add_flag(ui->ekg_label_count_text, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_label_count_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_label_count_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_label_count_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_label_count_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_label_count_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_label_count_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_label_RR_interval
    ui->ekg_label_RR_interval = lv_label_create(ui->ekg);
    lv_label_set_text(ui->ekg_label_RR_interval, "940\n\n\n\n");
    lv_label_set_long_mode(ui->ekg_label_RR_interval, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_label_RR_interval, 70, 114);
    lv_obj_set_size(ui->ekg_label_RR_interval, 67, 28);
    lv_obj_add_flag(ui->ekg_label_RR_interval, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_label_RR_interval, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_label_RR_interval, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_label_RR_interval, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_label_RR_interval, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_label_RR_interval, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_label_RR_interval, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ekg_label_count
    ui->ekg_label_count = lv_label_create(ui->ekg);
    lv_label_set_text(ui->ekg_label_count, "320\n\n\n\n");
    lv_label_set_long_mode(ui->ekg_label_count, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ekg_label_count, 345, 114);
    lv_obj_set_size(ui->ekg_label_count, 67, 28);
    lv_obj_add_flag(ui->ekg_label_count, LV_OBJ_FLAG_FLOATING);

    //Write style for ekg_label_count, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ekg_label_count, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ekg_label_count, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ekg_label_count, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ekg_label_count, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ekg_label_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of ekg.


    //Update current screen layout.
    lv_obj_update_layout(ui->ekg);

    //Init events for screen.
    events_init_ekg(ui);
}

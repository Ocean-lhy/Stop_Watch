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



void setup_scr_home_digital(lv_ui *ui)
{
    //Write codes home_digital
    ui->home_digital = lv_obj_create(NULL);
    lv_obj_set_size(ui->home_digital, 466, 466);
    lv_obj_set_scrollbar_mode(ui->home_digital, LV_SCROLLBAR_MODE_OFF);

    //Write style for home_digital, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_digital, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->home_digital, &_img_bg_digital_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->home_digital, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->home_digital, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_arc_step
    ui->home_digital_arc_step = lv_arc_create(ui->home_digital);
    lv_arc_set_mode(ui->home_digital_arc_step, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->home_digital_arc_step, 0, 100);
    lv_arc_set_bg_angles(ui->home_digital_arc_step, 60, 120);
    lv_arc_set_value(ui->home_digital_arc_step, 70);
    lv_arc_set_rotation(ui->home_digital_arc_step, 0);
    lv_obj_set_pos(ui->home_digital_arc_step, 55, 99);
    lv_obj_set_size(ui->home_digital_arc_step, 383, 356);

    //Write style for home_digital_arc_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->home_digital_arc_step, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_digital_arc_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_digital_arc_step, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_arc_step, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_digital_arc_step, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->home_digital_arc_step, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_digital_arc_step, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_digital_arc_step, lv_color_hex(0xFF4818), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for home_digital_arc_step, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_digital_arc_step, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->home_digital_arc_step, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes home_digital_arc_flash
    ui->home_digital_arc_flash = lv_arc_create(ui->home_digital);
    lv_arc_set_mode(ui->home_digital_arc_flash, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->home_digital_arc_flash, 0, 100);
    lv_arc_set_bg_angles(ui->home_digital_arc_flash, 238, 300);
    lv_arc_set_value(ui->home_digital_arc_flash, 70);
    lv_arc_set_rotation(ui->home_digital_arc_flash, 0);
    lv_obj_set_pos(ui->home_digital_arc_flash, 54, 5);
    lv_obj_set_size(ui->home_digital_arc_flash, 388, 356);

    //Write style for home_digital_arc_flash, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_digital_arc_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_digital_arc_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->home_digital_arc_flash, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_digital_arc_flash, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_digital_arc_flash, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_arc_flash, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_arc_flash, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_arc_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_arc_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_arc_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_arc_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for home_digital_arc_flash, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->home_digital_arc_flash, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->home_digital_arc_flash, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->home_digital_arc_flash, lv_color_hex(0x1000ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for home_digital_arc_flash, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_digital_arc_flash, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->home_digital_arc_flash, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes home_digital_img_nxpLogo
    ui->home_digital_img_nxpLogo = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_nxpLogo, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_nxpLogo, &_img_nxp_alpha_77x23);
    lv_img_set_pivot(ui->home_digital_img_nxpLogo, 50,50);
    lv_img_set_angle(ui->home_digital_img_nxpLogo, 0);
    lv_obj_set_pos(ui->home_digital_img_nxpLogo, 482, 210);
    lv_obj_set_size(ui->home_digital_img_nxpLogo, 77, 23);

    //Write style for home_digital_img_nxpLogo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_nxpLogo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_nxpLogo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_nxpLogo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_nxpLogo, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_stepIcon
    ui->home_digital_img_stepIcon = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_stepIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_stepIcon, &_icn_step_red_alpha_20x24);
    lv_img_set_pivot(ui->home_digital_img_stepIcon, 50,50);
    lv_img_set_angle(ui->home_digital_img_stepIcon, 0);
    lv_obj_set_pos(ui->home_digital_img_stepIcon, 185, 401);
    lv_obj_set_size(ui->home_digital_img_stepIcon, 20, 24);

    //Write style for home_digital_img_stepIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_stepIcon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_stepIcon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_stepIcon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_stepIcon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_stepText
    ui->home_digital_label_stepText = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_stepText, "1526");
    lv_label_set_long_mode(ui->home_digital_label_stepText, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_stepText, 221, 401);
    lv_obj_set_size(ui->home_digital_label_stepText, 70, 24);

    //Write style for home_digital_label_stepText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_stepText, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_stepText, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_stepText, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_stepText, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_stepText, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_stepText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_weather1Text
    ui->home_digital_label_weather1Text = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_weather1Text, "26°");
    lv_label_set_long_mode(ui->home_digital_label_weather1Text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_weather1Text, 77, 294);
    lv_obj_set_size(ui->home_digital_label_weather1Text, 55, 24);

    //Write style for home_digital_label_weather1Text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_weather1Text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_weather1Text, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_weather1Text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_weather1Text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_weather1Text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_weather1Text, 253, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_digital_label_weather1Text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_digital_label_weather1Text, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_weather1Text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_week
    ui->home_digital_label_week = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_week, "WED");
    lv_label_set_long_mode(ui->home_digital_label_week, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_week, 40, 169);
    lv_obj_set_size(ui->home_digital_label_week, 79, 29);

    //Write style for home_digital_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_week, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_week, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_week, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_week, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_week, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_week, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_date
    ui->home_digital_label_date = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_date, "05/15");
    lv_label_set_long_mode(ui->home_digital_label_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_date, 40, 131);
    lv_obj_set_size(ui->home_digital_label_date, 87, 24);

    //Write style for home_digital_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_date, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_date, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_flash
    ui->home_digital_img_flash = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_flash, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_flash, &_icn_flash_blue_alpha_20x24);
    lv_img_set_pivot(ui->home_digital_img_flash, 50,50);
    lv_img_set_angle(ui->home_digital_img_flash, 0);
    lv_obj_set_pos(ui->home_digital_img_flash, 192, 41);
    lv_obj_set_size(ui->home_digital_img_flash, 20, 24);

    //Write style for home_digital_img_flash, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_flash, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_flash, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_flash, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_flashText
    ui->home_digital_label_flashText = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_flashText, "86%");
    lv_label_set_long_mode(ui->home_digital_label_flashText, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_flashText, 221, 41);
    lv_obj_set_size(ui->home_digital_label_flashText, 70, 24);

    //Write style for home_digital_label_flashText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_flashText, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_flashText, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_flashText, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_flashText, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_flashText, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_flashText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_dialDot
    ui->home_digital_img_dialDot = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_dialDot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_dialDot, &_img_menu_alpha_13x139);
    lv_img_set_pivot(ui->home_digital_img_dialDot, 50,50);
    lv_img_set_angle(ui->home_digital_img_dialDot, 0);
    lv_obj_set_pos(ui->home_digital_img_dialDot, 433, 166);
    lv_obj_set_size(ui->home_digital_img_dialDot, 13, 139);

    //Write style for home_digital_img_dialDot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_dialDot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_dialDot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_dialDot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_dialDot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_min
    ui->home_digital_label_min = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_min, "32");
    lv_label_set_long_mode(ui->home_digital_label_min, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_min, 142, 475);
    lv_obj_set_size(ui->home_digital_label_min, 180, 123);

    //Write style for home_digital_label_min, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_min, lv_color_hex(0xFF4818), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_min, &lv_font_montserratMedium_47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_min, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_min, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_min, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_label_hour
    ui->home_digital_label_hour = lv_label_create(ui->home_digital);
    lv_label_set_text(ui->home_digital_label_hour, "15");
    lv_label_set_long_mode(ui->home_digital_label_hour, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_digital_label_hour, 158, -153);
    lv_obj_set_size(ui->home_digital_label_hour, 178, 145);

    //Write style for home_digital_label_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_digital_label_hour, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_digital_label_hour, &lv_font_montserratMedium_47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_digital_label_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_digital_label_hour, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_digital_label_hour, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_digital_label_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_messageIcon
    ui->home_digital_img_messageIcon = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_messageIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_messageIcon, &_icn_message_alpha_29x29);
    lv_img_set_pivot(ui->home_digital_img_messageIcon, 50,50);
    lv_img_set_angle(ui->home_digital_img_messageIcon, 0);
    lv_obj_set_pos(ui->home_digital_img_messageIcon, 363, 319);
    lv_obj_set_size(ui->home_digital_img_messageIcon, 29, 29);

    //Write style for home_digital_img_messageIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_messageIcon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_messageIcon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_messageIcon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_messageIcon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_sportIcon
    ui->home_digital_img_sportIcon = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_sportIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_sportIcon, &_icn_sport_alpha_14x28);
    lv_img_set_pivot(ui->home_digital_img_sportIcon, 50,50);
    lv_img_set_angle(ui->home_digital_img_sportIcon, 0);
    lv_obj_set_pos(ui->home_digital_img_sportIcon, 376, 121);
    lv_obj_set_size(ui->home_digital_img_sportIcon, 14, 28);

    //Write style for home_digital_img_sportIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_sportIcon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_sportIcon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_sportIcon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_sportIcon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_weather1Icon
    ui->home_digital_img_weather1Icon = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_weather1Icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_weather1Icon, &_icn_weather_1_alpha_48x39);
    lv_img_set_pivot(ui->home_digital_img_weather1Icon, 50,50);
    lv_img_set_angle(ui->home_digital_img_weather1Icon, 0);
    lv_obj_set_pos(ui->home_digital_img_weather1Icon, 67, 247);
    lv_obj_set_size(ui->home_digital_img_weather1Icon, 48, 39);

    //Write style for home_digital_img_weather1Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_weather1Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_digital_img_weather1Icon, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_weather1Icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_weather1Icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_weather1Icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_sportText
    ui->home_digital_img_sportText = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_sportText, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_sportText, &_text_sport_alpha_59x59);
    lv_img_set_pivot(ui->home_digital_img_sportText, 50,50);
    lv_img_set_angle(ui->home_digital_img_sportText, 30);
    lv_obj_set_pos(ui->home_digital_img_sportText, 381, 90);
    lv_obj_set_size(ui->home_digital_img_sportText, 59, 59);

    //Write style for home_digital_img_sportText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_sportText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_sportText, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_sportText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_sportText, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_messageText
    ui->home_digital_img_messageText = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_messageText, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_messageText, &_text_message_alpha_83x83);
    lv_img_set_pivot(ui->home_digital_img_messageText, 50,50);
    lv_img_set_angle(ui->home_digital_img_messageText, -50);
    lv_obj_set_pos(ui->home_digital_img_messageText, 363, 305);
    lv_obj_set_size(ui->home_digital_img_messageText, 83, 83);

    //Write style for home_digital_img_messageText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_messageText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_messageText, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_messageText, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_messageText, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_digital_img_dot
    ui->home_digital_img_dot = lv_img_create(ui->home_digital);
    lv_obj_add_flag(ui->home_digital_img_dot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_digital_img_dot, &_dot_alpha_9x9);
    lv_img_set_pivot(ui->home_digital_img_dot, 50,50);
    lv_img_set_angle(ui->home_digital_img_dot, 0);
    lv_obj_set_pos(ui->home_digital_img_dot, 433, 166);
    lv_obj_set_size(ui->home_digital_img_dot, 9, 9);

    //Write style for home_digital_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_digital_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_digital_img_dot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_digital_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_digital_img_dot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of home_digital.


    //Update current screen layout.
    lv_obj_update_layout(ui->home_digital);

    //Init events for screen.
    events_init_home_digital(ui);
}

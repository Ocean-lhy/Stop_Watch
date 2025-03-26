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



void setup_scr_menstrual(lv_ui *ui)
{
    //Write codes menstrual
    ui->menstrual = lv_obj_create(NULL);
    lv_obj_set_size(ui->menstrual, 466, 466);
    lv_obj_set_scrollbar_mode(ui->menstrual, LV_SCROLLBAR_MODE_OFF);

    //Write style for menstrual, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menstrual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->menstrual, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->menstrual, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->menstrual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_home
    ui->menstrual_home = lv_img_create(ui->menstrual);
    lv_obj_add_flag(ui->menstrual_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menstrual_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->menstrual_home, 50,50);
    lv_img_set_angle(ui->menstrual_home, 0);
    lv_obj_set_pos(ui->menstrual_home, 387, 309);
    lv_obj_set_size(ui->menstrual_home, 42, 57);

    //Write style for menstrual_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menstrual_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menstrual_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menstrual_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_left
    ui->menstrual_left = lv_img_create(ui->menstrual);
    lv_obj_add_flag(ui->menstrual_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menstrual_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->menstrual_left, 50,50);
    lv_img_set_angle(ui->menstrual_left, 0);
    lv_obj_set_pos(ui->menstrual_left, 11, 204);
    lv_obj_set_size(ui->menstrual_left, 10, 38);
    lv_obj_add_flag(ui->menstrual_left, LV_OBJ_FLAG_FLOATING);

    //Write style for menstrual_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menstrual_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menstrual_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menstrual_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_right
    ui->menstrual_right = lv_img_create(ui->menstrual);
    lv_obj_add_flag(ui->menstrual_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menstrual_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->menstrual_right, 50,50);
    lv_img_set_angle(ui->menstrual_right, 0);
    lv_obj_set_pos(ui->menstrual_right, 437, 204);
    lv_obj_set_size(ui->menstrual_right, 10, 38);
    lv_obj_add_flag(ui->menstrual_right, LV_OBJ_FLAG_FLOATING);

    //Write style for menstrual_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menstrual_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menstrual_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menstrual_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_title
    ui->menstrual_title = lv_label_create(ui->menstrual);
    lv_label_set_text(ui->menstrual_title, "Step count");
    lv_label_set_long_mode(ui->menstrual_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menstrual_title, 0, -99);
    lv_obj_set_size(ui->menstrual_title, 466, 89);
    lv_obj_add_flag(ui->menstrual_title, LV_OBJ_FLAG_FLOATING);

    //Write style for menstrual_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menstrual_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menstrual_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menstrual_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menstrual_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menstrual_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menstrual_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->menstrual_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->menstrual_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->menstrual_title, lv_color_hex(0xBD1C39), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->menstrual_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menstrual_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_img_ovulation
    ui->menstrual_img_ovulation = lv_img_create(ui->menstrual);
    lv_obj_add_flag(ui->menstrual_img_ovulation, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menstrual_img_ovulation, &_img_menstrual_chart_alpha_262x269);
    lv_img_set_pivot(ui->menstrual_img_ovulation, 50,50);
    lv_img_set_angle(ui->menstrual_img_ovulation, 0);
    lv_obj_set_pos(ui->menstrual_img_ovulation, 102, 121);
    lv_obj_set_size(ui->menstrual_img_ovulation, 262, 269);

    //Write style for menstrual_img_ovulation, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menstrual_img_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menstrual_img_ovulation, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_img_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menstrual_img_ovulation, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_label_ovulation
    ui->menstrual_label_ovulation = lv_label_create(ui->menstrual);
    lv_label_set_text(ui->menstrual_label_ovulation, "Ovulation\n\n\n\n");
    lv_label_set_long_mode(ui->menstrual_label_ovulation, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menstrual_label_ovulation, 143, 486);
    lv_obj_set_size(ui->menstrual_label_ovulation, 179, 45);

    //Write style for menstrual_label_ovulation, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menstrual_label_ovulation, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menstrual_label_ovulation, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menstrual_label_ovulation, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menstrual_label_ovulation, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menstrual_label_ovulation, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_label_cycle
    ui->menstrual_label_cycle = lv_label_create(ui->menstrual);
    lv_label_set_text(ui->menstrual_label_cycle, "CYCLE DAY");
    lv_label_set_long_mode(ui->menstrual_label_cycle, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menstrual_label_cycle, 175, 22);
    lv_obj_set_size(ui->menstrual_label_cycle, 114, 28);

    //Write style for menstrual_label_cycle, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menstrual_label_cycle, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menstrual_label_cycle, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menstrual_label_cycle, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menstrual_label_cycle, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menstrual_label_cycle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menstrual_label_days
    ui->menstrual_label_days = lv_label_create(ui->menstrual);
    lv_label_set_text(ui->menstrual_label_days, "12");
    lv_label_set_long_mode(ui->menstrual_label_days, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menstrual_label_days, 155, 194);
    lv_obj_set_size(ui->menstrual_label_days, 154, 121);

    //Write style for menstrual_label_days, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menstrual_label_days, lv_color_hex(0x00DB0e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menstrual_label_days, &lv_font_montserratMedium_47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menstrual_label_days, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menstrual_label_days, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menstrual_label_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menstrual.


    //Update current screen layout.
    lv_obj_update_layout(ui->menstrual);

    //Init events for screen.
    events_init_menstrual(ui);
}

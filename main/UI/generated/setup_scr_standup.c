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



void setup_scr_standup(lv_ui *ui)
{
    //Write codes standup
    ui->standup = lv_obj_create(NULL);
    lv_obj_set_size(ui->standup, 466, 466);
    lv_obj_set_scrollbar_mode(ui->standup, LV_SCROLLBAR_MODE_OFF);

    //Write style for standup, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->standup, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->standup, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->standup, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->standup, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_stand_icon
    ui->standup_stand_icon = lv_img_create(ui->standup);
    lv_obj_add_flag(ui->standup_stand_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->standup_stand_icon, &_img_stand_up_alpha_99x99);
    lv_img_set_pivot(ui->standup_stand_icon, 50,50);
    lv_img_set_angle(ui->standup_stand_icon, 0);
    lv_obj_set_pos(ui->standup_stand_icon, 183, -121);
    lv_obj_set_size(ui->standup_stand_icon, 99, 99);

    //Write style for standup_stand_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->standup_stand_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->standup_stand_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_stand_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->standup_stand_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_stand_text
    ui->standup_stand_text = lv_label_create(ui->standup);
    lv_label_set_text(ui->standup_stand_text, "Time to stand up!");
    lv_label_set_long_mode(ui->standup_stand_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->standup_stand_text, 51, 146);
    lv_obj_set_size(ui->standup_stand_text, 363, 38);

    //Write style for standup_stand_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->standup_stand_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->standup_stand_text, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->standup_stand_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->standup_stand_text, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->standup_stand_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->standup_stand_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_stand_time
    ui->standup_stand_time = lv_label_create(ui->standup);
    lv_label_set_text(ui->standup_stand_time, "Stand up and move a little for one mitute. ");
    lv_label_set_long_mode(ui->standup_stand_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->standup_stand_time, 53, 204);
    lv_obj_set_size(ui->standup_stand_time, 360, 58);

    //Write style for standup_stand_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->standup_stand_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->standup_stand_time, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->standup_stand_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->standup_stand_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->standup_stand_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_left
    ui->standup_left = lv_img_create(ui->standup);
    lv_obj_add_flag(ui->standup_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->standup_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->standup_left, 50,50);
    lv_img_set_angle(ui->standup_left, 0);
    lv_obj_set_pos(ui->standup_left, 11, 204);
    lv_obj_set_size(ui->standup_left, 10, 38);

    //Write style for standup_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->standup_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->standup_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->standup_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_right
    ui->standup_right = lv_img_create(ui->standup);
    lv_obj_add_flag(ui->standup_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->standup_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->standup_right, 50,50);
    lv_img_set_angle(ui->standup_right, 0);
    lv_obj_set_pos(ui->standup_right, 437, 204);
    lv_obj_set_size(ui->standup_right, 10, 38);

    //Write style for standup_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->standup_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->standup_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->standup_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_time_text
    ui->standup_time_text = lv_label_create(ui->standup);
    lv_label_set_text(ui->standup_time_text, "1 min ago");
    lv_label_set_long_mode(ui->standup_time_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->standup_time_text, 173, 287);
    lv_obj_set_size(ui->standup_time_text, 118, 30);

    //Write style for standup_time_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->standup_time_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->standup_time_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->standup_time_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->standup_time_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->standup_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_ok_btn
    ui->standup_ok_btn = lv_label_create(ui->standup);
    lv_label_set_text(ui->standup_ok_btn, "OK");
    lv_label_set_long_mode(ui->standup_ok_btn, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->standup_ok_btn, 130, 353);
    lv_obj_set_size(ui->standup_ok_btn, 204, 58);
    lv_obj_add_flag(ui->standup_ok_btn, LV_OBJ_FLAG_CLICKABLE);

    //Write style for standup_ok_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->standup_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_ok_btn, 23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->standup_ok_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->standup_ok_btn, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->standup_ok_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->standup_ok_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->standup_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->standup_ok_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->standup_ok_btn, 105, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->standup_ok_btn, lv_color_hex(0x414041), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->standup_ok_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->standup_ok_btn, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->standup_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->standup_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->standup_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->standup_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes standup_home_text
    ui->standup_home_text = lv_img_create(ui->standup);
    lv_obj_add_flag(ui->standup_home_text, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->standup_home_text, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->standup_home_text, 50,50);
    lv_img_set_angle(ui->standup_home_text, 0);
    lv_obj_set_pos(ui->standup_home_text, 379, 307);
    lv_obj_set_size(ui->standup_home_text, 42, 57);

    //Write style for standup_home_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->standup_home_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->standup_home_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->standup_home_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->standup_home_text, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of standup.


    //Update current screen layout.
    lv_obj_update_layout(ui->standup);

    //Init events for screen.
    events_init_standup(ui);
}

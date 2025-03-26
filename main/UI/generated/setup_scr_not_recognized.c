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



void setup_scr_not_recognized(lv_ui *ui)
{
    //Write codes not_recognized
    ui->not_recognized = lv_obj_create(NULL);
    lv_obj_set_size(ui->not_recognized, 466, 466);
    lv_obj_set_scrollbar_mode(ui->not_recognized, LV_SCROLLBAR_MODE_OFF);

    //Write style for not_recognized, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->not_recognized, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->not_recognized, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->not_recognized, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->not_recognized, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes not_recognized_left
    ui->not_recognized_left = lv_img_create(ui->not_recognized);
    lv_obj_add_flag(ui->not_recognized_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->not_recognized_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->not_recognized_left, 50,50);
    lv_img_set_angle(ui->not_recognized_left, 0);
    lv_obj_set_pos(ui->not_recognized_left, 11, 204);
    lv_obj_set_size(ui->not_recognized_left, 10, 38);

    //Write style for not_recognized_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->not_recognized_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->not_recognized_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->not_recognized_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->not_recognized_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes not_recognized_right
    ui->not_recognized_right = lv_img_create(ui->not_recognized);
    lv_obj_add_flag(ui->not_recognized_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->not_recognized_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->not_recognized_right, 50,50);
    lv_img_set_angle(ui->not_recognized_right, 0);
    lv_obj_set_pos(ui->not_recognized_right, 437, 204);
    lv_obj_set_size(ui->not_recognized_right, 10, 38);

    //Write style for not_recognized_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->not_recognized_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->not_recognized_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->not_recognized_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->not_recognized_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes not_recognized_home
    ui->not_recognized_home = lv_img_create(ui->not_recognized);
    lv_obj_add_flag(ui->not_recognized_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->not_recognized_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->not_recognized_home, 50,50);
    lv_img_set_angle(ui->not_recognized_home, 0);
    lv_obj_set_pos(ui->not_recognized_home, 379, 307);
    lv_obj_set_size(ui->not_recognized_home, 42, 57);

    //Write style for not_recognized_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->not_recognized_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->not_recognized_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->not_recognized_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->not_recognized_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes not_recognized_command_text
    ui->not_recognized_command_text = lv_label_create(ui->not_recognized);
    lv_label_set_text(ui->not_recognized_command_text, "Command not recognized");
    lv_label_set_long_mode(ui->not_recognized_command_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->not_recognized_command_text, 140, 399);
    lv_obj_set_size(ui->not_recognized_command_text, 186, 54);

    //Write style for not_recognized_command_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->not_recognized_command_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->not_recognized_command_text, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->not_recognized_command_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->not_recognized_command_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->not_recognized_command_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes not_recognized_no_mic_icon
    ui->not_recognized_no_mic_icon = lv_img_create(ui->not_recognized);
    lv_obj_add_flag(ui->not_recognized_no_mic_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->not_recognized_no_mic_icon, &_img_mic_2_alpha_225x231);
    lv_img_set_pivot(ui->not_recognized_no_mic_icon, 50,50);
    lv_img_set_angle(ui->not_recognized_no_mic_icon, 0);
    lv_obj_set_pos(ui->not_recognized_no_mic_icon, 120, -240);
    lv_obj_set_size(ui->not_recognized_no_mic_icon, 225, 231);

    //Write style for not_recognized_no_mic_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->not_recognized_no_mic_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->not_recognized_no_mic_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->not_recognized_no_mic_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->not_recognized_no_mic_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of not_recognized.


    //Update current screen layout.
    lv_obj_update_layout(ui->not_recognized);

    //Init events for screen.
    events_init_not_recognized(ui);
}

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



void setup_scr_play_sound(lv_ui *ui)
{
    //Write codes play_sound
    ui->play_sound = lv_obj_create(NULL);
    lv_obj_set_size(ui->play_sound, 466, 466);
    lv_obj_set_scrollbar_mode(ui->play_sound, LV_SCROLLBAR_MODE_OFF);

    //Write style for play_sound, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->play_sound, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->play_sound, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->play_sound, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->play_sound, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes play_sound_right
    ui->play_sound_right = lv_img_create(ui->play_sound);
    lv_obj_add_flag(ui->play_sound_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->play_sound_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->play_sound_right, 50,50);
    lv_img_set_angle(ui->play_sound_right, 0);
    lv_obj_set_pos(ui->play_sound_right, 437, 204);
    lv_obj_set_size(ui->play_sound_right, 10, 38);
    lv_obj_add_flag(ui->play_sound_right, LV_OBJ_FLAG_FLOATING);

    //Write style for play_sound_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->play_sound_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->play_sound_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->play_sound_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->play_sound_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes play_sound_left
    ui->play_sound_left = lv_img_create(ui->play_sound);
    lv_obj_add_flag(ui->play_sound_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->play_sound_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->play_sound_left, 50,50);
    lv_img_set_angle(ui->play_sound_left, 0);
    lv_obj_set_pos(ui->play_sound_left, 11, 204);
    lv_obj_set_size(ui->play_sound_left, 10, 38);
    lv_obj_add_flag(ui->play_sound_left, LV_OBJ_FLAG_FLOATING);

    //Write style for play_sound_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->play_sound_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->play_sound_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->play_sound_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->play_sound_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes play_sound_home
    ui->play_sound_home = lv_img_create(ui->play_sound);
    lv_obj_add_flag(ui->play_sound_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->play_sound_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->play_sound_home, 50,50);
    lv_img_set_angle(ui->play_sound_home, 0);
    lv_obj_set_pos(ui->play_sound_home, 387, 309);
    lv_obj_set_size(ui->play_sound_home, 42, 57);
    lv_obj_add_flag(ui->play_sound_home, LV_OBJ_FLAG_FLOATING);

    //Write style for play_sound_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->play_sound_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->play_sound_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->play_sound_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->play_sound_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes play_sound_img_find
    ui->play_sound_img_find = lv_img_create(ui->play_sound);
    lv_obj_add_flag(ui->play_sound_img_find, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->play_sound_img_find, &_img_find_device2_alpha_199x199);
    lv_img_set_pivot(ui->play_sound_img_find, 84,84);
    lv_img_set_angle(ui->play_sound_img_find, 0);
    lv_obj_set_pos(ui->play_sound_img_find, 133, 109);
    lv_obj_set_size(ui->play_sound_img_find, 199, 199);

    //Write style for play_sound_img_find, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->play_sound_img_find, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->play_sound_img_find, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->play_sound_img_find, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->play_sound_img_find, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes play_sound_btn_cancel
    ui->play_sound_btn_cancel = lv_btn_create(ui->play_sound);
    ui->play_sound_btn_cancel_label = lv_label_create(ui->play_sound_btn_cancel);
    lv_label_set_text(ui->play_sound_btn_cancel_label, "CANCEL");
    lv_label_set_long_mode(ui->play_sound_btn_cancel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->play_sound_btn_cancel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->play_sound_btn_cancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->play_sound_btn_cancel_label, LV_PCT(100));
    lv_obj_set_pos(ui->play_sound_btn_cancel, 149, 429);
    lv_obj_set_size(ui->play_sound_btn_cancel, 167, 64);

    //Write style for play_sound_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->play_sound_btn_cancel, 171, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->play_sound_btn_cancel, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->play_sound_btn_cancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->play_sound_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->play_sound_btn_cancel, 32, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->play_sound_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->play_sound_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->play_sound_btn_cancel, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->play_sound_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->play_sound_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes play_sound_title
    ui->play_sound_title = lv_label_create(ui->play_sound);
    lv_label_set_text(ui->play_sound_title, "Playing Sound\n");
    lv_label_set_long_mode(ui->play_sound_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->play_sound_title, 38, -45);
    lv_obj_set_size(ui->play_sound_title, 391, 46);
    lv_obj_add_flag(ui->play_sound_title, LV_OBJ_FLAG_FLOATING);

    //Write style for play_sound_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->play_sound_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->play_sound_title, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->play_sound_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->play_sound_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->play_sound_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->play_sound_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->play_sound_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of play_sound.


    //Update current screen layout.
    lv_obj_update_layout(ui->play_sound);

    //Init events for screen.
    events_init_play_sound(ui);
}

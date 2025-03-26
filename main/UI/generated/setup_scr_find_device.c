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



void setup_scr_find_device(lv_ui *ui)
{
    //Write codes find_device
    ui->find_device = lv_obj_create(NULL);
    lv_obj_set_size(ui->find_device, 466, 466);
    lv_obj_set_scrollbar_mode(ui->find_device, LV_SCROLLBAR_MODE_OFF);

    //Write style for find_device, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->find_device, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->find_device, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->find_device, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->find_device, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes find_device_title
    ui->find_device_title = lv_label_create(ui->find_device);
    lv_label_set_text(ui->find_device_title, "Find Device\n");
    lv_label_set_long_mode(ui->find_device_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->find_device_title, 0, -97);
    lv_obj_set_size(ui->find_device_title, 466, 89);
    lv_obj_add_flag(ui->find_device_title, LV_OBJ_FLAG_FLOATING);

    //Write style for find_device_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->find_device_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->find_device_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->find_device_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->find_device_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->find_device_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->find_device_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->find_device_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->find_device_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->find_device_title, lv_color_hex(0xD5D2D5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->find_device_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->find_device_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes find_device_right
    ui->find_device_right = lv_img_create(ui->find_device);
    lv_obj_add_flag(ui->find_device_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->find_device_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->find_device_right, 50,50);
    lv_img_set_angle(ui->find_device_right, 0);
    lv_obj_set_pos(ui->find_device_right, 437, 204);
    lv_obj_set_size(ui->find_device_right, 10, 38);
    lv_obj_add_flag(ui->find_device_right, LV_OBJ_FLAG_FLOATING);

    //Write style for find_device_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->find_device_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->find_device_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->find_device_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->find_device_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes find_device_left
    ui->find_device_left = lv_img_create(ui->find_device);
    lv_obj_add_flag(ui->find_device_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->find_device_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->find_device_left, 50,50);
    lv_img_set_angle(ui->find_device_left, 0);
    lv_obj_set_pos(ui->find_device_left, 11, 204);
    lv_obj_set_size(ui->find_device_left, 10, 38);
    lv_obj_add_flag(ui->find_device_left, LV_OBJ_FLAG_FLOATING);

    //Write style for find_device_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->find_device_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->find_device_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->find_device_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->find_device_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes find_device_home
    ui->find_device_home = lv_img_create(ui->find_device);
    lv_obj_add_flag(ui->find_device_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->find_device_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->find_device_home, 50,50);
    lv_img_set_angle(ui->find_device_home, 0);
    lv_obj_set_pos(ui->find_device_home, 387, 309);
    lv_obj_set_size(ui->find_device_home, 42, 57);
    lv_obj_add_flag(ui->find_device_home, LV_OBJ_FLAG_FLOATING);

    //Write style for find_device_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->find_device_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->find_device_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->find_device_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->find_device_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes find_device_img_find
    ui->find_device_img_find = lv_img_create(ui->find_device);
    lv_obj_add_flag(ui->find_device_img_find, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->find_device_img_find, &_img_find_device_alpha_137x135);
    lv_img_set_pivot(ui->find_device_img_find, 50,50);
    lv_img_set_angle(ui->find_device_img_find, 0);
    lv_obj_set_pos(ui->find_device_img_find, 172, 165);
    lv_obj_set_size(ui->find_device_img_find, 137, 135);

    //Write style for find_device_img_find, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->find_device_img_find, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->find_device_img_find, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->find_device_img_find, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->find_device_img_find, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes find_device_btn_start
    ui->find_device_btn_start = lv_btn_create(ui->find_device);
    ui->find_device_btn_start_label = lv_label_create(ui->find_device_btn_start);
    lv_label_set_text(ui->find_device_btn_start_label, "START");
    lv_label_set_long_mode(ui->find_device_btn_start_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->find_device_btn_start_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->find_device_btn_start, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->find_device_btn_start_label, LV_PCT(100));
    lv_obj_set_pos(ui->find_device_btn_start, 155, 422);
    lv_obj_set_size(ui->find_device_btn_start, 154, 67);

    //Write style for find_device_btn_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->find_device_btn_start, 171, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->find_device_btn_start, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->find_device_btn_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->find_device_btn_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->find_device_btn_start, 33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->find_device_btn_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->find_device_btn_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->find_device_btn_start, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->find_device_btn_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->find_device_btn_start, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of find_device.


    //Update current screen layout.
    lv_obj_update_layout(ui->find_device);

    //Init events for screen.
    events_init_find_device(ui);
}

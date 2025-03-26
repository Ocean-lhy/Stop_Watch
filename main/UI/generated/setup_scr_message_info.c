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



void setup_scr_message_info(lv_ui *ui)
{
    //Write codes message_info
    ui->message_info = lv_obj_create(NULL);
    lv_obj_set_size(ui->message_info, 466, 466);
    lv_obj_set_scrollbar_mode(ui->message_info, LV_SCROLLBAR_MODE_OFF);

    //Write style for message_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->message_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->message_info, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->message_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->message_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_app_icon
    ui->message_info_app_icon = lv_img_create(ui->message_info);
    lv_obj_add_flag(ui->message_info_app_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->message_info_app_icon, &_icn_whatsapp_alpha_71x71);
    lv_img_set_pivot(ui->message_info_app_icon, 50,50);
    lv_img_set_angle(ui->message_info_app_icon, 0);
    lv_obj_set_pos(ui->message_info_app_icon, 197, -85);
    lv_obj_set_size(ui->message_info_app_icon, 71, 71);

    //Write style for message_info_app_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->message_info_app_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->message_info_app_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_app_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->message_info_app_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_sender
    ui->message_info_sender = lv_label_create(ui->message_info);
    lv_label_set_text(ui->message_info_sender, "Elena");
    lv_label_set_long_mode(ui->message_info_sender, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->message_info_sender, 179, 8);
    lv_obj_set_size(ui->message_info_sender, 106, 38);

    //Write style for message_info_sender, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->message_info_sender, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->message_info_sender, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->message_info_sender, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->message_info_sender, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->message_info_sender, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->message_info_sender, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_message_text
    ui->message_info_message_text = lv_label_create(ui->message_info);
    lv_label_set_text(ui->message_info_message_text, "How are you? I will meet with Mike. And you? ");
    lv_label_set_long_mode(ui->message_info_message_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->message_info_message_text, 53, 189);
    lv_obj_set_size(ui->message_info_message_text, 360, 53);

    //Write style for message_info_message_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->message_info_message_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->message_info_message_text, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->message_info_message_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->message_info_message_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->message_info_message_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_left
    ui->message_info_left = lv_img_create(ui->message_info);
    lv_obj_add_flag(ui->message_info_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->message_info_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->message_info_left, 50,50);
    lv_img_set_angle(ui->message_info_left, 0);
    lv_obj_set_pos(ui->message_info_left, 11, 196);
    lv_obj_set_size(ui->message_info_left, 10, 38);

    //Write style for message_info_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->message_info_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->message_info_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->message_info_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_right
    ui->message_info_right = lv_img_create(ui->message_info);
    lv_obj_add_flag(ui->message_info_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->message_info_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->message_info_right, 50,50);
    lv_img_set_angle(ui->message_info_right, 0);
    lv_obj_set_pos(ui->message_info_right, 437, 196);
    lv_obj_set_size(ui->message_info_right, 10, 38);

    //Write style for message_info_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->message_info_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->message_info_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->message_info_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_time_text
    ui->message_info_time_text = lv_label_create(ui->message_info);
    lv_label_set_text(ui->message_info_time_text, "1 min ago");
    lv_label_set_long_mode(ui->message_info_time_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->message_info_time_text, 173, 287);
    lv_obj_set_size(ui->message_info_time_text, 118, 30);

    //Write style for message_info_time_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->message_info_time_text, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->message_info_time_text, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->message_info_time_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->message_info_time_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->message_info_time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_ok_btn
    ui->message_info_ok_btn = lv_label_create(ui->message_info);
    lv_label_set_text(ui->message_info_ok_btn, "OK");
    lv_label_set_long_mode(ui->message_info_ok_btn, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->message_info_ok_btn, 130, 356);
    lv_obj_set_size(ui->message_info_ok_btn, 204, 58);
    lv_obj_add_flag(ui->message_info_ok_btn, LV_OBJ_FLAG_CLICKABLE);

    //Write style for message_info_ok_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->message_info_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_ok_btn, 23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->message_info_ok_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->message_info_ok_btn, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->message_info_ok_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->message_info_ok_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->message_info_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->message_info_ok_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->message_info_ok_btn, 105, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->message_info_ok_btn, lv_color_hex(0x414041), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->message_info_ok_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->message_info_ok_btn, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->message_info_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->message_info_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->message_info_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->message_info_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes message_info_home_text
    ui->message_info_home_text = lv_img_create(ui->message_info);
    lv_obj_add_flag(ui->message_info_home_text, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->message_info_home_text, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->message_info_home_text, 50,50);
    lv_img_set_angle(ui->message_info_home_text, 0);
    lv_obj_set_pos(ui->message_info_home_text, 379, 307);
    lv_obj_set_size(ui->message_info_home_text, 42, 57);

    //Write style for message_info_home_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->message_info_home_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->message_info_home_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->message_info_home_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->message_info_home_text, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of message_info.


    //Update current screen layout.
    lv_obj_update_layout(ui->message_info);

    //Init events for screen.
    events_init_message_info(ui);
}

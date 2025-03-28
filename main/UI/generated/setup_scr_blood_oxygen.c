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



void setup_scr_blood_oxygen(lv_ui *ui)
{
    //Write codes blood_oxygen
    ui->blood_oxygen = lv_obj_create(NULL);
    lv_obj_set_size(ui->blood_oxygen, 466, 466);
    lv_obj_set_scrollbar_mode(ui->blood_oxygen, LV_SCROLLBAR_MODE_OFF);

    //Write style for blood_oxygen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->blood_oxygen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->blood_oxygen, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->blood_oxygen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->blood_oxygen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_arc_blood
    ui->blood_oxygen_arc_blood = lv_arc_create(ui->blood_oxygen);
    lv_arc_set_mode(ui->blood_oxygen_arc_blood, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->blood_oxygen_arc_blood, 0, 100);
    lv_arc_set_bg_angles(ui->blood_oxygen_arc_blood, 48, 211);
    lv_arc_set_value(ui->blood_oxygen_arc_blood, 70);
    lv_arc_set_rotation(ui->blood_oxygen_arc_blood, 0);
    lv_obj_set_pos(ui->blood_oxygen_arc_blood, 13, 161);
    lv_obj_set_size(ui->blood_oxygen_arc_blood, 439, 439);

    //Write style for blood_oxygen_arc_blood, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->blood_oxygen_arc_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->blood_oxygen_arc_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->blood_oxygen_arc_blood, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->blood_oxygen_arc_blood, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->blood_oxygen_arc_blood, lv_color_hex(0x10DEF6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_arc_blood, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->blood_oxygen_arc_blood, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->blood_oxygen_arc_blood, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->blood_oxygen_arc_blood, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->blood_oxygen_arc_blood, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->blood_oxygen_arc_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for blood_oxygen_arc_blood, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->blood_oxygen_arc_blood, 15, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->blood_oxygen_arc_blood, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->blood_oxygen_arc_blood, lv_color_hex(0x10DEF6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for blood_oxygen_arc_blood, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->blood_oxygen_arc_blood, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->blood_oxygen_arc_blood, lv_color_hex(0xFFFFFF), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->blood_oxygen_arc_blood, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->blood_oxygen_arc_blood, 4, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_home
    ui->blood_oxygen_home = lv_img_create(ui->blood_oxygen);
    lv_obj_add_flag(ui->blood_oxygen_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->blood_oxygen_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->blood_oxygen_home, 50,50);
    lv_img_set_angle(ui->blood_oxygen_home, 0);
    lv_obj_set_pos(ui->blood_oxygen_home, 395, 309);
    lv_obj_set_size(ui->blood_oxygen_home, 42, 57);

    //Write style for blood_oxygen_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->blood_oxygen_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->blood_oxygen_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->blood_oxygen_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_title
    ui->blood_oxygen_title = lv_label_create(ui->blood_oxygen);
    lv_label_set_text(ui->blood_oxygen_title, "Blood oxygen");
    lv_label_set_long_mode(ui->blood_oxygen_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->blood_oxygen_title, 0, -106);
    lv_obj_set_size(ui->blood_oxygen_title, 466, 89);
    lv_obj_add_flag(ui->blood_oxygen_title, LV_OBJ_FLAG_FLOATING);

    //Write style for blood_oxygen_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->blood_oxygen_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->blood_oxygen_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->blood_oxygen_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->blood_oxygen_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->blood_oxygen_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->blood_oxygen_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->blood_oxygen_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->blood_oxygen_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->blood_oxygen_title, lv_color_hex(0xBD1C39), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->blood_oxygen_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->blood_oxygen_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_label_blood
    ui->blood_oxygen_label_blood = lv_label_create(ui->blood_oxygen);
    lv_label_set_text(ui->blood_oxygen_label_blood, "93");
    lv_label_set_long_mode(ui->blood_oxygen_label_blood, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->blood_oxygen_label_blood, 114, 173);
    lv_obj_set_size(ui->blood_oxygen_label_blood, 164, 120);

    //Write style for blood_oxygen_label_blood, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->blood_oxygen_label_blood, lv_color_hex(0x31DAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->blood_oxygen_label_blood, &lv_font_montserratMedium_47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->blood_oxygen_label_blood, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->blood_oxygen_label_blood, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->blood_oxygen_label_blood, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_label_ago
    ui->blood_oxygen_label_ago = lv_label_create(ui->blood_oxygen);
    lv_label_set_text(ui->blood_oxygen_label_ago, "5 min ago");
    lv_label_set_long_mode(ui->blood_oxygen_label_ago, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->blood_oxygen_label_ago, 146, 366);
    lv_obj_set_size(ui->blood_oxygen_label_ago, 150, 30);

    //Write style for blood_oxygen_label_ago, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->blood_oxygen_label_ago, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->blood_oxygen_label_ago, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->blood_oxygen_label_ago, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->blood_oxygen_label_ago, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->blood_oxygen_label_ago, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_water_icon
    ui->blood_oxygen_water_icon = lv_img_create(ui->blood_oxygen);
    lv_obj_add_flag(ui->blood_oxygen_water_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->blood_oxygen_water_icon, &_icn_water_alpha_38x52);
    lv_img_set_pivot(ui->blood_oxygen_water_icon, 50,50);
    lv_img_set_angle(ui->blood_oxygen_water_icon, 0);
    lv_obj_set_pos(ui->blood_oxygen_water_icon, 278, 181);
    lv_obj_set_size(ui->blood_oxygen_water_icon, 38, 52);

    //Write style for blood_oxygen_water_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->blood_oxygen_water_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->blood_oxygen_water_icon, lv_color_hex(0x31DAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->blood_oxygen_water_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_water_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->blood_oxygen_water_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_label_percentage
    ui->blood_oxygen_label_percentage = lv_label_create(ui->blood_oxygen);
    lv_label_set_text(ui->blood_oxygen_label_percentage, "%");
    lv_label_set_long_mode(ui->blood_oxygen_label_percentage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->blood_oxygen_label_percentage, 278, 244);
    lv_obj_set_size(ui->blood_oxygen_label_percentage, 51, 40);

    //Write style for blood_oxygen_label_percentage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->blood_oxygen_label_percentage, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->blood_oxygen_label_percentage, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->blood_oxygen_label_percentage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->blood_oxygen_label_percentage, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->blood_oxygen_label_percentage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->blood_oxygen_label_percentage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_img_menu
    ui->blood_oxygen_img_menu = lv_img_create(ui->blood_oxygen);
    lv_obj_add_flag(ui->blood_oxygen_img_menu, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->blood_oxygen_img_menu, &_img_menu_alpha_13x118);
    lv_img_set_pivot(ui->blood_oxygen_img_menu, 50,50);
    lv_img_set_angle(ui->blood_oxygen_img_menu, 0);
    lv_obj_set_pos(ui->blood_oxygen_img_menu, 433, 173);
    lv_obj_set_size(ui->blood_oxygen_img_menu, 13, 118);

    //Write style for blood_oxygen_img_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->blood_oxygen_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->blood_oxygen_img_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_img_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->blood_oxygen_img_menu, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes blood_oxygen_img_dot
    ui->blood_oxygen_img_dot = lv_img_create(ui->blood_oxygen);
    lv_obj_add_flag(ui->blood_oxygen_img_dot, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->blood_oxygen_img_dot, &_dot_alpha_9x9);
    lv_img_set_pivot(ui->blood_oxygen_img_dot, 50,50);
    lv_img_set_angle(ui->blood_oxygen_img_dot, 0);
    lv_obj_set_pos(ui->blood_oxygen_img_dot, 432, 281);
    lv_obj_set_size(ui->blood_oxygen_img_dot, 9, 9);

    //Write style for blood_oxygen_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->blood_oxygen_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->blood_oxygen_img_dot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->blood_oxygen_img_dot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->blood_oxygen_img_dot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of blood_oxygen.


    //Update current screen layout.
    lv_obj_update_layout(ui->blood_oxygen);

    //Init events for screen.
    events_init_blood_oxygen(ui);
}

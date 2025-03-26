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



void setup_scr_step(lv_ui *ui)
{
    //Write codes step
    ui->step = lv_obj_create(NULL);
    lv_obj_set_size(ui->step, 466, 466);
    lv_obj_set_scrollbar_mode(ui->step, LV_SCROLLBAR_MODE_OFF);

    //Write style for step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->step, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_arc_step
    ui->step_arc_step = lv_arc_create(ui->step);
    lv_arc_set_mode(ui->step_arc_step, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->step_arc_step, 0, 100);
    lv_arc_set_bg_angles(ui->step_arc_step, 48, 212);
    lv_arc_set_value(ui->step_arc_step, 70);
    lv_arc_set_rotation(ui->step_arc_step, 0);
    lv_obj_set_pos(ui->step_arc_step, 13, 164);
    lv_obj_set_size(ui->step_arc_step, 439, 439);

    //Write style for step_arc_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->step_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->step_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->step_arc_step, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->step_arc_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->step_arc_step, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_arc_step, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->step_arc_step, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->step_arc_step, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->step_arc_step, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->step_arc_step, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->step_arc_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for step_arc_step, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->step_arc_step, 17, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->step_arc_step, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->step_arc_step, lv_color_hex(0x29CE08), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for step_arc_step, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->step_arc_step, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->step_arc_step, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes step_home
    ui->step_home = lv_img_create(ui->step);
    lv_obj_add_flag(ui->step_home, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->step_home, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->step_home, 50,50);
    lv_img_set_angle(ui->step_home, 0);
    lv_obj_set_pos(ui->step_home, 387, 309);
    lv_obj_set_size(ui->step_home, 42, 57);

    //Write style for step_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->step_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->step_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->step_home, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_label_current_steps
    ui->step_label_current_steps = lv_label_create(ui->step);
    lv_label_set_text(ui->step_label_current_steps, "5.8K");
    lv_label_set_long_mode(ui->step_label_current_steps, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->step_label_current_steps, 90, 164);
    lv_obj_set_size(ui->step_label_current_steps, 286, 137);

    //Write style for step_label_current_steps, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->step_label_current_steps, lv_color_hex(0x00DB0e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->step_label_current_steps, &lv_font_montserratMedium_47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->step_label_current_steps, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->step_label_current_steps, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->step_label_current_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_left
    ui->step_left = lv_img_create(ui->step);
    lv_obj_add_flag(ui->step_left, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->step_left, &_img_arrow_left_alpha_10x38);
    lv_img_set_pivot(ui->step_left, 50,50);
    lv_img_set_angle(ui->step_left, 0);
    lv_obj_set_pos(ui->step_left, 9, 204);
    lv_obj_set_size(ui->step_left, 10, 38);
    lv_obj_add_flag(ui->step_left, LV_OBJ_FLAG_FLOATING);

    //Write style for step_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->step_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->step_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->step_left, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_right
    ui->step_right = lv_img_create(ui->step);
    lv_obj_add_flag(ui->step_right, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->step_right, &_img_arrow_right_alpha_10x38);
    lv_img_set_pivot(ui->step_right, 50,50);
    lv_img_set_angle(ui->step_right, 0);
    lv_obj_set_pos(ui->step_right, 437, 204);
    lv_obj_set_size(ui->step_right, 10, 38);
    lv_obj_add_flag(ui->step_right, LV_OBJ_FLAG_FLOATING);

    //Write style for step_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->step_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->step_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->step_right, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_title
    ui->step_title = lv_label_create(ui->step);
    lv_label_set_text(ui->step_title, "Step count");
    lv_label_set_long_mode(ui->step_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->step_title, 0, -99);
    lv_obj_set_size(ui->step_title, 466, 89);
    lv_obj_add_flag(ui->step_title, LV_OBJ_FLAG_FLOATING);

    //Write style for step_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->step_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->step_title, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->step_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->step_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->step_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->step_title, 27, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->step_title, &_img_header_bg_466x89, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->step_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->step_title, lv_color_hex(0xBD1C39), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->step_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->step_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_cont_1
    ui->step_cont_1 = lv_obj_create(ui->step);
    lv_obj_set_pos(ui->step_cont_1, 131, 458);
    lv_obj_set_size(ui->step_cont_1, 202, 98);
    lv_obj_set_scrollbar_mode(ui->step_cont_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->step_cont_1, LV_OBJ_FLAG_FLOATING);

    //Write style for step_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->step_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_label_goals_steps
    ui->step_label_goals_steps = lv_label_create(ui->step_cont_1);
    lv_label_set_text(ui->step_label_goals_steps, "10 000\n\n\n\n\n");
    lv_label_set_long_mode(ui->step_label_goals_steps, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->step_label_goals_steps, 45, 43);
    lv_obj_set_size(ui->step_label_goals_steps, 129, 40);

    //Write style for step_label_goals_steps, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->step_label_goals_steps, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->step_label_goals_steps, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->step_label_goals_steps, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->step_label_goals_steps, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->step_label_goals_steps, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_label_goal
    ui->step_label_goal = lv_label_create(ui->step_cont_1);
    lv_label_set_text(ui->step_label_goal, "DAILY GOAL");
    lv_label_set_long_mode(ui->step_label_goal, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->step_label_goal, 42, 16);
    lv_obj_set_size(ui->step_label_goal, 128, 23);

    //Write style for step_label_goal, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->step_label_goal, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->step_label_goal, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->step_label_goal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->step_label_goal, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->step_label_goal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes step_icon_step
    ui->step_icon_step = lv_img_create(ui->step);
    lv_obj_add_flag(ui->step_icon_step, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->step_icon_step, &_img_step_small_alpha_33x53);
    lv_img_set_pivot(ui->step_icon_step, 50,50);
    lv_img_set_angle(ui->step_icon_step, 0);
    lv_obj_set_pos(ui->step_icon_step, 216, 16);
    lv_obj_set_size(ui->step_icon_step, 33, 53);

    //Write style for step_icon_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->step_icon_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->step_icon_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->step_icon_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->step_icon_step, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of step.


    //Update current screen layout.
    lv_obj_update_layout(ui->step);

    //Init events for screen.
    events_init_step(ui);
}

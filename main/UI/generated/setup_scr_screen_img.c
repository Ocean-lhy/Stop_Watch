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



void setup_scr_screen_img(lv_ui *ui)
{
    //Write codes screen_img
    ui->screen_img = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_img, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_img, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_img
    ui->screen_img_img = lv_img_create(ui->screen_img);
    lv_obj_add_flag(ui->screen_img_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_img, &_db1modified_alpha_466x466);
    lv_img_set_pivot(ui->screen_img_img, 233,233);
    lv_img_set_angle(ui->screen_img_img, 60);
    lv_obj_set_pos(ui->screen_img_img, 0, 0);
    lv_obj_set_size(ui->screen_img_img, 466, 466);

    //Write style for screen_img_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_img_1
    ui->screen_img_img_1 = lv_img_create(ui->screen_img);
    lv_obj_add_flag(ui->screen_img_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_img_1, &_raianglemodified_alpha_50x20);
    lv_img_set_pivot(ui->screen_img_img_1, 25,223);
    lv_img_set_angle(ui->screen_img_img_1, 0);
    lv_obj_set_pos(ui->screen_img_img_1, 208, 10);
    lv_obj_set_size(ui->screen_img_img_1, 50, 20);

    //Write style for screen_img_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_img_2
    ui->screen_img_img_2 = lv_img_create(ui->screen_img);
    lv_obj_add_flag(ui->screen_img_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_img_2, &_raianglemodified_alpha_50x20);
    lv_img_set_pivot(ui->screen_img_img_2, 23,10);
    lv_img_set_angle(ui->screen_img_img_2, 1800);
    lv_obj_set_pos(ui->screen_img_img_2, 208, 436);
    lv_obj_set_size(ui->screen_img_img_2, 50, 20);
    lv_obj_add_flag(ui->screen_img_img_2, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_img_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_img_3
    ui->screen_img_img_3 = lv_img_create(ui->screen_img);
    lv_obj_add_flag(ui->screen_img_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_img_3, &_raianglemodified_alpha_50x20);
    lv_img_set_pivot(ui->screen_img_img_3, 25,10);
    lv_img_set_angle(ui->screen_img_img_3, 2700);
    lv_obj_set_pos(ui->screen_img_img_3, -5, 223);
    lv_obj_set_size(ui->screen_img_img_3, 50, 20);
    lv_obj_add_flag(ui->screen_img_img_3, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_img_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_img_4
    ui->screen_img_img_4 = lv_img_create(ui->screen_img);
    lv_obj_add_flag(ui->screen_img_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_img_4, &_raianglemodified_alpha_50x20);
    lv_img_set_pivot(ui->screen_img_img_4, 25,10);
    lv_img_set_angle(ui->screen_img_img_4, 900);
    lv_obj_set_pos(ui->screen_img_img_4, 423, 223);
    lv_obj_set_size(ui->screen_img_img_4, 50, 20);
    lv_obj_add_flag(ui->screen_img_img_4, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_img_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_img.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_img);

    events_init_screen_img(ui);
}

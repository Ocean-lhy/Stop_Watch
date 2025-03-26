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



int call_digital_clock_1_min_value = 25;
int call_digital_clock_1_hour_value = 11;
int call_digital_clock_1_sec_value = 50;
void setup_scr_call(lv_ui *ui)
{
    //Write codes call
    ui->call = lv_obj_create(NULL);
    lv_obj_set_size(ui->call, 466, 466);
    lv_obj_set_scrollbar_mode(ui->call, LV_SCROLLBAR_MODE_OFF);

    //Write style for call, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->call, &_img_bg_2_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->call, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_img_8
    ui->call_img_8 = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_img_8, &_text_volume_alpha_32x86);
    lv_img_set_pivot(ui->call_img_8, 50,50);
    lv_img_set_angle(ui->call_img_8, 0);
    lv_obj_set_pos(ui->call_img_8, 34, 255);
    lv_obj_set_size(ui->call_img_8, 32, 86);

    //Write style for call_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_arc_1
    ui->call_arc_1 = lv_arc_create(ui->call);
    lv_arc_set_mode(ui->call_arc_1, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->call_arc_1, 0, 100);
    lv_arc_set_bg_angles(ui->call_arc_1, 120, 180);
    lv_arc_set_value(ui->call_arc_1, 70);
    lv_arc_set_rotation(ui->call_arc_1, 0);
    lv_obj_set_pos(ui->call_arc_1, 13, 79);
    lv_obj_set_size(ui->call_arc_1, 388, 356);

    //Write style for call_arc_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->call_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->call_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->call_arc_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->call_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->call_arc_1, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_arc_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->call_arc_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->call_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->call_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->call_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->call_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for call_arc_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->call_arc_1, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->call_arc_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->call_arc_1, lv_color_hex(0x08ce08), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for call_arc_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->call_arc_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->call_arc_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes call_img_7
    ui->call_img_7 = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_img_7, &_img_call_erica_alpha_466x298);
    lv_img_set_pivot(ui->call_img_7, 50,50);
    lv_img_set_angle(ui->call_img_7, 0);
    lv_obj_set_pos(ui->call_img_7, 0, -160);
    lv_obj_set_size(ui->call_img_7, 466, 298);

    //Write style for call_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_img_6
    ui->call_img_6 = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_img_6, &_text_home_alpha_42x57);
    lv_img_set_pivot(ui->call_img_6, 50,50);
    lv_img_set_angle(ui->call_img_6, 0);
    lv_obj_set_pos(ui->call_img_6, 379, 307);
    lv_obj_set_size(ui->call_img_6, 42, 57);

    //Write style for call_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_img_5
    ui->call_img_5 = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_img_5, &_icn_home_alpha_30x27);
    lv_img_set_pivot(ui->call_img_5, 50,50);
    lv_img_set_angle(ui->call_img_5, 0);
    lv_obj_set_pos(ui->call_img_5, 356, 307);
    lv_obj_set_size(ui->call_img_5, 30, 27);

    //Write style for call_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_img_4
    ui->call_img_4 = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_img_4, &_text_endcall_alpha_30x40);
    lv_img_set_pivot(ui->call_img_4, 50,50);
    lv_img_set_angle(ui->call_img_4, 80);
    lv_obj_set_pos(ui->call_img_4, 381, 90);
    lv_obj_set_size(ui->call_img_4, 30, 40);

    //Write style for call_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_hang_up_btn
    ui->call_hang_up_btn = lv_btn_create(ui->call);
    ui->call_hang_up_btn_label = lv_label_create(ui->call_hang_up_btn);
    lv_label_set_text(ui->call_hang_up_btn_label, "");
    lv_label_set_long_mode(ui->call_hang_up_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->call_hang_up_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->call_hang_up_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->call_hang_up_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->call_hang_up_btn, 323, 90);
    lv_obj_set_size(ui->call_hang_up_btn, 71, 71);

    //Write style for call_hang_up_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->call_hang_up_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->call_hang_up_btn, lv_color_hex(0xe60c08), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->call_hang_up_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->call_hang_up_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_hang_up_btn, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->call_hang_up_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->call_hang_up_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->call_hang_up_btn, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->call_hang_up_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->call_hang_up_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_hang_up
    ui->call_hang_up = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_hang_up, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_hang_up, &_icn_phone_alpha_30x23);
    lv_img_set_pivot(ui->call_hang_up, 50,50);
    lv_img_set_angle(ui->call_hang_up, 0);
    lv_obj_set_pos(ui->call_hang_up, 343, 114);
    lv_obj_set_size(ui->call_hang_up, 30, 23);

    //Write style for call_hang_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_hang_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_hang_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_hang_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_hang_up, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_caller
    ui->call_caller = lv_label_create(ui->call);
    lv_label_set_text(ui->call_caller, "Erica Smith");
    lv_label_set_long_mode(ui->call_caller, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->call_caller, 98, 269);
    lv_obj_set_size(ui->call_caller, 269, 38);

    //Write style for call_caller, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->call_caller, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->call_caller, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->call_caller, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->call_caller, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->call_caller, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->call_caller, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_digital_clock_1
    static bool call_digital_clock_1_timer_enabled = false;
    ui->call_digital_clock_1 = lv_dclock_create(ui->call, "11:25:50");
    if (!call_digital_clock_1_timer_enabled) {
        lv_timer_create(call_digital_clock_1_timer, 1000, NULL);
        call_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->call_digital_clock_1, 155, 323);
    lv_obj_set_size(ui->call_digital_clock_1, 154, 26);

    //Write style for call_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->call_digital_clock_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->call_digital_clock_1, &lv_font_montserratMedium_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->call_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->call_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->call_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_mute_btn
    ui->call_mute_btn = lv_btn_create(ui->call);
    ui->call_mute_btn_label = lv_label_create(ui->call_mute_btn);
    lv_label_set_text(ui->call_mute_btn_label, "");
    lv_label_set_long_mode(ui->call_mute_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->call_mute_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->call_mute_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->call_mute_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->call_mute_btn, 197, 364);
    lv_obj_set_size(ui->call_mute_btn, 71, 71);

    //Write style for call_mute_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->call_mute_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->call_mute_btn, lv_color_hex(0x292c29), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->call_mute_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->call_mute_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_mute_btn, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->call_mute_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->call_mute_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->call_mute_btn, &lv_font_montserratMedium_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->call_mute_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->call_mute_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_unmute_icon
    ui->call_unmute_icon = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_unmute_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_unmute_icon, &_icn_unmute_alpha_38x38);
    lv_img_set_pivot(ui->call_unmute_icon, 50,50);
    lv_img_set_angle(ui->call_unmute_icon, 0);
    lv_obj_set_pos(ui->call_unmute_icon, 213, 474);
    lv_obj_set_size(ui->call_unmute_icon, 38, 38);

    //Write style for call_unmute_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_unmute_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_unmute_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_unmute_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_unmute_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes call_mute_icon
    ui->call_mute_icon = lv_img_create(ui->call);
    lv_obj_add_flag(ui->call_mute_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->call_mute_icon, &_icn_mute_alpha_38x38);
    lv_img_set_pivot(ui->call_mute_icon, 50,50);
    lv_img_set_angle(ui->call_mute_icon, 0);
    lv_obj_set_pos(ui->call_mute_icon, 213, 381);
    lv_obj_set_size(ui->call_mute_icon, 38, 38);
    lv_obj_add_flag(ui->call_mute_icon, LV_OBJ_FLAG_HIDDEN);

    //Write style for call_mute_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->call_mute_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->call_mute_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->call_mute_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->call_mute_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of call.


    //Update current screen layout.
    lv_obj_update_layout(ui->call);

    //Init events for screen.
    events_init_call(ui);
}

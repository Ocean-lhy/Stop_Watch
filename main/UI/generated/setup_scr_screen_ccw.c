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



int screen_ccw_digital_clock_s_min_value = 0;
int screen_ccw_digital_clock_s_hour_value = 0;
int screen_ccw_digital_clock_s_sec_value = 0;
int screen_ccw_digital_clock_s_ms_value = 0;
int screen_ccw_analog_clock_ccw_hour_value = 0;
int screen_ccw_analog_clock_ccw_min_value = 0;
int screen_ccw_analog_clock_ccw_sec_value = 0;
void setup_scr_screen_ccw(lv_ui *ui)
{
    //Write codes screen_ccw
    ui->screen_ccw = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_ccw, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_ccw, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_ccw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ccw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ccw, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ccw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ccw_digital_clock_s
    static bool screen_ccw_digital_clock_s_timer_enabled = false;
    ui->screen_ccw_digital_clock_s = lv_dclock_create(ui->screen_ccw, "0:00:00.000");
    lv_obj_set_pos(ui->screen_ccw_digital_clock_s, 132, 249);
    lv_obj_set_size(ui->screen_ccw_digital_clock_s, 189, 39);

    //Write style for screen_ccw_digital_clock_s, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_ccw_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_ccw_digital_clock_s, lv_color_hex(0x12548b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ccw_digital_clock_s, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ccw_digital_clock_s, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ccw_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ccw_digital_clock_s, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ccw_digital_clock_s, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ccw_digital_clock_s, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ccw_digital_clock_s, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ccw_digital_clock_s, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ccw_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_ccw_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ccw_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ccw_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ccw_label_ms
    ui->screen_ccw_label_ms = lv_label_create(ui->screen_ccw);
    lv_label_set_text(ui->screen_ccw_label_ms, "0");
    lv_label_set_long_mode(ui->screen_ccw_label_ms, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_ccw_label_ms, 267, 216);
    lv_obj_set_size(ui->screen_ccw_label_ms, 158, 33);
    lv_obj_add_flag(ui->screen_ccw_label_ms, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_ccw_label_ms, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_ccw_label_ms, lv_color_hex(0x12548b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ccw_label_ms, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ccw_label_ms, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ccw_label_ms, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ccw_label_ms, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ccw_analog_clock_ccw
    static bool screen_ccw_analog_clock_ccw_timer_enabled = false;
    ui->screen_ccw_analog_clock_ccw = lv_analogclock_create(ui->screen_ccw);
    lv_analogclock_hide_digits(ui->screen_ccw_analog_clock_ccw, true);
    lv_analogclock_set_major_ticks(ui->screen_ccw_analog_clock_ccw, 2, 50, lv_color_hex(0x555555), 10);
    lv_analogclock_set_ticks(ui->screen_ccw_analog_clock_ccw, 2, 25, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_line(ui->screen_ccw_analog_clock_ccw, 0, lv_color_hex(0x000000), -90);
    lv_analogclock_set_min_needle_line(ui->screen_ccw_analog_clock_ccw, 0, lv_color_hex(0x000000), -60);
    lv_analogclock_set_sec_needle_line(ui->screen_ccw_analog_clock_ccw, 0, lv_color_hex(0x000000), -45);
    lv_analogclock_set_time(ui->screen_ccw_analog_clock_ccw, screen_ccw_analog_clock_ccw_hour_value, screen_ccw_analog_clock_ccw_min_value,screen_ccw_analog_clock_ccw_sec_value);
    // create timer
    // if (!screen_ccw_analog_clock_ccw_timer_enabled) {
    //     lv_timer_create(screen_ccw_analog_clock_ccw_timer, 1000, NULL);
    //     screen_ccw_analog_clock_ccw_timer_enabled = true;
    // }
    lv_obj_set_pos(ui->screen_ccw_analog_clock_ccw, 0, 0);
    lv_obj_set_size(ui->screen_ccw_analog_clock_ccw, 466, 466);

    //Write style for screen_ccw_analog_clock_ccw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ccw_analog_clock_ccw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_ccw_analog_clock_ccw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ccw_analog_clock_ccw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_ccw_analog_clock_ccw, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_ccw_analog_clock_ccw, lv_color_hex(0x000000), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ccw_analog_clock_ccw, &lv_font_Acme_Regular_28, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ccw_analog_clock_ccw, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for screen_ccw_analog_clock_ccw, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ccw_analog_clock_ccw, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ccw_analog_clock_ccw, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ccw_analog_clock_ccw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_ccw_img_1
    ui->screen_ccw_img_1 = lv_img_create(ui->screen_ccw);
    lv_obj_add_flag(ui->screen_ccw_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_ccw_img_1, &_min_needle_alpha_200x6);
    lv_img_set_pivot(ui->screen_ccw_img_1, 0,3);
    lv_img_set_angle(ui->screen_ccw_img_1, -900);
    lv_obj_set_pos(ui->screen_ccw_img_1, 233, 230);
    lv_obj_set_size(ui->screen_ccw_img_1, 200, 6);

    //Write style for screen_ccw_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_ccw_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_ccw_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ccw_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_ccw_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    
    if (!screen_ccw_digital_clock_s_timer_enabled) {
        lv_timer_create(screen_ccw_digital_clock_s_timer, 50, NULL);
        screen_ccw_digital_clock_s_timer_enabled = true;
    }
    extern uint8_t ccw_clock_state;
   ccw_clock_state = 2; 

    //The custom code of screen_ccw.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_ccw);

    //Init events for screen.
    events_init_screen_ccw(ui);
}

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



int screen_analog_clock_1_hour_value = 10;
int screen_analog_clock_1_min_value = 10;
int screen_analog_clock_1_sec_value = 45;
void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_analog_clock_1
    static bool screen_analog_clock_1_timer_enabled = false;
    ui->screen_analog_clock_1 = lv_analogclock_create(ui->screen);
    lv_analogclock_hide_digits(ui->screen_analog_clock_1, false);
    lv_analogclock_set_major_ticks(ui->screen_analog_clock_1, 2, 25, lv_color_hex(0x555555), 18);
    lv_analogclock_set_ticks(ui->screen_analog_clock_1, 2, 10, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_img(ui->screen_analog_clock_1, &_hour_needle_alpha_80x10, 16, 5);
    lv_analogclock_set_min_needle_img(ui->screen_analog_clock_1, &_min_needle_alpha_150x7, 26, 3);
    lv_analogclock_set_sec_needle_img(ui->screen_analog_clock_1, &_second_needle_alpha_185x15, 39, 7);
    lv_analogclock_set_time(ui->screen_analog_clock_1, screen_analog_clock_1_hour_value, screen_analog_clock_1_min_value,screen_analog_clock_1_sec_value);
    // create timer
    if (!screen_analog_clock_1_timer_enabled) {
        lv_timer_create(screen_analog_clock_1_timer, 1000, NULL);
        screen_analog_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->screen_analog_clock_1, 0, 0);
    lv_obj_set_size(ui->screen_analog_clock_1, 466, 466);

    //Write style for screen_analog_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_analog_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_analog_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_analog_clock_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_analog_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_analog_clock_1, lv_color_hex(0x525252), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_analog_clock_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_analog_clock_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_analog_clock_1, lv_color_hex(0x000000), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_analog_clock_1, &lv_font_Acme_Regular_28, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_analog_clock_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for screen_analog_clock_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_analog_clock_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_analog_clock_1, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_canvas_1
    ui->screen_canvas_1 = lv_canvas_create(ui->screen);
    static lv_color_t buf_screen_canvas_1[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(16, 16)];
    lv_canvas_set_buffer(ui->screen_canvas_1, buf_screen_canvas_1, 16, 16, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_canvas_1, lv_color_hex(0xffffff), 0);
    //Canvas draw arc
    lv_draw_arc_dsc_t screen_canvas_1_arc_dsc_0;
    lv_draw_arc_dsc_init(&screen_canvas_1_arc_dsc_0);
    screen_canvas_1_arc_dsc_0.color = lv_color_hex(0x000000);
    screen_canvas_1_arc_dsc_0.opa = 255;
    screen_canvas_1_arc_dsc_0.width = 8;
    lv_canvas_draw_arc(ui->screen_canvas_1, 8, 8, 8, 0, 360, &screen_canvas_1_arc_dsc_0);

    lv_obj_set_pos(ui->screen_canvas_1, 225, 225);
    lv_obj_set_size(ui->screen_canvas_1, 16, 16);
    lv_obj_set_scrollbar_mode(ui->screen_canvas_1, LV_SCROLLBAR_MODE_OFF);

    //The custom code of screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

}

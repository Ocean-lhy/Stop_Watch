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



int screen_clock_digital_clock_s_min_value = 10;
int screen_clock_digital_clock_s_hour_value = 10;
int screen_clock_digital_clock_s_sec_value = 45;
char screen_clock_digital_clock_s_meridiem[] = "AM";
int screen_clock_analog_clock_time_hour_value = 10;
int screen_clock_analog_clock_time_min_value = 10;
int screen_clock_analog_clock_time_sec_value = 45;
void setup_scr_screen_clock(lv_ui *ui)
{
    //Write codes screen_clock
    ui->screen_clock = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_clock, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_clock, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_clock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_clock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_clock, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_clock_img_logo
    ui->screen_clock_img_logo = lv_img_create(ui->screen_clock);
    lv_obj_add_flag(ui->screen_clock_img_logo, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_clock_img_logo, &_m5logo2022_alpha_90x72);
    lv_img_set_pivot(ui->screen_clock_img_logo, 50,50);
    lv_img_set_angle(ui->screen_clock_img_logo, 0);
    lv_obj_set_pos(ui->screen_clock_img_logo, 192, 290);
    lv_obj_set_size(ui->screen_clock_img_logo, 90, 72);

    //Write style for screen_clock_img_logo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_clock_img_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_clock_img_logo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_clock_img_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_clock_img_logo, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_clock_digital_clock_s
    static bool screen_clock_digital_clock_s_timer_enabled = false;
    ui->screen_clock_digital_clock_s = lv_dclock_create(ui->screen_clock, "10:10:45 AM");
    // if (!screen_clock_digital_clock_s_timer_enabled) {
    //     lv_timer_create(screen_clock_digital_clock_s_timer, 1000, NULL);
    //     screen_clock_digital_clock_s_timer_enabled = true;
    // }
    lv_obj_set_pos(ui->screen_clock_digital_clock_s, 258, 215);
    lv_obj_set_size(ui->screen_clock_digital_clock_s, 130, 36);

    //Write style for screen_clock_digital_clock_s, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_clock_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_clock_digital_clock_s, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_clock_digital_clock_s, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_clock_digital_clock_s, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_clock_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_clock_digital_clock_s, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_clock_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_clock_digital_clock_s, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_clock_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_clock_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_clock_digital_clock_s, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_clock_digital_clock_s, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_clock_digital_clock_s, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_clock_digital_clock_s, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_clock_digital_clock_s, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_clock_digital_clock_s, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_clock_digital_clock_s, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_clock_datetext_date
    ui->screen_clock_datetext_date = lv_label_create(ui->screen_clock);
    lv_label_set_text(ui->screen_clock_datetext_date, "2025/01/01");
    lv_obj_set_style_text_align(ui->screen_clock_datetext_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->screen_clock_datetext_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->screen_clock_datetext_date, screen_clock_datetext_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_clock_datetext_date, 81, 215);
    lv_obj_set_size(ui->screen_clock_datetext_date, 130, 36);

    //Write style for screen_clock_datetext_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_clock_datetext_date, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_clock_datetext_date, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_clock_datetext_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_clock_datetext_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_clock_datetext_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_clock_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_clock_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_clock_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_clock_datetext_date, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_clock_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_clock_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_clock_datetext_date, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_clock_datetext_date, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_clock_datetext_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_clock_datetext_date, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_clock_datetext_date, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_clock_datetext_date, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_clock_analog_clock_time
    static bool screen_clock_analog_clock_time_timer_enabled = false;
    ui->screen_clock_analog_clock_time = lv_analogclock_create(ui->screen_clock);
    lv_analogclock_hide_digits(ui->screen_clock_analog_clock_time, false);
    lv_analogclock_set_major_ticks(ui->screen_clock_analog_clock_time, 2, 25, lv_color_hex(0x555555), 18);
    lv_analogclock_set_ticks(ui->screen_clock_analog_clock_time, 2, 10, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_img(ui->screen_clock_analog_clock_time, &_hour_needle_alpha_80x10, 16, 5);
    lv_analogclock_set_min_needle_img(ui->screen_clock_analog_clock_time, &_min_needle_alpha_150x7, 26, 3);
    lv_analogclock_set_sec_needle_img(ui->screen_clock_analog_clock_time, &_second_needle_alpha_185x18, 39, 7);
    lv_analogclock_set_time(ui->screen_clock_analog_clock_time, screen_clock_analog_clock_time_hour_value, screen_clock_analog_clock_time_min_value,screen_clock_analog_clock_time_sec_value);  // set start time
    // create timer
    if (!screen_clock_analog_clock_time_timer_enabled) {
        lv_timer_create(screen_clock_analog_clock_time_timer, 450, NULL);
        screen_clock_analog_clock_time_timer_enabled = true;
        screen_clock_digital_clock_s_timer_enabled = true;
    }
    lv_obj_set_pos(ui->screen_clock_analog_clock_time, 0, 0);
    lv_obj_set_size(ui->screen_clock_analog_clock_time, 466, 466);

    //Write style for screen_clock_analog_clock_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_clock_analog_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_clock_analog_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_clock_analog_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_clock_analog_clock_time, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_clock_analog_clock_time, lv_color_hex(0x000000), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_clock_analog_clock_time, &lv_font_Acme_Regular_28, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_clock_analog_clock_time, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for screen_clock_analog_clock_time, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_clock_analog_clock_time, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_clock_analog_clock_time, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_clock_analog_clock_time, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_clock_canvas_dot
    ui->screen_clock_canvas_dot = lv_canvas_create(ui->screen_clock);
    static lv_color_t buf_screen_clock_canvas_dot[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(16, 16)];
    lv_canvas_set_buffer(ui->screen_clock_canvas_dot, buf_screen_clock_canvas_dot, 16, 16, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->screen_clock_canvas_dot, lv_color_hex(0xffffff), 0);
    //Canvas draw arc
    lv_draw_arc_dsc_t screen_clock_canvas_dot_arc_dsc_0;
    lv_draw_arc_dsc_init(&screen_clock_canvas_dot_arc_dsc_0);
    screen_clock_canvas_dot_arc_dsc_0.color = lv_color_hex(0x000000);
    screen_clock_canvas_dot_arc_dsc_0.opa = 255;
    screen_clock_canvas_dot_arc_dsc_0.width = 8;
    lv_canvas_draw_arc(ui->screen_clock_canvas_dot, 8, 8, 8, 0, 360, &screen_clock_canvas_dot_arc_dsc_0);

    lv_obj_set_pos(ui->screen_clock_canvas_dot, 225, 225);
    lv_obj_set_size(ui->screen_clock_canvas_dot, 16, 16);
    lv_obj_set_scrollbar_mode(ui->screen_clock_canvas_dot, LV_SCROLLBAR_MODE_OFF);

    //The custom code of screen_clock.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_clock);

    //Init events for screen.
    events_init_screen_clock(ui);
}

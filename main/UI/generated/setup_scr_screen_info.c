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

void setup_scr_screen_info(lv_ui *ui)
{
    //Write codes screen_info
    ui->screen_info = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_info, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_info, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->screen_info, &_StopWATCHUI2modified_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->screen_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->screen_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_info_bar_battery
    ui->screen_info_bar_battery = lv_bar_create(ui->screen_info);
    lv_obj_set_style_anim_time(ui->screen_info_bar_battery, 500, 0);
    lv_bar_set_mode(ui->screen_info_bar_battery, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_info_bar_battery, 0, 100);
    lv_bar_set_value(ui->screen_info_bar_battery, 100, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_info_bar_battery, 176, 357);
    lv_obj_set_size(ui->screen_info_bar_battery, 115, 20);

    //Write style for screen_info_bar_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_info_bar_battery, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_info_bar_battery, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_info_bar_battery, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_bar_battery, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_bar_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_info_bar_battery, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_info_bar_battery, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_info_bar_battery, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_info_bar_battery, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_bar_battery, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_info_label_battery
    ui->screen_info_label_battery = lv_label_create(ui->screen_info);
    lv_label_set_text(ui->screen_info_label_battery, "");
    lv_label_set_long_mode(ui->screen_info_label_battery, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_info_label_battery, 181, 359);
    lv_obj_set_size(ui->screen_info_label_battery, 109, 16);

    //Write style for screen_info_label_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_info_label_battery, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_info_label_battery, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_info_label_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_info_label_battery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_info_label_current
    ui->screen_info_label_current = lv_label_create(ui->screen_info);
    lv_label_set_text(ui->screen_info_label_current, "current: 0mA");
    lv_label_set_long_mode(ui->screen_info_label_current, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_info_label_current, 133, 333);
    lv_obj_set_size(ui->screen_info_label_current, 203, 18);

    //Write style for screen_info_label_current, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_info_label_current, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_info_label_current, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_info_label_current, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_info_label_current, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_info_label_gyro
    ui->screen_info_label_gyro = lv_label_create(ui->screen_info);
    lv_label_set_text(ui->screen_info_label_gyro, "");
    lv_label_set_long_mode(ui->screen_info_label_gyro, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_info_label_gyro, 101, 168);
    lv_obj_set_size(ui->screen_info_label_gyro, 255, 22);

    //Write style for screen_info_label_gyro, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_info_label_gyro, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_info_label_gyro, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_info_label_gyro, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_info_label_gyro, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_label_gyro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_info_label_accel
    ui->screen_info_label_accel = lv_label_create(ui->screen_info);
    lv_label_set_text(ui->screen_info_label_accel, "");
    lv_label_set_long_mode(ui->screen_info_label_accel, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_info_label_accel, 85, 200);
    lv_obj_set_size(ui->screen_info_label_accel, 293, 25);

    //Write style for screen_info_label_accel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_info_label_accel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_info_label_accel, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_info_label_accel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_info_label_accel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_label_accel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_info_label_charge
    ui->screen_info_label_charge = lv_label_create(ui->screen_info);
    lv_label_set_text(ui->screen_info_label_charge, "bat charging");
    lv_label_set_long_mode(ui->screen_info_label_charge, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_info_label_charge, 141, 304);
    lv_obj_set_size(ui->screen_info_label_charge, 194, 18);

    //Write style for screen_info_label_charge, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_info_label_charge, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_info_label_charge, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_info_label_charge, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_info_label_charge, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_label_charge, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_info_label_touc
    ui->screen_info_label_touc = lv_label_create(ui->screen_info);
    lv_label_set_text(ui->screen_info_label_touc, "Touch: 0, 0");
    lv_label_set_long_mode(ui->screen_info_label_touc, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_info_label_touc, 104, 233);
    lv_obj_set_size(ui->screen_info_label_touc, 255, 22);

    //Write style for screen_info_label_touc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_info_label_touc, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_info_label_touc, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_info_label_touc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_info_label_touc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_info_label_touc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_info.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_info);

    //Init events for screen.
    events_init_screen_info(ui);
}

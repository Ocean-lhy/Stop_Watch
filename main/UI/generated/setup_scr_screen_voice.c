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

void setup_scr_screen_voice(lv_ui *ui)
{
    //Write codes screen_voice
    ui->screen_voice = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_voice, 466, 466);
    lv_obj_set_scrollbar_mode(ui->screen_voice, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_voice, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->screen_voice, &_StopWATCHUI2modified_466x466, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->screen_voice, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->screen_voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_voice_bar_battery
    ui->screen_voice_bar_battery = lv_bar_create(ui->screen_voice);
    lv_obj_set_style_anim_time(ui->screen_voice_bar_battery, 500, 0);
    lv_bar_set_mode(ui->screen_voice_bar_battery, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_voice_bar_battery, 0, 100);
    lv_bar_set_value(ui->screen_voice_bar_battery, 100, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_voice_bar_battery, 176, 357);
    lv_obj_set_size(ui->screen_voice_bar_battery, 115, 20);

    //Write style for screen_voice_bar_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_voice_bar_battery, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_voice_bar_battery, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_voice_bar_battery, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_bar_battery, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_voice_bar_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_voice_bar_battery, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_voice_bar_battery, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_voice_bar_battery, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_voice_bar_battery, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_bar_battery, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_voice_label_battery
    ui->screen_voice_label_battery = lv_label_create(ui->screen_voice);
    lv_label_set_text(ui->screen_voice_label_battery, "");
    lv_label_set_long_mode(ui->screen_voice_label_battery, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_voice_label_battery, 181, 359);
    lv_obj_set_size(ui->screen_voice_label_battery, 109, 16);

    //Write style for screen_voice_label_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_voice_label_battery, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_voice_label_battery, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_voice_label_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_voice_label_battery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_voice_label_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_voice_btn_record
    ui->screen_voice_btn_record = lv_btn_create(ui->screen_voice);
    ui->screen_voice_btn_record_label = lv_label_create(ui->screen_voice_btn_record);
    lv_label_set_text(ui->screen_voice_btn_record_label, "record");
    lv_label_set_long_mode(ui->screen_voice_btn_record_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_voice_btn_record_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_voice_btn_record, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_voice_btn_record_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_voice_btn_record, 158, 153);
    lv_obj_set_size(ui->screen_voice_btn_record, 148, 50);

    //Write style for screen_voice_btn_record, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_voice_btn_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_voice_btn_record, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_voice_btn_record, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_voice_btn_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_btn_record, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_voice_btn_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_voice_btn_record, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_voice_btn_record, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_voice_btn_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_voice_btn_record, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_voice_label_record
    ui->screen_voice_label_record = lv_label_create(ui->screen_voice);
    lv_label_set_text(ui->screen_voice_label_record, "0.0s");
    lv_label_set_long_mode(ui->screen_voice_label_record, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_voice_label_record, 158, 120);
    lv_obj_set_size(ui->screen_voice_label_record, 159, 20);

    //Write style for screen_voice_label_record, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_voice_label_record, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_voice_label_record, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_voice_label_record, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_voice_label_record, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_voice_label_record, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_voice_label_play
    ui->screen_voice_label_play = lv_label_create(ui->screen_voice);
    lv_label_set_text(ui->screen_voice_label_play, "");
    lv_label_set_long_mode(ui->screen_voice_label_play, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_voice_label_play, 158, 228);
    lv_obj_set_size(ui->screen_voice_label_play, 159, 20);

    //Write style for screen_voice_label_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_voice_label_play, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_voice_label_play, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_voice_label_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_voice_label_play, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_voice_label_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_voice_btn_play
    ui->screen_voice_btn_play = lv_btn_create(ui->screen_voice);
    ui->screen_voice_btn_play_label = lv_label_create(ui->screen_voice_btn_play);
    lv_label_set_text(ui->screen_voice_btn_play_label, "play");
    lv_label_set_long_mode(ui->screen_voice_btn_play_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_voice_btn_play_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_voice_btn_play, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_voice_btn_play_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_voice_btn_play, 158, 265);
    lv_obj_set_size(ui->screen_voice_btn_play, 148, 50);

    //Write style for screen_voice_btn_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_voice_btn_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_voice_btn_play, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_voice_btn_play, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_voice_btn_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_voice_btn_play, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_voice_btn_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_voice_btn_play, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_voice_btn_play, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_voice_btn_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_voice_btn_play, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_voice.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_voice);

    //Init events for screen.
    events_init_screen_voice(ui);
}

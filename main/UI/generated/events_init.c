/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "motor_driver.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "es8311_driver.h"

extern bool is_recording;
extern bool is_playing;
extern bool is_loop_test;

static char buffer[32];

static uint8_t is_recording_flag = 0;

static void screen_logo_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.screen_logo_img_2, 800, 1000, lv_obj_get_y(guider_ui.screen_logo_img_2), -466, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_logo_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_FADE_ON, 0, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    case LV_EVENT_KEY:
    {
        uint8_t key = *(uint8_t *)e->param;
        switch(key) {
        case 1:
        case 2:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_logo_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_FADE_ON, 0, 200, false, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_logo (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_logo, screen_logo_event_handler, LV_EVENT_ALL, ui);
}

static void screen_time_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_info, guider_ui.screen_info_del, &guider_ui.screen_time_del, setup_scr_screen_info, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // ui_load_scr_animation(&guider_ui, &guider_ui.screen_voice, guider_ui.screen_voice_del, &guider_ui.screen_time_del, setup_scr_screen_voice, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_img, guider_ui.screen_img_del, &guider_ui.screen_time_del, setup_scr_screen_img, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    case LV_EVENT_KEY:
    {
        uint8_t key = *(uint8_t *)e->param;
        switch(key) {
        case 1: // 左键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_info, guider_ui.screen_info_del, &guider_ui.screen_time_del, setup_scr_screen_info, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case 2: // 右键
        {
            lv_indev_wait_release(lv_indev_get_act());
            // ui_load_scr_animation(&guider_ui, &guider_ui.screen_voice, guider_ui.screen_voice_del, &guider_ui.screen_time_del, setup_scr_screen_voice, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_img, guider_ui.screen_img_del, &guider_ui.screen_time_del, setup_scr_screen_img, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_time (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_time, screen_time_event_handler, LV_EVENT_ALL, ui);
}

static void screen_info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_vibra, guider_ui.screen_vibra_del, &guider_ui.screen_info_del, setup_scr_screen_vibra, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_info_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    case LV_EVENT_KEY:
    {
        uint8_t key = *(uint8_t *)e->param;
        switch(key) {
        case 1: // 左键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_vibra, guider_ui.screen_vibra_del, &guider_ui.screen_info_del, setup_scr_screen_vibra, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case 2: // 右键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_info_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_info (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_info, screen_info_event_handler, LV_EVENT_ALL, ui);
}

static void screen_vibra_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_voice, guider_ui.screen_voice_del, &guider_ui.screen_vibra_del, setup_scr_screen_voice, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_info, guider_ui.screen_info_del, &guider_ui.screen_vibra_del, setup_scr_screen_info, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    case LV_EVENT_KEY:
    {
        uint8_t key = *(uint8_t *)e->param;
        switch(key) {
        case 1: // 左键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_voice, guider_ui.screen_voice_del, &guider_ui.screen_vibra_del, setup_scr_screen_voice, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case 2: // 右键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_info, guider_ui.screen_info_del, &guider_ui.screen_vibra_del, setup_scr_screen_info, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_vibra_slider_time_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_vibra_slider_time);
        sprintf(buffer, "vibration time\n%dms", value);
        if (guider_ui.screen_vibra_label_time) {
            lv_label_set_text(guider_ui.screen_vibra_label_time, buffer);
        }
        int intensity = lv_slider_get_value(guider_ui.screen_vibra_slider_intnsity);
        set_vibrate_cmd(intensity, value, 500);
        break;
    }
    default:
        break;
    }
}

static void screen_vibra_slider_intensity_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_vibra_slider_time);
        int intensity = lv_slider_get_value(guider_ui.screen_vibra_slider_intnsity);
        sprintf(buffer, "vibration intensity\n%d%%", intensity);
        if (guider_ui.screen_vibra_label_intensity) {
            lv_label_set_text(guider_ui.screen_vibra_label_intensity, buffer);
        }
        set_vibrate_cmd(intensity, value, 500);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_vibra (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_vibra, screen_vibra_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_vibra_slider_time, screen_vibra_slider_time_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_vibra_slider_intnsity, screen_vibra_slider_intensity_event_handler, LV_EVENT_ALL, ui);
}

static void screen_voice_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_voice_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_img, guider_ui.screen_img_del, &guider_ui.screen_voice_del, setup_scr_screen_img, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_vibra, guider_ui.screen_vibra_del, &guider_ui.screen_voice_del, setup_scr_screen_vibra, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    case LV_EVENT_KEY:
    {
        uint8_t key = *(uint8_t *)e->param;
        switch(key) {
        case 1: // 左键
        {
            lv_indev_wait_release(lv_indev_get_act());
            // ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_voice_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_img, guider_ui.screen_img_del, &guider_ui.screen_voice_del, setup_scr_screen_img, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case 2: // 右键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_vibra, guider_ui.screen_vibra_del, &guider_ui.screen_voice_del, setup_scr_screen_vibra, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        case 3: 
        {
            lv_label_set_text(guider_ui.screen_voice_btn_record_label, "start play");
            is_recording_flag = 2;
            break;
        }
        case 4:
        {
            lv_label_set_text(guider_ui.screen_voice_btn_record_label, "start record");
            is_recording_flag = 0;
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_voice_btn_play_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        if (!is_loop_test) 
        {
            is_loop_test = true;
            is_recording = false;
            is_playing = false;
            lv_label_set_text(guider_ui.screen_voice_btn_play_label, "stop");
            lv_label_set_text(guider_ui.screen_voice_btn_record_label, "start record");
            is_recording_flag = 0;
            es8311_test(1);
        } 
        else 
        {
            is_loop_test = false;
            lv_label_set_text(guider_ui.screen_voice_btn_play_label, "loop test");
            es8311_test(0);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_voice_btn_record_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        if (is_loop_test) 
        {
            is_loop_test = false;
            lv_label_set_text(guider_ui.screen_voice_btn_play_label, "loop test");
            es8311_test(0);
        }

        switch (is_recording_flag)
        {
            case 0:
            {
                is_recording = true;
                lv_label_set_text(guider_ui.screen_voice_btn_record_label, "stop record");
                is_recording_flag = 1;
            }
            break;
            case 1:
            {
                is_recording = false;
                lv_label_set_text(guider_ui.screen_voice_btn_record_label, "start play");
                is_recording_flag = 2;
            }
            break;
            case 2:
            {
                is_recording = false;
                lv_label_set_text(guider_ui.screen_voice_btn_record_label, "stop play");
                is_recording_flag = 3;
            }
            break;
            case 3:
            {
                is_recording = false;
                lv_label_set_text(guider_ui.screen_voice_btn_record_label, "start record");
                is_recording_flag = 0;
            }
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_voice_btn_label_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        default:
            break;
        }
    }
    default:
        break;
    }
}

void events_init_screen_voice (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_voice, screen_voice_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_voice_btn_play, screen_voice_btn_play_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_voice_btn_record, screen_voice_btn_record_event_handler, LV_EVENT_ALL, ui);
}

static void screen_img_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_img_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_voice, guider_ui.screen_voice_del, &guider_ui.screen_img_del, setup_scr_screen_voice, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    case LV_EVENT_KEY:
    {
        uint8_t key = *(uint8_t *)e->param;
        switch(key) {
        case 1: // 左键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_time, guider_ui.screen_time_del, &guider_ui.screen_img_del, setup_scr_screen_time, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case 2: // 右键
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_voice, guider_ui.screen_voice_del, &guider_ui.screen_img_del, setup_scr_screen_voice, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }   
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_img (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_img, screen_img_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{

}

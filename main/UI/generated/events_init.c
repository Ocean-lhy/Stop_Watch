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

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void home_analog_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.home_analog_nxp_log, 800, 0, lv_obj_get_x(guider_ui.home_analog_nxp_log), 291, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.home_analog_nxp_log, 800, 0, lv_obj_get_y(guider_ui.home_analog_nxp_log), 175, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_digital, guider_ui.home_digital_del, &guider_ui.home_analog_del, setup_scr_home_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true, false);
            if (guider_ui.home_analog_del) {
                guider_ui.home_analog_analog_clock_1 = NULL;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.contact_list, guider_ui.contact_list_del, &guider_ui.home_analog_del, setup_scr_contact_list, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true, false);
            if (guider_ui.home_analog_del) {
                guider_ui.home_analog_analog_clock_1 = NULL;
            }
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.home_analog_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true, false);
            if (guider_ui.home_analog_del) {
                guider_ui.home_analog_analog_clock_1 = NULL;
            }
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

static void home_analog_weather_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.home_analog_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void home_analog_sport_text_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.fitness, guider_ui.fitness_del, &guider_ui.home_analog_del, setup_scr_fitness, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void home_analog_battery_text_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.battery, guider_ui.battery_del, &guider_ui.home_analog_del, setup_scr_battery, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void home_analog_message_text_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.message_info, guider_ui.message_info_del, &guider_ui.home_analog_del, setup_scr_message_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_home_analog (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_analog, home_analog_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_analog_weather_icon, home_analog_weather_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_analog_sport_text, home_analog_sport_text_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_analog_battery_text, home_analog_battery_text_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_analog_message_text, home_analog_message_text_event_handler, LV_EVENT_ALL, ui);
}

static void home_digital_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.home_digital_img_nxpLogo, 800, 0, lv_obj_get_x(guider_ui.home_digital_img_nxpLogo), 291, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.home_digital_img_nxpLogo, 800, 0, lv_obj_get_y(guider_ui.home_digital_img_nxpLogo), 175, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.home_digital_label_min, 800, 0, lv_obj_get_x(guider_ui.home_digital_label_min), 145, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.home_digital_label_min, 800, 0, lv_obj_get_y(guider_ui.home_digital_label_min), 208, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.home_digital_label_hour, 800, 0, lv_obj_get_x(guider_ui.home_digital_label_hour), 143, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.home_digital_label_hour, 800, 0, lv_obj_get_y(guider_ui.home_digital_label_hour), 82, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.message_info, guider_ui.message_info_del, &guider_ui.home_digital_del, setup_scr_message_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.home_digital_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void home_digital_img_weather1Icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.home_digital_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_home_digital (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_digital, home_digital_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_digital_img_weather1Icon, home_digital_img_weather1Icon_event_handler, LV_EVENT_ALL, ui);
}

static void message_info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.message_info_app_icon, 800, 0, lv_obj_get_x(guider_ui.message_info_app_icon), 166, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.message_info_app_icon, 800, 0, lv_obj_get_y(guider_ui.message_info_app_icon), 30, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.message_info_sender, 800, 0, lv_obj_get_x(guider_ui.message_info_sender), 151, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.message_info_sender, 800, 0, lv_obj_get_y(guider_ui.message_info_sender), 107, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.message_list, guider_ui.message_list_del, &guider_ui.message_info_del, setup_scr_message_list, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.message_info_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void message_info_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_digital, guider_ui.home_digital_del, &guider_ui.message_info_del, setup_scr_home_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void message_info_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.message_list, guider_ui.message_list_del, &guider_ui.message_info_del, setup_scr_message_list, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void message_info_ok_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.message_info_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void message_info_home_text_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.message_info_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_message_info (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->message_info, message_info_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_info_left, message_info_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_info_right, message_info_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_info_ok_btn, message_info_ok_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_info_home_text, message_info_home_text_event_handler, LV_EVENT_ALL, ui);
}

static void message_list_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.message_list_app_icon, 800, 0, lv_obj_get_x(guider_ui.message_list_app_icon), 133, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.message_list_app_icon, 800, 0, lv_obj_get_y(guider_ui.message_list_app_icon), 10, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.standup, guider_ui.standup_del, &guider_ui.message_list_del, setup_scr_standup, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.message_info, guider_ui.message_info_del, &guider_ui.message_list_del, setup_scr_message_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void message_list_img_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void message_list_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.message_info, guider_ui.message_info_del, &guider_ui.message_list_del, setup_scr_message_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void message_list_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.standup, guider_ui.standup_del, &guider_ui.message_list_del, setup_scr_standup, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_message_list (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->message_list, message_list_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_list_img_home, message_list_img_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_list_left, message_list_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->message_list_right, message_list_right_event_handler, LV_EVENT_ALL, ui);
}

static void standup_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.standup_stand_icon, 800, 0, lv_obj_get_x(guider_ui.standup_stand_icon), 154, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.standup_stand_icon, 800, 0, lv_obj_get_y(guider_ui.standup_stand_icon), 23, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.car_lock, guider_ui.car_lock_del, &guider_ui.standup_del, setup_scr_car_lock, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.contact_list, guider_ui.contact_list_del, &guider_ui.standup_del, setup_scr_contact_list, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void standup_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.message_list, guider_ui.message_list_del, &guider_ui.standup_del, setup_scr_message_list, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void standup_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.car_lock, guider_ui.car_lock_del, &guider_ui.standup_del, setup_scr_car_lock, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void standup_ok_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.standup_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void standup_home_text_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.standup_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_standup (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->standup, standup_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->standup_left, standup_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->standup_right, standup_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->standup_ok_btn, standup_ok_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->standup_home_text, standup_home_text_event_handler, LV_EVENT_ALL, ui);
}

static void car_lock_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.car_lock_car_icon, 800, 0, lv_obj_get_x(guider_ui.car_lock_car_icon), 154, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.car_lock_car_icon, 800, 0, lv_obj_get_y(guider_ui.car_lock_car_icon), 23, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.car_lock_cont_1, 800, 0, lv_obj_get_x(guider_ui.car_lock_cont_1), 78, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.car_lock_cont_1, 800, 0, lv_obj_get_y(guider_ui.car_lock_cont_1), 193, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.car_lock_lock_icon2, 200, 800, lv_obj_get_x(guider_ui.car_lock_lock_icon2), 79, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.car_lock_lock_icon2, 200, 800, lv_obj_get_y(guider_ui.car_lock_lock_icon2), 30, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.car_start, guider_ui.car_start_del, &guider_ui.car_lock_del, setup_scr_car_start, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.standup, guider_ui.standup_del, &guider_ui.car_lock_del, setup_scr_standup, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void car_lock_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.standup, guider_ui.standup_del, &guider_ui.car_lock_del, setup_scr_standup, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void car_lock_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.car_start, guider_ui.car_start_del, &guider_ui.car_lock_del, setup_scr_car_start, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void car_lock_home_text_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.car_lock_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_car_lock (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->car_lock, car_lock_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->car_lock_left, car_lock_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->car_lock_right, car_lock_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->car_lock_home_text, car_lock_home_text_event_handler, LV_EVENT_ALL, ui);
}

static void car_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.car_start_start_imgbtn, 800, 0, lv_obj_get_x(guider_ui.car_start_start_imgbtn), 104, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.car_start_start_imgbtn, 800, 0, lv_obj_get_y(guider_ui.car_start_start_imgbtn), 179, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.car_start_car_icon, 800, 0, lv_obj_get_x(guider_ui.car_start_car_icon), 154, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.car_start_car_icon, 800, 0, lv_obj_get_y(guider_ui.car_start_car_icon), 23, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.listening, guider_ui.listening_del, &guider_ui.car_start_del, setup_scr_listening, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.car_lock, guider_ui.car_lock_del, &guider_ui.car_start_del, setup_scr_car_lock, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void car_start_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.car_lock, guider_ui.car_lock_del, &guider_ui.car_start_del, setup_scr_car_lock, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void car_start_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.listening, guider_ui.listening_del, &guider_ui.car_start_del, setup_scr_listening, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void car_start_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.car_start_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_car_start (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->car_start, car_start_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->car_start_left, car_start_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->car_start_right, car_start_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->car_start_home, car_start_home_event_handler, LV_EVENT_ALL, ui);
}

static void listening_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.listening_listen_text, 800, 0, lv_obj_get_x(guider_ui.listening_listen_text), 101, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.listening_listen_text, 800, 0, lv_obj_get_y(guider_ui.listening_listen_text), 307, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.not_recognized, guider_ui.not_recognized_del, &guider_ui.listening_del, setup_scr_not_recognized, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.car_start, guider_ui.car_start_del, &guider_ui.listening_del, setup_scr_car_start, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void listening_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.car_start, guider_ui.car_start_del, &guider_ui.listening_del, setup_scr_car_start, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void listening_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.not_recognized, guider_ui.not_recognized_del, &guider_ui.listening_del, setup_scr_not_recognized, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void listening_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.listening_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_listening (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->listening, listening_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->listening_left, listening_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->listening_right, listening_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->listening_home, listening_home_event_handler, LV_EVENT_ALL, ui);
}

static void not_recognized_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.not_recognized_no_mic_icon, 800, 0, lv_obj_get_x(guider_ui.not_recognized_no_mic_icon), 101, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.not_recognized_no_mic_icon, 800, 0, lv_obj_get_y(guider_ui.not_recognized_no_mic_icon), 72, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.not_recognized_command_text, 800, 0, lv_obj_get_x(guider_ui.not_recognized_command_text), 108, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.not_recognized_command_text, 800, 0, lv_obj_get_y(guider_ui.not_recognized_command_text), 307, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.recognized, guider_ui.recognized_del, &guider_ui.not_recognized_del, setup_scr_recognized, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.listening, guider_ui.listening_del, &guider_ui.not_recognized_del, setup_scr_listening, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void not_recognized_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.listening, guider_ui.listening_del, &guider_ui.not_recognized_del, setup_scr_listening, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void not_recognized_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.recognized, guider_ui.recognized_del, &guider_ui.not_recognized_del, setup_scr_recognized, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_not_recognized (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->not_recognized, not_recognized_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->not_recognized_left, not_recognized_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->not_recognized_right, not_recognized_right_event_handler, LV_EVENT_ALL, ui);
}

static void recognized_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.recognized_command_text, 800, 0, lv_obj_get_x(guider_ui.recognized_command_text), 137, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.recognized_command_text, 800, 0, lv_obj_get_y(guider_ui.recognized_command_text), 307, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.recognized_done_mic, 800, 0, lv_obj_get_x(guider_ui.recognized_done_mic), 101, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.recognized_done_mic, 800, 0, lv_obj_get_y(guider_ui.recognized_done_mic), 72, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.recognized_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.not_recognized, guider_ui.not_recognized_del, &guider_ui.recognized_del, setup_scr_not_recognized, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void recognized_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.not_recognized, guider_ui.not_recognized_del, &guider_ui.recognized_del, setup_scr_not_recognized, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void recognized_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.recognized_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_recognized (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->recognized, recognized_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->recognized_left, recognized_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->recognized_home, recognized_home_event_handler, LV_EVENT_ALL, ui);
}

static void contact_list_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.contact_list_label_title, 800, 0, lv_obj_get_x(guider_ui.contact_list_label_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.contact_list_label_title, 800, 0, lv_obj_get_y(guider_ui.contact_list_label_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.contact_list_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void contact_list_cont_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.call, guider_ui.call_del, &guider_ui.contact_list_del, setup_scr_call, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void contact_list_img_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.call, guider_ui.call_del, &guider_ui.contact_list_del, setup_scr_call, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void contact_list_img_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

void events_init_contact_list (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->contact_list, contact_list_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->contact_list_cont_2, contact_list_cont_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->contact_list_img_3, contact_list_img_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->contact_list_img_home, contact_list_img_home_event_handler, LV_EVENT_ALL, ui);
}

static void call_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.call_img_7, 800, 0, lv_obj_get_x(guider_ui.call_img_7), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.call_img_7, 800, 0, lv_obj_get_y(guider_ui.call_img_7), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.call_unmute_icon, 800, 0, lv_obj_get_x(guider_ui.call_unmute_icon), 180, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.call_unmute_icon, 800, 0, lv_obj_get_y(guider_ui.call_unmute_icon), 321, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void call_img_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.call_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void call_hang_up_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.call_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);

        if (guider_ui.call_del) {
            guider_ui.call_digital_clock_1 = NULL;
        }
        break;
    }
    default:
        break;
    }
}

static void call_unmute_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.call_mute_icon, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void call_mute_icon_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.call_unmute_icon, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.call_mute_icon, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_call (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->call, call_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->call_img_6, call_img_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->call_hang_up_btn, call_hang_up_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->call_unmute_icon, call_unmute_icon_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->call_mute_icon, call_mute_icon_event_handler, LV_EVENT_ALL, ui);
}

static void weather_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.weather_img_bgCloud, 5000, 0, lv_obj_get_x(guider_ui.weather_img_bgCloud), -194, &lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_img_bgCloud, 5000, 0, lv_obj_get_y(guider_ui.weather_img_bgCloud), 0, &lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_label_city, 800, 0, lv_obj_get_x(guider_ui.weather_label_city), 82, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_label_city, 800, 0, lv_obj_get_y(guider_ui.weather_label_city), 30, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_label_maxMin, 800, 0, lv_obj_get_x(guider_ui.weather_label_maxMin), 72, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_label_maxMin, 800, 0, lv_obj_get_y(guider_ui.weather_label_maxMin), 293, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_img_icon, 800, 0, lv_obj_get_x(guider_ui.weather_img_icon), 163, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_img_icon, 800, 0, lv_obj_get_y(guider_ui.weather_img_icon), 227, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather_hour, guider_ui.weather_hour_del, &guider_ui.weather_del, setup_scr_weather_hour, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.weather_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.fitness, guider_ui.fitness_del, &guider_ui.weather_del, setup_scr_fitness, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void weather_img_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

void events_init_weather (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weather, weather_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_img_home, weather_img_home_event_handler, LV_EVENT_ALL, ui);
}

static void weather_hour_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.weather_hour_title, 800, 0, lv_obj_get_x(guider_ui.weather_hour_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_hour_title, 800, 0, lv_obj_get_y(guider_ui.weather_hour_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather_week, guider_ui.weather_week_del, &guider_ui.weather_hour_del, setup_scr_weather_week, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.weather_hour_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void weather_hour_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.weather_hour_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void weather_hour_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.weather_hour_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void weather_hour_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather_week, guider_ui.weather_week_del, &guider_ui.weather_hour_del, setup_scr_weather_week, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_weather_hour (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weather_hour, weather_hour_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_hour_home, weather_hour_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_hour_left, weather_hour_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_hour_right, weather_hour_right_event_handler, LV_EVENT_ALL, ui);
}

static void weather_week_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.weather_week_week_title, 800, 0, lv_obj_get_x(guider_ui.weather_week_week_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.weather_week_week_title, 800, 0, lv_obj_get_y(guider_ui.weather_week_week_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.air_quality, guider_ui.air_quality_del, &guider_ui.weather_week_del, setup_scr_air_quality, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather_hour, guider_ui.weather_hour_del, &guider_ui.weather_week_del, setup_scr_weather_hour, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void weather_week_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.weather_week_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void weather_week_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather_hour, guider_ui.weather_hour_del, &guider_ui.weather_week_del, setup_scr_weather_hour, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void weather_week_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.air_quality, guider_ui.air_quality_del, &guider_ui.weather_week_del, setup_scr_air_quality, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_weather_week (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weather_week, weather_week_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_week_home, weather_week_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_week_left, weather_week_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_week_right, weather_week_right_event_handler, LV_EVENT_ALL, ui);
}

static void air_quality_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.air_quality_air_title, 800, 0, lv_obj_get_x(guider_ui.air_quality_air_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.air_quality_air_title, 800, 0, lv_obj_get_y(guider_ui.air_quality_air_title), 0, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.air_quality_ade_text, 800, 0, lv_obj_get_x(guider_ui.air_quality_ade_text), 102, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.air_quality_ade_text, 800, 0, lv_obj_get_y(guider_ui.air_quality_ade_text), 315, &lv_anim_path_bounce, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather_week, guider_ui.weather_week_del, &guider_ui.air_quality_del, setup_scr_weather_week, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void air_quality_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.air_quality_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void air_quality_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather_week, guider_ui.weather_week_del, &guider_ui.air_quality_del, setup_scr_weather_week, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_air_quality (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->air_quality, air_quality_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->air_quality_home, air_quality_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->air_quality_left, air_quality_left_event_handler, LV_EVENT_ALL, ui);
}

static void fitness_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.fitness_title, 800, 0, lv_obj_get_x(guider_ui.fitness_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_title, 800, 0, lv_obj_get_y(guider_ui.fitness_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_calorie_arc, 500, 0, lv_obj_get_x(guider_ui.fitness_calorie_arc), 7, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_calorie_arc, 500, 0, lv_obj_get_y(guider_ui.fitness_calorie_arc), 49, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_distance_arc, 500, 0, lv_obj_get_x(guider_ui.fitness_distance_arc), 32, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_distance_arc, 500, 0, lv_obj_get_y(guider_ui.fitness_distance_arc), 76, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_duration_arc, 500, 0, lv_obj_get_x(guider_ui.fitness_duration_arc), 57, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_duration_arc, 500, 0, lv_obj_get_y(guider_ui.fitness_duration_arc), 99, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_pluse_arc, 500, 0, lv_obj_get_x(guider_ui.fitness_pluse_arc), 82, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.fitness_pluse_arc, 500, 0, lv_obj_get_y(guider_ui.fitness_pluse_arc), 124, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.fitness_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.music_player, guider_ui.music_player_del, &guider_ui.fitness_del, setup_scr_music_player, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void fitness_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.fitness_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_fitness (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->fitness, fitness_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->fitness_home, fitness_home_event_handler, LV_EVENT_ALL, ui);
}

static void music_player_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.fitness, guider_ui.fitness_del, &guider_ui.music_player_del, setup_scr_fitness, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.flight, guider_ui.flight_del, &guider_ui.music_player_del, setup_scr_flight, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void music_player_img_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.music_player_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void music_player_img_puse_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.music_player_img_play, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.music_player_img_puse, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void music_player_img_play_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.music_player_img_play, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.music_player_img_puse, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_music_player (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->music_player, music_player_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->music_player_img_home, music_player_img_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->music_player_img_puse, music_player_img_puse_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->music_player_img_play, music_player_img_play_event_handler, LV_EVENT_ALL, ui);
}

static void flight_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.flight_flight_location, 800, 0, lv_obj_get_x(guider_ui.flight_flight_location), 36, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_flight_location, 800, 0, lv_obj_get_y(guider_ui.flight_flight_location), 86, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_flight_seat, 800, 0, lv_obj_get_x(guider_ui.flight_flight_seat), 64, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_flight_seat, 800, 0, lv_obj_get_y(guider_ui.flight_flight_seat), 295, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_title, 800, 0, lv_obj_get_x(guider_ui.flight_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_title, 800, 0, lv_obj_get_y(guider_ui.flight_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.flight_info, guider_ui.flight_info_del, &guider_ui.flight_del, setup_scr_flight_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.music_player, guider_ui.music_player_del, &guider_ui.flight_del, setup_scr_music_player, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.navigation, guider_ui.navigation_del, &guider_ui.flight_del, setup_scr_navigation, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void flight_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.flight_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_flight (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->flight, flight_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->flight_home, flight_home_event_handler, LV_EVENT_ALL, ui);
}

static void flight_info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.flight_info_title, 800, 0, lv_obj_get_x(guider_ui.flight_info_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_title, 800, 0, lv_obj_get_y(guider_ui.flight_info_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_qrcode, 800, 0, lv_obj_get_x(guider_ui.flight_info_qrcode), 93, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_qrcode, 800, 0, lv_obj_get_y(guider_ui.flight_info_qrcode), 144, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_flight_number, 800, 0, lv_obj_get_x(guider_ui.flight_info_flight_number), 129, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_flight_number, 800, 0, lv_obj_get_y(guider_ui.flight_info_flight_number), 102, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_number_text, 800, 0, lv_obj_get_x(guider_ui.flight_info_number_text), 120, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.flight_info_number_text, 800, 0, lv_obj_get_y(guider_ui.flight_info_number_text), 85, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.flight, guider_ui.flight_del, &guider_ui.flight_info_del, setup_scr_flight, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.flight, guider_ui.flight_del, &guider_ui.flight_info_del, setup_scr_flight, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void flight_info_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.flight_info_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_flight_info (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->flight_info, flight_info_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->flight_info_home, flight_info_home_event_handler, LV_EVENT_ALL, ui);
}

static void navigation_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.navigation_indicator, 800, 0, lv_obj_get_x(guider_ui.navigation_indicator), 88, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_indicator, 800, 0, lv_obj_get_y(guider_ui.navigation_indicator), 291, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_road_name, 800, 0, lv_obj_get_x(guider_ui.navigation_road_name), 83, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_road_name, 800, 0, lv_obj_get_y(guider_ui.navigation_road_name), 89, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_next_roadName, 800, 0, lv_obj_get_x(guider_ui.navigation_next_roadName), 93, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_next_roadName, 800, 0, lv_obj_get_y(guider_ui.navigation_next_roadName), 120, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_title, 800, 0, lv_obj_get_x(guider_ui.navigation_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.navigation_title, 800, 0, lv_obj_get_y(guider_ui.navigation_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.flight, guider_ui.flight_del, &guider_ui.navigation_del, setup_scr_flight, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.position, guider_ui.position_del, &guider_ui.navigation_del, setup_scr_position, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.payment, guider_ui.payment_del, &guider_ui.navigation_del, setup_scr_payment, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void navigation_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.navigation_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_navigation (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->navigation, navigation_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->navigation_home, navigation_home_event_handler, LV_EVENT_ALL, ui);
}

static void position_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.position_bottom, 800, 0, lv_obj_get_x(guider_ui.position_bottom), 96, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.position_bottom, 800, 0, lv_obj_get_y(guider_ui.position_bottom), 290, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.position_title, 800, 0, lv_obj_get_x(guider_ui.position_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.position_title, 800, 0, lv_obj_get_y(guider_ui.position_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        lv_obj_clear_flag(guider_ui.position_location_icon, LV_OBJ_FLAG_CLICKABLE);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.navigation, guider_ui.navigation_del, &guider_ui.position_del, setup_scr_navigation, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.navigation, guider_ui.navigation_del, &guider_ui.position_del, setup_scr_navigation, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void position_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.position_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_position (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->position, position_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->position_home, position_home_event_handler, LV_EVENT_ALL, ui);
}

static void payment_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.payment_bank_info, 800, 0, lv_obj_get_x(guider_ui.payment_bank_info), 63, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_bank_info, 800, 0, lv_obj_get_y(guider_ui.payment_bank_info), 313, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_amount, 1000, 0, lv_obj_get_x(guider_ui.payment_amount), 92, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_amount, 1000, 0, lv_obj_get_y(guider_ui.payment_amount), 101, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_next_buy, 800, 0, lv_obj_get_x(guider_ui.payment_next_buy), 130, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_next_buy, 800, 0, lv_obj_get_y(guider_ui.payment_next_buy), 84, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_title, 800, 0, lv_obj_get_x(guider_ui.payment_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_title, 800, 0, lv_obj_get_y(guider_ui.payment_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.navigation, guider_ui.navigation_del, &guider_ui.payment_del, setup_scr_navigation, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.payment_info, guider_ui.payment_info_del, &guider_ui.payment_del, setup_scr_payment_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.settings, guider_ui.settings_del, &guider_ui.payment_del, setup_scr_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void payment_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.payment_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_payment (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->payment, payment_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->payment_home, payment_home_event_handler, LV_EVENT_ALL, ui);
}

static void payment_info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.payment_info_pay_info, 800, 0, lv_obj_get_x(guider_ui.payment_info_pay_info), 69, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_info_pay_info, 800, 0, lv_obj_get_y(guider_ui.payment_info_pay_info), 246, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_info_title, 800, 0, lv_obj_get_x(guider_ui.payment_info_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.payment_info_title, 800, 0, lv_obj_get_y(guider_ui.payment_info_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.payment, guider_ui.payment_del, &guider_ui.payment_info_del, setup_scr_payment, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.payment, guider_ui.payment_del, &guider_ui.payment_info_del, setup_scr_payment, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void payment_info_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.payment_info_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_payment_info (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->payment_info, payment_info_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->payment_info_home, payment_info_home_event_handler, LV_EVENT_ALL, ui);
}

static void settings_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.settings_setting_info, 800, 0, lv_obj_get_x(guider_ui.settings_setting_info), 64, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.settings_setting_info, 800, 0, lv_obj_get_y(guider_ui.settings_setting_info), 89, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.settings_title, 800, 0, lv_obj_get_x(guider_ui.settings_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.settings_title, 800, 0, lv_obj_get_y(guider_ui.settings_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.payment, guider_ui.payment_del, &guider_ui.settings_del, setup_scr_payment, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.battery, guider_ui.battery_del, &guider_ui.settings_del, setup_scr_battery, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.blood_oxygen, guider_ui.blood_oxygen_del, &guider_ui.settings_del, setup_scr_blood_oxygen, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void settings_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.settings_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_settings (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->settings, settings_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_home, settings_home_event_handler, LV_EVENT_ALL, ui);
}

static void battery_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.battery_setting_info, 800, 0, lv_obj_get_x(guider_ui.battery_setting_info), 24, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.battery_setting_info, 800, 0, lv_obj_get_y(guider_ui.battery_setting_info), 84, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.battery_title, 800, 0, lv_obj_get_x(guider_ui.battery_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.battery_title, 800, 0, lv_obj_get_y(guider_ui.battery_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.settings, guider_ui.settings_del, &guider_ui.battery_del, setup_scr_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.info, guider_ui.info_del, &guider_ui.battery_del, setup_scr_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void battery_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.battery_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_battery (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->battery, battery_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->battery_home, battery_home_event_handler, LV_EVENT_ALL, ui);
}

static void info_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.info_setting_info, 800, 0, lv_obj_get_x(guider_ui.info_setting_info), 63, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.info_setting_info, 800, 0, lv_obj_get_y(guider_ui.info_setting_info), 83, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.info_title, 800, 0, lv_obj_get_x(guider_ui.info_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.info_title, 800, 0, lv_obj_get_y(guider_ui.info_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.battery, guider_ui.battery_del, &guider_ui.info_del, setup_scr_battery, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.find_device, guider_ui.find_device_del, &guider_ui.info_del, setup_scr_find_device, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void info_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.info_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_info (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->info, info_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->info_home, info_home_event_handler, LV_EVENT_ALL, ui);
}

static void find_device_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.find_device_title, 800, 0, lv_obj_get_x(guider_ui.find_device_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.find_device_title, 800, 0, lv_obj_get_y(guider_ui.find_device_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.find_device_btn_start, 800, 0, lv_obj_get_x(guider_ui.find_device_btn_start), 131, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.find_device_btn_start, 800, 0, lv_obj_get_y(guider_ui.find_device_btn_start), 308, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.info, guider_ui.info_del, &guider_ui.find_device_del, setup_scr_info, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void find_device_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.find_device_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void find_device_btn_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.play_sound, guider_ui.play_sound_del, &guider_ui.find_device_del, setup_scr_play_sound, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_find_device (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->find_device, find_device_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->find_device_home, find_device_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->find_device_btn_start, find_device_btn_start_event_handler, LV_EVENT_ALL, ui);
}

static void play_sound_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.play_sound_btn_cancel, 800, 0, lv_obj_get_x(guider_ui.play_sound_btn_cancel), 126, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.play_sound_btn_cancel, 800, 0, lv_obj_get_y(guider_ui.play_sound_btn_cancel), 308, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.play_sound_title, 800, 0, lv_obj_get_x(guider_ui.play_sound_title), 32, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.play_sound_title, 800, 0, lv_obj_get_y(guider_ui.play_sound_title), 35, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.play_sound_img_find, 500, 0, lv_img_get_zoom(guider_ui.play_sound_img_find), 331, &lv_anim_path_ease_in, LV_ANIM_REPEAT_INFINITE, 0, 500, 0, (lv_anim_exec_xcb_t)lv_img_set_zoom, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void play_sound_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.play_sound_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void play_sound_btn_cancel_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.find_device, guider_ui.find_device_del, &guider_ui.play_sound_del, setup_scr_find_device, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_play_sound (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->play_sound, play_sound_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->play_sound_home, play_sound_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->play_sound_btn_cancel, play_sound_btn_cancel_event_handler, LV_EVENT_ALL, ui);
}

static void blood_oxygen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.blood_oxygen_title, 800, 0, lv_obj_get_x(guider_ui.blood_oxygen_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_oxygen_title, 800, 0, lv_obj_get_y(guider_ui.blood_oxygen_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_oxygen_arc_blood, 800, 0, lv_obj_get_x(guider_ui.blood_oxygen_arc_blood), 11, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_oxygen_arc_blood, 800, 0, lv_obj_get_y(guider_ui.blood_oxygen_arc_blood), 11, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_oxygen_label_ago, 800, 0, lv_obj_get_x(guider_ui.blood_oxygen_label_ago), 123, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_oxygen_label_ago, 800, 0, lv_obj_get_y(guider_ui.blood_oxygen_label_ago), 260, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.settings, guider_ui.settings_del, &guider_ui.blood_oxygen_del, setup_scr_settings, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.ekg, guider_ui.ekg_del, &guider_ui.blood_oxygen_del, setup_scr_ekg, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.blood_oxygen_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void blood_oxygen_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.blood_oxygen_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_blood_oxygen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->blood_oxygen, blood_oxygen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->blood_oxygen_home, blood_oxygen_home_event_handler, LV_EVENT_ALL, ui);
}

static void ekg_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_clear_flag(guider_ui.ekg_cont_2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
        ui_animation(guider_ui.ekg_cont_2, 700, 0, lv_obj_get_x(guider_ui.ekg_cont_2), -127, &lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.ekg_cont_2, 700, 0, lv_obj_get_y(guider_ui.ekg_cont_2), 135, &lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.ekg_cont_1, 800, 0, lv_obj_get_x(guider_ui.ekg_cont_1), 106, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.ekg_cont_1, 800, 0, lv_obj_get_y(guider_ui.ekg_cont_1), 294, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.ekg_title, 800, 0, lv_obj_get_x(guider_ui.ekg_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.ekg_title, 800, 0, lv_obj_get_y(guider_ui.ekg_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.ekg_img_healthy, 500, 0, lv_img_get_zoom(guider_ui.ekg_img_healthy), 372, &lv_anim_path_ease_in, LV_ANIM_REPEAT_INFINITE, 0, 500, 0, (lv_anim_exec_xcb_t)lv_img_set_zoom, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.blood_oxygen, guider_ui.blood_oxygen_del, &guider_ui.ekg_del, setup_scr_blood_oxygen, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.stress_level, guider_ui.stress_level_del, &guider_ui.ekg_del, setup_scr_stress_level, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void ekg_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.ekg_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_ekg (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->ekg, ekg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ekg_home, ekg_home_event_handler, LV_EVENT_ALL, ui);
}

static void stress_level_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.stress_level_title, 800, 0, lv_obj_get_x(guider_ui.stress_level_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.stress_level_title, 800, 0, lv_obj_get_y(guider_ui.stress_level_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.stress_level_label_average, 800, 0, lv_obj_get_x(guider_ui.stress_level_label_average), 127, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.stress_level_label_average, 800, 0, lv_obj_get_y(guider_ui.stress_level_label_average), 286, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.stress_level_label_ago, 800, 0, lv_obj_get_x(guider_ui.stress_level_label_ago), 133, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.stress_level_label_ago, 800, 0, lv_obj_get_y(guider_ui.stress_level_label_ago), 88, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.ekg, guider_ui.ekg_del, &guider_ui.stress_level_del, setup_scr_ekg, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.blood_pressure, guider_ui.blood_pressure_del, &guider_ui.stress_level_del, setup_scr_blood_pressure, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void stress_level_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.stress_level_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_stress_level (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->stress_level, stress_level_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->stress_level_home, stress_level_home_event_handler, LV_EVENT_ALL, ui);
}

static void blood_pressure_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.blood_pressure_cont_1, 800, 0, lv_obj_get_x(guider_ui.blood_pressure_cont_1), 119, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_pressure_cont_1, 800, 0, lv_obj_get_y(guider_ui.blood_pressure_cont_1), 298, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_pressure_arc_stress, 800, 0, lv_obj_get_x(guider_ui.blood_pressure_arc_stress), 11, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_pressure_arc_stress, 800, 0, lv_obj_get_y(guider_ui.blood_pressure_arc_stress), 11, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_pressure_title, 800, 0, lv_obj_get_x(guider_ui.blood_pressure_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.blood_pressure_title, 800, 0, lv_obj_get_y(guider_ui.blood_pressure_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.stress_level, guider_ui.stress_level_del, &guider_ui.blood_pressure_del, setup_scr_stress_level, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.sleep, guider_ui.sleep_del, &guider_ui.blood_pressure_del, setup_scr_sleep, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void blood_pressure_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.blood_pressure_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_blood_pressure (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->blood_pressure, blood_pressure_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->blood_pressure_home, blood_pressure_home_event_handler, LV_EVENT_ALL, ui);
}

static void sleep_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.sleep_cont_1, 800, 0, lv_obj_get_x(guider_ui.sleep_cont_1), 111, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.sleep_cont_1, 800, 0, lv_obj_get_y(guider_ui.sleep_cont_1), 302, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.sleep_label_stages, 800, 0, lv_obj_get_x(guider_ui.sleep_label_stages), 112, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.sleep_label_stages, 800, 0, lv_obj_get_y(guider_ui.sleep_label_stages), 78, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.sleep_title, 800, 0, lv_obj_get_x(guider_ui.sleep_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.sleep_title, 800, 0, lv_obj_get_y(guider_ui.sleep_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.blood_pressure, guider_ui.blood_pressure_del, &guider_ui.sleep_del, setup_scr_blood_pressure, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.step, guider_ui.step_del, &guider_ui.sleep_del, setup_scr_step, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void sleep_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.sleep_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_sleep (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->sleep, sleep_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->sleep_home, sleep_home_event_handler, LV_EVENT_ALL, ui);
}

static void step_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.step_cont_1, 800, 0, lv_obj_get_x(guider_ui.step_cont_1), 111, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.step_cont_1, 800, 0, lv_obj_get_y(guider_ui.step_cont_1), 260, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.step_title, 800, 0, lv_obj_get_x(guider_ui.step_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.step_title, 800, 0, lv_obj_get_y(guider_ui.step_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.step_icon_step, 800, 0, lv_obj_get_x(guider_ui.step_icon_step), 182, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.step_icon_step, 800, 0, lv_obj_get_y(guider_ui.step_icon_step), 93, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.step_arc_step, 800, 0, lv_obj_get_x(guider_ui.step_arc_step), 11, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.step_arc_step, 800, 0, lv_obj_get_y(guider_ui.step_arc_step), 11, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.sleep, guider_ui.sleep_del, &guider_ui.step_del, setup_scr_sleep, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.menstrual, guider_ui.menstrual_del, &guider_ui.step_del, setup_scr_menstrual, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

void events_init_step (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->step, step_event_handler, LV_EVENT_ALL, ui);
}

static void menstrual_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.menstrual_label_cycle, 800, 0, lv_obj_get_x(guider_ui.menstrual_label_cycle), 148, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.menstrual_label_cycle, 800, 0, lv_obj_get_y(guider_ui.menstrual_label_cycle), 78, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.menstrual_label_ovulation, 800, 0, lv_obj_get_x(guider_ui.menstrual_label_ovulation), 121, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.menstrual_label_ovulation, 800, 0, lv_obj_get_y(guider_ui.menstrual_label_ovulation), 327, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.menstrual_title, 800, 0, lv_obj_get_x(guider_ui.menstrual_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.menstrual_title, 800, 0, lv_obj_get_y(guider_ui.menstrual_title), 0, &lv_anim_path_bounce, 1, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.blood_oxygen, guider_ui.blood_oxygen_del, &guider_ui.menstrual_del, setup_scr_blood_oxygen, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.step, guider_ui.step_del, &guider_ui.menstrual_del, setup_scr_step, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
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

static void menstrual_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_analog, guider_ui.home_analog_del, &guider_ui.menstrual_del, setup_scr_home_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_menstrual (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menstrual, menstrual_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menstrual_home, menstrual_home_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}

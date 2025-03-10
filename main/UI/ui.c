// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: Smartwatch

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void sec_Animation(lv_obj_t * TargetObject, int delay);
void min_Animation(lv_obj_t * TargetObject, int delay);
void hour_Animation(lv_obj_t * TargetObject, int delay);
void left_Animation(lv_obj_t * TargetObject, int delay);
void right_Animation(lv_obj_t * TargetObject, int delay);
void opa_on_Animation(lv_obj_t * TargetObject, int delay);
void dots_Animation(lv_obj_t * TargetObject, int delay);
void top_Animation(lv_obj_t * TargetObject, int delay);
void cloud_Animation(lv_obj_t * TargetObject, int delay);
void blood2_Animation(lv_obj_t * TargetObject, int delay);
void blood1_Animation(lv_obj_t * TargetObject, int delay);
void heart_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_watch_digital
void ui_watch_digital_screen_init(void);
void ui_event_watch_digital(lv_event_t * e);
lv_obj_t * ui_watch_digital;
lv_obj_t * ui_bg_1;
lv_obj_t * ui_hour_group;
lv_obj_t * ui_label_hour_1;
lv_obj_t * ui_label_hour_2;
lv_obj_t * ui_label_min;
lv_obj_t * ui_battery_group;
lv_obj_t * ui_date_group;
lv_obj_t * ui_weather_group_1;
lv_obj_t * ui_weather_title_group_1;
lv_obj_t * ui_step_group;
lv_obj_t * ui_daily_mission_group;
void ui_event_button_top_buttontop(lv_event_t * e);
lv_obj_t * ui_button_top;
void ui_event_button_down_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down;
lv_obj_t * ui_sec_dot;
lv_obj_t * ui_weather_dots_group2;
lv_obj_t * ui_dot14;
lv_obj_t * ui_dot15;
// CUSTOM VARIABLES


// SCREEN: ui_watch_analog
void ui_watch_analog_screen_init(void);
void ui_event_watch_analog(lv_event_t * e);
lv_obj_t * ui_watch_analog;
lv_obj_t * ui_bg_2;
lv_obj_t * ui_clock;
lv_obj_t * ui_dots;
lv_obj_t * ui_battery_group1;
lv_obj_t * ui_date_group2;
lv_obj_t * ui_day2;
lv_obj_t * ui_month2;
lv_obj_t * ui_year2;
lv_obj_t * ui_weather_title_group_2;
lv_obj_t * ui_weather_group_5;
lv_obj_t * ui_degree_7;
lv_obj_t * ui_cloud_fog_3;
lv_obj_t * ui_step_group2;
lv_obj_t * ui_daily_mission_group1;
void ui_event_button_top1_buttontop(lv_event_t * e);
lv_obj_t * ui_button_top1;
void ui_event_button_down1_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down1;
lv_obj_t * ui_clock_group;
lv_obj_t * ui_sec;
lv_obj_t * ui_min;
lv_obj_t * ui_hour;
lv_obj_t * ui_dots_group;
lv_obj_t * ui_dot16;
lv_obj_t * ui_dot17;
// CUSTOM VARIABLES


// SCREEN: ui_call
void ui_call_screen_init(void);
void ui_event_call(lv_event_t * e);
lv_obj_t * ui_call;
lv_obj_t * ui_bg_3;
lv_obj_t * ui_avatar;
lv_obj_t * ui_avatar_label;
lv_obj_t * ui_call_time;
lv_obj_t * ui_mute;
void ui_event_button_down2_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down2;
lv_obj_t * ui_volume_group;
lv_obj_t * ui_volume_percent;
lv_obj_t * ui_volume_image;
void ui_event_volume_arc(lv_event_t * e);
lv_obj_t * ui_volume_arc;
void ui_event_button_top2_buttontop(lv_event_t * e);
lv_obj_t * ui_button_top2;
// CUSTOM VARIABLES


// SCREEN: ui_weather_1
void ui_weather_1_screen_init(void);
void ui_event_weather_1(lv_event_t * e);
lv_obj_t * ui_weather_1;
lv_obj_t * ui_bg_4;
lv_obj_t * ui_city_gruop_1;
lv_obj_t * ui_weather_title_group_3;
lv_obj_t * ui_label_degree;
lv_obj_t * ui_rain_group;
lv_obj_t * ui_rain_icon;
lv_obj_t * ui_rain_percent;
lv_obj_t * ui_wind_group;
lv_obj_t * ui_wind_icon;
lv_obj_t * ui_wind_speed;
lv_obj_t * ui_weather_dots_group;
lv_obj_t * ui_dot1;
lv_obj_t * ui_dot2;
lv_obj_t * ui_weather_image_group;
lv_obj_t * ui_sun;
lv_obj_t * ui_clouds;
void ui_event_button_down3_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down3;
// CUSTOM VARIABLES


// SCREEN: ui_weather_2
void ui_weather_2_screen_init(void);
void ui_event_weather_2(lv_event_t * e);
lv_obj_t * ui_weather_2;
lv_obj_t * ui_bg5;
lv_obj_t * ui_weather_dots_group1;
lv_obj_t * ui_dot3;
lv_obj_t * ui_dot4;
lv_obj_t * ui_content;
lv_obj_t * ui_city_gruop_2;
lv_obj_t * ui_todady_weather_content;
lv_obj_t * ui_today_weather_group;
lv_obj_t * ui_today_weather_group1;
lv_obj_t * ui_today_weather_group2;
lv_obj_t * ui_today_weather_group3;
lv_obj_t * ui_today_weather_group4;
lv_obj_t * ui_today_weather_group5;
lv_obj_t * ui_today_weather_group6;
lv_obj_t * ui_today_weather_group7;
lv_obj_t * ui_today_weather_group8;
lv_obj_t * ui_days_forecast;
lv_obj_t * ui_week_weather_group;
lv_obj_t * ui_forecast_group;
lv_obj_t * ui_forecast_group1;
lv_obj_t * ui_forecast_group2;
lv_obj_t * ui_forecast_group3;
lv_obj_t * ui_forecast_group4;
lv_obj_t * ui_forecast_group5;
lv_obj_t * ui_space;
void ui_event_button_down4_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down4;
// CUSTOM VARIABLES


// SCREEN: ui_blood_oxy
void ui_blood_oxy_screen_init(void);
void ui_event_blood_oxy(lv_event_t * e);
lv_obj_t * ui_blood_oxy;
lv_obj_t * ui_bg6;
lv_obj_t * ui_title_group_1;
void ui_event_button_down5_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down5;
void ui_event_button_round_buttonround(lv_event_t * e);
lv_obj_t * ui_button_round;
lv_obj_t * ui_blood_presure_group;
lv_obj_t * ui_blood_oxygen;
lv_obj_t * ui_percent;
lv_obj_t * ui_pulse_group;
lv_obj_t * ui_arc_spo2;
lv_obj_t * ui_precent_70;
lv_obj_t * ui_precent_100;
lv_obj_t * ui_health_dots_group;
lv_obj_t * ui_dot7;
lv_obj_t * ui_dot6;
lv_obj_t * ui_dot5;
lv_obj_t * ui_dots_group1;
lv_obj_t * ui_dot18;
lv_obj_t * ui_dot19;
// CUSTOM VARIABLES


// SCREEN: ui_ecg
void ui_ecg_screen_init(void);
void ui_event_ecg(lv_event_t * e);
lv_obj_t * ui_ecg;
lv_obj_t * ui_Image1;
lv_obj_t * ui_bg1;
lv_obj_t * ui_title_group_2;
void ui_event_button_down6_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down6;
void ui_event_button_round1_buttonround(lv_event_t * e);
lv_obj_t * ui_button_round1;
lv_obj_t * ui_pulse_group1;
lv_obj_t * ui_health_dots_group1;
lv_obj_t * ui_dot9;
lv_obj_t * ui_dot8;
lv_obj_t * ui_dot10;
lv_obj_t * ui_chart_group;
lv_obj_t * ui_chart_ecg;
// CUSTOM VARIABLES


// SCREEN: ui_blood_pressure
void ui_blood_pressure_screen_init(void);
void ui_event_blood_pressure(lv_event_t * e);
lv_obj_t * ui_blood_pressure;
lv_obj_t * ui_bg2;
lv_obj_t * ui_Image3;
lv_obj_t * ui_title_group_3;
void ui_event_button_down7_buttondown(lv_event_t * e);
lv_obj_t * ui_button_down7;
void ui_event_button_round2_buttonround(lv_event_t * e);
lv_obj_t * ui_button_round2;
lv_obj_t * ui_blood_presure_group1;
lv_obj_t * ui_sys_group;
lv_obj_t * ui_sys;
lv_obj_t * ui_mmhg1;
lv_obj_t * ui_blood_oxygen1;
lv_obj_t * ui_pulse_group2;
lv_obj_t * ui_blood_presure_group2;
lv_obj_t * ui_dia_group;
lv_obj_t * ui_dia;
lv_obj_t * ui_mmhg2;
lv_obj_t * ui_blood_oxygen2;
lv_obj_t * ui_health_dots_group2;
lv_obj_t * ui_dot12;
lv_obj_t * ui_dot13;
lv_obj_t * ui_dot11;
// CUSTOM VARIABLES


// SCREEN: ui_measuing
void ui_measuing_screen_init(void);
void ui_event_measuing(lv_event_t * e);
lv_obj_t * ui_measuing;
lv_obj_t * ui_bg7;
lv_obj_t * ui_pulse_group3;
lv_obj_t * ui_measuring;
lv_obj_t * ui_Spinner2;
lv_obj_t * ui_blood_group;
lv_obj_t * ui_blood1;
lv_obj_t * ui_blood_fill;
lv_obj_t * ui_blood2;
void ui_event_x_button(lv_event_t * e);
lv_obj_t * ui_x_button;
lv_obj_t * ui_x;
// CUSTOM VARIABLES

// EVENTS
void ui_event____initial_actions0(lv_event_t * e);
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS
const lv_img_dsc_t * ui_imgset_bg[3] = {&ui_img_bg1_png, &ui_img_bg2_png, &ui_img_bg3_png};
const lv_img_dsc_t * ui_imgset_btn_bg_[3] = {&ui_img_btn_bg_1_png, &ui_img_btn_bg_2_png, &ui_img_btn_bg_3_png};
const lv_img_dsc_t * ui_imgset_call[2] = {&ui_img_call1_png, &ui_img_call2_png};
const lv_img_dsc_t * ui_imgset_heart[1] = {&ui_img_heart2_png};
const lv_img_dsc_t * ui_imgset_s[9] = {&ui_img_s1_png, &ui_img_s2_png, &ui_img_s3_png, &ui_img_s4_png, &ui_img_s5_png, &ui_img_s6_png, &ui_img_s7_png, &ui_img_s8_png, &ui_img_s9_png};
const lv_img_dsc_t * ui_imgset_wave[2] = {&ui_img_wave1_png, &ui_img_wave2_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void sec_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 36000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 3600);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);

}
void min_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 1400);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);

}
void hour_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 300);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);

}
void left_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t * PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 300);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_1, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, true);
    lv_anim_start(&PropertyAnimation_1);

}
void right_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 150, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t * PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 300);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_1, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, true);
    lv_anim_start(&PropertyAnimation_1);

}
void opa_on_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}
void dots_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 250);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 250);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 250);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 500);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}
void top_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 400);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void cloud_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, 10);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 1000);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void blood2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 3000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 166);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}
void blood1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 2000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 166, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}
void heart_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 900);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_zoom);
    lv_anim_set_values(&PropertyAnimation_0, 120, 60);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_zoom);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_watch_digital(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_watch_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_analog_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_watch_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_analog_screen_init);
    }
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        left_Animation(ui_hour_group, 0);
        right_Animation(ui_label_min, 0);
        opa_on_Animation(ui_weather_group_1, 300);
        opa_on_Animation(ui_date_group, 500);
        opa_on_Animation(ui_weather_title_group_1, 400);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
}

void ui_event_button_top_buttontop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_call, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_call_screen_init);
    }
}

void ui_event_button_down_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_weather_1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_weather_1_screen_init);
    }
}

void ui_event_watch_analog(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        min_Animation(ui_min, 0);
        hour_Animation(ui_hour, 0);
        opa_on_Animation(ui_weather_group_5, 300);
        opa_on_Animation(ui_date_group2, 500);
        opa_on_Animation(ui_weather_title_group_2, 400);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
}

void ui_event_button_top1_buttontop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_call, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_call_screen_init);
    }
}

void ui_event_button_down1_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_weather_1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_weather_1_screen_init);
    }
}

void ui_event_call(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        top_Animation(ui_avatar, 0);
        opa_on_Animation(ui_avatar_label, 300);
        opa_on_Animation(ui_call_time, 400);
        opa_on_Animation(ui_mute, 500);
    }
}

void ui_event_button_down2_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}

void ui_event_volume_arc(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        _ui_arc_set_text_value(ui_volume_percent, target, "", "%");
    }
}

void ui_event_button_top2_buttontop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_analog, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_analog_screen_init);
    }
}

void ui_event_weather_1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        left_Animation(ui_label_degree, 0);
        right_Animation(ui_sun, 100);
        right_Animation(ui_clouds, 200);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_weather_2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_weather_2_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_weather_2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_weather_2_screen_init);
    }
}

void ui_event_button_down3_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}

void ui_event_weather_2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_weather_1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_weather_1_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_weather_1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_weather_1_screen_init);
    }
}

void ui_event_button_down4_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}

void ui_event_blood_oxy(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        top_Animation(ui_blood_presure_group, 0);
        opa_on_Animation(ui_arc_spo2, 100);
        opa_on_Animation(ui_pulse_group, 200);
        opa_on_Animation(ui_button_round, 300);
        opa_on_Animation(ui_blood_presure_group, 0);
        top_Animation(ui_title_group_1, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecg, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_ecg_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_pressure, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_pressure_screen_init);
    }
}

void ui_event_button_down5_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}

void ui_event_button_round_buttonround(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_measuing, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_measuing_screen_init);
    }
}

void ui_event_ecg(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        top_Animation(ui_chart_group, 0);
        opa_on_Animation(ui_pulse_group1, 100);
        opa_on_Animation(ui_button_round1, 200);
        opa_on_Animation(ui_chart_ecg, 0);
        top_Animation(ui_title_group_2, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_pressure, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_pressure_screen_init);
    }
}

void ui_event_button_down6_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}

void ui_event_button_round1_buttonround(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_measuing, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_measuing_screen_init);
    }
}

void ui_event_blood_pressure(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        top_Animation(ui_blood_presure_group1, 0);
        opa_on_Animation(ui_blood_presure_group1, 0);
        top_Animation(ui_blood_presure_group2, 100);
        opa_on_Animation(ui_blood_presure_group2, 100);
        opa_on_Animation(ui_button_round2, 200);
        top_Animation(ui_title_group_3, 0);
        top_Animation(ui_pulse_group2, 100);
        opa_on_Animation(ui_pulse_group2, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ecg, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_ecg_screen_init);
    }
}

void ui_event_button_down7_buttondown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_watch_digital, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}

void ui_event_button_round2_buttonround(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_measuing, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_measuing_screen_init);
    }
}

void ui_event_measuing(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        top_Animation(ui_blood_group, 0);
        opa_on_Animation(ui_blood_group, 0);
        opa_on_Animation(ui_Spinner2, 300);
        opa_on_Animation(ui_pulse_group3, 200);
        opa_on_Animation(ui_measuring, 300);
        opa_on_Animation(ui_x_button, 300);
    }
}

void ui_event_x_button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_blood_oxy, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_blood_oxy_screen_init);
    }
}

void ui_event____initial_actions0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        sec_Animation(ui_sec_dot, 0);
        sec_Animation(ui_sec, 0);
        dots_Animation(ui_dots, 0);
        cloud_Animation(ui_clouds, 0);
        blood1_Animation(ui_blood1, 0);
        blood2_Animation(ui_blood2, 0);
        heart_Animation(ui_comp_get_child(ui_pulse_group3, UI_COMP_PULSEGROUP_HEART), 0);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_watch_digital_screen_init();
    ui_watch_analog_screen_init();
    ui_call_screen_init();
    ui_weather_1_screen_init();
    ui_weather_2_screen_init();
    ui_blood_oxy_screen_init();
    ui_ecg_screen_init();
    ui_blood_pressure_screen_init();
    ui_measuing_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui____initial_actions0, ui_event____initial_actions0, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui____initial_actions0);
    lv_disp_load_scr(ui_watch_digital);
}

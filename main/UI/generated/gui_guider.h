/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "lv_dclock.h"
#include "lv_analogclock.h"

typedef struct
{
  
	lv_obj_t *screen_logo;
	bool screen_logo_del;
	lv_obj_t *screen_logo_img_1;
	lv_obj_t *screen_logo_img_2;
	lv_obj_t *screen_time;
	bool screen_time_del;
	lv_obj_t *screen_time_bar_battery;
	lv_obj_t *screen_time_label_battery;
	lv_obj_t *screen_time_tabview_1;
	lv_obj_t *screen_time_tabview_1_tab_1;
	lv_obj_t *screen_time_tabview_1_tab_2;
	lv_obj_t *screen_time_tabview_1_tab_3;
	lv_obj_t *screen_time_tabview_1_tab_4;
	lv_obj_t *screen_time_cont_info;
	lv_obj_t *screen_time_label_touch;
	lv_obj_t *screen_time_label_charge;
	lv_obj_t *screen_time_label_accel;
	lv_obj_t *screen_time_label_gyro;
	lv_obj_t *screen_time_label_current;
	lv_obj_t *screen_time_cont_vibra;
	lv_obj_t *screen_time_slider_time;
	lv_obj_t *screen_time_slider_intensity;
	lv_obj_t *screen_time_label_time;
	lv_obj_t *screen_time_label_intensity;
	lv_obj_t *screen_time_cont_voice;
	lv_obj_t *screen_time_btn_record;
	lv_obj_t *screen_time_btn_record_label;
	lv_obj_t *screen_time_label_record;
	lv_obj_t *screen_time_label_play;
	lv_obj_t *screen_time_btn_play;
	lv_obj_t *screen_time_btn_play_label;
	lv_obj_t *screen_time_analog_clock_1;
	lv_obj_t *screen_info;
	bool screen_info_del;
	lv_obj_t *screen_info_bar_battery;
	lv_obj_t *screen_info_label_battery;
	lv_obj_t *screen_info_label_current;
	lv_obj_t *screen_info_label_gyro;
	lv_obj_t *screen_info_label_accel;
	lv_obj_t *screen_info_label_charge;
	lv_obj_t *screen_info_label_touc;
	lv_obj_t *screen_vibra;
	bool screen_vibra_del;
	lv_obj_t *screen_vibra_bar_battery;
	lv_obj_t *screen_vibra_label_battery;
	lv_obj_t *screen_vibra_slider_time;
	lv_obj_t *screen_vibra_slider_intnsity;
	lv_obj_t *screen_vibra_label_time;
	lv_obj_t *screen_vibra_label_intensity;
	lv_obj_t *screen_voice;
	bool screen_voice_del;
	lv_obj_t *screen_voice_bar_battery;
	lv_obj_t *screen_voice_label_battery;
	lv_obj_t *screen_voice_btn_record;
	lv_obj_t *screen_voice_btn_record_label;
	lv_obj_t *screen_voice_label_record;
	lv_obj_t *screen_voice_btn_play;
	lv_obj_t *screen_voice_btn_play_label;
	lv_obj_t *screen_img;
	bool screen_img_del;
	lv_obj_t *screen_img_img;
	lv_obj_t *screen_img_img_1;
	lv_obj_t *screen_img_img_2;
	lv_obj_t *screen_img_img_3;
	lv_obj_t *screen_img_img_4;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_logo(lv_ui *ui);
void setup_scr_screen_time(lv_ui *ui);
void setup_scr_screen_info(lv_ui *ui);
void setup_scr_screen_vibra(lv_ui *ui);
void setup_scr_screen_voice(lv_ui *ui);
void setup_scr_screen_img(lv_ui *ui);
LV_IMG_DECLARE(_StopWATCHUImodified_alpha_466x466);
LV_IMG_DECLARE(_StopWATCHUI1_alpha_466x466);

LV_IMG_DECLARE(_StopWATCHUI2modified_466x466);
LV_IMG_DECLARE(_img_clockwise_hour_alpha_18x98);
LV_IMG_DECLARE(_img_clockwise_min_alpha_18x157);
LV_IMG_DECLARE(_img_clockwise_sec_alpha_31x180);

LV_IMG_DECLARE(_StopWATCHUI2modified_466x466);

LV_IMG_DECLARE(_StopWATCHUI2modified_466x466);

LV_IMG_DECLARE(_StopWATCHUI2modified_466x466);
LV_IMG_DECLARE(_db1modified_alpha_466x466);
LV_IMG_DECLARE(_raianglemodified_alpha_50x20);
LV_IMG_DECLARE(_raianglemodified_alpha_50x20);
LV_IMG_DECLARE(_raianglemodified_alpha_50x20);
LV_IMG_DECLARE(_raianglemodified_alpha_50x20);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_Acme_Regular_22)


#ifdef __cplusplus
}
#endif
#endif

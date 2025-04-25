/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}
#endif


extern int screen_clock_digital_clock_s_hour_value;
extern int screen_clock_digital_clock_s_min_value;
extern int screen_clock_digital_clock_s_sec_value;
extern char screen_clock_digital_clock_s_meridiem[];

void screen_clock_digital_clock_s_timer(lv_timer_t *timer)
{
    clock_count_12(&screen_clock_digital_clock_s_hour_value, &screen_clock_digital_clock_s_min_value, &screen_clock_digital_clock_s_sec_value, screen_clock_digital_clock_s_meridiem);
    if (lv_obj_is_valid(guider_ui.screen_clock_digital_clock_s))
    {
        lv_dclock_set_text_fmt(guider_ui.screen_clock_digital_clock_s, "%d:%02d:%02d %s", screen_clock_digital_clock_s_hour_value, screen_clock_digital_clock_s_min_value, screen_clock_digital_clock_s_sec_value, screen_clock_digital_clock_s_meridiem);
    }
}
static lv_obj_t * screen_clock_datetext_date_calendar;

void screen_clock_datetext_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(screen_clock_datetext_date_calendar == NULL) {
            screen_clock_datetext_date_init_calendar(btn, s);
        }
    }
}

void screen_clock_datetext_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (screen_clock_datetext_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        screen_clock_datetext_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(screen_clock_datetext_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(screen_clock_datetext_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(screen_clock_datetext_date_calendar, highlighted_days, 1);
        lv_obj_align(screen_clock_datetext_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(screen_clock_datetext_date_calendar, screen_clock_datetext_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(screen_clock_datetext_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void screen_clock_datetext_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.screen_clock_datetext_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(screen_clock_datetext_date_calendar);
        screen_clock_datetext_date_calendar = NULL;
    }
}



extern int screen_clock_analog_clock_time_hour_value;
extern int screen_clock_analog_clock_time_min_value;
extern int screen_clock_analog_clock_time_sec_value;

extern uint16_t screen_clock_s_year;
extern uint8_t screen_clock_s_month;
extern uint8_t screen_clock_s_day;
static char screen_clock_datetext_date_text[16];

void screen_clock_analog_clock_time_timer(lv_timer_t *timer)
{
    // clock_count(&screen_clock_analog_clock_time_hour_value, &screen_clock_analog_clock_time_min_value, &screen_clock_analog_clock_time_sec_value);
    if (lv_obj_is_valid(guider_ui.screen_clock_analog_clock_time))
    {
        lv_analogclock_set_time(guider_ui.screen_clock_analog_clock_time, screen_clock_digital_clock_s_hour_value, screen_clock_digital_clock_s_min_value, screen_clock_digital_clock_s_sec_value);
    }
    // clock_count_12(&screen_clock_digital_clock_s_hour_value, &screen_clock_digital_clock_s_min_value, &screen_clock_digital_clock_s_sec_value, screen_clock_digital_clock_s_meridiem);
    if (lv_obj_is_valid(guider_ui.screen_clock_digital_clock_s))
    {
        lv_dclock_set_text_fmt(guider_ui.screen_clock_digital_clock_s, "%d:%02d:%02d %s", screen_clock_digital_clock_s_hour_value, screen_clock_digital_clock_s_min_value, screen_clock_digital_clock_s_sec_value, screen_clock_digital_clock_s_meridiem);
    }
    if (lv_obj_is_valid(guider_ui.screen_clock_datetext_date))
    {
        snprintf(screen_clock_datetext_date_text, sizeof(screen_clock_datetext_date_text), "%d/%d/%d", screen_clock_s_year, screen_clock_s_month, screen_clock_s_day);
        lv_label_set_text(guider_ui.screen_clock_datetext_date, screen_clock_datetext_date_text);
    }
}

extern int screen_ccw_digital_clock_s_hour_value;
extern int screen_ccw_digital_clock_s_min_value;
extern int screen_ccw_digital_clock_s_sec_value;
extern int screen_ccw_digital_clock_s_ms_value;

extern uint8_t ccw_clock_state;

// 秒表内部记时变量
static int stopwatch_hour = 0;
static int stopwatch_min = 0;
static int stopwatch_sec = 0;
static int stopwatch_ms = 0;
static uint64_t last_tick_time = 0;

void screen_ccw_digital_clock_s_timer(lv_timer_t *timer)
{
    // 根据当前秒表状态执行不同操作
    if (ccw_clock_state == 1) {
        // 运行状态：更新计时
        if (last_tick_time == 0) {
            // 第一次启动，初始化时间基准点
            last_tick_time = lv_tick_get();
        } else {
            // 计算经过的时间
            uint64_t current_time = lv_tick_get();
            uint64_t elapsed_ms = current_time - last_tick_time;
            last_tick_time = current_time;
            
            // 累加毫秒
            stopwatch_ms += elapsed_ms;
            
            // 处理进位
            if (stopwatch_ms >= 1000) {
                stopwatch_sec += stopwatch_ms / 1000;
                stopwatch_ms %= 1000;
                
                if (stopwatch_sec >= 60) {
                    stopwatch_min += stopwatch_sec / 60;
                    stopwatch_sec %= 60;
                    
                    if (stopwatch_min >= 60) {
                        stopwatch_hour += stopwatch_min / 60;
                        stopwatch_min %= 60;
                        
                        // 限制最大为24小时
                        if (stopwatch_hour >= 24) {
                            stopwatch_hour = 0;
                            stopwatch_min = 0;
                            stopwatch_sec = 0;
                            stopwatch_ms = 0;
                        }
                    }
                }
            }
        }
    } else if (ccw_clock_state == 2) {
        // 重置状态：清零并停止
        stopwatch_hour = 0;
        stopwatch_min = 0;
        stopwatch_sec = 0;
        stopwatch_ms = 0;
        last_tick_time = 0;
        ccw_clock_state = 0; // 重置后自动切换到停止状态
    } else {
        // 停止状态：不更新时间，只保持最后一次显示的值
        last_tick_time = 0; // 清除时间基准点
    }
    
    // 更新全局变量用于显示
    screen_ccw_digital_clock_s_hour_value = stopwatch_hour;
    screen_ccw_digital_clock_s_min_value = stopwatch_min;
    screen_ccw_digital_clock_s_sec_value = stopwatch_sec;
    screen_ccw_digital_clock_s_ms_value = stopwatch_ms;
    
    // 更新UI显示
    if (lv_obj_is_valid(guider_ui.screen_ccw_digital_clock_s))
    {
        lv_dclock_set_text_fmt(guider_ui.screen_ccw_digital_clock_s, "%d:%02d:%02d.%03d", 
            screen_ccw_digital_clock_s_hour_value, 
            screen_ccw_digital_clock_s_min_value, 
            screen_ccw_digital_clock_s_sec_value, 
            screen_ccw_digital_clock_s_ms_value);
    }
    if (lv_obj_is_valid(guider_ui.screen_ccw_img_1))
    {
        // 将当前秒和毫秒映射到-900到2700的角度范围
        // 一分钟 = 60秒 = 60000毫秒，映射到360度（3600个单位）
        int total_ms = stopwatch_sec * 1000 + stopwatch_ms;
        int angle = -900 + (total_ms * 3600) / 60000;
        
        // 确保角度在有效范围内
        if (angle > 2700) angle = 2700;
        if (angle < -900) angle = -900;
        
        lv_img_set_angle(guider_ui.screen_ccw_img_1, angle);
    }
}


extern int screen_ccw_analog_clock_ccw_hour_value;
extern int screen_ccw_analog_clock_ccw_min_value;
extern int screen_ccw_analog_clock_ccw_sec_value;

void screen_ccw_analog_clock_ccw_timer(lv_timer_t *timer)
{
    clock_count(&screen_ccw_analog_clock_ccw_hour_value, &screen_ccw_analog_clock_ccw_min_value, &screen_ccw_analog_clock_ccw_sec_value);
    if (lv_obj_is_valid(guider_ui.screen_ccw_analog_clock_ccw))
    {
        lv_analogclock_set_time(guider_ui.screen_ccw_analog_clock_ccw, screen_ccw_analog_clock_ccw_hour_value, screen_ccw_analog_clock_ccw_min_value, screen_ccw_analog_clock_ccw_sec_value);
    }
}


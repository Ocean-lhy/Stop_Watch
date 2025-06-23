#ifndef ES8311_DRIVER_H
#define ES8311_DRIVER_H

#include <stdint.h>
#include "i2c_bus.h"
#include "driver/i2s.h"
#include "es8311.h"
#include "pi4io_driver.h"

// ES8311设备地址
#define ES8311_ADDR 0x18

// I2S引脚定义
#define I2S_MCLK_PIN (gpio_num_t)18
#define I2S_BCLK_PIN (gpio_num_t)17
#define I2S_DADC_IN_PIN (gpio_num_t)16
#define I2S_LRCK_PIN (gpio_num_t)15
#define I2S_DDAC_OUT_PIN (gpio_num_t)14

// WAV文件类型定义
typedef enum {
    WAV_VOICE_START = 0,
    WAV_VOICE_BUTTON,
    WAV_VOICE_TOUCH,
    WAV_MAX
} wav_type_t;

// 初始化ES8311
void es8311_driver_init(i2c_bus_handle_t i2c_bus);

// 录音和播放任务
void record_and_play_task(void *arg);

// WAV播放任务
void wav_play_task(void *arg);

// WAV播放控制函数
void play_wav_file(wav_type_t wav_type);
void play_wav_file_from_isr(wav_type_t wav_type);
void stop_wav_playing(void);
bool is_wav_playing(void);

void start_recording(void);
void play_recording(void);
void stop_recording(void);
void stop_playing(void);
extern bool is_recording;
extern bool is_playing;
// 播放标志
extern uint8_t play_flag;

// WAV播放相关变量
extern bool is_wav_playing_flag;
extern wav_type_t current_wav_type;
extern TaskHandle_t wav_play_task_handle;

#endif // ES8311_DRIVER_H
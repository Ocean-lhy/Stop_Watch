#ifndef ES8311_DRIVER_H
#define ES8311_DRIVER_H

#include <stdint.h>
#include "i2c_bus.h"
#include "driver/i2s.h"
#include "es8311.h"

// ES8311设备地址
#define ES8311_ADDR 0x18

// I2S引脚定义
#define I2S_MCLK_PIN (gpio_num_t)18
#define I2S_BCLK_PIN (gpio_num_t)17
#define I2S_DADC_IN_PIN (gpio_num_t)16
#define I2S_LRCK_PIN (gpio_num_t)15
#define I2S_DDAC_OUT_PIN (gpio_num_t)14

// 初始化ES8311
void es8311_driver_init(i2c_bus_handle_t i2c_bus);

// 录音和播放任务
void record_and_play_task(void *arg);

void start_recording(void);
void play_recording(void);
void stop_recording(void);
void stop_playing(void);
extern bool is_recording;
extern bool is_playing;
// 播放标志
extern uint8_t play_flag;

#endif // ES8311_DRIVER_H
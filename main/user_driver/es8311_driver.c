#include "es8311_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "soc/soc_caps.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"
#include "esp_littlefs.h"
#include <string.h>
#include <errno.h>
#include <math.h>
#include "esp_timer.h"
#include "lcd_driver.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void record_and_play_task(void *arg);

static const char *TAG = "es8311_driver";
i2c_bus_device_handle_t es8311_dev = NULL;
uint8_t play_flag = 2;
bool is_recording = false;
bool is_playing = false;
bool is_loop_test = false;

#define RECORD_FILE "/littlefs/record.pcm"
#define RECORD_BUFFER_SIZE (1024 * 4)

extern const uint8_t test_pcm_start[] asm("_binary_test_pcm_start");
extern const uint8_t test_pcm_end[]   asm("_binary_test_pcm_end");

void es8311_driver_init(i2c_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "es8311_init");
    // i2c
    es8311_dev = i2c_bus_device_create(i2c_bus, ES8311_ADDR, 400000);
    if (es8311_dev == NULL)
    {
        ESP_LOGE(TAG, "es8311_dev i2c create failed");
    }
    else
    {
        ESP_LOGI(TAG, "es8311_dev i2c create success");
    }

    // i2s
    i2s_config_t i2s_cfg = {0};
    i2s_cfg.mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX);
    i2s_cfg.sample_rate          = 44100;
    i2s_cfg.bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT;
    i2s_cfg.channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT;
    i2s_cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    i2s_cfg.dma_buf_count        = 8;  // 增加DMA缓冲区数量
    i2s_cfg.dma_buf_len          = 1024; // 增加DMA缓冲区长度
    i2s_cfg.use_apll             = 1;
    i2s_cfg.intr_alloc_flags     = ESP_INTR_FLAG_LEVEL2;

    i2s_driver_install(I2S_NUM_0, &i2s_cfg, 0, NULL);
    i2s_pin_config_t i2s_pin_cfg = {0};
    i2s_pin_cfg.mck_io_num   = I2S_MCLK_PIN;
    i2s_pin_cfg.bck_io_num   = I2S_BCLK_PIN;
    i2s_pin_cfg.ws_io_num    = I2S_LRCK_PIN;
    i2s_pin_cfg.data_out_num = I2S_DDAC_OUT_PIN;
    i2s_pin_cfg.data_in_num  = I2S_DADC_IN_PIN;
    i2s_set_pin(I2S_NUM_0, &i2s_pin_cfg);
    // i2s_zero_dma_buffer(I2S_NUM_0);
    
    // es8311
    ESP_LOGI(TAG, "Start es8311 codec chip");
    audio_hal_codec_config_t es8311_cfg = {0};
    es8311_cfg.adc_input = AUDIO_HAL_ADC_INPUT_LINE1;
    es8311_cfg.dac_output = AUDIO_HAL_DAC_OUTPUT_ALL;
    es8311_cfg.codec_mode = AUDIO_HAL_CODEC_MODE_BOTH;
    es8311_cfg.i2s_iface.mode = AUDIO_HAL_MODE_SLAVE;
    es8311_cfg.i2s_iface.fmt = AUDIO_HAL_I2S_NORMAL;
    es8311_cfg.i2s_iface.samples = AUDIO_HAL_44K_SAMPLES;
    es8311_cfg.i2s_iface.bits = AUDIO_HAL_BIT_LENGTH_16BITS;
    ESP_LOGI(TAG, "init es8311");
    es8311_codec_init(&es8311_cfg);
    es8311_codec_config_i2s(es8311_cfg.codec_mode, &es8311_cfg.i2s_iface);
    es8311_codec_ctrl_state(AUDIO_HAL_CODEC_MODE_BOTH, AUDIO_HAL_CTRL_START);
    es8311_set_mic_gain(ES8311_MIC_GAIN_0DB);
    // 0xC0: -96 dB, 0x64: -50 dB, 0x00: 0 dB
    es8311_codec_set_voice_volume(0xBD);
    
    es8311_read_all();

    es8311_test(0);
    
    xTaskCreate(record_and_play_task, "record_and_play_task", 1024 * 8, NULL, 8, NULL);
}

void send_event(uint8_t key)
{
    if (example_lvgl_lock(-1))
    {
        lv_obj_t *current = lv_scr_act();
        lv_event_send(current, LV_EVENT_KEY, &key);
        example_lvgl_unlock();
    }
}

void record_and_play_task(void *arg)
{
    uint8_t *buffer = NULL;
    FILE *file = NULL;
    size_t bytes_read;
    size_t bytes_written;
    int64_t recording_start_time = 0;  // 记录录音开始时间
    size_t total_recorded_bytes = 0;   // 记录总录音字节数
    size_t total_played_bytes = 0;     // 记录总播放字节数
    
    while (1) 
    {
        // 处理录音
        if (is_recording) {
            if (file == NULL) {
                // 首次开始录音时打开文件
                file = fopen(RECORD_FILE, "wb");
                if (file == NULL) {
                    ESP_LOGE(TAG, "无法打开录音文件: %s", strerror(errno));
                    is_recording = false;
                    send_event(4);
                    continue;
                }
                
                // 分配缓冲区
                if (buffer == NULL) {
                    buffer = (uint8_t *)malloc(RECORD_BUFFER_SIZE);
                    if (buffer == NULL) {
                        ESP_LOGE(TAG, "无法分配录音缓冲区");
                        fclose(file);
                        file = NULL;
                        is_recording = false;
                        send_event(4);
                        continue;
                    }
                }
                
                // 记录录音开始时间
                recording_start_time = esp_timer_get_time();
                ESP_LOGI(TAG, "开始录音，最多持续10秒");
                ESP_LOGI(TAG, "录音配置: 采样率=44100Hz, 缓冲区大小=%d字节", RECORD_BUFFER_SIZE);
                total_recorded_bytes = 0; // 重置录音数据量统计
            }

            while (is_recording) 
            {
                // 检查是否已录音超过10秒
                if ((esp_timer_get_time() - recording_start_time) > 10000000) 
                { // 10秒 = 10,000,000微秒
                    ESP_LOGI(TAG, "录音已达到10秒上限，自动停止");
                    fclose(file);
                    file = NULL;
                    is_recording = false;
                    send_event(3);
                    continue;
                }
                
                if (i2s_read(I2S_NUM_0, buffer, RECORD_BUFFER_SIZE, &bytes_read, 50 / portTICK_PERIOD_MS) == ESP_OK) 
                {
                    if (bytes_read > 0) 
                    {
                        bytes_written = fwrite(buffer, 1, bytes_read, file);
                        if (bytes_written != bytes_read) 
                        {
                            ESP_LOGE(TAG, "写入文件失败: %s", strerror(errno));
                        }
                        else
                        {
                            total_recorded_bytes += bytes_written;
                        }
                    }
                }
                
                // 添加适当的延时，确保录音速度正确
                // 与播放使用相同的延时
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }

            if (file != NULL && !is_recording) 
            {
                // 录音停止，关闭文件
                fclose(file);
                file = NULL;
                ESP_LOGI(TAG, "录音已停止，总录音字节数: %d", total_recorded_bytes);
                is_recording = false;
                send_event(3);
            }
        } 
        
        // 处理播放
        if (is_playing) {
            if (file == NULL) {
                // 首次开始播放时打开文件
                file = fopen(RECORD_FILE, "rb");
                if (file == NULL) {
                    ESP_LOGE(TAG, "无法打开播放文件: %s", strerror(errno));
                    is_playing = false;
                    send_event(4);
                    continue;
                }
                
                // 分配缓冲区
                if (buffer == NULL) {
                    buffer = (uint8_t *)malloc(RECORD_BUFFER_SIZE);
                    if (buffer == NULL) {
                        ESP_LOGE(TAG, "无法分配播放缓冲区");
                        fclose(file);
                        file = NULL;
                        is_playing = false;
                        send_event(4);
                        continue;
                    }
                }
                
                ESP_LOGI(TAG, "开始播放");
                ESP_LOGI(TAG, "播放配置: 采样率=44100Hz, 缓冲区大小=%d字节", RECORD_BUFFER_SIZE);
                total_played_bytes = 0; // 重置播放数据量统计
            }
            
            while (is_playing) 
            {
                // 使用固定的块大小进行播放，确保播放速度正确
                bytes_read = fread(buffer, 1, RECORD_BUFFER_SIZE, file);
                if (bytes_read > 0 && is_playing) 
                { // 再次检查是否仍在播放
                    if (i2s_write(I2S_NUM_0, buffer, bytes_read, &bytes_written, 50 / portTICK_PERIOD_MS) != ESP_OK) 
                    {
                        ESP_LOGE(TAG, "I2S写入失败");
                    }
                    else
                    {
                        total_played_bytes += bytes_written;
                    }
                    
                    // 添加适当的延时，确保播放速度正确
                    // 使用固定的延时，避免计算错误
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                } 
                else 
                {
                    // 文件读取完毕或出错
                    if (feof(file)) {
                        ESP_LOGI(TAG, "播放完成，总播放字节数: %d", total_played_bytes);
                        fclose(file);
                        file = NULL;
                        is_playing = false;
                        send_event(4);
                    } 
                    else 
                    if (bytes_read <= 0 && !is_playing) 
                    {
                        // 播放被停止
                        fclose(file);
                        file = NULL;
                        is_playing = false;
                        send_event(4);
                        ESP_LOGI(TAG, "播放已停止");
                    } 
                    else
                    {
                        ESP_LOGE(TAG, "读取文件错误: %s", strerror(errno));
                    }
                }
            }

            if (file != NULL && !is_playing) 
            {
                // 播放停止，关闭文件
                fclose(file);
                file = NULL;
                ESP_LOGI(TAG, "播放已停止");
                send_event(4);
            }
        } 
        
        // 如果既不录音也不播放，释放缓冲区
        if (!is_recording && !is_playing && buffer != NULL) 
        {
            free(buffer);
            buffer = NULL;
        }
        
        // 减少延时，更快地响应停止命令
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void start_recording(void)
{
    if (is_recording) {
        ESP_LOGI(TAG, "已经在录音中");
        return;
    }
    
    is_recording = true;
    is_playing = false;
}

void play_recording(void)
{
    if (is_playing) 
    {
        ESP_LOGI(TAG, "已经在播放中");
        return;
    }
    
    is_playing = true;
    is_recording = false;
}

void stop_recording(void)
{
    is_recording = false;
}

void stop_playing(void)
{
    is_playing = false;
}

void play_demo_audio(void)
{
    if (is_playing) 
    {
        ESP_LOGI(TAG, "已经在播放中");
        return;
    }
    
    // 检查是否有内置的示例音频
    size_t demo_audio_size = test_pcm_end - test_pcm_start;
    if (demo_audio_size == 0) {
        ESP_LOGW(TAG, "没有内置示例音频，生成测试音频");
        // 创建任务来生成和播放测试音频
        xTaskCreate(generate_and_play_test_audio_task, "test_audio_task", 1024 * 4, NULL, 8, NULL);
        return;
    }
    
    ESP_LOGI(TAG, "开始播放示例音频，大小: %d 字节", demo_audio_size);
    
    // 设置播放标志
    is_playing = true;
    is_recording = false;
    
    // 创建任务来播放示例音频
    xTaskCreate(play_demo_audio_task, "play_demo_audio_task", 1024 * 4, NULL, 8, NULL);
}

void play_demo_audio_task(void *arg)
{
    size_t bytes_written;
    size_t chunk_size = RECORD_BUFFER_SIZE;
    size_t total_bytes_played = 0;
    size_t demo_audio_size = test_pcm_end - test_pcm_start;
    
    ESP_LOGI(TAG, "示例音频播放任务开始");
    
    while (is_playing && total_bytes_played < demo_audio_size) 
    {
        // 计算本次要播放的数据大小
        size_t remaining_bytes = demo_audio_size - total_bytes_played;
        size_t current_chunk_size = (remaining_bytes < chunk_size) ? remaining_bytes : chunk_size;
        
        // 播放当前块的数据
        if (i2s_write(I2S_NUM_0, (const char*)test_pcm_start + total_bytes_played, current_chunk_size, &bytes_written, 50 / portTICK_PERIOD_MS) != ESP_OK) 
        {
            ESP_LOGE(TAG, "I2S写入失败");
            break;
        }
        
        total_bytes_played += bytes_written;
        
        // 减少延时以提高播放流畅度
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    
    if (total_bytes_played >= demo_audio_size) {
        ESP_LOGI(TAG, "示例音频播放完成");
    } else {
        ESP_LOGI(TAG, "示例音频播放被停止");
    }
    
    // 播放完成，重置标志
    is_playing = false;
    
    // 删除任务
    vTaskDelete(NULL);
}

void generate_and_play_test_audio_task(void *arg)
{
    // 生成一个简单的正弦波测试音频
    const int sample_rate = 44100;
    const int duration_ms = 3000; // 3秒
    const int frequency = 440; // 440Hz (A音)
    const int amplitude = 16384; // 16位音频的最大值的一半
    
    int total_samples = (sample_rate * duration_ms) / 1000;
    int16_t *audio_buffer = malloc(RECORD_BUFFER_SIZE);
    
    if (audio_buffer == NULL) {
        ESP_LOGE(TAG, "无法分配音频缓冲区");
        is_playing = false;
        vTaskDelete(NULL);
        return;
    }
    
    ESP_LOGI(TAG, "开始生成和播放测试音频");
    is_playing = true;
    is_recording = false;
    
    int sample_index = 0;
    while (is_playing && sample_index < total_samples) {
        // 生成当前块的音频数据
        int samples_in_chunk = 0;
        for (int i = 0; i < RECORD_BUFFER_SIZE / 2 && sample_index < total_samples; i++) {
            // 生成正弦波
            double t = (double)sample_index / sample_rate;
            int16_t sample = (int16_t)(amplitude * sin(2 * M_PI * frequency * t));
            audio_buffer[i] = sample;
            sample_index++;
            samples_in_chunk++;
        }
        
        if (samples_in_chunk > 0) {
            size_t bytes_written;
            size_t bytes_to_write = samples_in_chunk * 2; // 16位 = 2字节
            
            if (i2s_write(I2S_NUM_0, audio_buffer, bytes_to_write, &bytes_written, 50 / portTICK_PERIOD_MS) != ESP_OK) {
                ESP_LOGE(TAG, "I2S写入失败");
                break;
            }
        }
        
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    
    free(audio_buffer);
    
    if (sample_index >= total_samples) {
        ESP_LOGI(TAG, "测试音频播放完成");
    } else {
        ESP_LOGI(TAG, "测试音频播放被停止");
    }
    
    is_playing = false;
    vTaskDelete(NULL);
}
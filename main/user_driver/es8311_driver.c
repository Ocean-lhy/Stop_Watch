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
#include "py32_driver.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const char *TAG = "es8311_driver";
i2c_bus_device_handle_t es8311_dev = NULL;

#define RECORD_FILE "/littlefs/record.pcm"
#define RECORD_BUFFER_SIZE (1024 * 4)
#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_BITS_PER_SAMPLE 16
#define AUDIO_CHANNELS 2

// 音频测试控制标志
static volatile bool stop_audio_test = false;

extern const uint8_t test_pcm_start[] asm("_binary_test_pcm_start");
extern const uint8_t test_pcm_end[]   asm("_binary_test_pcm_end");

void es8311_driver_init(i2c_bus_handle_t i2c_bus)
{
    ESP_LOGI(TAG, "es8311_init");
    
    // i2c初始化
    es8311_dev = i2c_bus_device_create(i2c_bus, ES8311_ADDR, 100000);
    if (es8311_dev == NULL) {
        ESP_LOGE(TAG, "es8311_dev i2c create failed");
        return;
    }
    ESP_LOGI(TAG, "es8311_dev i2c create success");

    // i2s配置
    i2s_config_t i2s_cfg = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .use_apll = 1,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL2
    };
    
    esp_err_t ret = i2s_driver_install(I2S_NUM_0, &i2s_cfg, 0, NULL);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "i2s_driver_install failed: %s", esp_err_to_name(ret));
        return;
    }

    i2s_pin_config_t i2s_pin_cfg = {
        .mck_io_num = I2S_MCLK_PIN,
        .bck_io_num = I2S_BCLK_PIN,
        .ws_io_num = I2S_LRCK_PIN,
        .data_out_num = I2S_DDAC_OUT_PIN,
        .data_in_num = I2S_DADC_IN_PIN
    };
    i2s_set_pin(I2S_NUM_0, &i2s_pin_cfg);

    // es8311编解码器配置
    ESP_LOGI(TAG, "Start es8311 codec chip");
    audio_hal_codec_config_t es8311_cfg = {
        .adc_input = AUDIO_HAL_ADC_INPUT_LINE1,
        .dac_output = AUDIO_HAL_DAC_OUTPUT_ALL,
        .codec_mode = AUDIO_HAL_CODEC_MODE_BOTH,
        .i2s_iface = {
            .mode = AUDIO_HAL_MODE_SLAVE,
            .fmt = AUDIO_HAL_I2S_NORMAL,
            .samples = AUDIO_HAL_44K_SAMPLES,
            .bits = AUDIO_HAL_BIT_LENGTH_16BITS
        }
    };
    
    es8311_codec_init(&es8311_cfg);
    es8311_codec_config_i2s(es8311_cfg.codec_mode, &es8311_cfg.i2s_iface);
    es8311_codec_ctrl_state(AUDIO_HAL_CODEC_MODE_BOTH, AUDIO_HAL_CTRL_START);
    es8311_set_mic_gain(ES8311_MIC_GAIN_12DB);
    es8311_codec_set_voice_volume(0xA0);
    
    es8311_read_all();
    es8311_test(0);
    
    ESP_LOGI(TAG, "ES8311 initialization completed");
}

/**
 * 音频播放测试函数 - 播放内置音频或生成的测试音频
 * 该函数会一直播放直到手动停止
 */
void audio_play_test(void)
{
    ESP_LOGI(TAG, "=== 开始音频播放测试 ===");
    
    stop_audio_test = false;
    uint8_t *audio_buffer = malloc(RECORD_BUFFER_SIZE);
    if (audio_buffer == NULL) {
        ESP_LOGE(TAG, "无法分配音频缓冲区");
        return;
    }

    py32_speaker_enable();
    vTaskDelay(100 / portTICK_PERIOD_MS);

    // 检查是否有内置音频
    size_t demo_audio_size = test_pcm_end - test_pcm_start;

    size_t total_played = 0;

    if (demo_audio_size > 0) {
        // 播放内置音频
        ESP_LOGI(TAG, "播放内置音频，大小: %zu 字节", demo_audio_size);
        
        while (demo_audio_size > total_played) {
            
            // 循环播放内置音频
            while (!stop_audio_test && total_played < demo_audio_size) {
                size_t remaining = demo_audio_size - total_played;
                size_t chunk_size = (remaining < RECORD_BUFFER_SIZE) ? remaining : RECORD_BUFFER_SIZE;
                
                // 复制音频数据到缓冲区
                memcpy(audio_buffer, test_pcm_start + total_played, chunk_size);
                
                size_t bytes_written;
                esp_err_t ret = i2s_write(I2S_NUM_0, audio_buffer, chunk_size, &bytes_written, portMAX_DELAY);
                if (ret != ESP_OK) {
                    ESP_LOGE(TAG, "I2S写入失败: %s", esp_err_to_name(ret));
                    break;
                }
                
                total_played += bytes_written;
            }
        }
        // 清空I2S
        i2s_zero_dma_buffer(I2S_NUM_0);

    } else {
        // 生成并播放测试音频（440Hz正弦波）
        ESP_LOGI(TAG, "生成440Hz测试音频");
        
        const int amplitude = 8192; // 降低音量
        const int frequency = 440;
        int sample_count = 0;
        
        while (!stop_audio_test) {
            // 生成一个缓冲区的音频数据
            int16_t *samples = (int16_t *)audio_buffer;
            int samples_per_buffer = RECORD_BUFFER_SIZE / (sizeof(int16_t) * AUDIO_CHANNELS);
            
            for (int i = 0; i < samples_per_buffer && !stop_audio_test; i++) {
                double t = (double)sample_count / AUDIO_SAMPLE_RATE;
                int16_t sample = (int16_t)(amplitude * sin(2 * M_PI * frequency * t));
                
                // 立体声：左右声道相同
                samples[i * 2] = sample;     // 左声道
                samples[i * 2 + 1] = sample; // 右声道
                sample_count++;
            }
            
            size_t bytes_written;
            esp_err_t ret = i2s_write(I2S_NUM_0, audio_buffer, RECORD_BUFFER_SIZE, &bytes_written, portMAX_DELAY);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "I2S写入失败: %s", esp_err_to_name(ret));
                break;
            }
        }
    }
    
    free(audio_buffer);
    py32_speaker_disable();
    ESP_LOGI(TAG, "=== 音频播放测试结束 ===");
}

/**
 * 录音并播放测试函数
 * 先录音指定时间，然后播放录音内容，只执行一次
 */
void audio_record_and_play_test(void)
{
    ESP_LOGI(TAG, "=== 开始录音并播放测试 ===");
    
    stop_audio_test = false;
    uint8_t *audio_buffer = malloc(RECORD_BUFFER_SIZE);
    if (audio_buffer == NULL) {
        ESP_LOGE(TAG, "无法分配音频缓冲区");
        return;
    }

    FILE *record_file = NULL;
    size_t total_recorded = 0;
    const size_t max_record_time_us = 5000000; // 5秒录音时间
    
    // === 录音阶段 ===
    ESP_LOGI(TAG, "开始录音 (5秒)...");
    
    record_file = fopen(RECORD_FILE, "wb");
    if (record_file == NULL) {
        ESP_LOGE(TAG, "无法创建录音文件: %s", strerror(errno));
        free(audio_buffer);
        return;
    }
    
    int64_t record_start_time = esp_timer_get_time();
    total_recorded = 0;
    
    while (!stop_audio_test && (esp_timer_get_time() - record_start_time) < max_record_time_us) {
        size_t bytes_read;
        esp_err_t ret = i2s_read(I2S_NUM_0, audio_buffer, RECORD_BUFFER_SIZE, &bytes_read, 100 / portTICK_PERIOD_MS);
        
        if (ret == ESP_OK && bytes_read > 0) {
            size_t bytes_written = fwrite(audio_buffer, 1, bytes_read, record_file);
            if (bytes_written != bytes_read) {
                ESP_LOGE(TAG, "写入文件失败: %s", strerror(errno));
                break;
            }
            total_recorded += bytes_written;
        }
    }
    
    fclose(record_file);
    record_file = NULL;
    
    ESP_LOGI(TAG, "录音完成，总字节数: %zu", total_recorded);

    py32_speaker_enable();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    // === 播放阶段 ===
    ESP_LOGI(TAG, "开始播放录音...");
    
    record_file = fopen(RECORD_FILE, "rb");
    if (record_file == NULL) {
        ESP_LOGE(TAG, "无法打开录音文件: %s", strerror(errno));
        free(audio_buffer);
        py32_speaker_disable();
        return;
    }
    
    size_t total_played = 0;
    while (!stop_audio_test && total_played < total_recorded) {
        size_t bytes_read = fread(audio_buffer, 1, RECORD_BUFFER_SIZE, record_file);
        if (bytes_read == 0) {
            if (feof(record_file)) {
                ESP_LOGI(TAG, "播放完成");
                break;
            } else {
                ESP_LOGE(TAG, "读取文件错误: %s", strerror(errno));
                break;
            }
        }
        
        size_t bytes_written;
        esp_err_t ret = i2s_write(I2S_NUM_0, audio_buffer, bytes_read, &bytes_written, portMAX_DELAY);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "I2S写入失败: %s", esp_err_to_name(ret));
            break;
        }
        
        total_played += bytes_written;
    }
    
    fclose(record_file);
    record_file = NULL;

    // 清空I2S
    i2s_zero_dma_buffer(I2S_NUM_0);
    
    ESP_LOGI(TAG, "播放完成，总播放字节数: %zu", total_played);
    
    free(audio_buffer);
    ESP_LOGI(TAG, "=== 录音并播放测试结束 ===");
    py32_speaker_disable();
}

# BMI270-Sensor-API 目录下的C文件
file(GLOB BMI_SRCS BMI270-Sensor-API/*.c)

file(GLOB UI_SRCS 
    UI/*.c 
    UI/components/*.c 
    UI/screens/*.c
    UI/images/*.c
    UI/fonts/*.c
)

file(GLOB AUDIO_SRCS es8311/*.c)

idf_component_register(
                    SRCS "main.cpp" "i2c_bus.c" "ir_nec_encoder.c" "ir_test.c" "mesh_stick_pink.c" "mesh_stick_green.c" ${BMI_SRCS} ${UI_SRCS} ${AUDIO_SRCS}
                    INCLUDE_DIRS "."  "BMI270-Sensor-API" "UI" "es8311"
                    REQUIRES driver nvs_flash esp_codec_dev spi_flash esp_lcd_touch esp_lcd_co5300 esp_lcd_touch_cst9217
                    EMBED_TXTFILES "test.pcm")

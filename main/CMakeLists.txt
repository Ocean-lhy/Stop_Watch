# BMI270-Sensor-API 目录下的C文件
file(GLOB BMI_SRCS BMI270-Sensor-API/*.c)

file(GLOB UI_SRCS 
    UI/*.c 
    UI/custom/*.c
    UI/generated/*.c
    UI/generated/guider_customer_fonts/*.c
    UI/generated/guider_fonts/*.c
    UI/generated/images/*.c
)

file(GLOB USER_DRIVER_SRCS user_driver/*.c)

set(include_dirs 
    UI/custom 
    UI/generated 
    UI/generated/guider_customer_fonts
    UI/generated/guider_fonts
    UI/generated/images
    )

file(GLOB AUDIO_SRCS es8311/*.c)

idf_component_register(
    SRCS 
        "main.cpp"
        "i2c_bus.c"
        ${USER_DRIVER_SRCS}
        ${BMI_SRCS}
        ${UI_SRCS}
        ${AUDIO_SRCS}
    INCLUDE_DIRS 
        "."
        ${include_dirs}
        "BMI270-Sensor-API"
        "UI"
        "es8311"
        "user_driver"
    REQUIRES 
        driver 
        nvs_flash 
        esp_codec_dev 
        spi_flash 
        esp_lcd_touch 
        esp_lcd_co5300 
        esp_lcd_touch_cst9217
    # EMBED_TXTFILES "test.pcm"
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_LVGL_H_INCLUDE_SIMPLE=1)


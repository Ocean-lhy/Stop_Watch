# BMI270-Sensor-API 目录下的C文件
file(GLOB BMI_SRCS BMI270-Sensor-API/*.c)

idf_component_register(
                    SRCS 
                        "main.cpp" "i2c_bus.c" "ir_nec_encoder.c" "ir_test.c" "mesh_stick_pink.c" "mesh_stick_green.c" ${BMI_SRCS}
                    INCLUDE_DIRS
                        ""  "BMI270-Sensor-API")

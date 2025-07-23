
idf_component_register(SRCS m5_ic_aw32001.cpp m5_ic_aw32001_regset.cpp
                    INCLUDE_DIRS "."
                    REQUIRES i2c_bus
                    REQUIRES driver
                    )

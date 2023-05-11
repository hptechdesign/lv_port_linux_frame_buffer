cmake_minimum_required(VERSION 3.12.4)

add_library(widgets
				bar_waterTemp.c
				meter_airPressure.c
				meter_fuelPressure.c
				meter_oilPressure.c
				meter_rpm.c)
target_include_directories(widgets PRIVATE .)


cmake_minimum_required(VERSION 3.12.4)


add_executable(${PROJECT_NAME} 
				main.c 
				mouse_cursor_icon.c 
				bar_waterTemp.c
				meter_airPressure.c
				meter_fuelPressure.c
				meter_oilPressure.c
				meter_rpm.c)
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::drivers)
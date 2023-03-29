cmake_minimum_required(VERSION 3.12.4)

# MSYS2 packages
# First open MSYS2 terminal and install:
# pacman -S mingw-w64-x86_64-SDL2

# Then the following should be found by cmake:

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})



add_executable(${PROJECT_NAME} 
				main.c 
				serial.c
				mouse_cursor_icon.c 
				bar_waterTemp.c
				meter_airPressure.c
				meter_fuelPressure.c
				meter_oilPressure.c
				meter_rpm.c)

target_link_libraries(${PROJECT_NAME} 
							PRIVATE 	lvgl 
										lvgl::drivers
										#${SDL2_LIBRARIES}
										rs232)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED 17)
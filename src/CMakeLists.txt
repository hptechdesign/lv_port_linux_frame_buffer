cmake_minimum_required(VERSION 3.12.4)

if(${TARGET_PLATFORM} STREQUAL "win")
	# MSYS2 package:
	# If not installed, first open MSYS2 terminal and install:
	# pacman -S mingw-w64-x86_64-SDL2
	# Then the following should be found by cmake:
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})
	set(ecu_libs 		lvgl 
						lvgl::drivers
						${SDL2_LIBRARIES} #order is important here
						rs232
						widgets
	)

else() # RPi_ecu_build
	set(ecu_libs 		lvgl 
						lvgl::drivers 
						rs232
						widgets
	)

endif()

add_executable(${PROJECT_NAME} 
				main_display.c 
				serial.c
				sensor.c
				mouse_cursor_icon.c)

add_subdirectory(widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE ${ecu_libs})

if(${TARGET_PLATFORM} STREQUAL "win")
	# Create ecu_sensor_spoofer if compiling for windows
	add_executable(ecu_sensor_spoofer 
								main_spoofer.c 
								serial.c
								sensor.c)					
	target_link_libraries(ecu_sensor_spoofer PRIVATE rs232)
endif()

# If a clean commit, then release binaries will be copied to a bin/release_xxx folder
include(copy_release_bins.cmake)
						
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED 17)

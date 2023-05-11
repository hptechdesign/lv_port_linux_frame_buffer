# src/CMakeLists.txt
#
# Create project target executables

cmake_minimum_required(VERSION 3.26)

if(${TARGET_PLATFORM} STREQUAL "win")

	# Set the Windows-specific ECU libraries
	set(ecu_libs 		lvgl::drivers
						lvgl::lvgl
						SDL2::SDL2main 
						SDL2::SDL2-static 
						rs232
						widgets
	)
include_directories(${sdl2_SOURCE_DIR}/include )
elseif(${TARGET_PLATFORM} STREQUAL "rpi")

	# Set the RPi-specific ECU libraries
	set(ecu_libs 		lvgl::drivers
						lvgl::lvgl 
						rs232
						widgets
	)

endif()
message("------------------------- \neculibs: ${ecu_libs}\n-----------------------------")
# Create the main ECU executable - both platforms
add_executable(${PROJECT_NAME} 
				main_display.c 
				serial.c
				sensor.c
				mouse_cursor_icon.c
				crc.c)

add_subdirectory(widgets)
target_link_libraries(widgets PRIVATE lvgl::lvgl)
target_include_directories(widgets PUBLIC lvgl::lvgl )

# Link the platform-specific libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${ecu_libs})
target_include_directories(${PROJECT_NAME} PUBLIC ${ecu_libs}  ${sdl2_SOURCE_DIR}/include)


if(${TARGET_PLATFORM} STREQUAL "win")

	# Create ecu_sensor_spoofer if compiling for windows
	add_executable(ecu_sensor_spoofer 
					main_spoofer.c 
					serial.c
					sensor.c
					crc.c)
	target_link_libraries(ecu_sensor_spoofer PRIVATE rs232)
endif()

# Copy release binaries to a bin/ sub-folder
include(copy_release_bins.cmake)
						
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED 17)

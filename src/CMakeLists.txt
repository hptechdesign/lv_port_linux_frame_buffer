# src/CMakeLists.txt
#
# Create project target executables

cmake_minimum_required(VERSION 3.26)

if(${TARGET_PLATFORM} STREQUAL "win")

	# Require MSYS2 SDL2 package:
	find_package(SDL2 REQUIRED)
	# If SDL2 is not installed, first open MSYS2 terminal and install:
	# pacman -S mingw-w64-x86_64-SDL2
	include_directories(${SDL2_INCLUDE_DIRS})
	
	# Set the Windows-specific ECU libraries
	set(ecu_libs 		lvgl 
						lvgl::drivers
						${SDL2_LIBRARIES} #order is important here
						rs232
						widgets
	)

elseif(${TARGET_PLATFORM} STREQUAL "rpi")

	# Set the RPi-specific ECU libraries
	set(ecu_libs 		lvgl 
						lvgl::drivers 
						rs232
						widgets
	)

endif()

# Create the main ECU executable - both platforms
add_executable(${PROJECT_NAME} 
				main_display.c 
				serial.c
				sensor.c
				mouse_cursor_icon.c)

add_subdirectory(widgets)
# Link the platform-specific libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${ecu_libs})

if(${TARGET_PLATFORM} STREQUAL "win")

	# Create ecu_sensor_spoofer if compiling for windows
	add_executable(ecu_sensor_spoofer 
								main_spoofer.c 
								serial.c
								sensor.c)					
	target_link_libraries(ecu_sensor_spoofer PRIVATE rs232)
endif()

# Copy release binaries to a bin/ sub-folder
include(copy_release_bins.cmake)
						
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED 17)

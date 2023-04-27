# CMakeLists.txt - top level
#
# Creates targets:
# 	rpi_ecu_display - for RPi (X-compile)
# 	win_ecu_display - for Windows (simulator)
# 	ecu_sensor_spoofer - for Windows (simulator)

cmake_minimum_required(VERSION 3.26)
# set policy for compatibility with LVGL
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
#include utitilty functions
include(utils.cmake)

# 'set_platform.cmake' contains a command to select 'win' or 'rpi' build.
# If it does not exist, it will be created - it is not kept under version control.
if(EXISTS "${CMAKE_SOURCE_DIR}/set_platform.cmake")
	message("Found set_platform.cmake - including...")
	message("Set a new TARGET_PLATFORM ('win'/'rpi') from within set_platform.cmake")
	include(set_platform.cmake)
else()
	# Create the missing file
	utils_createSetPlatformFile()
	message("Including set_platform.cmake")
	include(set_platform.cmake)
endif()

# Check that a valid TARGET_PLATFORM has been set from within 'set_platform.cmake'
if(DEFINED TARGET_PLATFORM)
	if(${TARGET_PLATFORM} STREQUAL "win")
		message("Building for Windows")
	elseif(${TARGET_PLATFORM} STREQUAL "rpi")
		message("Building for RPi on Raspbian")
	else()
		message(SEND_ERROR "Invalid TARGET_PLATFORM selected: '${TARGET_PLATFORM}'")
		message("Check TARGET_PLATFORM setting in 'set_platform.cmake'")
	endif()
endif()

# getVersionDetails() gets the project version details, in the format 
# (int) MAJ_VER, (int) MIN_VER, (int) COMMITS_PAST, (str) CLEAN_FLAG
# (str) TARGET_SUFFIX is also provided
getVersionDetails()
message("Target suffix is: " ${TARGET_SUFFIX})

# Set up platform-specific options
if(${TARGET_PLATFORM} STREQUAL "rpi")
	# RPi environment settings
	set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

	# Must convert windows environment variables to cmake internal format
	file(TO_CMAKE_PATH $ENV{RPIDEV_LOC} TOOLCHAIN_LOC)

	set(CMAKE_SYSTEM_NAME Linux)
	set(CMAKE_SYSTEM_PROCESSOR arm)

	set(CMAKE_SYSROOT ${TOOLCHAIN_LOC}/arm-linux-gnueabihf/sysroot)
	set(CMAKE_STAGING_PREFIX /home/rpi_ecu_display/stage)

	set(tools ${TOOLCHAIN_LOC})
	set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc.exe)
	set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++.exe)

	set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

	add_compile_definitions(RPI_ECU_DISPLAY=1)
	# PLATFORM_SUFFIX is used to name the binary release folders
	set(PLATFORM_SUFFIX armv8_rpi_raspbian_v)
	# Set the main ECU display executable taret name
	set(${TARGET_NAME} rpi_ecu_display_${TARGET_SUFFIX})
	# Set the project name
	project(rpi_ecu_display)
else()
	# Windows platform selected
	add_compile_definitions(WIN_ECU_DISPLAY=1)
	# PLATFORM_SUFFIX is used to name the binary release folders
	set(PLATFORM_SUFFIX x86_64_win64)
	# Set the main ECU display executable taret name
	set(${TARGET_NAME} win_ecu_display_${TARGET_SUFFIX})
	# Set the project name
	project(win_ecu_display)   
endif()

# Common compiler flags
add_compile_definitions(MAJ_VER=${MAJ_VER}
						MIN_VER=${MIN_VER}
						COMMITS_PAST=${COMMITS_PAST}
						CLEAN_FLAG="${CLEAN_FLAG}")

set(LV_LVGL_H_INCLUDE_SIMPLE ON)
set(LV_CONF_INCLUDE_SIMPLE ON)
set(GCC_COVERAGE_COMPILE_FLAGS 
	"-DLV_CONF_INCLUDE_SIMPLE"
	"-DLV_LVGL_H_INCLUDE_SIMPLE"
	)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

#target executables will be placed in bin/
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Specify path to own LVGL config header
set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h
    CACHE STRING "" FORCE)

set(FETCHCONTENT_QUIET FALSE)
# Fetch external dependencies
include(${CMAKE_CURRENT_SOURCE_DIR}/external/external.cmake)


add_subdirectory(src)
#include_directories(src)
#

target_compile_definitions(${PROJECT_NAME} PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)





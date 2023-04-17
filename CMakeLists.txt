# rpi_ecu_display - for RPi (X-compile) and Windows (Simulator)
cmake_minimum_required(VERSION 3.22)

include(set_platform.cmake)

if((NOT ${TARGET_PLATFORM} STREQUAL win) AND (NOT ${TARGET_PATFORM} STREQUAL rpi))
	message("Invalid build option. Please ensure there is a 'set_platform.cmake' file located in the top level project directory, which sets TARGET_PLATFORM as either 'win' or 'rpi'(and not both) - e.g. set(TARGET_PLATFORM \"win\")")
		message("Default build is win")
		set(TARGET_PLATFORM "win")
endif()


# Get the project version details, in the format 
# (int) MAJ_VER, (int) MIN_VER, (int) COMMITS_PAST, (str) CLEAN_FLAG
include(version.cmake)
message("Target suffix is: " ${TARGET_SUFFIX})

# Set up platform-specific options
if(${TARGET_PLATFORM} STREQUAL "rpi")
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

	set(${TARGET_NAME} rpi_ecu_display_${TARGET_SUFFIX})

	project(rpi_ecu_display)
else()
	# Windows platform selected
	add_compile_definitions(WIN_ECU_DISPLAY=1)

	set(${TARGET_NAME} win_ecu_display_${TARGET_SUFFIX})

	project(win_ecu_display)   
endif()
# Common flags
add_compile_definitions(MAJ_VER=${MAJ_VER}
						MIN_VER=${MIN_VER}
						COMMITS_PAST=${COMMITS_PAST}
						CLEAN_FLAG="${CLEAN_FLAG}")

set(GCC_COVERAGE_COMPILE_FLAGS 
	"-DLV_CONF_INCLUDE_SIMPLE"
	)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

#target executables will be placed in bin/
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(inc 
					inc/rs-232 
					src)

add_subdirectory(inc/lvgl)
add_subdirectory(inc/lv_drivers)
add_subdirectory(inc/rs-232)
add_subdirectory(src)

target_compile_definitions(${PROJECT_NAME} PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)





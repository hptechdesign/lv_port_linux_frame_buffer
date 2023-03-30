cmake_minimum_required(VERSION 3.12.4)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

#must convert windows environment variables to cmake internal format
#file(TO_CMAKE_PATH $ENV{RPIDEV_LOC} TOOLCHAIN_LOC)

#set(CMAKE_SYSTEM_NAME Linux)
#set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_SYSROOT ${TOOLCHAIN_LOC}/arm-linux-gnueabihf/sysroot)
#set(CMAKE_STAGING_PREFIX /home/rpi_ecu_display/stage)

#set(tools ${TOOLCHAIN_LOC})
#set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc.exe)
#set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++.exe)

#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


#add_compile_definitions(RPI_ECU_DISPLAY=1)


SET(GCC_COVERAGE_COMPILE_FLAGS "-DLV_CONF_INCLUDE_SIMPLE")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

project(sdl_ecu_display)

include_directories(inc inc/SPinGW src)

add_subdirectory(inc/lvgl)
add_subdirectory(inc/lv_drivers)
add_subdirectory(inc/rs-232)
add_subdirectory(src)

# this next command generates a compile_command.json file for intellisense to recognise
# the add_compile_definitions used. Note: used by Ninja and Makefile generators, check others
#target_compile_definitions(rpi_ecu_display PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)

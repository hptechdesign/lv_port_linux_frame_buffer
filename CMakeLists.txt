cmake_minimum_required(VERSION 3.12.4)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

#must convert windows environment variables to cmake internal format
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

project(lvgl_fb)

include_directories(.)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c)
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers)

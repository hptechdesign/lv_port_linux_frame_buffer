cmake_minimum_required(VERSION 3.1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(lvgl_fb)

include_directories(.)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c)
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers)

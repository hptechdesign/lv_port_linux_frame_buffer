cmake_minimum_required(VERSION 3.12.4)


add_executable(${PROJECT_NAME} main.c mouse_cursor_icon.c meter_rpm.c)
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers)
cmake_minimum_required(VERSION 3.26)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)
include(sdl2)
include(lv_drivers)
include(lvgl)

include(rs232)
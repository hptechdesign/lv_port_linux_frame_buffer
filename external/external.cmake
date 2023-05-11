cmake_minimum_required(VERSION 3.26)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)
if(${TARGET_PLATFORM} STREQUAL "win")
    include(sdl2)
endif()
include(lv_drivers)
include(lvgl)

include(rs232)
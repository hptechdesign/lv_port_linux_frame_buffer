cmake_minimum_required(VERSION 3.26)

# lvgl
include(fetchcontent)
FetchContent_Declare(lvgl
	GIT_REPOSITORY https://github.com/hptechdesign/lvgl.git
	GIT_TAG 8ab9e88e95e2e316864426a3e9bbc1b0d8c9b920)

FetchContent_MakeAvailable(lvgl)
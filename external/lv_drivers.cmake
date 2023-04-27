cmake_minimum_required(VERSION 3.26)

# lv_drivers
include(fetchcontent)
FetchContent_Declare(lv_drivers
	GIT_REPOSITORY https://github.com/hptechdesign/lv_drivers.git
	GIT_TAG 1413f5ebb6d21bc8ebb45448826dd7b4bbd3b7a3)

	
FetchContent_MakeAvailable(lv_drivers)
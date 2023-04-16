cmake_minimum_required(VERSION 3.12.4)

# Project options (select only one):
set(TARGET_PLATFORM "win") #= create build/win_ecu_display and build/ecu_sensor_spoofer executables
#set(TARGET_PLATFORM "rpi")  #= create build/rpi_ecu_display executable

# This section fetches the git version details and creates variables which can be used
# both within the apps and also as suffixes for the created binaries
execute_process(COMMAND git describe --tags --dirty --always
    OUTPUT_VARIABLE GIT_VERSION)
message("Project version number is: " ${GIT_VERSION})
# Do some clunky manipulations - expected format, if git is installed, is:
# 'v1.0-7-g133d586-dirty', 
# where 'dirty' is only found when source files have been modified since the previous
# commit
# generate lists from string
string(REPLACE "-" ";" VERSION_LIST ${GIT_VERSION})
list(LENGTH VERSION_LIST LISTLEN)
if (LISTLEN GREATER_EQUAL 3)
	list(GET VERSION_LIST 0 MAJ_MIN)
	string(REPLACE "." ";"  MAJ_MIN_LIST ${MAJ_MIN})
	list(GET MAJ_MIN_LIST 0 MAJ_VER)
	list(GET MAJ_MIN_LIST 1 MIN_VER)
	list(GET VERSION_LIST 1 COMMITS_PAST)
	list(GET VERSION_LIST 3 CLEAN)
	message("MAJ_VER:" ${MAJ_VER} "\nMIN_VER:" ${MIN_VER} "\nCOMMITS_PAST:" ${COMMITS_PAST} "\nCLEAN:" ${CLEAN})
	if (${CLEAN} MATCHES "^dirty")
		set(CLEAN_FLAG "+")
	endif()
	set(TARGET_SUFFIX ${MAJ_VER}.${MIN_VER}-${COMMITS_PAST}${CLEAN_FLAG})
else()
	#fallback in case git is not installed
	set(TARGET_SUFFIX "noVerDetails")
endif()
message("Target suffix is: " ${TARGET_SUFFIX})

# set up platform-specific options
if(${TARGET_PLATFORM} STREQUAL "rpi")
	set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

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

	add_compile_definitions(RPI_ECU_DISPLAY=1)

	set(${TARGET_NAME} rpi_ecu_display_${TARGET_SUFFIX})
	project(rpi_ecu_display)
else()
	# windows platform selected
	add_compile_definitions(WIN_ECU_DISPLAY=1)
	set(${TARGET_NAME} win_ecu_display_${TARGET_SUFFIX})
	project(win_ecu_display)   
endif()


SET(GCC_COVERAGE_COMPILE_FLAGS 
	"-DLV_CONF_INCLUDE_SIMPLE"
	)


SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_compile_definitions(MAJ_VER="${MAJ_VER}")
add_compile_definitions(MIN_VER="${MIN_VER}")
add_compile_definitions(COMMITS_PAST="${COMMITS_PAST}")
add_compile_definitions(CLEAN_FLAG="${CLEAN_FLAG}")


#target executables will be placed in bin/
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(inc inc/rs-232 src)

add_subdirectory(inc/lvgl)
add_subdirectory(inc/lv_drivers)
add_subdirectory(inc/rs-232)
add_subdirectory(src)


target_compile_definitions(${PROJECT_NAME} PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)





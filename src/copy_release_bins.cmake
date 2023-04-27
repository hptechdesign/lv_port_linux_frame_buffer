# copy_release_bins.cmake
#
# Create release folder and binaries from git repo version details

# Warn if repository is not clean
message("Checking clean flag status")
if(NOT CLEAN_FLAG STREQUAL "+")
	message("Build is clean")
else()
	message(WARNING "Build is dirty")
endif()

# Set release folder name
set(DEST ${CMAKE_SOURCE_DIR}/bin/ecu_display-${PLATFORM_SUFFIX}_${TARGET_SUFFIX})

# Copy the binaries and stamp with version details
if(${TARGET_PLATFORM} STREQUAL "win")
	# Copy main project binary to release folder
	add_custom_command(TARGET ${PROJECT_NAME} 
               POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:win_ecu_display> 
			   ${DEST}/${PROJECT_NAME}_${TARGET_SUFFIX}.exe)

	# Copy SDL2 dll to release folder (should not be needed after static linking update)
	#add_custom_command(TARGET ${PROJECT_NAME} 
	#POST_BUILD
	#COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> 
	#${DEST}
	#)

	# Copy ecu_sensor_spoofer binary to release folder
	add_custom_command(TARGET ecu_sensor_spoofer 
               POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ecu_sensor_spoofer> 
			   ${DEST}/ecu_sensor_spoofer_${TARGET_SUFFIX}.exe)
	message("Release binaries will be copied to " ${DEST})

else() # RPi_ecu_build

	# Copy main project binary to release folder
	add_custom_command(TARGET ${PROJECT_NAME} 
               POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> 
			   ${DEST}/${PROJECT_NAME}_${TARGET_SUFFIX})
	message("Release binaries will be copied to " ${DEST})
			
endif()
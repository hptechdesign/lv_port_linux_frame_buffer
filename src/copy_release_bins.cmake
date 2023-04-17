# If a clean commit, copy the binaries and stamp with version details
if(${TARGET_PLATFORM} STREQUAL "win")
	message("Checking clean flag status")
	if(NOT CLEAN_FLAG STREQUAL "+")
		message("Build is clean")
	else()
		message(WARNING "Build is dirty")
	endif()
	# Set release folder name
	set(DEST ${CMAKE_SOURCE_DIR}/bin/x86_64_win64_v${MAJ_VER}.${MIN_VER})
	# Copy main project binary to release folder
	add_custom_command(TARGET ${PROJECT_NAME} 
               POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:win_ecu_display> 
			   ${DEST}/${PROJECT_NAME}_${TARGET_SUFFIX}.exe)
	# Copy SDL2 dll to bin folder
	#add_custom_command(TARGET ${PROJECT_NAME} 
	#	POST_BUILD
	#	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> 
	#	$<TARGET_FILE_DIR:${PROJECT_NAME}>
	#	COMMAND_EXPAND_LISTS
	#)
	# Copy SDL2 dll to release folder
	add_custom_command(TARGET ${PROJECT_NAME} 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> 
	${DEST}
	)


	# Copy ecu_sensor_spoofer binary to release folder
	add_custom_command(TARGET ecu_sensor_spoofer 
               POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ecu_sensor_spoofer> 
			   ${DEST}/ecu_sensor_spoofer_${TARGET_SUFFIX}.exe)
	message("Release binaries will be copied to " ${DEST})


else() # RPi_ecu_build
	message("Checking clean flag status")
	if(NOT CLEAN_FLAG STREQUAL "+")
		message("Build is clean")
	else()
		message([WARNING] "Build is dirty")
	endif()
	# Set release folder name
	set(DEST ${CMAKE_SOURCE_DIR}/bin/armv8_rpi_raspbian_v${MAJ_VER}.${MIN_VER})
	# Copy main project binary to release folder
	add_custom_command(TARGET ${PROJECT_NAME} 
               POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> 
			   ${DEST}/${PROJECT_NAME}_${TARGET_SUFFIX})
	message("Release binaries will be copied to " ${DEST})
			
endif()
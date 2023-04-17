# If a clean commit, copy the binaries and stamp with version details
if(${TARGET_PLATFORM} STREQUAL "win")
	message("Checking clean flag status")
	if(NOT CLEAN_FLAG STREQUAL "+")
		message("Build is clean")
		# Set release folder name
		set(DEST ${CMAKE_SOURCE_DIR}/bin/x86_64_w64_v${MAJ_VER}.${MIN_VER})
		add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> 
				   ${DEST}/${PROJECT_NAME}_${TARGET_SUFFIX}.exe)
		add_custom_command(TARGET ecu_sensor_spoofer 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ecu_sensor_spoofer> 
				   ${DEST}/ecu_sensor_spoofer_${TARGET_SUFFIX}.exe)
		message("Release binaries will be copied to " ${DEST})
				
	else()
		 message("Build is not clean")
	endif()

else() # RPi_ecu_build
	message("Checking clean flag status")
	if(NOT CLEAN_FLAG STREQUAL "+")
		message("Build is clean")
		# Set release folder name
		set(DEST ${CMAKE_SOURCE_DIR}/bin/armv8_rpi_raspbian_v${MAJ_VER}.${MIN_VER})
		add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> 
				   ${DEST}/${PROJECT_NAME}_${TARGET_SUFFIX})
		message("Release binaries will be copied to " ${DEST})
				
	else()
	message("Build is not clean")
	endif()
	
endif()
# If a clean commit, copy the binaries and stamp with version details
if(${TARGET_PLATFORM} STREQUAL "win")
	
	if(${CLEAN_FLAG} STREQUAL "")
		add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> 
				   ${CMAKE_SOURCE_DIR}/bin/release_${MAJ_VER}_${MIN_VER}/${PROJECT_NAME}_${TARGET_SUFFIX}.exe)
		add_custom_command(TARGET ecu_sensor_spoofer 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ecu_sensor_spoofer> 
				   ${CMAKE_SOURCE_DIR}/bin/release_${MAJ_VER}_${MIN_VER}/ecu_sensor_spoofer_${TARGET_SUFFIX}.exe)
	endif()

else() # RPi_ecu_build

	if(${CLEAN_FLAG} STREQUAL "")

		add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> 
				   ${CMAKE_SOURCE_DIR}/bin/release_${MAJ_VER}_${MIN_VER}/${PROJECT_NAME}_${TARGET_SUFFIX})
	endif()
	
endif()
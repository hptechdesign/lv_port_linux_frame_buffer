# utils.cmake
#
# various utility functions for the rpi_ecu_display project


#
# create 'set_platform.cmake', which defines which platform to build for
function(utils_createSetPlatformFile)
	message("Creating 'set_platform.cmake' file in the top level project directory")
	message("Select TARGET_PLATFORM ('win' or 'rpi') from set_platform.cmake")
	message("Default build is win")
	# set the new file text
	string(CONCAT SET_PLATFORM_TEXT 
		"# This file is auto-generated and must not be under version control, so release\n" 
		"# binaries for any platform can be selected without dirtying the commit log\n"
		"\n# Project options (select only one):\n"
		"set(TARGET_PLATFORM \"win\") #= create win_ecu_display and ecu_sensor_spoofer executables\n"
		"#set(TARGET_PLATFORM \"rpi\")  #= create rpi_ecu_display executable\n"
		)
	# now create the missing file. It is already in.gitignore so won't be commited.
	file(WRITE ${CMAKE_SOURCE_DIR}/set_platform.cmake ${SET_PLATFORM_TEXT})
endfunction()

#
# get the project's git version details
function(getVersionDetails)
	# Fetch the git version details and create variables which can be used within the apps
	execute_process(COMMAND 
					git describe --long --tags --dirty --always  
					OUTPUT_VARIABLE GIT_VERSION)
	message("Project version number is: " ${GIT_VERSION})
	# Do some clunky manipulations - expected format, if git is installed, is:
	# 'v1.0-7-g133d586-dirty', 
	# where 'dirty' is only found when source files have been modified since the previous
	# commit
	
	# Generate lists from string
	string(REPLACE "-" ";" VERSION_LIST ${GIT_VERSION})		# e.g. 'v1.0;7;g133d586;dirty'
	list(LENGTH VERSION_LIST LISTLEN)						# LISTLEN = 3 if clean, 4 if dirty
	if (LISTLEN GREATER_EQUAL 3)							# Valid result is 3 or 4
		list(GET VERSION_LIST 0 MAJ_MIN)					# e.g. 'v1.0'
		string(REPLACE "." ";"  MAJ_MIN_LIST ${MAJ_MIN})	# e.g. 'v1;0'
		list(GET MAJ_MIN_LIST 0 MAJ_VER)		# e.g. 'v1'
		string(REPLACE "v" "" MAJ_VER ${MAJ_VER})			# e.g. '1'
		list(GET MAJ_MIN_LIST 1 MIN_VER)		# e.g. '0'
		list(GET VERSION_LIST 1 COMMITS_PAST)	# e.g. '7'
		list(GET VERSION_LIST 2 HASH)			# e.g. 'g133d586'
		if(LISTLEN EQUAL 4)									# LISTLEN = 4 if dirty 
			set(CLEAN_FLAG "+")
		else()
			set(CLEAN_FLAG "")
		endif()
		# Report found variables
		message("MAJ_VER:" ${MAJ_VER} "\nMIN_VER:" ${MIN_VER} "\nCOMMITS_PAST:" ${COMMITS_PAST} 
				"\nHASH:" ${HASH} "\nCLEAN:" ${CLEAN_FLAG})
		# Create suffix to append to the binary target filenames		
		set(TARGET_SUFFIX v${MAJ_VER}.${MIN_VER}-${COMMITS_PAST}${CLEAN_FLAG} PARENT_SCOPE)
	else()
		# Fallback in case git is not installed
		set(TARGET_SUFFIX "noVerDetails")
		set(MAJ_VER 0)
		set(MIN_VER 0)
		set(COMMITS_PAST 0)
		set(HASH "unknown")
		set(CLEAN_FLAG "+")
	endif()
	set(MAJ_VER ${MAJ_VER} PARENT_SCOPE)
	set(MIN_VER ${MIN_VER} PARENT_SCOPE)
	set(COMMITS_PAST ${COMMITS_PAST} PARENT_SCOPE)
	set(HASH ${HASH} PARENT_SCOPE)
	set(CLEAN_FLAG ${CLEAN_FLAG} PARENT_SCOPE)
endfunction()
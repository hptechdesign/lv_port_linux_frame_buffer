# Fetch the git version details and create variables which can be used within the apps
execute_process(COMMAND git describe --tags --dirty --always  OUTPUT_VARIABLE GIT_VERSION)
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
	list(GET MAJ_MIN_LIST 0 MAJ_VER)					# e.g. 'v1'
	string(REPLACE "v" "" MAJ_VER ${MAJ_VER})			# e.g. '1'
	list(GET MAJ_MIN_LIST 1 MIN_VER)					# e.g. '0'
	list(GET VERSION_LIST 1 COMMITS_PAST)				# e.g. '7'
	list(GET VERSION_LIST 2 HASH)						# e.g. 'g133d586'
	if(LISTLEN EQUAL 4)									# LISTLEN = 4 if dirty 
		set(CLEAN_FLAG "+")
	else()
		set(CLEAN_FLAG "")
	endif()
	# Report found variables
	message("MAJ_VER:" ${MAJ_VER} "\nMIN_VER:" ${MIN_VER} "\nCOMMITS_PAST:" ${COMMITS_PAST} 
			"\nHASH:" ${HASH} "\nCLEAN:" ${CLEAN_FLAG})
	# Create suffix to append to the binary target filenames		
	set(TARGET_SUFFIX v${MAJ_VER}.${MIN_VER}-${COMMITS_PAST}${CLEAN_FLAG})
else()
	# Fallback in case git is not installed
	set(TARGET_SUFFIX "noVerDetails")
	set(MAJ_VER 0)
	set(MIN_VER 0)
	set(COMMITS_PAST 0)
	set(HASH "NoDetail")
	set(CLEAN_FLAG "+")
endif()
cmake_minimum_required(VERSION 3.26)

# rs-232
FetchContent_Declare(rs232
	GIT_REPOSITORY https://github.com/hptechdesign/rs-232.git
	GIT_TAG 6659d7285c7268461e140614c8d62cb9d883a847)

FetchContent_MakeAvailable(rs232)
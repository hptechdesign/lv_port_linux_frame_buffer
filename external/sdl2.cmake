cmake_minimum_required(VERSION 3.26)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.26.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
set(SDL_TEST_ENABLED_BY_DEFAULT OFF)
set(BUILD_SHARED_LIBS FALSE)
FetchContent_MakeAvailable(SDL2)
file(COPY ${sdl2_SOURCE_DIR}/include/ DESTINATION ${sdl2_SOURCE_DIR}/../sdl2_include)
set(SDL_LIBRARIES ${SDL_LIBRARIES} SDL2::SDL2main SDL2::SDL2-static)

#define RPI_ECU_DISPLAY 1
#define SDL_ECU_DISPLAY 0

/****************** Drivers  *************/
#if ((RPI_ECU_DISPLAY + SDL_ECU_DISPLAY) != 1)
#error More than one build configuration is defined
#endif // ((RPI_ECU_DISPLAY + SDL_ECU_DISPLAY) != 1)

// RPI drivers
#if RPI_ECU_DISPLAY
#ifndef __linux__
#define __linux__
#endif
#include "init_rpi_env.h"
#include <unistd.h>

// Windows drivers
#elif SDL_ECU_DISPLAY 
// include the lvgl sdl header
#include "sdl/sdl.h"
// also include the SDL2 header
#include "sdl.h"
#include "Windows.h"
#endif  //RPI_ECU_DISPLAY elif SDL_ECU_DISPLAY

/****************** Application *************/
#define SMALL_METER_SIZE  200
#define LARGE_METER_SIZE  250
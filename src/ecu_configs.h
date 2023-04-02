
#define RPI_ECU_DISPLAY 0
#define SDL_ECU_DISPLAY 1

/****************** Drivers  *************/
#if ((RPI_ECU_DISPLAY + SDL_ECU_DISPLAY) != 1)
#error More than one build configuration is defined
#endif // ((RPI_ECU_DISPLAY + SDL_ECU_DISPLAY) != 1)


/****************** Application *************/
#define SMALL_METER_SIZE  200
#define LARGE_METER_SIZE  250
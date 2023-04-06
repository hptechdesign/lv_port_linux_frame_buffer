/**
 * @file ecu_configs.h
 * @author Huw Price
 * @brief Project level header
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#define ANIMATION_ENABLED 0

/****************** Drivers  *************/
#if((RPI_ECU_DISPLAY + WIN_ECU_DISPLAY) != 1)
#error More than one build configuration is defined
#endif // ((RPI_ECU_DISPLAY + WIN_ECU_DISPLAY) != 1)

/****************** Application *************/
#define SMALL_METER_SIZE 200
#define LARGE_METER_SIZE 250
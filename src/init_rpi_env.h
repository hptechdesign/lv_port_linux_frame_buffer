/**
 * @file init_rpi_env.h
 * @author Huw Price
 * @brief RPi specific headers
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INIT_RPI_ENV_H
#define INIT_RPI_ENV_H

#include "ecu_configs.h"

#if RPI_ECU_DISPLAY

#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#endif // RPI_ECU_DISPLAY
#endif // INIT_RPI_ENV_H
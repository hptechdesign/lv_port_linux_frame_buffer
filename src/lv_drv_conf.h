/**
 * @file lv_drv_conf.h
 * @author Huw Price
 * @brief Wrapper to redirect lvgl library calls according to selected build
 * platform
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "ecu_configs.h"

#if WIN_ECU_DISPLAY
#include "lv_drv_conf_sdl.h"
#else
#include "lv_drv_conf_rpi.h"
#endif // WIN_ECU_DISPLAY
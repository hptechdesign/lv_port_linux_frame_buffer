/**
 * @file arc_timing.h
 * @author Huw Price
 * @brief Arc display for injector timing
 * @date 2023-05-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ecu_configs.h"

#define ARC_TIMING_XPOS 300
#define ARC_TIMING_YPOS 300

#define ARC_TIMING_SIZEX 150
#define ARC_TIMING_SIZEY 150

#define ARC_TIMING_MIN -90
#define ARC_TIMING_MAX 120

#define ARC_TIMING_FONT &lv_font_montserrat_12
#define LABEL_ARC_TIMING_FONT &lv_font_montserrat_14

void arc_timing(void);

void arc_timingSetValue(uint16_t val);

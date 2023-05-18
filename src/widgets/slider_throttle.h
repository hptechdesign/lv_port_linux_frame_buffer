/**
 * @file slider_throttle.h
 * @author Huw Price
 * @brief Slider display for throttle position
 * @date 2023-05-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ecu_configs.h"

#define SLIDER_THROTTLE_XPOS 50
#define SLIDER_THROTTLE_YPOS 240

#define SLIDER_THROTTLE_SIZEX 15
#define SLIDER_THROTTLE_SIZEY 150

#define SLIDER_THROTTLE_MIN -90
#define SLIDER_THROTTLE_MAX 120

#define SLIDER_THROTTLE_FONT &lv_font_montserrat_12
#define LABEL_SLIDER_THROTTLE_FONT &lv_font_montserrat_14

void slider_throttle(void);

void slider_throttleSetValue(uint16_t val);

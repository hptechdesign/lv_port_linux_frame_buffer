/**
 * @file bar_waterTemp.h
 * @author Huw Price
 * @brief Bar display for water temperature
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ecu_configs.h"

#define BAR_WATERTEMP1_XPOS 325
#define BAR_WATERTEMP1_YPOS 275

#define BAR_WATERTEMP2_XPOS BAR_WATERTEMP1_XPOS
#define BAR_WATERTEMP2_YPOS BAR_WATERTEMP1_YPOS + 70

#define BAR_WATERTEMP_SIZEX 150
#define BAR_WATERTEMP_SIZEY 20

#define BAR_WATERTEMP_MIN 75
#define BAR_WATERTEMP_MAX 125

#define BAR_WATERTEMP_LOW_THRESH (BAR_WATERTEMP_MAX * 0.5)
#define BAR_WATERTEMP_HIGH_THRESH (BAR_WATERTEMP_MAX * 0.8)

#define BAR_WATERTEMP_FONT &lv_font_montserrat_12
#define LABEL_WATERTEMP_FONT &lv_font_montserrat_12

void bar_waterTemp1(void);
void bar_waterTemp2(void);

void bar_waterTempASetValue(uint16_t val);
void bar_waterTempBSetValue(uint16_t val);

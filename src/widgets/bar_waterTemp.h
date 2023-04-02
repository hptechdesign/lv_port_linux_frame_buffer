#include "ecu_configs.h"

#define BAR_WATERTEMP1_XPOS 30
#define BAR_WATERTEMP1_YPOS 340

#define BAR_WATERTEMP2_XPOS BAR_WATERTEMP1_XPOS
#define BAR_WATERTEMP2_YPOS BAR_WATERTEMP1_YPOS+70

#define BAR_WATERTEMP_SIZEX 250
#define BAR_WATERTEMP_SIZEY 30

#define BAR_WATERTEMP_MIN 0
#define BAR_WATERTEMP_MAX 3000

#define BAR_WATERTEMP_LOW_THRESH  (BAR_WATERTEMP_MAX*0.2)
#define BAR_WATERTEMP_HIGH_THRESH  (BAR_WATERTEMP_MAX*0.8)

#define BAR_WATERTEMP_FONT &lv_font_montserrat_12
#define LABEL_WATERTEMP_FONT &lv_font_montserrat_14



void bar_waterTemp1(void);
void bar_waterTemp2(void);

void bar_waterTempASetValue(uint16_t val);
void bar_waterTempBSetValue(uint16_t val);

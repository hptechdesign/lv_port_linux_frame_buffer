#include "ecu_configs.h"

#define METER_OILP_XPOS (50)
#define METER_OILP_YPOS 10
#define METER_OILP_SIZE SMALL_METER_SIZE

#define METER_OILP_LABEL_YOFFSET 50

#define METER_OILP_MIN 0
#define METER_OILP_MAX 3500

#define METER_OILP_LOW_THRESH  (METER_OILP_MAX*0.2)
#define METER_OILP_HIGH_THRESH  (METER_OILP_MAX*0.8)

#define METER_OILP_FONT &lv_font_montserrat_12
#define LABEL_OILP_FONT &lv_font_montserrat_14

void meter_oilPressure(void);
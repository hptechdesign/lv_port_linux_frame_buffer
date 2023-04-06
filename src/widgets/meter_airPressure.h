/**
 * @file meter_airPressure.h
 * @author Huw Price
 * @brief meter display for air pressure
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#define METER_AIRP_XPOS 300
#define METER_AIRP_YPOS 10
#define METER_AIRP_SIZE SMALL_METER_SIZE

#define METER_AIRP_LABEL_YOFFSET 50

#define METER_AIRP_MIN 0
#define METER_AIRP_MAX 1400

#define METER_AIRP_LOW_THRESH (METER_AIRP_MAX * 0.2)
#define METER_AIRP_HIGH_THRESH (METER_AIRP_MAX * 0.8)

#define METER_AIRP_FONT &lv_font_montserrat_12
#define LABEL_AIRP_FONT &lv_font_montserrat_14

void meter_airPressure(void);
void meter_airPressureSetValue(uint16_t value);
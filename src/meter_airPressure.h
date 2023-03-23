#define METER_AIRP_XPOS (520 - 200)
#define METER_AIRP_YPOS 10
#define METER_AIRP_SIZE 200

#define METER_AIRP_LABEL_YOFFSET 35

#define METER_AIRP_MIN 0
#define METER_AIRP_MAX 1400

#define METER_AIRP_LOW_THRESH  (METER_AIRP_MAX*0.2)
#define METER_AIRP_HIGH_THRESH  (METER_AIRP_MAX*0.8)

#define METER_AIRP_FONT &lv_font_montserrat_12


void meter_airPressure(void);
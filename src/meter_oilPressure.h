#define METER_OILP_XPOS (520+25)
#define METER_OILP_YPOS 10
#define METER_OILP_SIZE 200

#define METER_OILP_LABEL_YOFFSET 35

#define METER_OILP_MIN 0
#define METER_OILP_MAX 3000

#define METER_OILP_LOW_THRESH  (METER_OILP_MAX*0.2)
#define METER_OILP_HIGH_THRESH  (METER_OILP_MAX*0.8)

#define METER_OILP_FONT &lv_font_montserrat_12


void meter_oilPressure(void);
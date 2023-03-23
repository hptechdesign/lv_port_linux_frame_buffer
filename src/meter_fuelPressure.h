#define METER_FUELP_XPOS (520+25)
#define METER_FUELP_YPOS 10
#define METER_FUELP_SIZE 200

#define METER_FUELP_LABEL_YOFFSET 50

#define METER_FUELP_MIN 0
#define METER_FUELP_MAX 3000

#define METER_FUELP_LOW_THRESH  (METER_FUELP_MAX*0.2)
#define METER_FUELP_HIGH_THRESH  (METER_FUELP_MAX*0.8)

#define METER_FUELP_FONT &lv_font_montserrat_12
#define LABEL_FUELP_FONT &lv_font_montserrat_14


void meter_fuelPressure(void);
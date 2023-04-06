/**
 * @file meter_rpm.h
 * @author Huw Price
 * @brief Meter display for crank speed
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#define METER_RPM_XPOS 520
#define METER_RPM_YPOS 230
#define METER_RPM_SIZE 250

#define METER_RPM_MIN 0
#define METER_RPM_MAX 3000

#define METER_RPM_LOW_THRESH (METER_RPM_MAX * 0.2)
#define METER_RPM_HIGH_THRESH (METER_RPM_MAX * 0.8)

void meter_rpm(void);
void meter_rpmSetValue(uint16_t value);
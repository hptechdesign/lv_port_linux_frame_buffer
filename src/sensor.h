#ifndef _SENSOR_H
#define _SENSOR_H


#include <stdint.h>
#include "serial.h"







//ecu_sensor_spoofer:
void sensor_generateData(void);
//rpi_ecu_display:
void sensor_getData(void);

/* Public getters and setters*/

uint16_t sensor_getCrankRpm(void);
uint16_t sensor_getManifoldPressure(void);
uint16_t sensor_getTemperatureA(void);
uint16_t sensor_getTemperatureB(void);
uint16_t sensor_getOilPressure(void);
uint16_t sensor_getFuelPressure(void);

void sensor_setCrankRpm(uint16_t rpm);
void sensor_setManifoldPressure(uint16_t pressure_mbar);
void sensor_setTemperatureA(uint16_t temperature_degC);
void sensor_setTemperatureB(uint16_t temperature_degC);
void sensor_setOilPressure(uint16_t pressure_mbar);
void sensor_setFuelPressure(uint16_t pressure_bar);

#endif // _SENSOR_H
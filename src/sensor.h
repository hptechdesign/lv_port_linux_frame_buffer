/**
 * @file sensor.h
 * @author Huw Price
 * @brief
 * Sensor values can be spoofed by calling sensor_generateData().
 * Serial module uses the sensor_setXxx() commands to store the data in private
 * structs.
 * Application software uses the sensor_getXxxx() commands to retrieve
 * stored data.
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _SENSOR_H
#define _SENSOR_H

#include <stdint.h>

/* Typedefs - Consider hiding these implementation details, export a pointer
 * instead */
typedef struct control_data
{
    uint16_t fire_angle_deg;
    float injector_duty_ms; // consider other formats e.g fixed point
    float peak_hold_ms;     // consider other formats
} control_data_t;

typedef struct sensor_data
{
    uint16_t crank_rpm;
    uint16_t manifold_pressure_mbar;
    uint16_t temperature_a_degC;
    uint16_t temperature_b_degC;
    uint16_t oil_pressure_mbar;
    uint16_t fuel_pressure_bar;
} sensor_data_t;

/* Public function prototypes */
void sensor_fillBufWithCurrentData(char * buf);
// rpi_ecu_display:
void sensor_getData(void);
// application data getters
uint16_t sensor_getCrankRpm(void);
uint16_t sensor_getManifoldPressure(void);
uint16_t sensor_getTemperatureA(void);
uint16_t sensor_getTemperatureB(void);
uint16_t sensor_getOilPressure(void);
uint16_t sensor_getFuelPressure(void);

// ecu_sensor_spoofer:
void sensor_generateData(void);
// spoofer data setters
void sensor_setCrankRpm(uint16_t rpm);
void sensor_setManifoldPressure(uint16_t pressure_mbar);
void sensor_setTemperatureA(uint16_t temperature_degC);
void sensor_setTemperatureB(uint16_t temperature_degC);
void sensor_setOilPressure(uint16_t pressure_mbar);
void sensor_setFuelPressure(uint16_t pressure_bar);

#endif // _SENSOR_H
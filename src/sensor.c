/**
 * @file sensor.c
 * @brief Store or serve sensor data.
 *
 * Sensor values can be spoofed using sensor_generateData().
 * Serial module uses the sensor_setXxx() commands to store the data in private structs.
 * Application software uses the sensor_getXxxx() commands to retrieve stored data.
 */

/* Includes */
#include "sensor.h"
#include "serial.h"


#define SPOOF_CRANK_RPM_MEDIAN 2100
#define SPOOF_MANIFOLD_PRESSURE_MEDIAN 1000
#define SPOOF_TEMPERATURE_A_MEDIAN 98
#define SPOOF_TEMPERATURE_B_MEDIAN 99
#define SPOOF_OIL_PRESSURE_MEDIAN 2500
#define SPOOF_FUEL_PRESSURE_MEDIAN 2200


/* Private macros */
static control_data_t control_data =
{
	.fire_angle_deg= 0,
	.injector_duty_ms = 0,
	.peak_hold_ms =0
};
static sensor_data_t sensor_data =
{
	.crank_rpm = 0,
	.manifold_pressure_mbar = 0,
	.temperature_a_degC = 0,
	.temperature_b_degC = 0,
	.oil_pressure_mbar = 0,
	.fuel_pressure_bar = 0
};

/* Private function prototypes */
void sensor_generateData(void);
void sensor_getData(void);

/* Global variables */

/* Private functions */

// this function is used in the spoofer
void sensor_generateData(void)
{
	int r=0; 
	int temp=0;

	temp=sensor_getCrankRpm();
	r = rand() % (SPOOF_CRANK_RPM_MEDIAN/20);
	temp>SPOOF_CRANK_RPM_MEDIAN ? (temp-=r):(temp+=r);
	sensor_setCrankRpm(temp);

	temp=sensor_getManifoldPressure();
	r = rand() % (SPOOF_MANIFOLD_PRESSURE_MEDIAN/20);
	temp>SPOOF_MANIFOLD_PRESSURE_MEDIAN ? (temp-=r):(temp+=r);
	sensor_setManifoldPressure(temp);

	temp=sensor_getTemperatureA();
	r = rand() % (SPOOF_TEMPERATURE_A_MEDIAN/20);
	temp>SPOOF_TEMPERATURE_A_MEDIAN ? (temp-=r):(temp+=r);
	sensor_setTemperatureA(temp);

	sensor_getTemperatureB();
	r = rand() % (SPOOF_TEMPERATURE_B_MEDIAN/20);
	temp>SPOOF_TEMPERATURE_B_MEDIAN ? (temp-=r):(temp+=r);
	sensor_setTemperatureB(temp);

	sensor_getOilPressure();
	r = rand() % (SPOOF_OIL_PRESSURE_MEDIAN/20);
	temp>SPOOF_OIL_PRESSURE_MEDIAN ? (temp-=r):(temp+=r);
	sensor_setOilPressure(temp);

	sensor_getFuelPressure();
	r = rand() % (SPOOF_FUEL_PRESSURE_MEDIAN/20);
	temp>SPOOF_FUEL_PRESSURE_MEDIAN ? (temp-=r):(temp+=r);
	sensor_setFuelPressure(temp);
}

// this function is used in rpi_ecu_display
void sensor_getData(void)
{
	serial_getSensorData(&sensor_data);
}

/* Public functions */


/* Getters */

uint16_t sensor_getCrankRpm(void)
{
	return sensor_data.crank_rpm; 
}

uint16_t sensor_getManifoldPressure(void)
{
	return sensor_data.manifold_pressure_mbar; 
}

uint16_t sensor_getTemperatureA(void)
{
	return sensor_data.temperature_a_degC; 
}

uint16_t sensor_getTemperatureB(void)
{
	return sensor_data.temperature_b_degC; 
}

uint16_t sensor_getOilPressure(void)
{
	return sensor_data.oil_pressure_mbar; 
}

uint16_t sensor_getFuelPressure(void)
{
	return sensor_data.fuel_pressure_bar; 
}

/* Setters */

void sensor_setCrankRpm(uint16_t rpm)
{
	sensor_data.crank_rpm = rpm; 
}

void sensor_setManifoldPressure(uint16_t pressure_mbar)
{
	sensor_data.manifold_pressure_mbar=pressure_mbar; 
}

void sensor_setTemperatureA(uint16_t temperature_degC)
{
	sensor_data.temperature_a_degC=temperature_degC; 
}

void sensor_setTemperatureB(uint16_t temperature_degC)
{
	sensor_data.temperature_b_degC=temperature_degC; 
}

void sensor_setOilPressure(uint16_t pressure_mbar)
{
	sensor_data.oil_pressure_mbar=pressure_mbar; 
}

void sensor_setFuelPressure(uint16_t pressure_bar)
{
	sensor_data.fuel_pressure_bar=pressure_bar; 
}
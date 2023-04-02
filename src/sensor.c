#include "sensor.h"
#include "serial.h"

static control_data_t control_data =
{
	.fire_angle_deg= 15,
	.injector_duty_ms = 2.5,
	.peak_hold_ms =0.5
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


// this function is used in the spoofer
void sensor_generateData(void)
{
	//static for now - animate later
	sensor_setCrankRpm(1523);
	sensor_setManifoldPressure(934);
	sensor_setTemperatureA(95);
	sensor_setTemperatureB(87);
	sensor_setOilPressure(967);
	sensor_setFuelPressure(2745);

}

// this function is used in rpi_ecu_display
void sensor_getData(void)
{
	serial_getSensorData(&sensor_data);


}



/************************** GET SENSOR DATA *******************************************/

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

/************************** SET SENSOR DATA *******************************************/

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
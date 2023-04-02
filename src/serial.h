

#ifndef _SERIAL_H
#define _SERIAL_H

// Serial port
#include "rs232.h"
#include "sensor.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define CONTROL_FRAME_SIZE 11
#define SENSOR_FRAME_SIZE 33


/* Typedefs - Consider hiding these implementation details, export a pointer instead */
typedef struct control_data{
	uint16_t fire_angle_deg;
	float injector_duty_ms;			// consider other formats e.g fixed point
	float peak_hold_ms;				// consider other formats
}control_data_t;

typedef struct sensor_data{
	uint16_t crank_rpm;
	uint16_t manifold_pressure_mbar;
	uint16_t temperature_a_degC;
	uint16_t temperature_b_degC;
	uint16_t oil_pressure_mbar;
	uint16_t fuel_pressure_bar;
}sensor_data_t;

typedef enum {
	mode_startup,
	mode_select_port,
	mode_ascii,
	mode_stream_data
}serial_modes_t;



typedef  enum {			//  Units:
	fire_angle_delimit,		// N/A
	fire_angle_x10,			// Degrees
	fire_angle_x1,			// Degrees
	injector_duty_delimit,	// N/A
	injector_duty_x10,		// ms
	injector_duty_x1,		// ms
	peak_hold_delimit,		// N/A
	peak_hold_x1,			// ms
	peak_hold_x0_1,			// ms
	control_crc_byte1,				// N/A
	control_crc_byte2				// N/A
}control_data_byte_t;

typedef  enum {
	crank_rpm_delimit,
	crank_rpm_x1000,
	crank_rpm_x100,
	crank_rpm_x10,
	map_delimit,
	manifold_pressure_x1000,
	manifold_pressure_x100,
	manifold_pressure_x10,
	temperature_delimit_a,
	temperature_a_delimit,
	temperature_a_x100,
	temperature_a_x10,
	temperature_a_x1,
	temperature_delimit_b,
	temperature_b_delimit,
	temperature_b_x100,
	temperature_b_x10,
	temperature_b_x1,
	oil_pressure_delimit,
	oil_pressure_x1000,
	oil_pressure_x100,
	oil_pressure_x10,
	fuel_pressure_delimit,
	fuel_pressure_x1000,
	fuel_pressure_x100,
	fuel_pressure_x10,
	intake_airflow_delimit,
	intake_airflow_res1,
	intake_airflow_res2,
	intake_airflow_res3,
	intake_airflow_res4,
	sensor_crc_byte1,
	sensor_crc_byte2
}sensor_data_byte_t;


int serial_init(void);
void serial_puts(char* msg);
int serial_readAscii(void);
char* serial_getAsciiBuffer();

//rpi_ecu_display:
void serial_getSensorData(sensor_data_t* rx_buffer);
//ecu_sensor_spoofer:
void serial_sendSensorPacket(void);


#endif //_SERIAL_H
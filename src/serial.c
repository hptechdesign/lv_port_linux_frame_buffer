/**
 * @file serial.c
 * @author Huw Price
 * @brief Serial port functions for ecu_display and sensor_spoofer
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

/* Includes */
#include "ecu_configs.h"
#include "serial.h"
#include "sensor.h"
#include "crc.h"

/* Private macros and typedefs */
typedef unsigned char BYTE;

// Private functions
void serial_selectPort(void);
void serial_encapsulateSensorData(void);

// Static variables
static int winPort = -1;     // windows COM port is always equal to (port+1)
static int port    = -1;     /* port 0 = /dev/ttyS0 (COM1 on windows) */
static int bdrate  = 115200; /* 115200 baud */
static char mode[] = {'8', 'N', '1', 0};

// Buffers for the ascii functions
static char msg[64];
static char str[2][512];
static int t = 0, r = 0;
static char buf[4096];

// Buffers for control & sensor data packets
// this buffer used in ECU_SENSOR_SPOOFER -- ifdef them out at some point
static BYTE tx_sensor_data[SENSOR_FRAME_SIZE];
static BYTE rx_control_data[CONTROL_FRAME_SIZE];

// this buffer used in RPI_ECU_DISPLAY
static BYTE rx_sensor_data[SENSOR_FRAME_SIZE];
static BYTE tx_control_data[CONTROL_FRAME_SIZE];

static serial_modes_t serial_mode;

/**
 * @brief serial_sendSensorPacket
 *
 */

void serial_sendSensorPacket(void)
{
    if(serial_mode == mode_stream_data) {
        serial_encapsulateSensorData();
        // check this is actually polled tx - I've assumed it is
        RS232_SendBuf(port, &tx_sensor_data[0], SENSOR_FRAME_SIZE);
    }
}

/**
 * @brief serial_sendSensorPacket
 *
 * @param sensor_packet
 */

void serial_encapsulateSensorData(void)
{
    if(1) // consider checking if tx is in progress, e.g. if using interrupt
          // driven tx
    {
        tx_sensor_data[crank_rpm_delimit] = 'S';
        tx_sensor_data[crank_rpm_x1000]   = (BYTE)(sensor_getCrankRpm() / 1000);
        tx_sensor_data[crank_rpm_x100] =
            (BYTE)((sensor_getCrankRpm() % 1000) / 100);
        tx_sensor_data[crank_rpm_x10] =
            (BYTE)((sensor_getCrankRpm() % 100) / 10);
        tx_sensor_data[map_delimit] = 'M';
        tx_sensor_data[manifold_pressure_x1000] =
            (BYTE)(sensor_getManifoldPressure() / 1000);
        tx_sensor_data[manifold_pressure_x100] =
            (BYTE)((sensor_getManifoldPressure() % 1000) / 100);
        tx_sensor_data[manifold_pressure_x10] =
            (BYTE)((sensor_getManifoldPressure() % 100) / 10);
        tx_sensor_data[temperature_delimit_a] = 'T';
        tx_sensor_data[temperature_a_delimit] = 'A';
        tx_sensor_data[temperature_a_x100] =
            (BYTE)((sensor_getTemperatureA() % 1000) / 100);
        tx_sensor_data[temperature_a_x10] =
            (BYTE)((sensor_getTemperatureA() % 100) / 10);
        tx_sensor_data[temperature_a_x1] =
            (BYTE)((sensor_getTemperatureA() % 10));
        tx_sensor_data[temperature_delimit_b] = 'T';
        tx_sensor_data[temperature_b_delimit] = 'B';
        tx_sensor_data[temperature_b_x100] =
            (BYTE)((sensor_getTemperatureB() % 1000) / 100);
        tx_sensor_data[temperature_b_x10] =
            (BYTE)((sensor_getTemperatureB() % 100) / 10);
        tx_sensor_data[temperature_b_x1] =
            (BYTE)((sensor_getTemperatureB() % 10));
        tx_sensor_data[oil_pressure_delimit] = 'P';
        tx_sensor_data[oil_pressure_x1000] =
            (BYTE)(sensor_getOilPressure() / 1000);
        tx_sensor_data[oil_pressure_x100] =
            (BYTE)((sensor_getOilPressure() % 1000) / 100);
        tx_sensor_data[oil_pressure_x10] =
            (BYTE)((sensor_getOilPressure() % 100) / 10);
        tx_sensor_data[fuel_pressure_delimit] = 'D';
        tx_sensor_data[fuel_pressure_x1000] =
            (BYTE)(sensor_getFuelPressure() / 1000);
        tx_sensor_data[fuel_pressure_x100] =
            (BYTE)((sensor_getFuelPressure() % 1000) / 100);
        tx_sensor_data[fuel_pressure_x10] =
            (BYTE)((sensor_getFuelPressure() % 100) / 10);
        tx_sensor_data[intake_airflow_delimit] = 'F';
        tx_sensor_data[intake_airflow_res1]    = (BYTE)0;
        tx_sensor_data[intake_airflow_res2]    = (BYTE)0;
        tx_sensor_data[intake_airflow_res3]    = (BYTE)0;
        tx_sensor_data[intake_airflow_res4]    = (BYTE)0;
        tx_sensor_data[sensor_crc_byte1]       = (BYTE)0xBE;
        tx_sensor_data[sensor_crc_byte2]       = (BYTE)0xEF;
    }
}

/**
 * @brief serial_getControlData
 *
 * @return struct control_packet_t
 */

control_data_t serial_getControlData(void)
{
    if(serial_mode == mode_stream_data) {
        // sensor_decodeControlPacket();
        // read the next CONTROL_FRAME_SIZE bytes and return as control packet
    }
}

/**
 * @brief serial_getSensorData
 *
 * @return void
 */

void serial_getSensorData(sensor_data_t * rx_buffer)
{
    uint16_t crc_bytes = 0;

    if(serial_mode == mode_stream_data) {
        int rx_bytes = 0, timeout = 0;
        BYTE byteBuf = '0';
        while(rx_bytes < SENSOR_FRAME_SIZE && timeout < 0xFFFFF) {
            // order is important here, else we'd drop the second byte after
            // identifying the first delimiter First finish processing any part
            // received buffers
            if(rx_bytes > 0) {
                rx_bytes += RS232_PollComport(port, &rx_sensor_data[rx_bytes],
                                              (SENSOR_FRAME_SIZE - rx_bytes));
            }
            // then look for the first delimiter
            else if(RS232_PollComport(port, &byteBuf, 1) == 1 &&
                    byteBuf == 'S') {
                rx_sensor_data[0] = byteBuf;
                rx_bytes          = 1;
            } else {
                if(timeout == 0) {
                    // nothing in serial buffer - give up immediately
                    break;
                } else {
                    timeout++;
                }
            }
        }

        // Calculate CRC on payload bytes
        crc_bytes = crcFast(&rx_sensor_data[0], (size_t)31);
        // Check calculated vs received CRC bytes
        if(rx_sensor_data[sensor_crc_byte1] ==
               (BYTE)((crc_bytes >> 8) & 0xFF) &&
           (rx_sensor_data[sensor_crc_byte2] == (BYTE)crc_bytes & 0xFF)) {

            if(rx_sensor_data[crank_rpm_delimit] == 'S') {
                rx_buffer->crank_rpm = rx_sensor_data[crank_rpm_x1000] * 1000;
                rx_buffer->crank_rpm += rx_sensor_data[crank_rpm_x100] * 100;
                rx_buffer->crank_rpm += rx_sensor_data[crank_rpm_x10] * 10;
            }

            if(rx_sensor_data[map_delimit] == 'M') {
                rx_buffer->manifold_pressure_mbar =
                    rx_sensor_data[manifold_pressure_x1000] * 1000;
                rx_buffer->manifold_pressure_mbar +=
                    rx_sensor_data[manifold_pressure_x100] * 100;
                rx_buffer->manifold_pressure_mbar +=
                    rx_sensor_data[manifold_pressure_x10] * 10;
            }

            if(rx_sensor_data[temperature_delimit_a] == 'T' &&
               rx_sensor_data[temperature_a_delimit] == 'A') {
                rx_buffer->temperature_a_degC =
                    rx_sensor_data[temperature_a_x100] * 100;
                rx_buffer->temperature_a_degC +=
                    rx_sensor_data[temperature_a_x10] * 10;
                rx_buffer->temperature_a_degC +=
                    rx_sensor_data[temperature_a_x1];
            }

            if(rx_sensor_data[temperature_delimit_b] == 'T' &&
               rx_sensor_data[temperature_b_delimit] == 'B') {
                rx_buffer->temperature_b_degC =
                    rx_sensor_data[temperature_b_x100] * 100;
                rx_buffer->temperature_b_degC +=
                    rx_sensor_data[temperature_b_x10] * 10;
                rx_buffer->temperature_b_degC +=
                    rx_sensor_data[temperature_b_x1];
            }

            if(rx_sensor_data[oil_pressure_delimit] == 'P') {
                rx_buffer->oil_pressure_mbar =
                    rx_sensor_data[oil_pressure_x1000] * 1000;
                rx_buffer->oil_pressure_mbar +=
                    rx_sensor_data[oil_pressure_x100] * 100;
                rx_buffer->oil_pressure_mbar +=
                    rx_sensor_data[oil_pressure_x10] * 10;
            }

            if(rx_sensor_data[fuel_pressure_delimit] == 'D') {
                rx_buffer->fuel_pressure_bar =
                    rx_sensor_data[fuel_pressure_x1000] * 1000;
                rx_buffer->fuel_pressure_bar +=
                    rx_sensor_data[fuel_pressure_x100] * 100;
                rx_buffer->fuel_pressure_bar +=
                    rx_sensor_data[fuel_pressure_x10] * 10;
            }

            // rx_sensor_data[intake_airflow_delimit];
            // rx_sensor_data[intake_airflow_res1];
            // rx_sensor_data[intake_airflow_res2];
            // rx_sensor_data[intake_airflow_res3];
            // rx_sensor_data[intake_airflow_res4];
        }
    }
}

/**
 * @brief serial_init
 *
 *  Initialise serial port, user selects ascii or stream mode
 *
 * @return int stream mode
 */

int serial_init(serial_modes_t program_mode)
{
    // user selects serial mode
    int userInput = 0;
    serial_mode   = mode_select_port;

#if WIN_ECU_DISPLAY
    // only need to ask user for mode if in display program - not
    // ecu_sensor_spoofer:
    if(program_mode != mode_internal_spoof) {
        printf("\n\nSelect test mode.\n 1 = External serial ECU data\n 2 = "
               "Generate "
               "internal spoofed ECU_Data\n: ");
        while(scanf("%d", &userInput) != 1) {
            printf("Please enter a value [1 or 2].\n");
        };
        if(userInput > 0 && userInput < 3) {
            if(userInput == 1) {
                serial_mode = mode_stream_data;
                printf("\nRunning in external sensor mode (serial).");
            } else {
                serial_mode = mode_internal_spoof;
                printf("\nRunning in internal spoof mode.");
            }
        } else {
            snprintf(msg, sizeof(msg), "\n\rSelection [%3d] is not valid.\
                Please enter a value [1 or 2].",
                     userInput);
            printf(msg);
        }
    } else {
        serial_mode = mode_stream_data;
    }
#else
    serial_mode = mode_stream_data;
    printf("\nRunning in sensor sensor mode.");
#endif

    if(serial_mode == mode_stream_data) {
#if WIN_ECU_DISPLAY
        serial_selectPort();
#else
        port = 0;
#endif
        // open the selected port
        if(RS232_OpenComport(port, bdrate, mode, 0)) {
            return (mode_port_error);
        }

// serial splash message
#if WIN_ECU_DISPLAY || ECU_SENSOR_SPOOFER
        snprintf(msg, sizeof(msg), "\n\rOpened port: COM%d\n", (port + 1));
#elif RPI_ECU_DISPLAY
        snprintf(msg, sizeof(msg), "Opened port: %3d\n", port);
#endif
        printf(msg);
        serial_puts(msg);
    }

    crcInit();
    return (serial_mode);
}

/**
 * @brief serial_selectPort
 *
 */

void serial_selectPort(void)
{
    int userInput = 0;

    while(port == -1) {
        // select serial port

        printf("\n\nEnter a COM port number: ");
        while(scanf("%d", &userInput) != 1) {
            printf("Please enter a value [1 to 99].\n");
        };
        if(userInput > 0 && userInput < 100) {
            winPort = userInput;
            port    = winPort - 1;
        } else {
            snprintf(msg, sizeof(msg), "\n\rSelection [%3d] is not valid.\
        Please enter a value [1-99].",
                     userInput);
            printf(msg);
        }
    }
}

/**
 * @brief serial_puts
 *
 * @param msg
 */

void serial_puts(char * msg)
{
    if(serial_mode == mode_ascii) {
        strcpy(str[t], msg);
        RS232_cputs(port, str[t]);
        printf(">>> TX: %s\n", str[t++]);
        t %= 2;
    }
}

/**
 * @brief serial_readAscii
 *
 * @return int
 */

int serial_readAscii(void)
{
    int n = 0, i = 0;
    if(serial_mode == mode_ascii) {
        n = RS232_PollComport(port, buf, 4095);

        if(n > 0) {
            buf[n] = 0; /* always put a "null" at the end of a string! */

            for(i = 0; i < n; i++) {
                if(buf[i] < 32) /* replace unreadable control-codes by dots */
                {
                    buf[i] = '.';
                }
            }

            printf("received %i bytes: %s\n", n, (char *)buf);
        }
    }
    return n;
}

/**
 * @brief serial_getAsciiBuffer
 *
 * @return char*
 */

char * serial_getAsciiBuffer()
{
    return &buf[0];
}

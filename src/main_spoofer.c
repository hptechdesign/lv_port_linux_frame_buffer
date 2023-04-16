/**
 * @file main_spoofer.c
 * @author Huw Price
 * @brief ECU sensor spoofer, generates fake sensor signals and txs over UART
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

// **************  Common includes

#include "ecu_configs.h"
#include "serial.h"
#include "sensor.h"

// Widgets

// Windows drivers
#include "Windows.h"
#include <unistd.h>

static char printBuf[4096];

// ************** MAIN

int main(int argc, char * argv[])
{

    snprintf(printBuf, sizeof(printBuf),
             "\n******************************************\n* Windows ECU "
             "Sensor Spoofer "
             "%s.%s-%s%s\n******************************************\n",
             MAJ_VER, MIN_VER, COMMITS_PAST, CLEAN_FLAG);
    printf("%s", printBuf);

    // user selects serial port - mode is always spoof
    serial_modes_t mode = serial_init(mode_internal_spoof);
    if((mode != mode_ascii) && (mode != mode_stream_data)) {
        printf("Failed to initialise serial port");
        return 3;
    }

    for(;;) {

        serial_sendSensorPacket();
        sensor_fillBufWithCurrentData(printBuf);
        printf("%s", printBuf);
        // note this is static for now - the data doesn't change
        sensor_generateData();
        usleep(100000);
    }

    return 0;
}

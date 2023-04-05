


// **************  Common includes

#include "ecu_configs.h"
#include "serial.h"
#include "sensor.h"

// Widgets




// Windows drivers
#include "Windows.h"
#include <unistd.h>

static unsigned char serialBuf[4096];

// ************** MAIN

int main(int argc, char *argv[])
{

    printf("\nBegin main loop");
    //user selects serial port
    serial_modes_t mode = serial_init();
    if((mode != mode_ascii) && (mode!=mode_stream_data))
    {
        printf("Failed to initialise serial port");
         return 3;
    }

    

    


    for (;;) {
        printf("Hello again\n");
        serial_sendSensorPacket();
        // note this is static for now - the data doesn't change
        sensor_generateData();
        usleep(100000);
    }


    return 0;
}

/**
 * @file main_display.c
 * @author Huw Price
 * @brief ECU display for RPI and Windows simulator
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

// **************  Common includes
#include "lvgl.h"
#include "ecu_configs.h"
#include "sensor.h"
#include "serial.h"

// Widgets
#include "widgets/bar_waterTemp.h"
#include "widgets/meter_airPressure.h"
#include "widgets/meter_fuelPressure.h"
#include "widgets/meter_oilPressure.h"
#include "widgets/meter_rpm.h"
#include <stdio.h>

// RPI drivers
#if RPI_ECU_DISPLAY
#ifndef __linux__
#define __linux__
#endif //__linux__

#include "init_rpi_env.h"
#include <unistd.h>

// Windows drivers
#elif WIN_ECU_DISPLAY
// include the lvgl sdl header
#include "sdl/sdl.h"
#include "SDL.h"
#include "Windows.h"
#include "unistd.h"
#endif // RPI_ECU_DISPLAY elif WIN_ECU_DISPLAY

// **************  DEFINES
#define DISP_BUF_SIZE (128 * 1024)

/* Private functions */
void display_updateWidgets(void);
void printVersionDetails(void);

static unsigned char serialBuf[4096];

// ************** MAIN

int main(int argc, char * argv[])
{
    printVersionDetails();

    // user selects serial port
    serial_modes_t mode = serial_init(mode_select_port);
    if((mode != mode_internal_spoof) && (mode != mode_stream_data)) {
        printf("\nFailed to initialise serial port");
        // keep window open
        char prompt = 0;
        printf("\nPress a key and press enter to continue \n");
        scanf("%d", &prompt);
        // exit program
        return mode_port_error;
    }

    /*LittlevGL init*/
    lv_init();
#if WIN_ECU_DISPLAY
    sdl_init();
#endif

    // set up the display driver
#if WIN_ECU_DISPLAY
#define BUFFER_SIZE (SDL_HOR_RES * SDL_VER_RES)
    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;
    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t * buf_1[BUFFER_SIZE] = {0};
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL
     * instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, BUFFER_SIZE);
    /*A variable to hold the drivers. Must be static or global.*/
    static lv_disp_drv_t disp_drv;
    /*Basic initialization*/
    lv_disp_drv_init(&disp_drv);
    /*Set an initialized buffer*/
    disp_drv.draw_buf = &disp_buf;
    /*Set a flush callback to draw to the display*/
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res  = SDL_HOR_RES; /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res  = SDL_VER_RES; /*Set the vertical resolution in pixels*/
    /*Register the driver and save the created display objects*/
    lv_disp_t * disp = lv_disp_drv_register(&disp_drv);
    lv_theme_default_init(disp, lv_color_make(0x77, 0x44, 0xBB),
                          lv_color_make(0x14, 0x14, 0x3C), 1,
                          lv_font_default());

    static lv_indev_drv_t indev_drv;
    /*Basic initialization*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

#elif RPI_ECU_DISPLAY
    //// SETUP PI:
    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res  = 800;
    disp_drv.ver_res  = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the
     * mouse position and state*/
    indev_drv_1.read_cb      = evdev_read;
    lv_indev_t * mouse_indev = lv_indev_drv_register(&indev_drv_1);

    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj =
        lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
    lv_indev_set_cursor(mouse_indev,
                        cursor_obj);                /*Connect the image  object to the driver*/
#endif // SDL(elif)RPI_ECU_DISPLAY

    /*Draw Widgets*/
    bar_waterTemp1();
    bar_waterTemp2();
    meter_oilPressure();
    meter_airPressure();
    meter_fuelPressure();
    meter_rpm();

    int nBytes = 0;
#if RPI_ECU_DISPLAY
    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_timer_handler();
        // usleep(5000);
        //  poll for serial data
        sensor_getSerialRXData();
        // update widgets

        bar_waterTempASetValue(sensor_getTemperatureA());
        bar_waterTempBSetValue(sensor_getTemperatureB());
        meter_airPressureSetValue(sensor_getManifoldPressure());
        meter_fuelPressureSetValue(sensor_getFuelPressure());
        meter_oilPressureSetValue(sensor_getOilPressure());
        meter_rpmSetValue(sensor_getCrankRpm());
    }
#endif /// RPI_ECU_DISPLAY

#if WIN_ECU_DISPLAY
    for(;;) {
        // Run LVGL engine
        lv_tick_inc(1);
        lv_timer_handler();
        // usleep(1000);

        if(mode == mode_stream_data) {
            //  poll for serial data
            sensor_getSerialRXData();
        } else {
            // spoof the sensor data
            sensor_generateData();
        }

        display_updateWidgets();
    }

#endif // WIN_ECU_DISPLAY

    return 0;
}

void display_updateWidgets(void)
{
    // update widgets
    bar_waterTempASetValue(sensor_getTemperatureA());
    bar_waterTempBSetValue(sensor_getTemperatureB());
    meter_airPressureSetValue(sensor_getManifoldPressure());
    meter_fuelPressureSetValue(sensor_getFuelPressure());
    meter_oilPressureSetValue(sensor_getOilPressure());
    meter_rpmSetValue(sensor_getCrankRpm());
}

#if RPI_ECU_DISPLAY
/// Used in RPI build, not windows:
/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
#endif // RPI_ECU_DISPLAY

/**
 * @brief Print version details
 *
 */
void printVersionDetails(void)
{
    char tempBuf[512];
    snprintf(tempBuf, sizeof(tempBuf),
             "\n********************************\n* Windows ECU Display "
             "%d.%d-%d%s\n********************************\n",
             MAJ_VER, MIN_VER, COMMITS_PAST, CLEAN_FLAG);
    printf("%s", tempBuf);
}
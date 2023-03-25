#ifndef INIT_WIN_H
#define INIT_WIN_H

/*
 * PROJECT:   LVGL PC Simulator using Visual Studio
 * FILE:      LVGL.Simulator.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */
#if WIN_ECU_DISPLAY
#include <Windows.h>

#include "resource.h"


#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"
//#include "lvgl/examples/lv_examples.h"
//#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"


bool single_display_mode_initialization(void);
unsigned int __stdcall lv_win32_window_thread_entrypoint(void* raw_parameter);

#endif  //WIN_ECU_DISPLAY
#endif //#ifndef INIT_WIN_H

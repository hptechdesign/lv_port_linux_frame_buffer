/**
 * @file init_win_env.cpp
 * @author Huw Price
 * @brief Windows-specific initialisation functions
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#if WIN_ECU_DISPLAY

#include "initWin.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include <stdio.h>

bool single_display_mode_initialization()
{
    if(!lv_win32_init(
           GetModuleHandleW(NULL), SW_SHOW, 800, 480,
           LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL)))) {
        return false;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    return true;
}

#include <process.h>

HANDLE g_window_mutex        = NULL;
bool g_initialization_status = false;

#define LVGL_SIMULATOR_MAXIMUM_DISPLAYS 16

HWND g_display_window_handles[LVGL_SIMULATOR_MAXIMUM_DISPLAYS];

unsigned int __stdcall lv_win32_window_thread_entrypoint(void * raw_parameter)
{
    size_t display_id = *(size_t *)(raw_parameter);

    HINSTANCE instance_handle = GetModuleHandleW(NULL);
    int show_window_mode      = SW_SHOW;
    HICON icon_handle  = LoadIconW(instance_handle, MAKEINTRESOURCE(IDI_LVGL));
    lv_coord_t hor_res = 800;
    lv_coord_t ver_res = 480;

    wchar_t window_title[256];
    memset(window_title, 0, sizeof(window_title));
    //_snwprintf(
    //    window_title,
    //    256,
    //    L"ECU Display Simulator for Windows Desktop (800 x 480)",
    //    display_id);

    g_display_window_handles[display_id] =
        lv_win32_create_display_window(L"ECU Display Simulator for Windows "
                                       L"Desktop (800 x 480)", // window_title,
                                       hor_res, ver_res, instance_handle,
                                       icon_handle, show_window_mode);
    if(!g_display_window_handles[display_id]) {
        return 0;
    }

    g_initialization_status = true;

    SetEvent(g_window_mutex);

    MSG message;
    while(GetMessageW(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    lv_win32_quit_signal = true;

    return 0;
}

#endif // #if WIN_ECU_DISPLAY

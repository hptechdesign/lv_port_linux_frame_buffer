/**
 * @file slider_throttle.c
 * @author Huw Price
 * @brief Arc display for injector timing
 * @date 2023-05-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lvgl.h"
#include "slider_throttle.h"
#include <stdio.h>

static lv_obj_t * slider;
static lv_obj_t * slider_label;
static lv_obj_t * slider_title;

void slider_throttleSetValue(uint16_t val)
{
    lv_slider_set_value(slider, val, LV_ANIM_OFF);
}

static void slider_event_cb(lv_event_t * e);

/**
 * A default slider with a label displaying the current value
 */
void slider_throttle(void)
{
    /*Create a slider */
    slider = lv_slider_create(lv_scr_act());
    lv_obj_set_pos(slider, SLIDER_THROTTLE_XPOS, SLIDER_THROTTLE_YPOS);
    lv_obj_set_size(slider, SLIDER_THROTTLE_SIZEX, SLIDER_THROTTLE_SIZEY);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /*Create a label below the slider*/
    slider_label = lv_label_create(lv_scr_act());
    lv_label_set_text(slider_label, "0%");

    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    /*Create a label below the slider*/
    slider_title = lv_label_create(lv_scr_act());
    lv_label_set_text(slider_title, "THROTTLE");
    lv_obj_align_to(slider_title, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
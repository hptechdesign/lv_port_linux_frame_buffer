/**
 * @file arc_timing.c
 * @author Huw Price
 * @brief Arc display for injector timing
 * @date 2023-05-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lvgl.h"
#include "arc_timing.h"
#include <stdio.h>

static lv_obj_t * arc_throttle;
static lv_obj_t * arc_label;
static lv_obj_t * arc_title;

void arc_timingSetValue(uint16_t val)
{
    lv_arc_set_value(arc_throttle, val);
}

static void value_changed_event_cb(lv_event_t * e);

void arc_timing(void)
{

    /*Create an Arc*/
    arc_throttle = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc_throttle, ARC_TIMING_SIZEX, ARC_TIMING_SIZEY);
    lv_arc_set_rotation(arc_throttle,
                        (270 - (ARC_TIMING_MAX - ARC_TIMING_MIN) * 2));
    lv_arc_set_bg_angles(arc_throttle, 0,
                         (ARC_TIMING_MAX - ARC_TIMING_MIN) * 4);
    lv_arc_set_range(arc_throttle, ARC_TIMING_MIN, ARC_TIMING_MAX);
    lv_arc_set_value(arc_throttle, 0);
    lv_obj_set_pos(arc_throttle, ARC_TIMING_XPOS, ARC_TIMING_YPOS);

    /*Create a label below the slider*/
    arc_label = lv_label_create(lv_scr_act());
    lv_label_set_text(arc_label, "0°");
    lv_obj_align_to(arc_label, arc_throttle, LV_ALIGN_CENTER, 0, 0);

    /*Create a label below the slider*/
    arc_title = lv_label_create(lv_scr_act());
    lv_label_set_text(arc_title, "INJECTOR\nFIRING\nANGLE");
    // lv_label_set_align(arc_title, LV_TEXT_ALIGN_CENTER);
    lv_obj_align_to(arc_title, arc_throttle, LV_ALIGN_OUT_BOTTOM_MID, 0, -30);

    lv_obj_add_event_cb(arc_throttle, value_changed_event_cb,
                        LV_EVENT_VALUE_CHANGED, arc_label);

    /*Manually update the label for the first time*/
    lv_event_send(arc_throttle, LV_EVENT_VALUE_CHANGED, NULL);
}

static void value_changed_event_cb(lv_event_t * e)
{
    lv_obj_t * arc   = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);

    lv_label_set_text_fmt(label, "%d°", lv_arc_get_value(arc));

    /*Rotate the label to the current position of the arc*/
    // lv_arc_rotate_obj_to_angle(label, arc, 25);
}

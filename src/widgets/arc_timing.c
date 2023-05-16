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

static lv_obj_t * arc;

void arc_timingSetValue(uint16_t val)
{
    lv_arc_set_value(arc, val);
}

static void value_changed_event_cb(lv_event_t * e);

void arc_timing(void)
{
    lv_obj_t * label = lv_label_create(lv_scr_act());

    /*Create an Arc*/
    arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc, ARC_TIMING_SIZEX, ARC_TIMING_SIZEY);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 10);
    lv_obj_set_pos(arc, ARC_TIMING_XPOS, ARC_TIMING_YPOS);
    lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED,
                        label);

    /*Manually update the label for the first time*/
    lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL);
}

static void value_changed_event_cb(lv_event_t * e)
{
    lv_obj_t * arc   = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);

    lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

    /*Rotate the label to the current position of the arc*/
    lv_arc_rotate_obj_to_angle(arc, label, 25);
}

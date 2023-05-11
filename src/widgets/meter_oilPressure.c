/**
 * @file meter_oilPressure.c
 * @author Huw Price
 * @brief Meter display for oil pressure
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lvgl.h"
#include "meter_oilPressure.h"
#include <stdio.h>

static lv_obj_t * meter;
static lv_meter_indicator_t * indic;

static void set_value(void * indic, int32_t v)
{
#if ANIMATION_ENABLED
    lv_meter_set_indicator_value(meter, indic, v);
#endif
}

void meter_oilPressureSetValue(uint16_t value)
{
    lv_meter_set_indicator_value(meter, indic, (int)value);
}

/**
 * A simple meter
 */
void meter_oilPressure(void)
{
    meter = lv_meter_create(lv_scr_act());
    lv_obj_set_pos(meter, METER_OILP_XPOS, METER_OILP_YPOS);
    lv_obj_set_size(meter, METER_OILP_SIZE, METER_OILP_SIZE);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_range(meter, scale, METER_OILP_MIN, METER_OILP_MAX, 270,
                             135);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10,
                             lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(),
                                   15);
    lv_obj_set_style_text_font(meter, METER_OILP_FONT, LV_PART_MAIN);

    /*Add a blue arc to the start*/
    indic =
        lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic, METER_OILP_MIN);
    lv_meter_set_indicator_end_value(meter, indic, METER_OILP_LOW_THRESH);

    /*Make the tick lines blue at the start of the scale*/
    indic =
        lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE),
                                 lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, METER_OILP_MIN);
    lv_meter_set_indicator_end_value(meter, indic, METER_OILP_LOW_THRESH);

    /*Add a red arc to the end*/
    indic =
        lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, METER_OILP_HIGH_THRESH);
    lv_meter_set_indicator_end_value(meter, indic, METER_OILP_MAX);

    /*Make the tick lines red at the end of the scale*/
    indic =
        lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED),
                                 lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, METER_OILP_HIGH_THRESH);
    lv_meter_set_indicator_end_value(meter, indic, METER_OILP_MAX);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 4,
                                     lv_palette_main(LV_PALETTE_GREY), -10);

    // Draw label
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); /*Break the long lines*/
    lv_label_set_recolor(label1,
                         true); /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#ffffff OIL\nPressure, mBar");
    lv_obj_set_width(
        label1, METER_OILP_SIZE); /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(label1, METER_OILP_XPOS,
                   METER_OILP_YPOS + METER_OILP_SIZE -
                       METER_OILP_LABEL_YOFFSET);
    lv_obj_set_style_text_font(label1, LABEL_OILP_FONT, LV_PART_MAIN);

#if ANIMATION_ENABLED
    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_var(&a, indic);
    lv_anim_set_values(&a, METER_OILP_MIN, METER_OILP_HIGH_THRESH);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
#endif
}

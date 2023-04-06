/**
 * @file bar_waterTemp.c
 * @author Huw Price
 * @brief Bar display for water temperature
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lvgl/lvgl.h"
#include "bar_waterTemp.h"
#include <stdio.h>

lv_obj_t * barA;
lv_obj_t * barB;

static void set_value(void * bar, int32_t v);

void bar_waterTempASetValue(uint16_t val)
{
    lv_bar_set_value(barA, val, LV_ANIM_OFF);
}

void bar_waterTempBSetValue(uint16_t val)
{
    lv_bar_set_value(barB, val, LV_ANIM_OFF);
}

static void set_value(void * bar, int32_t v)
{
#if ANIMATION_ENABLED
    lv_bar_set_value(bar, v, LV_ANIM_OFF);
#endif
}

static void event_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if(dsc->part != LV_PART_INDICATOR) return;

    lv_obj_t * obj = lv_event_get_target(e);

    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.font = LV_FONT_DEFAULT;

    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", (int)lv_bar_get_value(obj));

    lv_point_t txt_size;
    lv_txt_get_size(&txt_size, buf, label_dsc.font, label_dsc.letter_space,
                    label_dsc.line_space, LV_COORD_MAX, label_dsc.flag);

    lv_area_t txt_area;
    // /*If the indicator is long enough put the text inside on the right*/
    // if(lv_area_get_width(dsc->draw_area) > txt_size.x + 20) {
    //     txt_area.x2 = dsc->draw_area->x2 - 5;
    //     txt_area.x1 = txt_area.x2 - txt_size.x + 1;
    //     label_dsc.color = lv_color_white();
    // }
    // /*If the indicator is still short put the text out of it on the right*/
    // else {
    //     txt_area.x1 = dsc->draw_area->x2 + 5;
    //     txt_area.x2 = txt_area.x1 + txt_size.x - 1;
    //     label_dsc.color = lv_color_white();
    // }
    txt_area.x1     = dsc->draw_area->x2 + 5;
    txt_area.x2     = txt_area.x1 + txt_size.x - 1;
    label_dsc.color = lv_color_white();

    txt_area.y1 = dsc->draw_area->y1 +
                  (lv_area_get_height(dsc->draw_area) - txt_size.y) / 2;
    txt_area.y2 = txt_area.y1 + txt_size.y - 1;

    lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
}

/**
 * Custom drawer on the bar to display the current value
 */
void bar_waterTemp1(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    barA = lv_bar_create(lv_scr_act());
    lv_obj_add_style(barA, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_event_cb(barA, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_set_size(barA, BAR_WATERTEMP_SIZEX, BAR_WATERTEMP_SIZEY);
    lv_obj_set_pos(barA, BAR_WATERTEMP1_XPOS, BAR_WATERTEMP1_YPOS);
    lv_bar_set_range(barA, 0, 150);

    // Draw label
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); /*Break the long lines*/
    lv_label_set_recolor(label1,
                         true); /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#ffffff Cylinder One, °C");
    lv_obj_set_width(
        label1,
        BAR_WATERTEMP_SIZEX); /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(label1, BAR_WATERTEMP1_XPOS,
                   BAR_WATERTEMP1_YPOS + BAR_WATERTEMP_SIZEY + 5);

#if ANIMATION_ENABLED
    // Animate
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, barA);
    lv_anim_set_values(&a, 80, 110);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_time(&a, 10000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
#endif
}

void bar_waterTemp2(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    barB = lv_bar_create(lv_scr_act());
    lv_obj_add_style(barB, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_event_cb(barB, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_set_size(barB, BAR_WATERTEMP_SIZEX, BAR_WATERTEMP_SIZEY);
    lv_obj_set_pos(barB, BAR_WATERTEMP2_XPOS, BAR_WATERTEMP2_YPOS);
    lv_bar_set_range(barB, 0, 150);

    // Draw label
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); /*Break the long lines*/
    lv_label_set_recolor(label1,
                         true); /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#ffffff Cylinder Two, °C");
    lv_obj_set_width(
        label1,
        BAR_WATERTEMP_SIZEX); /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(label1, BAR_WATERTEMP2_XPOS,
                   BAR_WATERTEMP2_YPOS + BAR_WATERTEMP_SIZEY + 5);

#if ANIMATION_ENABLED
    // Animate
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, barB);
    lv_anim_set_values(&a, 80, 120);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_time(&a, 8000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
#endif
}

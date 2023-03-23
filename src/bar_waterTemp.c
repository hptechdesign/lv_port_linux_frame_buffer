#include "lvgl.h"
#include "bar_waterTemp.h"

static void set_value(void * bar, int32_t v)
{
    lv_bar_set_value(bar, v, LV_ANIM_OFF);
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
    lv_txt_get_size(&txt_size, buf, label_dsc.font, label_dsc.letter_space, label_dsc.line_space, LV_COORD_MAX,
                    label_dsc.flag);

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
    txt_area.x1 = dsc->draw_area->x2 + 5;
    txt_area.x2 = txt_area.x1 + txt_size.x - 1;
    label_dsc.color = lv_color_white();

    txt_area.y1 = dsc->draw_area->y1 + (lv_area_get_height(dsc->draw_area) - txt_size.y) / 2;
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

    lv_obj_t * bar = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_event_cb(bar, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_set_size(bar, BAR_WATERTEMP1_SIZEX, BAR_WATERTEMP1_SIZEY);
    lv_obj_set_pos(bar,BAR_WATERTEMP1_XPOS,BAR_WATERTEMP1_YPOS);
    lv_bar_set_range(bar, 0, 150);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, bar);
    lv_anim_set_values(&a, 80, 110);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_time(&a, 10000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);

}

void bar_waterTemp2(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    lv_obj_t * bar = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_event_cb(bar, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_set_size(bar, BAR_WATERTEMP2_SIZEX, BAR_WATERTEMP2_SIZEY);
    lv_obj_set_pos(bar,BAR_WATERTEMP2_XPOS,BAR_WATERTEMP2_YPOS);
    lv_bar_set_range(bar, 0, 150);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, bar);
    lv_anim_set_values(&a, 80, 120);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_time(&a, 8000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);

}

#include "lvgl.h"
#include "bar_temperature.h"

static void set_temp(void * bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
}

/**
 * A temperature meter example
 */
void bar_temperature1(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);

    lv_obj_t * bar1 = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar1, &style_indic, LV_PART_INDICATOR);
	lv_obj_set_pos(bar1, BAR_TEMP1_XPOS, BAR_TEMP1_YPOS);
    lv_obj_set_size(bar1, BAR_TEMP1_SIZEX, BAR_TEMP1_SIZEY);
    //lv_obj_set_size(bar1, 20, 200);
    //lv_obj_center(bar1);
    lv_bar_set_range(bar1, 0, 120);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_temp);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_set_var(&a, bar1);
    lv_anim_set_values(&a, 0, 120);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

/**
 * A temperature meter example
 */
void bar_temperature2(void)
{
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_VER);

    lv_obj_t * bar2 = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar2, &style_indic, LV_PART_INDICATOR);
	lv_obj_set_pos(bar2, BAR_TEMP2_XPOS, BAR_TEMP2_YPOS);
    lv_obj_set_size(bar2, BAR_TEMP2_SIZEX, BAR_TEMP2_SIZEY);
    //lv_obj_set_size(bar2, 20, 200);
    //lv_obj_center(bar2);
    lv_bar_set_range(bar2, 0, 120);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_temp);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_set_var(&a, bar2);
    lv_anim_set_values(&a, 0, 120);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}
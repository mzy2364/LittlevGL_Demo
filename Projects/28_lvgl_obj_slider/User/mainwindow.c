/*
*******************************************************************************************************
*
* 文件名称 : mainwindow.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : GUI 主文件
*
*******************************************************************************************************
*/

#include "gui_user.h"



void lv_obj_slider_test(void);



/**
* @brief GUI主函数
* @param None
* @retval	None
*/
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */

	lv_font_cn_style_init();			/* 初始化中文字体 */

	lv_obj_slider_test();				/* 滑块控件测试 */

}


static void slider_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		/* 调节背光 */
		uint8_t value = 0;
		value = lv_slider_get_value(obj);
		gui_hal_backlight(value);
	}
}


/**
* @brief 控件测试函数
* @param None
* @retval	None
*/
void lv_obj_slider_test(void)
{

	uint8_t i = 0;
	uint8_t buf[10] = { 0 };
	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_label;
	static lv_style_t style_knob;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_WHITE;		/* 设置底色 */
	style_desktop.body.grad_color = LV_COLOR_WHITE;		/* 设置渐变色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;


	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	//lv_theme_set_current(lv_theme_material_init(210, NULL));			/* 设置主题 */

	lv_style_copy(&style_knob, &lv_style_pretty);
	style_knob.body.opa = LV_OPA_50;


	lv_obj_t *slider = lv_slider_create(scr, NULL);						/* 创建slider控件 */
	lv_obj_align(slider, NULL, LV_ALIGN_IN_TOP_MID, 0, 30);				/* 设置位置 */
	lv_slider_set_range(slider, 0, 100);								/* 设置滑块的范围 */
	lv_slider_set_value(slider, lv_slider_get_max_value(slider), true);	/* 设置滑块的值为最大值,动画打开 */
	lv_obj_set_event_cb(slider, slider_event_cb);						/* 设置对象的事件回调函数 */
	lv_slider_set_knob_in(slider,false);
	lv_slider_set_style(slider, LV_SLIDER_STYLE_KNOB, &style_knob);


	/* 创建label控件 */
	lv_style_copy(&style_label, &style_cn_16);
	style_label.text.color = LV_COLOR_BLACK;
	lv_obj_t *label = lv_label_create(scr, NULL);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_text(label, "滑动滑块调节背光");
	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);


}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


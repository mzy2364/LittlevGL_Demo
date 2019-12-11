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



void lv_obj_gauge_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_gauge_test();				/* 量规控件测试 */
	
}



static void gauge1_adjust(lv_task_t *t)
{
	static uint8_t value=0;
	static uint8_t dir = 1;
	if (dir)
		value++;
	else
		value--;
	if (value >= 100)
		dir = 0;
	if (value == 0)
		dir = 1;

	lv_gauge_set_value(t->user_data, 0, value);

}

static void gauge2_adjust(lv_task_t *t)
{
	lv_gauge_set_value(t->user_data, 0, gui_hal_adc_light_get_ratio());

}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_gauge_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;


	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_WHITE;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */


	lv_obj_t *gauge1 = lv_gauge_create(scr, NULL);				/* 创建gauge控件 */
	lv_obj_align(gauge1, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);	/* 设置位置 */
	lv_gauge_set_value(gauge1, 0, 10);							/* 设置值 */
	lv_gauge_set_critical_value(gauge1, 80);					/* 设置临界值 */

	lv_obj_t *label = lv_label_create(scr, NULL);				/* 创建label控件 */
	lv_label_set_text(label, "AUTO");							/* 设置文本 */
	lv_obj_align(label, gauge1, LV_ALIGN_OUT_TOP_MID, 0, 0);	/* 设置位置 */

	lv_obj_t *gauge2 = lv_gauge_create(scr, NULL);				/* 创建gauge控件 */
	lv_obj_align(gauge2, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 20);	/* 设置位置 */

	lv_obj_t *labe2 = lv_label_create(scr, NULL);				/* 创建label控件 */
	lv_label_set_text(labe2, "LIGHT");							/* 设置文本 */
	lv_obj_align(labe2, gauge2, LV_ALIGN_OUT_TOP_MID, 0, 0);	/* 设置位置 */

	lv_task_create(gauge1_adjust, 100, LV_TASK_PRIO_LOW, gauge1);	/* 创建任务刷新gauge指针的值 */
	
	lv_task_create(gauge2_adjust, 100, LV_TASK_PRIO_LOW, gauge2);	/* 创建任务刷新gauge指针的值 */


}





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

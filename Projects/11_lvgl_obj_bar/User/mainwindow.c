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



void lv_obj_bar_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_bar_test();					/* 进度条控件测试 */
	
}




static void task_change_bar(lv_task_t *t)
{
	if (lv_bar_get_value(t->user_data) < lv_bar_get_max_value(t->user_data))
	{
		lv_bar_set_value(t->user_data, (lv_bar_get_value(t->user_data)+1), LV_ANIM_OFF);
	}
	else
	{
		lv_bar_set_value(t->user_data, lv_bar_get_min_value(t->user_data), LV_ANIM_OFF);
	}
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_bar_test(void)
{
	/* 新建个样式 */
	static lv_style_t style_desktop;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);		/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);			/* 设置样式 */

	lv_obj_t *bar1 = lv_bar_create(scr, NULL);		/* 创建bar控件 */
	lv_bar_set_anim_time(bar1, 2000);				/* 设置动画时间 */
	lv_bar_set_range(bar1, 0, 100);					/* 设置值的范围,最大值和最小值 */
	lv_bar_set_value(bar1, 100, LV_ANIM_ON);		/* 设置bar的值,动画显示打开 */
	lv_obj_align(bar1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);	/* 设置位置 */

	lv_obj_t *bar2 = lv_bar_create(scr, NULL);		/* 创建bar控件 */
	lv_bar_set_sym(bar2, true);						/* 启用对称 */
	lv_bar_set_range(bar2, -100, 100);					/* 设置范围 */
	lv_bar_set_value(bar2, 50, LV_ANIM_ON);		/* 设置bar的值,动画显示打开 */
	lv_obj_align(bar2, bar1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);	/* 设置位置 */

	lv_task_create(task_change_bar, 100, LV_TASK_PRIO_LOW, bar2);	/* 创建个任务定期修改bar的值 */

}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


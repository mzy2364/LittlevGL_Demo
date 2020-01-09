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




void lv_obj_led_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_led_test();					/* LED控件测试 */
	
}


static void led_bright_task(lv_task_t *t)
{
	/* 调节亮度 */
	lv_led_set_bright(t->user_data,(uint8_t)(((float)gui_hal_adc_light_get_ratio()/100)*255));
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_led_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_led;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_WHITE;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	/* 修改led控件的样式,默认的样式看不出led的效果 */
	lv_style_copy(&style_led, &lv_style_pretty_color);
	style_led.body.shadow.width = 5;
	style_led.body.radius = LV_RADIUS_CIRCLE;
	style_led.body.border.width = 3;
	style_led.body.border.opa = LV_OPA_30;
	style_led.body.main_color = lv_color_hsv_to_rgb(210, 100, 100);
	style_led.body.grad_color = lv_color_hsv_to_rgb(210, 100, 40);
	style_led.body.border.color = lv_color_hsv_to_rgb(210, 60, 60);
	style_led.body.shadow.color = lv_color_hsv_to_rgb(210, 100, 100);




	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */


	lv_obj_t *led1 = lv_led_create(scr, NULL);				/* 创建led控件 */
	lv_led_set_style(led1, LV_LED_STYLE_MAIN, &style_led);	/* 设置样式 */
	lv_obj_align(led1, NULL, LV_ALIGN_IN_TOP_MID, -50, 10);	/* 设置位置 */
	lv_led_on(led1);										/* 打开led */


	lv_obj_t *led2 = lv_led_create(scr, led1);				/* 创建led控件,复制之前的属性 */
	lv_obj_align(led2, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);	/* 设置位置 */
	lv_led_off(led2);							/* 关闭led */

	lv_obj_t *led3 = lv_led_create(scr, led1);				/* 创建led控件,复制之前的属性 */
	lv_obj_align(led3, NULL, LV_ALIGN_IN_TOP_MID, 50, 10);	/* 设置位置 */
	lv_led_off(led3);										/* 关闭led */
	
	lv_task_create(led_bright_task, 500, LV_TASK_PRIO_LOW, led3);	/* 创建任务动态调节led3的亮度 */


}





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


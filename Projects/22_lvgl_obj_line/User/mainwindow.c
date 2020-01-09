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


lv_point_t line_points[] = { { 5, 5 }, { 70, 70 }, { 120, 10 }, { 180, 60 }, { 240, 10 } };

lv_point_t line_points_weather[] = { { 5, 12 }, { 70, 14 }, { 120, 15 }, { 180, 16 }, { 240, 16 } };

void lv_obj_line_test(void);
void create_line_note(lv_obj_t *line, lv_obj_t *parent, lv_point_t points[], uint16_t num);
void create_line_point(lv_obj_t *line, lv_obj_t *parent, lv_point_t points[], uint16_t num, uint16_t point_size);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_line_test();					/* 线条控件测试 */
	
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_line_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_line;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_WHITE;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	/* 修改line控件的样式 */
	lv_style_copy(&style_line, &lv_style_plain);
	style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
	style_line.line.width = 3;
	style_line.line.rounded = 1;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_obj_t *line1 = lv_line_create(scr, NULL);				/* 创建line控件 */
	lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);	/* 设置样式 */
	lv_line_set_points(line1, line_points, 5);					/* 设置点阵集 */
	lv_obj_align(line1, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);		/* 设置位置 */
	lv_line_set_y_invert(line1, true);							/* 反转y,默认是数字大的在下面,反转后数字大的在上面 */
	
	create_line_note(line1, scr, line_points, 5);				/* 创建注释 */
	create_line_point(line1, scr, line_points, 5, 8);			/* 创建点 */

	lv_obj_t *line2 = lv_line_create(scr, line1);				/* 创建line控件,复制line1的属性 */
	lv_line_set_points(line2, line_points_weather, 5);			/* 设置点阵集 */
	lv_obj_align(line2, line1, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);	/* 设置位置 */
	create_line_note(line2, scr, line_points_weather, 5);		/* 创建注释 */
	create_line_point(line2, scr, line_points_weather, 5, 5);	/* 创建点 */

}


/**
  * @brief 为line控件创建注释
  * @param line-控件指针
  * @param parent-注释父对象
  * @param points-点阵
  * @param num-数量
  * @retval	None
  */
void create_line_note(lv_obj_t *line, lv_obj_t *parent, lv_point_t points[], uint16_t num)
{
	uint16_t i = 0;
	uint8_t value[25];
	for ( i = 0; i < num; i++)
	{
		memset(value,0,sizeof(value));
		lv_obj_t *label1 = lv_label_create(parent, NULL);
		sprintf(value, "%d", points[i].y);
		lv_label_set_text(label1,value);
		lv_obj_align(label1, line, LV_ALIGN_IN_BOTTOM_LEFT, points[i].x-10, (-points[i].y) + 30);

	}
}


/**
  * @brief 为line控件创建放大的点
  * @param line-控件指针
  * @param parent-注释父对象
  * @param points-点阵
  * @param num-数量
  * @param point_size-点的大小
  * @retval	None
  * @note 实际是用led控件模拟点
  */
void create_line_point(lv_obj_t *line, lv_obj_t *parent, lv_point_t points[], uint16_t num, uint16_t point_size)
{
	uint16_t i = 0;

	static lv_style_t style_led;
	lv_style_copy(&style_led, &lv_style_pretty_color);
	style_led.body.radius = LV_RADIUS_CIRCLE;
	style_led.body.main_color = LV_COLOR_MAKE(0xb5, 0x0f, 0x04);
	style_led.body.grad_color = LV_COLOR_MAKE(0x50, 0x07, 0x02);
	style_led.body.border.color = LV_COLOR_MAKE(0xfa, 0x0f, 0x00);
	style_led.body.border.width = 1;
	style_led.body.border.opa = LV_OPA_30;
	style_led.body.shadow.color = LV_COLOR_MAKE(0xb5, 0x0f, 0x04);
	style_led.body.shadow.width = 1;


	for (i = 0; i < num; i++)
	{

		lv_obj_t *led = lv_led_create(parent, NULL);
		lv_obj_set_size(led, point_size, point_size);
		lv_led_set_style(led,LV_LED_STYLE_MAIN,&style_led);
		lv_obj_align(led, line, LV_ALIGN_IN_BOTTOM_LEFT, points[i].x-3, (-points[i].y)+3);
	}
}






/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


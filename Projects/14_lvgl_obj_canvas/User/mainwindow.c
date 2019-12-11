﻿/*
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



void lv_obj_canvas_test(void);


lv_point_t polyon_point[3] = { {200,20}, {200,100}, {350,50} };
lv_point_t line_point[5] = { { 350, 30 }, { 350, 100 }, { 400, 100 }, { 400, 30 }, { 350, 30 } };

/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_canvas_test();				/* 画布控件测试 */
	
}






/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_canvas_test(void)
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

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);			/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);				/* 设置样式 */


	uint16_t *buf = lv_mem_alloc(LV_HOR_RES*LV_VER_RES * 2);		/* 申请一个屏幕大小的缓冲区供画布使用 */
	lv_obj_t *canvas = lv_canvas_create(scr, NULL);					/* 创建 canvas 控件 */

	lv_canvas_set_buffer(canvas, buf, LV_HOR_RES, LV_VER_RES, LV_IMG_CF_TRUE_COLOR);	/* 设置缓冲区 */

	lv_canvas_draw_rect(canvas, 100, 100, 100, 100, &lv_style_scr);			/* 画矩形 */

	lv_canvas_draw_text(canvas, 10, 10, 200, &lv_style_scr, "hello world", LV_LABEL_ALIGN_LEFT);	/* 画文字 */

	lv_canvas_draw_arc(canvas, 50, 100, 30, 0, 270, &lv_style_scr);			/* 画圆 */

	lv_canvas_draw_polygon(canvas, polyon_point, 3, &lv_style_scr);			/* 画区域 */
	
	lv_canvas_draw_line(canvas, line_point, 5, &lv_style_scr);				/* 画线 */

	lv_obj_t *btn = lv_btn_create(canvas, NULL);			/* 创建位于画布上的按钮 */
	lv_obj_set_pos(btn, 300, 130);							/* 设置按钮坐标 */
}






/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


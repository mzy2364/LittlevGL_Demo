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

uint8_t *list_value_x="0\n1\n2\n3\n4\n5\n6\n7\n\8\n\9";
uint8_t *list_value_y = "100\n90\n80\n70\n60\n50\n40\n30\n20\n10\n0";

lv_chart_series_t *ser_cpu;
lv_chart_series_t *ser_light;

void lv_obj_chart_test(void);
void math_test(void);


/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_chart_test();				/* 图表控件测试 */
	
}



static void update_chart(lv_task_t *t)
{
	/* 更新图表 */
	lv_chart_set_next(t->user_data, ser_cpu, gui_hal_cpuusage_get());
	lv_chart_set_next(t->user_data, ser_light, gui_hal_adc_light_get_ratio());
}


static void btn_event(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_RELEASED) 
	{
		math_test();
	}
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_chart_test(void)
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

	lv_obj_t *chart = lv_chart_create(scr,NULL);		/* 创建图表控件 */
	lv_obj_align(chart,NULL,LV_ALIGN_IN_TOP_MID,0,30);	/* 设置位置 */
	lv_chart_set_point_count(chart,10);					/* 设置显示的点数量 */
	lv_chart_set_series_width(chart,4);					/* 设置线宽度 */
	lv_chart_set_range(chart,0,100);					/* 设置范围0-100 */
	lv_chart_set_div_line_count(chart, 9, 5);			/* 设置分割线的数量 */
	lv_chart_set_margin(chart, 50);						/* 设置标注的扩展长度 */
	lv_chart_set_type(chart, LV_CHART_TYPE_POINT | LV_CHART_TYPE_LINE);	/* 显示方式 显示点和线 */
	lv_chart_set_x_tick_texts(chart, list_value_x, 1, LV_CHART_AXIS_DRAW_LAST_TICK);	/* 设置标注的文本 */
	lv_obj_set_size(chart,300,300);						/* 设置控件尺寸 */
	lv_chart_set_x_tick_length(chart, 10, 10);			/* 刻度线长度 */
	lv_chart_set_y_tick_texts(chart, list_value_y, 1, LV_CHART_AXIS_DRAW_LAST_TICK);	/* 设置标注的文本 */
	lv_chart_set_y_tick_length(chart, 10, 10);			/* 刻度线长度 */

	ser_cpu = lv_chart_add_series(chart,LV_COLOR_RED);		/* 创建线条 */
	ser_light = lv_chart_add_series(chart, LV_COLOR_BLUE);	/* 创建线条 */

	lv_task_create(update_chart,500,LV_TASK_PRIO_LOW,chart);	/* 创建定期更新的任务 */


	lv_obj_t *btn = lv_btn_create(scr,NULL);					/* 创建按钮 */
	lv_obj_t *label_btn = lv_label_create(btn,NULL);				/* 创建按钮的文本 */
	lv_label_set_style(label_btn, LV_LABEL_STYLE_MAIN, &style_cn_16);	/* 设置控件样式为中文字体的样式 */
	lv_label_set_text(label_btn, "开始运算 ");						/* 设置文本 */
	lv_obj_align(btn,chart,LV_ALIGN_OUT_BOTTOM_MID,0,30);		/* 设置位置 */
	lv_obj_set_event_cb(btn, btn_event);						/* 设置对象事件回调函数 */

	
	lv_obj_t *label1 = lv_label_create(scr,NULL);				/* 创建label控件 */
	lv_obj_align(label1,chart,LV_ALIGN_OUT_RIGHT_MID,0,-10);	/* 设置位置 */
	lv_label_set_recolor(label1,true);							/* 允许文字重新着色 */
	lv_label_set_text(label1, "#FF0000 RED:CPU#");				/* 设置文字 */
	lv_label_set_body_draw(label1,true);						/* 允许绘制body */
	lv_label_set_style(label1,LV_LABEL_STYLE_MAIN,&lv_style_scr);	/* 重设样式 */

	lv_obj_t *label2 = lv_label_create(scr, label1);				/* 创建label控件 */
	lv_obj_align(label2, chart, LV_ALIGN_OUT_RIGHT_MID, 0, 10);		/* 设置位置 */
	lv_label_set_text(label2, "#0000FF BLUE:LIGHT#");				/* 设置文字 */
}

void math_test(void)
{
	float a = 3.14159f;
	float b = 1.25697f;
	float c;
	uint32_t i = 0;

	for ( i = 0; i < 65535; i++)
	{
		c = a * b;
		c = c * c;
		
	}
}




/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


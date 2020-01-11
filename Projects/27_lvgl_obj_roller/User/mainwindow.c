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

const uint8_t month[] = "January\nFebruary\nMarch\nApril\nMay\nJune\nJuly\nAugust\nSeptember\nOctober\nNovember\nDecember";
const uint8_t year[] = "2019\n2020\n2021\n2022\n2023\n2024\n2025\n2026\n2027\n2028" ;
uint8_t date[100] = { 0 };
uint8_t min[200] = { 0 };
uint8_t hour[100] = { 0 };

uint8_t date_buf[100];


lv_obj_t *roller_year;
lv_obj_t *roller_month;
lv_obj_t *roller_date;
lv_obj_t *roller_hour;
lv_obj_t *roller_min;
lv_obj_t *label_date;


void lv_obj_roller_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_roller_test();				/* 滚动框控件测试 */
	
}




static void roller_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED) 
	{
		memset(date_buf, 0, sizeof(date_buf));

		char buf[100];
		sprintf(buf, "%02d", lv_roller_get_selected(roller_date) + 1);		/* 获取选择的索引 */
		//lv_roller_get_selected_str(roller_date, buf, sizeof(buf));
		strcat(date_buf, buf);
		strcat(date_buf, " ");
		memset(buf, 0, sizeof(buf));

		lv_roller_get_selected_str(roller_month, buf, sizeof(buf));			/* 获取选择的字符串 */
		strcat(date_buf, buf);
		strcat(date_buf, " ");
		memset(buf, 0, sizeof(buf));

		lv_roller_get_selected_str(roller_year, buf, sizeof(buf));
		strcat(date_buf, buf);
		strcat(date_buf, "   ");
		memset(buf, 0, sizeof(buf));

		sprintf(buf,"%02d",lv_roller_get_selected(roller_hour));
		//lv_roller_get_selected_str(roller_hour, buf, sizeof(buf));
		strcat(date_buf, buf);
		strcat(date_buf, ":");
		memset(buf, 0, sizeof(buf));

		sprintf(buf, "%02d", lv_roller_get_selected(roller_min));
		//lv_roller_get_selected_str(roller_min, buf, sizeof(buf));
		strcat(date_buf, buf);
		strcat(date_buf, " ");
		memset(buf, 0, sizeof(buf));

		lv_label_set_text(label_date, date_buf);						/* 设置选择的时间 */
		lv_obj_align(label_date, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);		/* 文本改变后重新设置一下位置 */
	}
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_roller_test(void)
{

	uint8_t i = 0;
	uint8_t buf[10] = {0};
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

	roller_year = lv_roller_create(scr, NULL);							/* 创建roller控件 */
	lv_obj_set_pos(roller_year, 0, 50);									/* 设置坐标 */
	lv_roller_set_options(roller_year, year, LV_ROLLER_MODE_INIFINITE);	/* 添加内容 */
	lv_roller_set_fix_width(roller_year, 100);							/* 设置宽度 */
	lv_roller_set_visible_row_count(roller_year, 8);					/* 设置显示的行数 */
	lv_obj_set_event_cb(roller_year, roller_event_cb);					/* 设置事件回调函数 */
	lv_roller_set_selected(roller_year, 0, true);						/* 手动设置选择项 */


	/* 填充日期时间缓冲区 */
	for ( i = 1; i <= 31; i++)
	{
		if (i < 31)
			sprintf(buf, "%d\n", i);
		else
			sprintf(buf, "%d", i);
		strcat(date,buf);
	}

	for (i = 0; i <= 23; i++)
	{
		if (i < 23)
			sprintf(buf, "%d\n", i);
		else
			sprintf(buf, "%d", i);
		strcat(hour, buf);
	}

	for (i = 0; i <= 59; i++)
	{
		if (i < 59)
			sprintf(buf, "%d\n", i);
		else
			sprintf(buf, "%d", i);
		strcat(min, buf);
	}

	roller_month = lv_roller_create(scr, NULL);
	lv_obj_set_pos(roller_month, 100, 50);
	lv_roller_set_options(roller_month, month, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_fix_width(roller_month, 100);
	lv_roller_set_visible_row_count(roller_month, 8);
	lv_obj_set_event_cb(roller_month, roller_event_cb);
	lv_roller_set_selected(roller_month, 12-1, true);

	roller_date = lv_roller_create(scr, NULL);
	lv_obj_set_pos(roller_date, 200, 50);
	lv_roller_set_options(roller_date, date, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_fix_width(roller_date, 100);
	lv_roller_set_visible_row_count(roller_date, 8);
	lv_obj_set_event_cb(roller_date, roller_event_cb);
	lv_roller_set_selected(roller_date, 9-1, true);

	roller_hour = lv_roller_create(scr, NULL);
	lv_obj_set_pos(roller_hour, 300, 50);
	lv_roller_set_options(roller_hour, hour, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_fix_width(roller_hour, 90);
	lv_roller_set_visible_row_count(roller_hour, 8);
	lv_obj_set_event_cb(roller_hour, roller_event_cb);
	lv_roller_set_selected(roller_hour, 21-1, true);

	roller_min = lv_roller_create(scr, NULL);
	lv_obj_set_pos(roller_min, 390, 50);
	lv_roller_set_options(roller_min, min, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_fix_width(roller_min, 90);
	lv_roller_set_visible_row_count(roller_min, 8);
	lv_obj_set_event_cb(roller_min, roller_event_cb);
	lv_roller_set_selected(roller_min, 5-1, true);

	
	/* 创建label用于显示选择的时间 */
	label_date = lv_label_create(scr,NULL);	
	lv_label_set_long_mode(label_date, LV_LABEL_LONG_EXPAND);
	lv_label_set_text(label_date,"");

	/* 手动发送一个事件,使得label显示的时间可以更新 */
	lv_event_send(roller_min, LV_EVENT_VALUE_CHANGED, NULL);

}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


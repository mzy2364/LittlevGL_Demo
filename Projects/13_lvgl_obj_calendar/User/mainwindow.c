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

const uint8_t *month_name[12] = {"01","02","03","04","05","06","07","08","09","10","11","12"};
const uint8_t *day_name[7] = { "7", "1", "2", "3", "4", "5", "6"};

lv_calendar_date_t today_date = 
{
	.year = 2019,
	.month = 2,
	.day = 1,


};

void lv_obj_calender_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
		lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_calender_test();				/* 日历控件测试 */
	
}



static void calendar_handler(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED) {
		lv_calendar_date_t * date = lv_calendar_get_pressed_date(obj);	/* 获取按下选择的日期 */
		if (date) {
			lv_calendar_set_today_date(obj, date);		/* 设置日期为当前按下的 */
		}
	}
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_calender_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_calendar_header;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);			/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);				/* 设置样式 */


	lv_obj_t *calendar = lv_calendar_create(scr, NULL);				/* 创建日历控件 */
	lv_style_copy(&style_calendar_header, lv_calendar_get_style(calendar, LV_CALENDAR_STYLE_HEADER));	/* 获取 header 的属性 */
	//style_calendar_header.text.font = style_cn_12.text.font;		/* 设置中文字体 */
	/* header 设置中文后符号字体显示不是很好 */
	lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_HEADER, &style_calendar_header);	/* 设置 header 的样式 */
	lv_obj_align(calendar, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);			/* 设置位置 */
	lv_calendar_set_month_names(calendar, month_name);					/* 设置月份的名称 */
	lv_calendar_set_day_names(calendar, day_name);						/* 设置日期的名称 */
	lv_calendar_set_today_date(calendar, &today_date);					/* 设置当前日期 */
	lv_calendar_set_showed_date(calendar, &today_date);					/* 设置显示日期 */

	/* 高亮日期 */
	static lv_calendar_date_t highlihted_days[3];		/* 定义需要高亮的日期数组,请用全局或者 static */
	highlihted_days[0].year = 2019;
	highlihted_days[0].month = 7;
	highlihted_days[0].day = 26;

	highlihted_days[1].year = today_date.year;
	highlihted_days[1].month = today_date.month;
	highlihted_days[1].day = today_date.day;

	lv_calendar_set_highlighted_dates(calendar, highlihted_days, 2);	/* 设置高亮日期 */

	lv_obj_set_event_cb(calendar, calendar_handler);				/* 设置对象事件回调函数 */

}






/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


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

const uint8_t *list1_option = "red\ngreen\nblue\nyellow\nwhite\nblack";

void lv_obj_ddlist_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_ddlist_test();				/* 下拉框控件测试 */
	
}


static void ddlist_event(lv_obj_t * obj, lv_event_t event)
{
	uint8_t select = 0;
	if (event == LV_EVENT_VALUE_CHANGED) 
	{
		char buf[32];
		lv_ddlist_get_selected_str(obj, buf, sizeof(buf));
		select = lv_ddlist_get_selected(obj);
		switch(select)
		{
			case 0:
				gui_hal_led_set_color(0X000000FF);
				break;
			case 1:
				gui_hal_led_set_color(0X0000FF00);
				break;
			case 2:
				gui_hal_led_set_color(0X00FF0000);
				break;
			case 3:
				gui_hal_led_set_color(0X0000FFFF);
				break;
			case 4:
				gui_hal_led_set_color(0X00FFFFFF);
				break;
			case 5:
				gui_hal_led_set_color(0X00000000);
				break;
			default:
				break;
			
		}
		//printf("Option: %s index:%d\n", buf, lv_ddlist_get_selected(obj));
	}
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_ddlist_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_ddlist_bg;


	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_obj_t *ddlist1 = lv_ddlist_create(scr, NULL);			/* 创建ddlist控件 */

	/* 复制样式并修改一些属性 */
	lv_style_copy(&style_ddlist_bg, lv_ddlist_get_style(ddlist1,LV_DDLIST_STYLE_BG));
	style_ddlist_bg.body.padding.left = 10;
	style_ddlist_bg.body.padding.right = 10;
	style_ddlist_bg.body.padding.top = 10;
	style_ddlist_bg.body.padding.bottom = 10;
	style_ddlist_bg.text.line_space = 10;		/* 文字的垂直间距,这个属性可以增加每个选项的高度 */

	/* 设置样式 */
	lv_ddlist_set_style(ddlist1, LV_DDLIST_STYLE_BG, &style_ddlist_bg);

	lv_ddlist_set_anim_time(ddlist1, 100);		/* 设置动画时间 */
	lv_ddlist_set_options(ddlist1, list1_option);	/* 设置选项 */
	lv_ddlist_set_fix_width(ddlist1, 150);			/* 设置宽度 */
	//lv_ddlist_set_fix_height(ddlist1, 100);		/* 设置高度 */
	//lv_ddlist_set_sb_mode(ddlist1, LV_SB_MODE_UNHIDE);	/* 设置滚动条模式 */
	lv_ddlist_open(ddlist1, true);					/* 打开ddlist下拉 */
	lv_ddlist_set_draw_arrow(ddlist1, true);		/* 显示下拉箭头 */
	lv_obj_align(ddlist1, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);	/* 设置位置 */
	lv_obj_set_event_cb(ddlist1, ddlist_event);		/* 设置事件回调函数 */

}





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


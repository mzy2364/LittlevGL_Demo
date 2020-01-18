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




static lv_obj_t * kb;


void lv_obj_win_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */

	lv_obj_win_test();					/* 窗口控件测试 */


	
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_win_test(void)
{

	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_win_bg;
	static lv_style_t style_win_header;
	static lv_style_t style_label;

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

	lv_obj_t * win = lv_win_create(scr, NULL);				/* 创建win控件 */
	lv_style_copy(&style_win_header, lv_win_get_style(win, LV_WIN_STYLE_HEADER));
	lv_style_copy(&style_win_bg, lv_win_get_style(win, LV_WIN_STYLE_BG));
	style_win_bg.body.border.width = 3;						/* 边框宽度 */
	style_win_bg.body.border.color = style_win_header.body.main_color;	/* 边框颜色 */
	lv_win_set_style(win, LV_WIN_STYLE_BG, &style_win_bg);		/* 设置win控件的样式 */
	lv_win_set_title(win, "Window title");						/* 设置win控件的标题 */
	lv_win_set_btn_size(win,100);								/* 设置win控件的控制按钮尺寸 */
	lv_obj_set_size(win,lv_obj_get_width(scr)-50,lv_obj_get_height(scr)/2);	/* 设置控件尺寸 */
	lv_win_set_drag(win, true);									/* 设置win控件可拖动 */

	lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);	/* 创建一个关闭按钮 */
	lv_obj_set_event_cb(close_btn, lv_win_close_event_cb);			/* 设置按钮的事件回调函数 */
	lv_win_add_btn(win, LV_SYMBOL_SETTINGS);						/* 添加一个控制按钮 */

	/* 在主页面创建一个label */
	lv_obj_t * txt = lv_label_create(win, NULL);
	lv_label_set_text(txt, "This is the content of the window\n\n"
		"You can add control buttons to\n"
		"the window header\n\n"
		"The content area becomes automatically\n"
		"scrollable is it's large enough.\n\n"
		" You can scroll the content\n"
		"See the scroll bar on the right!");

}




/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


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


void lv_obj_ta_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */

	lv_obj_ta_test();					/* 文本区域控件测试 */


	
}



static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
{
	/* Just call the regular event handler */
	lv_kb_def_event_cb(event_kb, event);

}



static void ta_event_cb(lv_obj_t * ta, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		/* Focus on the clicked text area */
		if (kb != NULL)
			lv_kb_set_ta(kb, ta);
	}
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_ta_test(void)
{

	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_tabview;
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

	lv_theme_set_current(lv_theme_material_init(210, NULL));			/* 设置主题 */

	lv_obj_t *ta_ssid = lv_ta_create(scr, NULL);			/* 创建ta控件 */
	lv_ta_set_text(ta_ssid, "");							/* 设置空文本 */
	lv_ta_set_one_line(ta_ssid, true);						/* 单行模式 */
	lv_obj_set_width(ta_ssid, LV_HOR_RES / 2 - 20);			/* 宽度 */
	lv_obj_set_pos(ta_ssid, 5, 20);							/* 设置坐标 */
	lv_obj_set_event_cb(ta_ssid, ta_event_cb);				/* 设置事件回调函数 */
	lv_ta_set_max_length(ta_ssid, 16);						/* 设置最大长度 */

	/* 创建label用于引导用户输入 */
	lv_obj_t * label_ssid = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label_ssid, "SSID:");
	lv_obj_align(label_ssid, ta_ssid, LV_ALIGN_OUT_TOP_LEFT, 0, 0);


	lv_obj_t *ta_pwd = lv_ta_create(scr, NULL);
	lv_ta_set_text(ta_pwd, "");
	lv_ta_set_one_line(ta_pwd, true);
	lv_obj_set_width(ta_pwd, LV_HOR_RES / 2 - 20);
	lv_ta_set_cursor_type(ta_pwd, LV_CURSOR_LINE | LV_CURSOR_HIDDEN);	/* 临时隐藏光标,选择后再显示 */
	lv_obj_align(ta_pwd, ta_ssid, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);
	lv_obj_set_event_cb(ta_pwd, ta_event_cb);
	lv_ta_set_pwd_mode(ta_pwd, true);						/* 设置为密文模式 */
	lv_ta_set_max_length(ta_pwd, 16);			
	lv_ta_set_pwd_show_time(ta_pwd, 10);					/* 设置密码可以查看的最长时间,过了这个时间以后变成*号 */
	

	lv_obj_t * label_pwd = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label_pwd, "PWD:");
	lv_obj_align(label_pwd, ta_pwd, LV_ALIGN_OUT_TOP_LEFT, 0, 0);


	lv_obj_t *ta_ip = lv_ta_create(scr, NULL);
	lv_ta_set_text(ta_ip, "");
	lv_ta_set_one_line(ta_ip, true);
	lv_obj_set_width(ta_ip, LV_HOR_RES / 2 - 20);
	lv_ta_set_cursor_type(ta_ip, LV_CURSOR_LINE | LV_CURSOR_HIDDEN);
	lv_obj_align(ta_ip, ta_ssid, LV_ALIGN_OUT_BOTTOM_MID, 0, 150);
	lv_obj_set_event_cb(ta_ip, ta_event_cb);
	lv_ta_set_max_length(ta_ip, 16);
	lv_ta_set_accepted_chars(ta_ip, "0123456789.");			/* 设置可接收的字符,相当于正则表达式 */

	lv_obj_t * label_ip = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label_ip, "SERVER_IP:");
	lv_obj_align(label_ip, ta_ip, LV_ALIGN_OUT_TOP_LEFT, 0, 0);


	lv_obj_t *ta_port = lv_ta_create(scr, NULL);
	lv_ta_set_text(ta_port, "");
	lv_ta_set_one_line(ta_port, true);
	lv_obj_set_width(ta_port, LV_HOR_RES / 2 - 20);
	lv_ta_set_cursor_type(ta_port, LV_CURSOR_LINE | LV_CURSOR_HIDDEN);
	lv_obj_align(ta_port, ta_ssid, LV_ALIGN_OUT_BOTTOM_MID, 0, 250);
	lv_obj_set_event_cb(ta_port, ta_event_cb);
	lv_ta_set_max_length(ta_port, 5);
	lv_ta_set_accepted_chars(ta_port, "0123456789");
	lv_ta_set_placeholder_text(ta_port, "0-65535");		/* 在文本输入框为空的时候,设置一个提示文本 */

	lv_obj_t * label_port = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label_port, "SERVER_PORT:");
	lv_obj_align(label_port, ta_port, LV_ALIGN_OUT_TOP_LEFT, 0, 0);




	/* 创建键盘 */
	kb = lv_kb_create(scr, NULL);
	lv_obj_align(kb, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	lv_obj_set_event_cb(kb, kb_event_cb);

	/* 设置键盘对应的输入区域 */
	lv_kb_set_ta(kb, ta_ssid);
	lv_kb_set_cursor_manage(kb, true);


}





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


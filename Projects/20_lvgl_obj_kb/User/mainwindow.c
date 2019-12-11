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


lv_obj_t *kb;
lv_obj_t *ta;
lv_style_t rel_style, pr_style;

void lv_obj_kb_test(void);

static void keyboard_event_cb(lv_obj_t * obj, lv_event_t event);
static void text_area_event(lv_obj_t * obj, lv_event_t event);


/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_kb_test();					/* 键盘控件测试 */
	
}


static void text_area_event(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		/* 创建键盘 */
		if (kb == NULL)
		{
			kb = lv_kb_create(lv_scr_act(), NULL);
			lv_kb_set_cursor_manage(kb, true);
			lv_kb_set_style(kb, LV_KB_STYLE_BG, &lv_style_transp_tight);
			lv_kb_set_style(kb, LV_KB_STYLE_BTN_REL, &rel_style);
			lv_kb_set_style(kb, LV_KB_STYLE_BTN_PR, &pr_style);
			lv_obj_set_event_cb(kb, keyboard_event_cb);
			lv_kb_set_ta(kb, ta);
		}

	}
}



static void keyboard_event_cb(lv_obj_t * obj, lv_event_t event)
{
	

	lv_kb_def_event_cb(kb, event);

	if (event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL) 
	{
		/* 确定按钮或者取消按钮被按下 */
		lv_obj_del(kb);
		kb = NULL;
	}
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_kb_test(void)
{


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

	/* 设置样式 */
	lv_style_copy(&rel_style, &lv_style_btn_rel);
	rel_style.body.radius = 0;
	rel_style.body.border.width = 1;

	lv_style_copy(&pr_style, &lv_style_btn_pr);
	pr_style.body.radius = 0;
	pr_style.body.border.width = 1;


	kb = lv_kb_create(scr, NULL);								/* 创建键盘控件 */
	lv_kb_set_cursor_manage(kb, true);							/* 打开光标管理 */
	lv_kb_set_style(kb, LV_KB_STYLE_BG, &lv_style_transp_tight);/* 设置键盘的样式 */
	lv_kb_set_style(kb, LV_KB_STYLE_BTN_REL, &rel_style);
	lv_kb_set_style(kb, LV_KB_STYLE_BTN_PR, &pr_style);
	lv_obj_set_event_cb(kb, keyboard_event_cb);					/* 设置对象的事件回调函数 */


	ta = lv_ta_create(lv_scr_act(), NULL);						/* 创建文字区域 */
	lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);			/* 设置位置 */
	lv_ta_set_text(ta, "");										/* 清空文本 */
	lv_obj_set_event_cb(ta, text_area_event);					/* 设置对象的事件回调函数 */


	lv_kb_set_ta(kb, ta);					/* 给键盘分配文本区域 */

	

}





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

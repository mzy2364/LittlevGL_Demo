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



void lv_obj_checkbox_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_checkbox_test();				/* 复选框控件测试 */
	
}



static void cb1_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
		color = gui_hal_led_get_current_color();
		(lv_cb_is_checked(obj)?(color |= 0X000000FF):(color &= ~(0X000000FF)));
		gui_hal_led_set_color(color);

		break;
	default:
		break;
	}
}

static void cb2_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
		color = gui_hal_led_get_current_color();
		(lv_cb_is_checked(obj)?(color |= 0X00FF0000):(color &= ~(0X00FF0000)));
		gui_hal_led_set_color(color);
		break;
	default:
		break;
	}
}

static void cb3_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
		color = gui_hal_led_get_current_color();
		(lv_cb_is_checked(obj)?(color |= 0X0000FF00):(color &= ~(0X0000FF00)));
		gui_hal_led_set_color(color);

		break;
	default:
		break;
	}
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_checkbox_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_bg_cb;
	static lv_style_t style_box_cb1;
	static lv_style_t style_box_cb2;
	static lv_style_t style_box_cb3;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);			/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);				/* 设置样式 */


	lv_obj_t *cb1 = lv_cb_create(scr, NULL);				/* 创建 checkbox 控件 */
	lv_style_copy(&style_bg_cb, &lv_style_plain_color);		/* 复制样式 */
	style_bg_cb.text.font = style_cn_16.text.font;			/* 设置样式字体 */
	style_bg_cb.body.opa = 0;								/* 设置样式不透明度 */
	lv_cb_set_text(cb1, "红灯");							/* 设置复选框文字 */
	lv_cb_set_style(cb1, LV_CB_STYLE_BG, &style_bg_cb);		/* 设置复选框背景的样式 */
	lv_obj_align(cb1, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);	/* 设置位置 */

	lv_style_copy(&style_box_cb1, &lv_style_btn_pr);		/* 复制样式,左边 box 的样式 */
	style_box_cb1.body.main_color = LV_COLOR_RED;			/* 设置样式主颜色为红色 */
	style_box_cb1.body.grad_color = LV_COLOR_RED;			/* 设置样式渐变色,跟主色一样 */
	lv_cb_set_style(cb1, LV_CB_STYLE_BOX_TGL_REL, &style_box_cb1);	/* 设置左边 box 被选中的样式 */

	lv_obj_set_event_cb(cb1, cb1_event_cb);					/* 设置对象事件回调函数 */


	lv_obj_t *cb2 = lv_cb_create(scr, cb1);					/* 创建 checkbox 控件,从前面创建的控件复制属性 */
	lv_cb_set_text(cb2, "蓝灯");							/* 设置文字 */
	lv_obj_align(cb2, cb1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);	/* 设置位置 */

	lv_style_copy(&style_box_cb2, &style_box_cb1);			/* 复制样式 */
	style_box_cb2.body.main_color = LV_COLOR_BLUE;			/* 设置样式主颜色为蓝色 */
	style_box_cb2.body.grad_color = LV_COLOR_BLUE;			/* 设置样式渐变色跟主色一致 */
	lv_cb_set_style(cb2, LV_CB_STYLE_BOX_TGL_REL, &style_box_cb2); /* 设置左边 box 被选中的样式 */

	lv_obj_set_event_cb(cb2, cb2_event_cb);					/* 设置对象事件回调函数 */	

	lv_obj_t *cb3 = lv_cb_create(scr, cb1);					/* 创建 checkbox 控件,从前面创建的控件复制属性 */
	lv_cb_set_text(cb3, "绿灯");							/* 设置文字 */
	lv_obj_align(cb3, cb2, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);	/* 设置位置 */

	lv_style_copy(&style_box_cb3, &style_box_cb1);			/* 复制样式 */
	style_box_cb3.body.main_color = lv_color_hex(0X00FF00);	/* 设置样式主颜色为绿色 */
	style_box_cb3.body.grad_color = lv_color_hex(0X00FF00);	/* 设置样式渐变色跟主色一致 */
	lv_cb_set_style(cb3, LV_CB_STYLE_BOX_TGL_REL, &style_box_cb3);	/* 设置左边 box 被选中的样式 */

	lv_obj_set_event_cb(cb3, cb3_event_cb);					/* 设置对象事件回调函数 */	



	lv_obj_t *cb4 = lv_cb_create(scr, NULL);				/* 创建 checkbox 控件,从前面创建的控件复制属性 */
	lv_cb_set_text(cb4, "Check");							/* 设置文字 */
	lv_obj_align(cb4, cb3, LV_ALIGN_OUT_BOTTOM_MID, -100, 50);	/* 设置位置 */
	lv_cb_set_checked(cb4, true);							/* 设置选中 */


	lv_obj_t *cb5 = lv_cb_create(scr, NULL);				/* 创建 checkbox 控件,从前面创建的控件复制属性 */
	lv_cb_set_text(cb5, "Uncheck");							/* 设置文字 */
	lv_obj_align(cb5, cb3, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);	/* 设置位置 */
	lv_cb_set_checked(cb5, false);							/* 设置取消选中 */


	lv_obj_t *cb6 = lv_cb_create(scr, NULL);				/* 创建 checkbox 控件,从前面创建的控件复制属性 */
	lv_cb_set_text(cb6, "Inactive");							/* 设置文字 */
	lv_obj_align(cb6, cb3, LV_ALIGN_OUT_BOTTOM_MID, 100, 50);	/* 设置位置 */
	lv_cb_set_inactive(cb6);								/* 禁用 */
	//lv_btn_set_state(cb6, LV_BTN_STATE_REL);

}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


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



void lv_obj_sw_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	//lv_load_user_font_from_file();		/* 加载中文字体 */
	
	//lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_sw_test();					/* 开关控件测试 */
	
}


static void sw1_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	if (event == LV_EVENT_VALUE_CHANGED) 
	{
		color = gui_hal_led_get_current_color();
		(lv_sw_get_state(obj)?(color |= 0X000000FF):(color &= ~(0X000000FF)));
		gui_hal_led_set_color(color);
		
	}
}

static void sw2_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		color = gui_hal_led_get_current_color();
		(lv_sw_get_state(obj)?(color |= 0X0000FF00):(color &= (0X0000FF00)));
		gui_hal_led_set_color(color);
	}
}

static void sw3_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		color = gui_hal_led_get_current_color();
		(lv_sw_get_state(obj)?(color |= 0X00FF0000):(color &= ~(0X00FF0000)));
		gui_hal_led_set_color(color);
	}
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_sw_test(void)
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

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);		/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);			/* 设置样式 */

	lv_obj_t *sw = lv_sw_create(scr, NULL);				/* 创建sw控件 */
	lv_obj_align(sw, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);	/* 设置位置 */

	/* 为sw控件新建样式 */
	static lv_style_t bg_style;
	static lv_style_t indic_style;
	static lv_style_t knob_on_style1;
	static lv_style_t knob_on_style2;
	static lv_style_t knob_on_style3;
	static lv_style_t knob_off_style;

	/* 设置style属性 */
	lv_style_copy(&bg_style, &lv_style_pretty);
	bg_style.body.radius = LV_RADIUS_CIRCLE;					/* 圆形 */
	bg_style.body.padding.top = 6;								/* 顶部填充 */
	bg_style.body.padding.bottom = 6;							/* 底部填充 */

	lv_style_copy(&indic_style, &lv_style_pretty_color);
	indic_style.body.radius = LV_RADIUS_CIRCLE;					/* 圆形 */
	indic_style.body.main_color = lv_color_hex(0x9fc8ef);		/* 主颜色 */
	indic_style.body.grad_color = lv_color_hex(0x9fc8ef);		/* 阴影颜色 */
	indic_style.body.padding.left = 0;							/* 上下左右填充 */
	indic_style.body.padding.right = 0;
	indic_style.body.padding.top = 0;
	indic_style.body.padding.bottom = 0;

	lv_style_copy(&knob_off_style, &lv_style_pretty);
	knob_off_style.body.radius = LV_RADIUS_CIRCLE;				/* 圆形 */
	knob_off_style.body.shadow.width = 4;						/* 阴影宽度 */
	knob_off_style.body.shadow.type = LV_SHADOW_BOTTOM;			/* 底部阴影 */

	lv_style_copy(&knob_on_style1, &lv_style_pretty_color);
	knob_on_style1.body.radius = LV_RADIUS_CIRCLE;				/* 圆形 */
	knob_on_style1.body.shadow.width = 4;						/* 阴影宽度 */
	knob_on_style1.body.shadow.type = LV_SHADOW_BOTTOM;			/* 底部阴影 */
	knob_on_style1.body.main_color = LV_COLOR_RED;				/* 主色 */

	/* 创建sw控件并设置样式 */
	lv_obj_t *sw1 = lv_sw_create(scr, NULL);					/* 创建sw控件 */
	lv_sw_set_style(sw1, LV_SW_STYLE_BG, &bg_style);			/* 设置背景样式 */
	lv_sw_set_style(sw1, LV_SW_STYLE_INDIC, &indic_style);		/* 填充样式 */
	lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_ON, &knob_on_style1);	/* 开关打开的样式 */
	lv_sw_set_style(sw1, LV_SW_STYLE_KNOB_OFF, &knob_off_style);/* 开关关闭的样式 */
	lv_obj_set_size(sw1, 120, 50);								/* 设置尺寸 */
	lv_obj_align(sw1, NULL, LV_ALIGN_CENTER, 0, -100);			/* 设置位置 */
	lv_obj_t *label_sw1 = lv_label_create(scr, NULL);			/* 创建label控件 */
	lv_label_set_text(label_sw1, "RED");						/* 设置文本 */
	lv_obj_align(label_sw1, sw1, LV_ALIGN_IN_LEFT_MID, -50, 0);	/* 设置位置 */
	lv_obj_set_event_cb(sw1, sw1_event_cb);						/* 为sw控件设置事件回调函数 */


	lv_style_copy(&knob_on_style2, &knob_on_style1);			/* 复制样式的属性 */
	knob_on_style2.body.main_color = lv_color_hex(0x00ff00);	/* 重设主颜色 */
	lv_obj_t *sw2 = lv_sw_create(scr, sw1);						/* 创建sw控件,从sw1复制属性 */
	lv_sw_set_style(sw2, LV_SW_STYLE_KNOB_ON, &knob_on_style2);	/* 重新设置开关打开的样式 */
	lv_obj_align(sw2, NULL, LV_ALIGN_CENTER, 0, 0);				/* 设置位置 */
	lv_obj_t *label_sw2 = lv_label_create(scr, NULL);			/* 创建label控件 */
	lv_label_set_text(label_sw2, "GREEN");						/* 设置文本 */
	lv_obj_align(label_sw2, sw2, LV_ALIGN_IN_LEFT_MID, -50, 0);	/* 设置位置 */
	lv_obj_set_event_cb(sw2, sw2_event_cb);						/* 设置事件回调函数 */


	lv_style_copy(&knob_on_style3, &knob_on_style2);			/* 复制样式的属性 */
	knob_on_style3.body.main_color = LV_COLOR_BLUE;				/* 重设主颜色 */
	lv_obj_t *sw3 = lv_sw_create(scr, sw1);						/* 创建sw控件,从sw1复制属性 */
	lv_sw_set_style(sw3, LV_SW_STYLE_KNOB_ON, &knob_on_style3);	/* 重新设置开关打开的样式 */
	lv_obj_align(sw3, NULL, LV_ALIGN_CENTER, 0, 100);			/* 设置位置 */
	lv_obj_t *label_sw3 = lv_label_create(scr, NULL);			/* 创建label控件 */
	lv_label_set_text(label_sw3, "BLUE");						/* 设置文本 */
	lv_obj_align(label_sw3, sw3, LV_ALIGN_IN_LEFT_MID, -50, 0);	/* 设置位置 */
	lv_obj_set_event_cb(sw3, sw3_event_cb);						/* 设置事件回调函数 */

}






/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


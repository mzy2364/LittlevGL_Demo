/*
*******************************************************************************************************
*
* 文件名称 : app_led.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : LED应用
*
*******************************************************************************************************
*/

/* 头文件 -----------------------------------------------------------*/
#include "gui_user.h"

static lv_style_t style_led;
static lv_obj_t *led;

static void sw1_event_cb(lv_obj_t * obj, lv_event_t event);
static void sw2_event_cb(lv_obj_t * obj, lv_event_t event);
static void sw3_event_cb(lv_obj_t * obj, lv_event_t event);


static void btn_back_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_RELEASED)
	{
		/* 退出窗口 */
		lv_obj_del(lv_obj_get_parent(obj));
	}
}





lv_obj_t * app_led_create(void *user_data)
{
	(void)user_data;

	static lv_style_t style_btn_back;
	static lv_style_t style_label_back;
	static lv_style_t style_label_title;
	static lv_style_t style_bg;

	lv_style_copy(&style_btn_back, &lv_style_transp);
	lv_style_copy(&style_bg, &lv_style_scr);
	lv_style_copy(&style_label_title, &lv_style_scr);
	lv_style_copy(&style_label_back, &lv_style_transp);
	style_label_back.text.font = &lv_font_roboto_28;
	style_label_back.text.color = LV_COLOR_WHITE;
	style_bg.body.main_color = lv_color_hex(0x32323a);
	style_bg.body.grad_color = lv_color_hex(0x32323a);

	lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_style(obj,&style_bg);

	lv_obj_t *btn_back = lv_btn_create(obj,NULL);
	lv_obj_set_size(btn_back,100,60);
	lv_obj_set_event_cb(btn_back, btn_back_event_cb);
	lv_btn_set_style(btn_back, LV_BTN_STYLE_REL, &style_btn_back);
	lv_btn_set_style(btn_back, LV_BTN_STYLE_PR, &style_btn_back);

	lv_obj_t *label_back = lv_label_create(obj, NULL);
	lv_label_set_style(label_back, LV_LABEL_STYLE_MAIN, &style_label_back);
	lv_label_set_text(label_back,LV_SYMBOL_LEFT);
	//lv_obj_set_pos(label_back,20,20);
	lv_obj_align(label_back,btn_back,LV_ALIGN_IN_LEFT_MID,20,0);
	

	lv_obj_t *label_title = lv_label_create(obj, NULL);
	style_label_title.text.color = LV_COLOR_WHITE;
	style_label_title.text.font = &lv_font_roboto_28;
	lv_label_set_style(label_title, LV_LABEL_STYLE_MAIN, &style_label_title);
	lv_label_set_text(label_title, "LED");
	lv_obj_align(label_title, obj, LV_ALIGN_IN_TOP_MID, 0, 16);

	
	led = lv_led_create(obj,NULL);
	lv_obj_align(led, obj, LV_ALIGN_IN_TOP_MID, 0, 100);
	lv_style_copy(&style_led,lv_led_get_style(led,LV_LED_STYLE_MAIN));
	style_led.body.main_color = LV_COLOR_BLACK;
	style_led.body.grad_color = LV_COLOR_BLACK;
	lv_led_set_style(led, LV_LED_STYLE_MAIN, &style_led);

	lv_obj_t *sw_red = lv_sw_create(obj,NULL);
	lv_obj_align(sw_red,obj,LV_ALIGN_IN_TOP_MID,0,200);
	lv_obj_set_event_cb(sw_red, sw1_event_cb);
	lv_obj_t *label_red = lv_label_create(obj,NULL);
	lv_label_set_style(label_red, LV_LABEL_STYLE_MAIN, &style_label_title);
	lv_label_set_text(label_red, "RED:");
	lv_obj_align(label_red, sw_red,LV_ALIGN_OUT_LEFT_MID,-10,0);


	lv_obj_t *sw_green = lv_sw_create(obj, NULL);
	lv_obj_align(sw_green, obj, LV_ALIGN_IN_TOP_MID, 0, 300);
	lv_obj_set_event_cb(sw_green, sw2_event_cb);
	lv_obj_t *label_green = lv_label_create(obj, NULL);
	lv_label_set_style(label_green, LV_LABEL_STYLE_MAIN, &style_label_title);
	lv_label_set_text(label_green, "GREEN:");
	lv_obj_align(label_green, sw_green, LV_ALIGN_OUT_LEFT_MID, -10, 0);

	lv_obj_t *sw_blue = lv_sw_create(obj, NULL);
	lv_obj_align(sw_blue, obj, LV_ALIGN_IN_TOP_MID, 0, 400);
	lv_obj_set_event_cb(sw_blue, sw3_event_cb);
	lv_obj_t *label_blue = lv_label_create(obj, NULL);
	lv_label_set_style(label_blue, LV_LABEL_STYLE_MAIN, &style_label_title);
	lv_label_set_text(label_blue, "BLUE:");
	lv_obj_align(label_blue, sw_blue, LV_ALIGN_OUT_LEFT_MID, -10, 0);


	return obj;
}



static void sw1_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		color = gui_hal_led_get_current_color();
		(lv_sw_get_state(obj) ? (color |= 0X000000FF) : (color &= ~(0X000000FF)));
		gui_hal_led_set_color(color);
		style_led.body.main_color = lv_color_hex(color_change(color));
		style_led.body.grad_color = lv_color_hex(color_change(color));
		lv_led_set_style(led, LV_LED_STYLE_MAIN, &style_led);
	}
}

static void sw2_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		color = gui_hal_led_get_current_color();
		(lv_sw_get_state(obj) ? (color |= 0X0000FF00) : (color &= ~(0X0000FF00)));
		gui_hal_led_set_color(color);
		style_led.body.main_color = lv_color_hex(color_change(color));
		style_led.body.grad_color = lv_color_hex(color_change(color));
		lv_led_set_style(led, LV_LED_STYLE_MAIN, &style_led);
	}
}

static void sw3_event_cb(lv_obj_t * obj, lv_event_t event)
{
	uint32_t color = 0;
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		color = gui_hal_led_get_current_color();
		(lv_sw_get_state(obj) ? (color |= 0X00FF0000) : (color &= ~(0X00FF0000)));
		gui_hal_led_set_color(color);
		style_led.body.main_color = lv_color_hex(color_change(color));
		style_led.body.grad_color = lv_color_hex(color_change(color));
		lv_led_set_style(led, LV_LED_STYLE_MAIN, &style_led);
	}
}


/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/
































/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

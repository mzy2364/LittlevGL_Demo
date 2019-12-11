/*
*******************************************************************************************************
*
* 文件名称 : app_wechat.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 微信应用
*
*******************************************************************************************************
*/

#include "gui_user.h"


static void btn_back_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_RELEASED)
	{
		/* 退出窗口 */
		lv_obj_del(lv_obj_get_parent(obj));
	}
}


lv_obj_t * app_wechat_create(void *user_data)
{
	(void)user_data;

	static lv_style_t style_btn_back;
	static lv_style_t style_label_back;
	static lv_style_t style_label_title;
	static lv_style_t style_bg;
	static lv_style_t style_list;

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
	lv_obj_set_style(obj, &style_bg);

	lv_obj_t *btn_back = lv_btn_create(obj, NULL);
	lv_obj_set_size(btn_back, 100, 60);
	lv_obj_set_event_cb(btn_back, btn_back_event_cb);
	lv_btn_set_style(btn_back, LV_BTN_STYLE_REL, &style_btn_back);
	lv_btn_set_style(btn_back, LV_BTN_STYLE_PR, &style_btn_back);

	lv_obj_t *label_back = lv_label_create(obj, NULL);
	lv_label_set_style(label_back, LV_LABEL_STYLE_MAIN, &style_label_back);
	lv_label_set_text(label_back, LV_SYMBOL_LEFT);
	//lv_obj_set_pos(label_back,20,20);
	lv_obj_align(label_back, btn_back, LV_ALIGN_IN_LEFT_MID, 20, 0);


	lv_obj_t *label_title = lv_label_create(obj, NULL);
	style_label_title.text.color = LV_COLOR_WHITE;
	style_label_title.text.font = &lv_font_roboto_28;
	lv_label_set_style(label_title, LV_LABEL_STYLE_MAIN, &style_label_title);
	lv_label_set_text(label_title, "WECHAT");
	lv_obj_align(label_title, obj, LV_ALIGN_IN_TOP_MID, 0, 16);


	lv_obj_t *tabview;
	tabview = lv_tabview_create(obj, NULL);
	lv_obj_set_pos(tabview, 0, 60);
	lv_obj_set_size(tabview, LV_HOR_RES, 740);
	lv_tabview_set_btns_pos(tabview, LV_TABVIEW_BTNS_POS_BOTTOM);
	

	lv_obj_t *page_chats = lv_tabview_add_tab(tabview, "Chats");
	lv_obj_t *page_contacts = lv_tabview_add_tab(tabview, "Contacts");
	lv_obj_t *page_discover = lv_tabview_add_tab(tabview, "Discover");
	lv_obj_t *page_me = lv_tabview_add_tab(tabview, "Me");



	lv_obj_t *list = lv_list_create(page_chats, NULL);
	//lv_obj_set_pos(list, 0, 60);
	lv_obj_set_size(list, LV_HOR_RES, 740);
	lv_style_copy(&style_list, lv_list_get_style(list,LV_LIST_STYLE_BG));
	style_list.body.radius = 0;
	style_list.body.border.width = 0;
	style_list.body.padding.top = 0;


	lv_list_set_style(list, LV_LIST_STYLE_BG, &style_list);

	return obj;
}











/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


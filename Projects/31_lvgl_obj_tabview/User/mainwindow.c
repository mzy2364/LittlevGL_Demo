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

lv_img_dsc_t img_desktop;

lv_img_dsc_t icon_star;
lv_img_dsc_t icon_qzone;
lv_img_dsc_t icon_qq;
lv_img_dsc_t icon_airbnb;
lv_img_dsc_t icon_amazon;
lv_img_dsc_t icon_wechat;
lv_img_dsc_t icon_google;
lv_img_dsc_t icon_windows;
lv_img_dsc_t icon_facebook;
lv_img_dsc_t icon_baidu;
lv_img_dsc_t icon_android;




typedef struct
{
	lv_img_dsc_t *icon_img;
	const char *text_en;
	const char *text_cn;
	const char *icon_fname;


}icon_item;

static const icon_item icon_desktop_page1[] =
{
	{ &icon_star, "Star", "星光 ", "0:/lvgl/star.bin" },
	{ &icon_qzone, "Qzone", "QQ空间 ", "0:/lvgl/qzone.bin" },
	{ &icon_qq, "QQ", "QQ", "0:/lvgl/tencent_qq.bin" },
	{ &icon_airbnb, "Airbnb", "爱彼 ", "0:/lvgl/airbnb.bin" },
	{ &icon_amazon, "Amazon", "亚马 ", "0:/lvgl/amazon.bin" },
	{ &icon_wechat, "Wechat", "微信 ", "0:/lvgl/wechat.bin" },
	{ &icon_google, "Google", "谷歌 ", "0:/lvgl/google.bin" },
	{ &icon_windows, "Windows", "窗口 ", "0:/lvgl/windows.bin" },
	{ &icon_facebook, "Facebook", "脸书 ", "0:/lvgl/facebook.bin" },
	{ &icon_baidu, "Baidu", "百度 ", "0:/lvgl/baidu.bin" },
	{ &icon_android, "Android", "安卓 ", "0:/lvgl/android.bin" },
};

static const icon_item icon_desktop_page2[] =
{
	{ &icon_amazon, "Amazon", "亚马 ", "0:/lvgl/amazon.bin" },
	{ &icon_wechat, "Wechat", "微信 ", "0:/lvgl/wechat.bin" },
	{ &icon_google, "Google", "谷歌 ", "0:/lvgl/google.bin" },
	{ &icon_windows, "Windows", "窗口 ", "0:/lvgl/windows.bin" },
	{ &icon_facebook, "Facebook", "脸书 ", "0:/lvgl/facebook.bin" },
	{ &icon_baidu, "Baidu", "百度 ", "0:/lvgl/baidu.bin" },
	{ &icon_android, "Android", "安卓 ", "0:/lvgl/android.bin" },
};

static const icon_item icon_desktop_page3[] =
{
	{ &icon_star, "Star", "星光 ", "0:/lvgl/star.bin" },
	{ &icon_qzone, "Qzone", "QQ空间 ", "0:/lvgl/qzone.bin" },
	{ &icon_qq, "QQ", "QQ", "0:/lvgl/tencent_qq.bin" },
	{ &icon_wechat, "Wechat", "微信 ", "0:/lvgl/wechat.bin" },
	{ &icon_google, "Google", "谷歌 ", "0:/lvgl/google.bin" },
	{ &icon_windows, "Windows", "窗口 ", "0:/lvgl/windows.bin" },
	{ &icon_facebook, "Facebook", "脸书 ", "0:/lvgl/facebook.bin" },

};


void lv_obj_tabview_desktop_test(void);
void lv_obj_tabview_test(void);
void lv_load_icon_desktop(icon_item *item, uint16_t icon_num);
void lv_create_icon_desktop(lv_obj_t *parent, icon_item *item, uint16_t icon_num);




/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */

	/* 加载图片 */
	lv_load_img_bin_from_file(&img_desktop, "0:/lvgl/bg02.bin");

	lv_load_icon_desktop(icon_desktop_page1, sizeof(icon_desktop_page1) / sizeof(icon_desktop_page1[0]));
	
	//lv_obj_tabview_desktop_test();				/* 多页控件测试 */

	lv_obj_tabview_test();				/* 多页控件测试 */


	
}




/**
* @brief 控件测试函数
* @param None
* @retval	None
*/
void lv_obj_tabview_desktop_test(void)
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

	lv_obj_t *img_bg = lv_img_create(scr, NULL);
	lv_img_set_src(img_bg, &img_desktop);

	lv_obj_t *tabview = lv_tabview_create(scr, NULL);
	//lv_tabview_set_btns_hidden(tabview, true);
	lv_style_copy(&style_tabview, lv_tabview_get_style(tabview, LV_TABVIEW_STYLE_BG));
	style_tabview.body.opa = 0;
	lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &style_tabview);
	lv_tabview_set_anim_time(tabview, 10);



	lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
	lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
	lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");


	lv_create_icon_desktop(tab1, icon_desktop_page1, sizeof(icon_desktop_page1) / sizeof(icon_desktop_page1[0]));
	lv_create_icon_desktop(tab2, icon_desktop_page2, sizeof(icon_desktop_page2) / sizeof(icon_desktop_page2[0]));
	lv_create_icon_desktop(tab3, icon_desktop_page3, sizeof(icon_desktop_page3) / sizeof(icon_desktop_page3[0]));

	//lv_style_copy(&style_label, &lv_style_pretty);
	//style_label.text.font = style_cn_16.text.font;
	//style_label.body.opa = 150;
	//style_label.body.border.width = 0;

	//lv_obj_t * label = lv_label_create(tab1, NULL);
	//lv_label_set_body_draw(label, true);
	//lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	//lv_label_set_text(label, "This the first tab");

	//label = lv_label_create(tab2, NULL);
	//lv_label_set_body_draw(label, true);
	//lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	//lv_label_set_text(label, "Second tab");

	//label = lv_label_create(tab3, NULL);
	//lv_label_set_body_draw(label, true);
	//lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	//lv_label_set_text(label, "Third tab");


}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_tabview_test(void)
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

	lv_obj_t *img_bg = lv_img_create(scr, NULL);						/* 创建背景 */
	lv_img_set_src(img_bg, &img_desktop);
	

	lv_obj_t *tabview = lv_tabview_create(scr, NULL);					/* 创建tabview控件 */
	//lv_tabview_set_btns_hidden(tabview, true);						/* 隐藏导航栏目 */
	lv_style_copy(&style_tabview,lv_tabview_get_style(tabview,LV_TABVIEW_STYLE_BG));
	style_tabview.body.opa = 0;											/* 设置全透明 */
	lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &style_tabview);
	lv_tabview_set_anim_time(tabview, 10);								/* 设置动画时间 */


	/* 添加3个页面 */
	lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
	lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
	lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");


	/* 在页面上添加控件 */
	lv_style_copy(&style_label, &lv_style_pretty);
	style_label.text.font = style_cn_16.text.font;
	style_label.body.opa = 150;
	style_label.body.border.width = 0;

	lv_obj_t * label = lv_label_create(tab1, NULL);
	lv_label_set_body_draw(label, true);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_text(label, "This the first tab");

	label = lv_label_create(tab2, NULL);
	lv_label_set_body_draw(label, true);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_text(label, "Second tab");

	label = lv_label_create(tab3, NULL);
	lv_label_set_body_draw(label, true);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_text(label, "Third tab");


}


/**
  * @brief 加载图标
  * @param None
  * @retval	None
  */
void lv_load_icon_desktop(icon_item *item, uint16_t icon_num)
{
	uint16_t i = 0;
	for (i = 0; i < icon_num; ++i)
	{
		lv_load_img_bin_from_file(item[i].icon_img, item[i].icon_fname);
	}
}


/**
  * @brief 创建icon
  * @param None
  * @retval	None
  */
void lv_create_icon_desktop(lv_obj_t *parent, icon_item *item, uint16_t icon_num)
{

	uint16_t i = 0;
	uint16_t x_pos = 0, y_pos = 0;

	static lv_style_t style_label;
	lv_style_copy(&style_label, &lv_style_pretty);
	style_label.text.font = style_cn_16.text.font;

	x_pos = 32;
	y_pos = 40;

	for (i = 0; i < icon_num; ++i)
	{
		x_pos = ((i % 4) * 120) + 10;
		y_pos = ((i / 4) * 120) + 32;

		lv_obj_t *btn = lv_btn_create(parent, NULL);
		lv_obj_t *image = lv_img_create(btn, NULL);
		lv_obj_t *label = lv_label_create(btn, NULL);

		lv_obj_set_pos(btn, x_pos, y_pos);
		lv_obj_set_size(btn, 100, 120);
		lv_btn_set_style(btn, LV_BTN_STYLE_REL, &lv_style_transp);
		lv_btn_set_style(btn, LV_BTN_STYLE_PR, &lv_style_btn_ina);


		lv_img_set_src(image, item[i].icon_img);

		//style_label.text.color = LV_COLOR_WHITE;
		//style_label.body.main_color = LV_COLOR_BLACK;
		//style_label.body.grad_color = LV_COLOR_BLACK;
		style_label.body.opa = 150;
		style_label.body.border.width = 0;

		lv_label_set_body_draw(label, true);

		lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
		lv_label_set_text(label, item[i].text_cn);
		lv_obj_align(label, btn, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	}

}



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


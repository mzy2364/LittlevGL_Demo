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



void lv_obj_tabview_desktop_test(void);
void lv_obj_tabview_test(void);





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



	lv_obj_tabview_test();				/* 多页控件测试 */


	
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

	//lv_theme_set_current(lv_theme_material_init(210, NULL));			/* 设置主题 */

	lv_obj_t *img_bg = lv_img_create(scr, NULL);						/* 创建背景 */
	lv_img_set_src(img_bg, &img_desktop);
	

	lv_obj_t *tabview = lv_tabview_create(scr, NULL);					/* 创建tabview控件 */
	//lv_tabview_set_btns_hidden(tabview, true);						/* 隐藏导航栏目 */
	//lv_tabview_set_btns_pos(tabview, LV_TABVIEW_BTNS_POS_RIGHT);			/* 设置导航栏位置 */
	lv_style_copy(&style_tabview,lv_tabview_get_style(tabview,LV_TABVIEW_STYLE_BG));
	style_tabview.body.opa = 0;											/* 设置全透明 */
	lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &style_tabview);
	lv_tabview_set_anim_time(tabview, 100);								/* 设置动画时间 */


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





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


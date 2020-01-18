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


void lv_obj_tileview_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */

	lv_obj_tileview_test();				/* 平铺控件测试 */


	
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_tileview_test(void)
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


	static lv_point_t valid_pos[] = { { 0, 0 }, { 0, 1 }, { 1, 1 } };
	lv_obj_t *tileview;
	tileview = lv_tileview_create(scr, NULL);
	lv_tileview_set_valid_positions(tileview, valid_pos, 3);
	lv_tileview_set_edge_flash(tileview, true);

	lv_obj_t * tile1 = lv_obj_create(tileview, NULL);
	lv_obj_set_size(tile1, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_style(tile1, &lv_style_pretty);
	lv_tileview_add_element(tileview, tile1);

	/* 向页面一添加一个label */
	lv_obj_t * label = lv_label_create(tile1, NULL);
	lv_label_set_text(label, "Tile 1");
	lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

	/* 向页面二添加一个list */
	lv_obj_t * list = lv_list_create(tileview, NULL);
	lv_obj_set_size(list, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_pos(list, 0, LV_VER_RES);
	lv_list_set_scroll_propagation(list, true);
	lv_list_set_sb_mode(list, LV_SB_MODE_OFF);
	lv_tileview_add_element(tileview, list);

	lv_obj_t * list_btn;
	list_btn = lv_list_add_btn(list, NULL, "One");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Two");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Three");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Four");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Five");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Six");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Seven");
	lv_tileview_add_element(tileview, list_btn);

	list_btn = lv_list_add_btn(list, NULL, "Eight");
	lv_tileview_add_element(tileview, list_btn);

	/* 向页面三添加一个按钮 */
	lv_obj_t * tile3 = lv_obj_create(tileview, tile1);
	lv_obj_set_pos(tile3, LV_HOR_RES, LV_VER_RES);
	lv_tileview_add_element(tileview, tile3);

	lv_obj_t * btn = lv_btn_create(tile3, NULL);
	lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);

	label = lv_label_create(btn, NULL);
	lv_label_set_text(label, "Button");


}

/*
git remote add origin git@gitee.com:mzy2364/LittlevGL_Demo.git
*/



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


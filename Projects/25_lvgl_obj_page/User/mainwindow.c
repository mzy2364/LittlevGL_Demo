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

static const uint8_t text[] = {
	"\xe9\x95\xbf\xe6\x81\xa8\xe6\xad\x8c\n\
	\xe6\xb1\x89\xe7\x9a\x87\xe9\x87\x8d\xe8\x89\xb2\xe6\x80\x9d\xe5\x80\xbe\xe5\x9b\xbd\xef\xbc\x8c\xe5\xbe\xa1\xe5\xae\x87\xe5\xa4\x9a\xe5\xb9\xb4\xe6\xb1\x82\xe4\xb8\x8d\xe5\xbe\x97\xe3\x80\x82\n\
	\xe6\x9d\xa8\xe5\xae\xb6\xe6\x9c\x89\xe5\xa5\xb3\xe5\x88\x9d\xe9\x95\xbf\xe6\x88\x90\xef\xbc\x8c\xe5\x85\xbb\xe5\x9c\xa8\xe6\xb7\xb1\xe9\x97\xba\xe4\xba\xba\xe6\x9c\xaa\xe8\xaf\x86\xe3\x80\x82\n\
	\xe5\xa4\xa9\xe7\x94\x9f\xe4\xb8\xbd\xe8\xb4\xa8\xe9\x9a\xbe\xe8\x87\xaa\xe5\xbc\x83\xef\xbc\x8c\xe4\xb8\x80\xe6\x9c\x9d\xe9\x80\x89\xe5\x9c\xa8\xe5\x90\x9b\xe7\x8e\x8b\xe4\xbe\xa7\xe3\x80\x82\n"
};


static lv_img_dsc_t img_bg;

void lv_obj_page_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_load_img_bin_from_file(&img_bg,"0:/lvgl/bg01.bin");

	lv_obj_page_test();					/* 页面控件测试 */
	
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_page_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_label;
	static lv_style_t style_page_edge_flash;


	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_style_copy(&style_page_edge_flash, &lv_style_plain_color);
	style_page_edge_flash.body.radius = 100;
	style_page_edge_flash.body.opa = LV_OPA_30;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_obj_t * page1 = lv_page_create(scr, NULL);			/* 创建page控件 */
	lv_obj_set_size(page1, LV_HOR_RES, LV_VER_RES);						/* 设置大小 */
	lv_obj_align(page1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);	/* 设置位置 */
	lv_page_set_edge_flash(page1, true);					/* 在滑到边缘的时候有个圆圈的特效 */
	lv_page_set_style(page1, LV_PAGE_STYLE_EDGE_FLASH, &style_page_edge_flash);		/* 设置边缘闪烁部分的样式 */

	//printf("width:%d height:%d\n", lv_page_get_scrl_width(page1), lv_page_get_scrl_height(page1));
	//printf("width:%d height:%d\n", lv_page_get_fit_width(page1), lv_page_get_fit_height(page1));

	//lv_page_set_scrl_fit(page1, LV_FIT_NONE);

	/* 在page控件上添加子对象 */
	lv_obj_t * label_page1 = lv_label_create(page1, NULL);
	lv_style_copy(&style_label, lv_label_get_style(label_page1, LV_LABEL_STYLE_MAIN));	
	style_label.text.font = style_cn_16.text.font;
	lv_label_set_style(label_page1, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_long_mode(label_page1, LV_LABEL_LONG_BREAK);
	lv_obj_set_width(label_page1, lv_page_get_fit_width(page1));
	lv_label_set_text(label_page1, text);

	lv_obj_t *btn = lv_btn_create(page1, NULL);
	lv_obj_align(btn,label_page1,LV_ALIGN_OUT_BOTTOM_MID,0,0);
	lv_page_glue_obj(btn, true);

	lv_obj_t *btnm = lv_btnm_create(page1, NULL);
	lv_obj_align(btnm, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_page_glue_obj(btnm, true);

	lv_obj_t *cont = lv_cont_create(page1, NULL);
	lv_obj_align(cont, btnm, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_page_glue_obj(cont, true);

	lv_obj_t *img = lv_img_create(page1, NULL);
	lv_obj_align(img, cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_img_set_src(img, &img_bg);
	

	//lv_page_focus(page1, img, LV_ANIM_ON);	/* 聚焦控件 */

	lv_page_scroll_hor(page1, 50); /* 水平滚动页面 */

	lv_page_scroll_ver(page1, -50);	/* 垂直滚动页面 */

	/* 设置布局,设置后子对象的对齐等属性可能失效 */
	lv_page_set_scrl_layout(page1, LV_LAYOUT_CENTER);

}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


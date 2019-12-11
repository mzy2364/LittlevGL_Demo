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

lv_img_dsc_t file_img;
lv_img_dsc_t directory_img;
lv_img_dsc_t close_img;
lv_img_dsc_t edit_img;
lv_img_dsc_t save_img;



void lv_obj_list_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */

	lv_load_img_bin_from_file(&file_img,"0:/lvgl/file_img.bin");
	lv_load_img_bin_from_file(&directory_img, "0:/lvgl/directory_img.bin");
	lv_load_img_bin_from_file(&close_img, "0:/lvgl/close_img.bin");
	lv_load_img_bin_from_file(&edit_img, "0:/lvgl/edit_img.bin");
	lv_load_img_bin_from_file(&save_img, "0:/lvgl/save_img.bin");
	
	lv_obj_list_test();					/* 列表控件测试 */
	
}



/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_list_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_GRAY;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;


	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_obj_t *list = lv_list_create(scr, NULL);				/* 创建list控件 */
	lv_obj_set_size(list, 160, 200);						/* 设置尺寸 */
	lv_obj_align(list, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);	/* 设置位置 */
	lv_list_set_edge_flash(list, true);						/* 当滑动到顶部或者底部的时候,有个圆圈的效果 */


	/* 给list添加按钮,直接添加中文不能显示,需要添加按钮的时候文本设置为NULL,然后添加label到按钮 */
	/* 图标用库自带的或者自己创建的都可以 */
	lv_obj_t *btn_list;
	lv_obj_t *label;

	btn_list = lv_list_add_btn(list, LV_SYMBOL_FILE, NULL);
	label = lv_label_create(btn_list,NULL);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_cn_16);
	lv_label_set_text(label,"新建");

	btn_list = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, NULL);
	label = lv_label_create(btn_list, NULL);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_cn_16);
	lv_label_set_text(label, "打开");

	btn_list = lv_list_add_btn(list, &close_img, NULL);
	label = lv_label_create(btn_list, NULL);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_cn_16);
	lv_label_set_text(label, "关闭");

	btn_list = lv_list_add_btn(list, &edit_img, NULL);
	label = lv_label_create(btn_list, NULL);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_cn_16);
	lv_label_set_text(label, "编辑");

	btn_list = lv_list_add_btn(list, &save_img, NULL);
	label = lv_label_create(btn_list, NULL);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_cn_16);
	lv_label_set_text(label, "保存");

}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


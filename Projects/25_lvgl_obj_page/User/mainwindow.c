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

	lv_load_img_bin_from_file(&file_img,"0:/lvgl/file_img.bin");
	lv_load_img_bin_from_file(&directory_img, "0:/lvgl/directory_img.bin");
	lv_load_img_bin_from_file(&close_img, "0:/lvgl/close_img.bin");
	lv_load_img_bin_from_file(&edit_img, "0:/lvgl/edit_img.bin");
	lv_load_img_bin_from_file(&save_img, "0:/lvgl/save_img.bin");
	
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
	static lv_style_t style_btn_rel;
	static lv_style_t style_btn_pr;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;


	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_obj_t * page1 = lv_page_create(scr, NULL);			/* 创建page控件 */
	lv_obj_set_size(page1, 200, 200);						/* 设置大小 */
	lv_obj_align(page1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);	/* 设置位置 */
	lv_page_set_edge_flash(page1, true);					/* 在滑到顶部或者底部的时候有个圆圈的特效 */

	lv_obj_t * label_page1 = lv_label_create(page1, NULL);	/* 在page上面创建一个label */
	
	
	lv_style_copy(&style_label, lv_label_get_style(label_page1, LV_LABEL_STYLE_MAIN));	
	style_label.text.font = style_cn_16.text.font;
	lv_label_set_style(label_page1, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_long_mode(label_page1, LV_LABEL_LONG_BREAK);
	lv_obj_set_width(label_page1, lv_page_get_fit_width(page1));

	lv_label_set_text(label_page1, "全面建成小康社会,是“两个一百年”奋斗目标的第一个百年奋斗目标,是我们党向人民,向历史作出的庄严承诺,是近十四亿中国人民的共同期盼.实现这个宏伟目标，标志着我们向全面建成社会主义现代化强国迈出了至关重要的一步。现在到了一鼓作气、决战决胜的历史时刻，要坚定信心、攻坚克难，确保到二〇二〇年全面建成小康社会。 ");

	

}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


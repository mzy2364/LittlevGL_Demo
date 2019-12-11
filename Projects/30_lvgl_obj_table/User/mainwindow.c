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



void lv_obj_table_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_table_test();				/* 表格控件测试 */
	
}




/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_table_test(void)
{

	/* 新建个样式 */
	static lv_style_t style_desktop;

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


	lv_obj_t * table = lv_table_create(scr, NULL);
	lv_table_set_col_cnt(table, 2);
	lv_table_set_row_cnt(table, 7);
	lv_table_set_col_width(table, 0, 100);
	lv_table_set_col_width(table, 1, 150);
	lv_table_set_cell_merge_right(table, 0, 0, true);

	lv_table_set_cell_align(table, 0, 0, LV_LABEL_ALIGN_CENTER);

	lv_table_set_cell_type(table, 0, 0, 2);
	lv_table_set_cell_type(table, 0, 1, 2);

	lv_table_set_cell_value(table, 0, 0, "Bison-Board");
	lv_table_set_cell_value(table, 1, 0, "MCU");
	lv_table_set_cell_value(table, 2, 0, "RAM");
	lv_table_set_cell_value(table, 3, 0, "FLASH");
	lv_table_set_cell_value(table, 4, 0, "DISPLAY");
	lv_table_set_cell_value(table, 5, 0, "USB");
	lv_table_set_cell_value(table, 6, 0, "WIRELESS");



	lv_table_set_cell_value(table, 1, 1, "STM32F429IGT6");
	lv_table_set_cell_value(table, 2, 1, "32M SDRAM");
	lv_table_set_cell_value(table, 3, 1, "16M SPI-FLASH");
	lv_table_set_cell_value(table, 4, 1, "4.3 800*480 RGB565");
	lv_table_set_cell_value(table, 5, 1, "TYPE-C*2");
	lv_table_set_cell_value(table, 6, 1, "WIFI+2.4G");

	lv_obj_align(table, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


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



void lv_font_cn_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	
	
	lv_font_cn_test();					/* 中文测试 */
	
}


/**
  * @brief 中文显示测试函数
  * @param None
  * @retval	None
  */
void lv_font_cn_test(void)
{
	
	/* 设置字体颜色 */
	style_cn_12.text.color = LV_COLOR_BLACK;
	style_cn_16.text.color = LV_COLOR_BLACK;
	style_cn_24.text.color = LV_COLOR_BLACK;
	style_cn_32.text.color = LV_COLOR_BLACK;
	
	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	
	
	lv_obj_t *label1 = lv_label_create(scr,NULL);			/* 创建label控件 */
	lv_obj_set_style(label1,&style_cn_12);					/* 为控件设置新的 style */
	lv_obj_set_pos(label1,0,0);								/* 设置控件的坐标 */
	lv_label_set_text(label1,"中文字体12号");				/* 设置文字 */
	lv_obj_align(label1,NULL,LV_ALIGN_IN_TOP_MID,0,100);	/* 设置控件的对齐方式-相对坐标 */
	
	lv_obj_t *label2 = lv_label_create(scr,NULL);			/* 创建label控件 */
	lv_obj_set_style(label2,&style_cn_16);					/* 为控件设置新的 style */
	lv_obj_set_pos(label2,0,0);								/* 设置控件的坐标 */
	lv_label_set_text(label2,"中文字体16号");				/* 设置文字 */
	lv_obj_align(label2,label1,LV_ALIGN_OUT_BOTTOM_MID,0,10);	/* 设置控件的对齐方式-相对坐标 */

	lv_obj_t *label3 = lv_label_create(scr,NULL);			/* 创建label控件 */
	lv_obj_set_style(label3,&style_cn_24);					/* 为控件设置新的 style */
	lv_obj_set_pos(label3,0,0);								/* 设置控件的坐标 */
	lv_label_set_text(label3,"中文字体24号");				/* 设置文字 */
	lv_obj_align(label3,label2,LV_ALIGN_OUT_BOTTOM_MID,0,10);	/* 设置控件的对齐方式-相对坐标 */
	
	
	lv_obj_t *label4 = lv_label_create(scr,NULL);			/* 创建label控件 */
	lv_obj_set_style(label4,&style_cn_32);					/* 为控件设置新的 style */
	lv_obj_set_pos(label4,0,0);								/* 设置控件的坐标 */
	lv_label_set_text(label4,"中文字体32号");				/* 设置文字 */
	lv_obj_align(label4,label3,LV_ALIGN_OUT_BOTTOM_MID,0,10);	/* 设置控件的对齐方式-相对坐标 */

}









/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

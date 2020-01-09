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

/* 引入字体,等同于extern */
LV_FONT_DECLARE(font1)


void lv_font_cn_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_font_cn_test();					/* 中文测试 */
	
}

/**
  * @brief 中文显示测试函数
  * @param None
  * @retval	None
  */
void lv_font_cn_test(void)
{
	
	static lv_style_t style_cn;								/* 定义新的样式,请注意使用 static 或者全局变量 */
	lv_style_copy(&style_cn, &lv_style_pretty_color);		/* 复制style的属性 */
	style_cn.text.font = &font1;						/* 设置新字体 */
	style_cn.text.color = LV_COLOR_BLACK;					/* 设置文字颜色 */
	
	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	
	
	lv_obj_t *label1 = lv_label_create(scr,NULL);			/* 创建label控件 */
	lv_obj_set_style(label1,&style_cn);						/* 为控件设置新的 style */
	lv_obj_set_pos(label1,0,0);								/* 设置控件的坐标 */
	lv_label_set_text(label1,"你好世界");					/* 设置文字 */
	lv_obj_align(label1,NULL,LV_ALIGN_IN_TOP_MID,0,100);	/* 设置控件的对齐方式-相对坐标 */
	
	
}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

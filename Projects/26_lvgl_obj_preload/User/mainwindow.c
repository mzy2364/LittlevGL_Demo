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


void lv_obj_preload_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_preload_test();				/* 加载器控件测试 */
	
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_preload_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_preload;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */


	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;


	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_style_copy(&style_preload, &lv_style_plain);
	style_preload.line.width = 10;							/* 旋转部分线的宽度 */
	style_preload.line.color = lv_color_hex3(0x258);		/* 旋转部分线的颜色 */
	style_preload.body.border.color = lv_color_hex3(0xBBB); /* 背景的颜色 */
	style_preload.body.border.width = 10;					/* 背景的圆圈的宽度 */
	style_preload.body.padding.left = 0;					/* 左边部分填充为0 */

	lv_obj_t * preload = lv_preload_create(scr, NULL);		/* 创建preload控件 */
	lv_obj_set_size(preload, 100, 100);						/* 设置尺寸 */
	lv_obj_align(preload, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);/* 设置位置 */
	lv_preload_set_style(preload, LV_PRELOAD_STYLE_MAIN, &style_preload);	/* 设置样式 */

	lv_preload_set_arc_length(preload, 180);					/* 弧的角度 */
	lv_preload_set_spin_time(preload, 800);					/* 旋转时长 */
	lv_preload_set_type(preload, LV_PRELOAD_TYPE_SPINNING_ARC);	/* 旋转类型 */
	lv_preload_set_dir(preload, LV_PRELOAD_DIR_BACKWARD);		/* 旋转方向 */
}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


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



void lv_obj_label_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	
	lv_obj_label_test();				/* 标签控件测试 */
	
}





/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_label_test(void)
{
	
	/* 为样式重新设置文字颜色 */
	style_cn_12.text.color = LV_COLOR_BLUE;
	style_cn_16.text.color = LV_COLOR_BLUE;
	style_cn_24.text.color = LV_COLOR_BLUE;
	style_cn_32.text.color = LV_COLOR_BLUE;
	
	

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	
	lv_obj_t *label1 = lv_label_create(scr,NULL);					/* 创建label控件 */
	lv_label_set_style(label1,LV_LABEL_STYLE_MAIN,&style_cn_16);	/* 设置为中文字体的style */
	lv_label_set_text(label1,"label控件 ");							/* 设置文字 */
	lv_obj_align(label1,NULL,LV_ALIGN_IN_TOP_MID,0,0);				/* 设置位置 */
	
	
	lv_obj_t *label2 = lv_label_create(scr,NULL);					/* 创建label控件 */
	lv_label_set_style(label2,LV_LABEL_STYLE_MAIN,&style_cn_16);	/* 设置为中文字体的style */
	lv_label_set_text(label2,"换行label控件\n第二行的");				/* 设置文字 */
	lv_obj_align(label2,label1,LV_ALIGN_OUT_BOTTOM_MID,0,0);		/* 设置位置 */
	
	
	lv_obj_t *label3 = lv_label_create(scr,NULL);					/* 创建label控件 */
	lv_label_set_style(label3,LV_LABEL_STYLE_MAIN,&style_cn_16);	/* 设置为中文字体的style */
	lv_label_set_text(label3,"这是一个长文本,会进行滚动显示,跳兔科技,所行不止所想,");	/* 设置长文本 */
	lv_label_set_long_mode(label3,LV_LABEL_LONG_SROLL_CIRC);		/* 设置长文本的模式为循环滚动显示 */
	lv_obj_set_width(label3, 480);									/* 设置label的宽度,注意要放在设置长文本模式后面 */
	lv_obj_align(label3, NULL, LV_ALIGN_CENTER, 0, 0);				/* 设置位置 */

	
	lv_obj_t *label4 = lv_label_create(scr,NULL);					/* 创建label控件 */
	lv_label_set_style(label4,LV_LABEL_STYLE_MAIN,&style_cn_16);	/* 设置为中文字体的style */
	lv_label_set_recolor(label4, true);								/* 允许文字重新着色 */
	lv_label_set_text(label4,"#000080 多种##000000 颜色##6666ff 文本#");	/* 设置不同颜色的文本,注意#号包含以及空格 */
	lv_obj_align(label4,label3,LV_ALIGN_OUT_BOTTOM_MID,0,0);		/* 设置位置 */

	

}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


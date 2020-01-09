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


/* 定义个图片 */
lv_img_dsc_t image_bin1;



void lv_img_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_load_img_bin_from_file(&image_bin1,"0:/lvgl/bg01.bin");	/* 从文件加载 bin 格式的图片到图片变量 */
	
	lv_img_test();						/* 图片测试 */
	
}





/**
  * @brief 图片显示测试函数
  * @param None
  * @retval	None
  */
void lv_img_test(void)
{

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	
	lv_obj_t *image = lv_img_create(scr,NULL);				/* 创建 image 控件 */
	lv_img_set_src(image,&image_bin1);						/* 为控件设置图片 */
	lv_obj_align(image,NULL,LV_ALIGN_IN_TOP_MID,0,0);		/* 设置控件的对齐方式,相对坐标 */
	

	
}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


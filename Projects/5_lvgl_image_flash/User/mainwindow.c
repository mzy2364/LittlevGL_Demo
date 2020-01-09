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


/* 引入图片,相当于extern */
LV_IMG_DECLARE(tiaotu_logo)
LV_IMG_DECLARE(tiaotu)
LV_IMG_DECLARE(wechat_avatar)


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
	
	
	lv_img_test();						/* 图片显示测试 */
	
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
	lv_img_set_src(image,&tiaotu);						/* 为控件设置图片 */
	lv_obj_align(image,NULL,LV_ALIGN_IN_TOP_MID,0,0);		/* 设置控件的对齐方式,相对坐标 */
	
	lv_obj_t *image1 = lv_img_create(scr,NULL);				/* 创建 image 控件 */
	lv_img_set_src(image1,&wechat_avatar);						/* 为控件设置图片 */
	lv_obj_align(image1,NULL,LV_ALIGN_IN_TOP_MID,100,0);		/* 设置控件的对齐方式,相对坐标 */
	
}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

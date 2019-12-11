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







/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{
	
	lv_obj_t * scr = lv_disp_get_scr_act(NULL);
	
	lv_obj_t *label = lv_label_create(scr,NULL);
	
	lv_label_set_text(label,"Hello World!");
	
	lv_obj_align(label,NULL,LV_ALIGN_CENTER,0,0);
	
	
}












/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/



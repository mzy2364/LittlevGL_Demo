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



extern void lv_test_theme_1(lv_theme_t * th);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_test_theme_1(lv_theme_alien_init(210,NULL));
	
}











/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

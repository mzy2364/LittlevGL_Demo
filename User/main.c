/*
*******************************************************************************************************
*
* 文件名称 : main.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 主函数文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"
#include "gui_user.h"
#include "task.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/


/* 函数声明 ---------------------------------------------------------*/



/**
  * @brief main主函数
  * @param None
  * @retval	None
  */
int main(void)
{

	bsp_init();
	
	my_task_schedule();
	

	
	
}




/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

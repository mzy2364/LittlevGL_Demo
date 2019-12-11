/*
*******************************************************************************************************
*
* 文件名称 : wks.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : IO模拟液晶屏需要的SPI初始化,由液晶屏厂家代码移植,不作太多注释
* 
*******************************************************************************************************
*/



#ifndef _WKS_H
#define _WKS_H

/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"

/* 宏定义 -----------------------------------------------------------*/

/* 定义IO操作 */
#define LCD_RST(n) (n?HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET))

#define LCD_CS(n) (n?HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET))

#define LCD_SCL(n) (n?HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET))

#define LCD_SDA(n) (n?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET))


/* 函数声明 ----------------------------------------------------------*/

void LCD_initial(void);







#endif


/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

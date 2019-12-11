/*
*******************************************************************************************************
*
* 文件名称 : spi.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : SPI驱动头文件
* 
*******************************************************************************************************
*/

#ifndef _SPI_H
#define _SPI_H



/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"



/* 宏定义 -----------------------------------------------------------*/



/* 函数声明 ----------------------------------------------------------*/

/* 外部调用函数 */
void spi6_init(void);
void spi2_init(void);

uint8_t spi2_send_receive_byte(uint8_t txdata);
uint8_t spi6_send_receive_byte(uint8_t txdata);

/* 仅内部调用函数 */

 
#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

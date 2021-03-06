/*
*******************************************************************************************************
*
* 文件名称 : usart.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 串口配置头文件
* 
*******************************************************************************************************
*/

#ifndef _USART_H
#define _USART_H



/* 头文件 ------------------------------------------------------------*/

#include "bsp.h"
#include <stdio.h>


/* 全局变量 ----------------------------------------------------------*/

extern UART_HandleTypeDef huart1;

/* 函数声明 ----------------------------------------------------------*/

void usart_init(void);

void usart6_send_string(uint8_t *str,uint16_t len);
void usart6_put_char(uint8_t c);



#endif



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* 文件名称 : board.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : RT-Thread配置文件
* 
*******************************************************************************************************
*/


#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32f4xx.h>

#define STM32_CONSOLE_USART		1

void rt_hw_board_init(void);

#if STM32_CONSOLE_USART == 0
#define CONSOLE_DEVICE "no"
#elif STM32_CONSOLE_USART == 1
#define CONSOLE_DEVICE "uart1"
#elif STM32_CONSOLE_USART == 2
#define CONSOLE_DEVICE "uart2"
#elif STM32_CONSOLE_USART == 3
#define CONSOLE_DEVICE "uart3"
#endif

#define FINSH_DEVICE_NAME   CONSOLE_DEVICE

#endif




/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

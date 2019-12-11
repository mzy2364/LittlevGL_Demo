/*
*******************************************************************************************************
*
* �ļ����� : board.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : RT-Thread�����ļ�
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




/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

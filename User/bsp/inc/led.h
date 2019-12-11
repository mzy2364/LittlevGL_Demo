/*
*******************************************************************************************************
*
* �ļ����� : led.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : LED����ͷ�ļ�
* 
*******************************************************************************************************
*/

#ifndef _LED_H
#define _LED_H



/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"



/* �궨�� -----------------------------------------------------------*/

/*����LED��PIN���źͶ�Ӧ�Ķ˿ں�ʱ��*/
#define LED_RED_PIN              GPIO_PIN_15
#define LED_RED_PORT             GPIOA
#define LED_RED_CLK_ENABLE       __HAL_RCC_GPIOA_CLK_ENABLE()

#define LED_BLUE_PIN             GPIO_PIN_3
#define LED_BLUE_PORT            GPIOD
#define LED_BLUE_CLK_ENABLE      __HAL_RCC_GPIOD_CLK_ENABLE()

#define LED_GREEN_PIN            GPIO_PIN_4
#define LED_GREEN_PORT           GPIOD
#define LED_GREEN_CLK_ENABLE     __HAL_RCC_GPIOD_CLK_ENABLE()


/*����LED����ɫ,���ܻ����׼��RGB��ɫ��һ��*/
#define LED_BLACK   0X00000000
#define LED_RED	    0X000000FF
#define LED_GREEN	0X0000FF00
#define LED_BLUE	0X00FF0000
#define LED_CYAN    0X00FFFF00
#define LED_MAGENTA 0X00FF00FF
#define LED_YELLOW  0X0000FFFF
#define LED_WHITE	0X00FFFFFF




/* �������� ----------------------------------------------------------*/

void led_init(void);
void led_color(uint32_t color);
void led_toggle(void);
uint32_t led_current_color(void);


 
#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

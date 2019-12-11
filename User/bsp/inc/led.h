/*
*******************************************************************************************************
*
* 文件名称 : led.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : LED驱动头文件
* 
*******************************************************************************************************
*/

#ifndef _LED_H
#define _LED_H



/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"



/* 宏定义 -----------------------------------------------------------*/

/*定义LED的PIN引脚和对应的端口和时钟*/
#define LED_RED_PIN              GPIO_PIN_15
#define LED_RED_PORT             GPIOA
#define LED_RED_CLK_ENABLE       __HAL_RCC_GPIOA_CLK_ENABLE()

#define LED_BLUE_PIN             GPIO_PIN_3
#define LED_BLUE_PORT            GPIOD
#define LED_BLUE_CLK_ENABLE      __HAL_RCC_GPIOD_CLK_ENABLE()

#define LED_GREEN_PIN            GPIO_PIN_4
#define LED_GREEN_PORT           GPIOD
#define LED_GREEN_CLK_ENABLE     __HAL_RCC_GPIOD_CLK_ENABLE()


/*定义LED的颜色,可能会跟标准的RGB颜色不一样*/
#define LED_BLACK   0X00000000
#define LED_RED	    0X000000FF
#define LED_GREEN	0X0000FF00
#define LED_BLUE	0X00FF0000
#define LED_CYAN    0X00FFFF00
#define LED_MAGENTA 0X00FF00FF
#define LED_YELLOW  0X0000FFFF
#define LED_WHITE	0X00FFFFFF




/* 函数声明 ----------------------------------------------------------*/

void led_init(void);
void led_color(uint32_t color);
void led_toggle(void);
uint32_t led_current_color(void);


 
#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

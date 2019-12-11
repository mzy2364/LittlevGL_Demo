/*
*******************************************************************************************************
*
* 文件名称 : key_fifo.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 按键驱动头文件
* 
*******************************************************************************************************
*/

#ifndef _KEY_FIFO_H
#define _KEY_FIFO_H



/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"



/* 宏定义 -----------------------------------------------------------*/

/* 按键端口定义 */
#define KEY_WKUP_PIN GPIO_PIN_0
#define KEY_WKUP_GPIO_PORT GPIOA
#define KEY_WKUP_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()

#define KEY_RIGHT_PIN GPIO_PIN_2
#define KEY_RIGHT_GPIO_PORT GPIOH
#define KEY_RIGHT_CLK_ENABLE __HAL_RCC_GPIOH_CLK_ENABLE()

#define KEY_LEFT_PIN GPIO_PIN_7
#define KEY_LEFT_GPIO_PORT GPIOD
#define KEY_LEFT_CLK_ENABLE __HAL_RCC_GPIOD_CLK_ENABLE()


/* 按键个数 */
#define KEY_COUNT 4
/* 按键滤波时间 单位10ms */
#define KEY_FILTER_TIME   5
/* 按键长按时间 单位10ms */
#define KEY_LONG_TIME     100
/* 定义按键FIFO缓冲区大小 */
#define KEY_FIFO_SIZE	4



/* typedef -----------------------------------------------------------*/

/* 按键是否按下 */
typedef enum
{
	KEY_ISDOWN = 0,
	KEY_NOTDOWN,
}KEY_DOWN;


/* 按键类型 */
typedef enum
{
	KEY_NONE = 0,
	
	KEY_LEFT_DOWN,
	KEY_LEFT_UP,
	KEY_LEFT_LONG,
	
	KEY_WKUP_DOWN,
	KEY_WKUP_UP,
	KEY_WKUP_LONG,
	
	KEY_RIGHT_DOWN,
	KEY_RIGHT_UP,
	KEY_RIGHT_LONG,
	
	KEY_POWER_DOWN,
	KEY_POWER_UP,
	KEY_POWER_LONG,
	
}KEY_ENUM;


/* 按键结构体 */
typedef struct
{
	uint8_t (*IsKeyDownFunc)(void);		//按键是否按下的函数指针
	
	uint8_t Count;	//滤波器计数器
	uint16_t LongCount;	//长按计数器
	uint16_t LongTime;	//按键按下的时间
	uint8_t State;		//按键的当前状态
	uint8_t RepeatSpeed;	//连续按键周期
	uint8_t RepeatCount;		//连续按键计数器	
	
	
}KEY_T;


/* fifo结构体 */
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];        //按键缓冲区
	uint8_t Read;                      //读指针
	uint8_t Write;                     //写指针
	
}KEY_FIFO;




/* 函数声明 ----------------------------------------------------------*/

/* 外部调用函数 */
void key_fifo_init(void);
void key_clear(void);
uint8_t key_is_init(void);
void key_scan(void);
uint8_t key_get(void);


/* 仅内部调用函数 */
void key_put(uint8_t keyCode);
static void key_gpio_config(void);
static void key_var_init(void);
static void key_detect(uint8_t i);
 
#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

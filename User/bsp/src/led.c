/*
*******************************************************************************************************
*
* 文件名称 : led.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : LED驱动文件
* 
*******************************************************************************************************
*/


/* 头文件 -----------------------------------------------------------*/
#include "led.h"


/* 变量 -------------------------------------------------------------*/
static __IO uint32_t current_color = 0;


/**
  * @brief LED初始化
  * @param None
  * @retval	None
  * @note 主要完成时钟使能,端口配置
  */
void led_init(void)
{

	/* 定义一个GPIO初始化结构体 */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO端口时钟使能 */
	LED_RED_CLK_ENABLE;
	LED_BLUE_CLK_ENABLE;
	LED_GREEN_CLK_ENABLE;


	/*配置RED灯的GPIO */
	GPIO_InitStruct.Pin = LED_RED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);

	/* 配置BLUE灯的GPIO */
	GPIO_InitStruct.Pin = LED_BLUE_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_BLUE_PORT, &GPIO_InitStruct);

	/* 配置GREEN灯的GPIO */
	GPIO_InitStruct.Pin = LED_GREEN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_GREEN_PORT, &GPIO_InitStruct);


	/* 关闭所有LED */
	HAL_GPIO_WritePin(LED_RED_PORT,LED_RED_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_BLUE_PORT,LED_BLUE_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_PORT,LED_GREEN_PIN,GPIO_PIN_SET);

}


/**
  * @brief LED显示对应的颜色
  * @param color 需要显示的颜色
  * @retval	None
  * @note 7种颜色,参数在头文件定义了
  */
void led_color(uint32_t color)
{
	current_color = color;
	if(color & LED_RED)
	{
		/*open red led*/
		HAL_GPIO_WritePin(LED_RED_PORT,LED_RED_PIN,GPIO_PIN_RESET);
	}
	else
	{
		/*close red led*/
		HAL_GPIO_WritePin(LED_RED_PORT,LED_RED_PIN,GPIO_PIN_SET);
	}
	if(color & LED_GREEN)
	{
		/*open green led*/
		HAL_GPIO_WritePin(LED_GREEN_PORT,LED_GREEN_PIN,GPIO_PIN_RESET);
	}
	else
	{
		/*close green led*/
		HAL_GPIO_WritePin(LED_GREEN_PORT,LED_GREEN_PIN,GPIO_PIN_SET);
	}
	if(color & LED_BLUE)
	{
		/*open blue led*/
		HAL_GPIO_WritePin(LED_BLUE_PORT,LED_BLUE_PIN,GPIO_PIN_RESET);
	}
	else
	{
		/*close blue led*/
		HAL_GPIO_WritePin(LED_BLUE_PORT,LED_BLUE_PIN,GPIO_PIN_SET);
	}
}

/**
  * @brief LED获取当前的颜色
  * @param None
  * @retval	当前LED的颜色
  */
uint32_t led_current_color(void)
{
	return current_color;
}

/**
  * @brief LED切换颜色
  * @param None
  * @retval	None
  * @note 8种颜色,每调用一次该函数切换一次颜色
  */
void led_toggle(void)
{
	switch(current_color)
	{
		case LED_BLACK:
			current_color = LED_RED;
			led_color(current_color);
			break;
		case LED_RED:
			current_color = LED_GREEN;
			led_color(current_color);
			break;
		case LED_GREEN:
			current_color = LED_BLUE;
			led_color(current_color);
			break;
		case LED_BLUE:
			current_color = LED_CYAN;
			led_color(current_color);
			break;
		case LED_CYAN:
			current_color = LED_MAGENTA;
			led_color(current_color);
			break;
		case LED_MAGENTA:
			current_color = LED_YELLOW;
			led_color(current_color);
			break;
		case LED_YELLOW:
			current_color = LED_WHITE;
			led_color(current_color);
			break;
		case LED_WHITE:
			current_color = LED_BLACK;
			led_color(current_color);
			break;
		default:
			break;
	}
}




/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

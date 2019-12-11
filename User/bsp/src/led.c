/*
*******************************************************************************************************
*
* �ļ����� : led.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : LED�����ļ�
* 
*******************************************************************************************************
*/


/* ͷ�ļ� -----------------------------------------------------------*/
#include "led.h"


/* ���� -------------------------------------------------------------*/
static __IO uint32_t current_color = 0;


/**
  * @brief LED��ʼ��
  * @param None
  * @retval	None
  * @note ��Ҫ���ʱ��ʹ��,�˿�����
  */
void led_init(void)
{

	/* ����һ��GPIO��ʼ���ṹ�� */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO�˿�ʱ��ʹ�� */
	LED_RED_CLK_ENABLE;
	LED_BLUE_CLK_ENABLE;
	LED_GREEN_CLK_ENABLE;


	/*����RED�Ƶ�GPIO */
	GPIO_InitStruct.Pin = LED_RED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);

	/* ����BLUE�Ƶ�GPIO */
	GPIO_InitStruct.Pin = LED_BLUE_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_BLUE_PORT, &GPIO_InitStruct);

	/* ����GREEN�Ƶ�GPIO */
	GPIO_InitStruct.Pin = LED_GREEN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_GREEN_PORT, &GPIO_InitStruct);


	/* �ر�����LED */
	HAL_GPIO_WritePin(LED_RED_PORT,LED_RED_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_BLUE_PORT,LED_BLUE_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_PORT,LED_GREEN_PIN,GPIO_PIN_SET);

}


/**
  * @brief LED��ʾ��Ӧ����ɫ
  * @param color ��Ҫ��ʾ����ɫ
  * @retval	None
  * @note 7����ɫ,������ͷ�ļ�������
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
  * @brief LED��ȡ��ǰ����ɫ
  * @param None
  * @retval	��ǰLED����ɫ
  */
uint32_t led_current_color(void)
{
	return current_color;
}

/**
  * @brief LED�л���ɫ
  * @param None
  * @retval	None
  * @note 8����ɫ,ÿ����һ�θú����л�һ����ɫ
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




/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

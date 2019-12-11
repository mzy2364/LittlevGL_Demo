/*
*******************************************************************************************************
*
* 文件名称 : usart.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 串口驱动文件
* 
*******************************************************************************************************
*/


/* 头文件 -----------------------------------------------------------*/
#include "usart.h"
#include <stdio.h>



/* 变量 -------------------------------------------------------------*/

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;


/**
  * @brief USART初始化
  * @param None
  * @retval	None
  * @note 主要完成结构体配置
  */
void usart_init(void)
{
	huart1.Instance = USART1;							//串口1
	huart1.Init.BaudRate = 115200;						//波特率
	huart1.Init.WordLength = UART_WORDLENGTH_8B;		//8位数据位
	huart1.Init.StopBits = UART_STOPBITS_1;				//1位数据位
	huart1.Init.Parity = UART_PARITY_NONE;				//无奇偶校验位
	huart1.Init.Mode = UART_MODE_TX_RX;					//串口收发模式
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//无硬件流控制
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;	//不启用OverSampling
	if (HAL_UART_Init(&huart1) != HAL_OK)				//初始化串口1
	{
		Error_Handler();
	}
  
	huart6.Instance = USART6;							//串口6
	huart6.Init.BaudRate = 115200;						//波特率
	huart6.Init.WordLength = UART_WORDLENGTH_8B;		//8位数据位
	huart6.Init.StopBits = UART_STOPBITS_1;				//1位数据位
	huart6.Init.Parity = UART_PARITY_NONE;				//无奇偶校验位
	huart6.Init.Mode = UART_MODE_TX_RX;					//串口收发模式
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//无硬件流控制
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;	//不启用OverSampling
	if (HAL_UART_Init(&huart6) != HAL_OK)				//初始化串口6
	{
		Error_Handler();
	}
	
}



/**
  * @brief USART6发送指定长度字符串
  * @param str-字符串指针
  * @param len-字符串长度
  * @retval	None
  */
void usart6_send_string(uint8_t *str,uint16_t len)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)str, len, 1000); 
}



/**
  * @brief USART底层初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_Init()调用,主要完成时钟使能,IO配置
  */
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(uartHandle->Instance==USART1)
	{
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10    ------> USART1_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	}
	else if(uartHandle->Instance==USART6)
	{
		
		/* USART6 clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**USART6 GPIO Configuration    
		PC6     ------> USART6_TX
		PC7     ------> USART6_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USART6 interrupt Init */
		HAL_NVIC_SetPriority(USART6_IRQn, 15, 3);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
		
		__HAL_UART_ENABLE_IT(uartHandle,UART_IT_RXNE);
		//__HAL_UART_ENABLE_IT(uartHandle,UART_IT_IDLE);
	}

}


/**
  * @brief USART底层去初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_DeInit()调用,主要完成时钟禁能,IO配置清除
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if(uartHandle->Instance==USART1)
	{
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10    ------> USART1_RX 
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

	}
	else if(uartHandle->Instance==USART6)
	{
		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10    ------> USART1_RX 
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);
		  
		/* USART6 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART6_IRQn);

	}
  
} 

/**
  * @brief  将C库printf函数重新定位到USART
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF); 

	return ch;
}  


/**
  * @brief This function handles USART6 global interrupt.
  */
void USART6_IRQHandler(void)
{
	if((__HAL_UART_GET_FLAG(&huart6,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
		//rec[count++] = USART6->DR;
		usart6_put_char(USART6->DR);
		
	}
	else if(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_IDLE)!=RESET)	//空闲中断
	{
		
		__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	}

	HAL_UART_IRQHandler(&huart6);
}


/**
  * @brief  USART6接收一字节数据
  * @param  c-接收的数据
  * @retval None
  * @note 该函数会被串口中断函数调用
  */
__weak void usart6_put_char(uint8_t c)
{
	/* USART6接收一字节 */
}



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

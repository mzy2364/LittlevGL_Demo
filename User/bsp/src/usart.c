/*
*******************************************************************************************************
*
* �ļ����� : usart.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : ���������ļ�
* 
*******************************************************************************************************
*/


/* ͷ�ļ� -----------------------------------------------------------*/
#include "usart.h"
#include <stdio.h>



/* ���� -------------------------------------------------------------*/

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;


/**
  * @brief USART��ʼ��
  * @param None
  * @retval	None
  * @note ��Ҫ��ɽṹ������
  */
void usart_init(void)
{
	huart1.Instance = USART1;							//����1
	huart1.Init.BaudRate = 115200;						//������
	huart1.Init.WordLength = UART_WORDLENGTH_8B;		//8λ����λ
	huart1.Init.StopBits = UART_STOPBITS_1;				//1λ����λ
	huart1.Init.Parity = UART_PARITY_NONE;				//����żУ��λ
	huart1.Init.Mode = UART_MODE_TX_RX;					//�����շ�ģʽ
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//��Ӳ��������
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;	//������OverSampling
	if (HAL_UART_Init(&huart1) != HAL_OK)				//��ʼ������1
	{
		Error_Handler();
	}
  
	huart6.Instance = USART6;							//����6
	huart6.Init.BaudRate = 115200;						//������
	huart6.Init.WordLength = UART_WORDLENGTH_8B;		//8λ����λ
	huart6.Init.StopBits = UART_STOPBITS_1;				//1λ����λ
	huart6.Init.Parity = UART_PARITY_NONE;				//����żУ��λ
	huart6.Init.Mode = UART_MODE_TX_RX;					//�����շ�ģʽ
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//��Ӳ��������
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;	//������OverSampling
	if (HAL_UART_Init(&huart6) != HAL_OK)				//��ʼ������6
	{
		Error_Handler();
	}
	
}



/**
  * @brief USART6����ָ�������ַ���
  * @param str-�ַ���ָ��
  * @param len-�ַ�������
  * @retval	None
  */
void usart6_send_string(uint8_t *str,uint16_t len)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)str, len, 1000); 
}



/**
  * @brief USART�ײ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_Init()����,��Ҫ���ʱ��ʹ��,IO����
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
  * @brief USART�ײ�ȥ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_DeInit()����,��Ҫ���ʱ�ӽ���,IO�������
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
  * @brief  ��C��printf�������¶�λ��USART
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
	if((__HAL_UART_GET_FLAG(&huart6,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
		//rec[count++] = USART6->DR;
		usart6_put_char(USART6->DR);
		
	}
	else if(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_IDLE)!=RESET)	//�����ж�
	{
		
		__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	}

	HAL_UART_IRQHandler(&huart6);
}


/**
  * @brief  USART6����һ�ֽ�����
  * @param  c-���յ�����
  * @retval None
  * @note �ú����ᱻ�����жϺ�������
  */
__weak void usart6_put_char(uint8_t c)
{
	/* USART6����һ�ֽ� */
}



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

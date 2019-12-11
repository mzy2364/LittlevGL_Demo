/*
*******************************************************************************************************
*
* �ļ����� : spi.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : SPI�����ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "spi.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/
SPI_HandleTypeDef hspi6;
SPI_HandleTypeDef hspi2;

/* �������� ---------------------------------------------------------*/


/**
  * @brief SPI6��ʼ��
  * @param None
  * @retval	None
  * @note ��Ҫ��ɽṹ������
  */
void spi6_init(void)
{
	hspi6.Instance = SPI6;
	hspi6.Init.Mode = SPI_MODE_MASTER;
	hspi6.Init.Direction = SPI_DIRECTION_2LINES;
	hspi6.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi6.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi6.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi6.Init.NSS = SPI_NSS_SOFT;
	hspi6.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi6.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi6.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi6.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi6.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi6) != HAL_OK)
	{
		Error_Handler();
	}
}




/**
  * @brief SPI2��ʼ��
  * @param None
  * @retval	None
  * @note ��Ҫ��ɽṹ������
  */
void spi2_init(void)
{
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;			//�����Ƶ���,��ֹϵͳʱ������Ϊ240MHz��ʱ��SPI-NRF24L01ͨ���쳣
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
}


/**
  * @brief SPI2���Ͳ�����һ�ֽ�����
  * @param None
  * @retval	���յ�����
  * @note 
  */
uint8_t spi2_send_receive_byte(uint8_t txdata)
{
	uint8_t rxdata;
	HAL_SPI_TransmitReceive(&hspi2,&txdata,&rxdata,1,1000);
	return rxdata;
}


/**
  * @brief SPI6���Ͳ�����һ�ֽ�����
  * @param None
  * @retval	���յ�����
  * @note 
  */
uint8_t spi6_send_receive_byte(uint8_t txdata)
{
	uint8_t rxdata;
	HAL_SPI_TransmitReceive(&hspi6,&txdata,&rxdata,1,1000);
	return rxdata;
}


/**
  * @brief SPI�ײ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_Init()����,��Ҫ���ʱ��ʹ��,IO����
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(spiHandle->Instance==SPI6)
	{

		/* SPI6 clock enable */
		__HAL_RCC_SPI6_CLK_ENABLE();

		__HAL_RCC_GPIOG_CLK_ENABLE();
		/**SPI6 GPIO Configuration    
		PG12     ------> SPI6_MISO
		PG13     ------> SPI6_SCK
		PG14     ------> SPI6_MOSI 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI6;
		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	}
	if(spiHandle->Instance==SPI2)
	{

		/* SPI2 clock enable */
		__HAL_RCC_SPI2_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI2 GPIO Configuration    
		PB13     ------> SPI2_SCK
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	}
}




/**
  * @brief SPI�ײ�ȥ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_DeInit()����,��Ҫ���ʱ�ӽ���,IO�������
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

	if(spiHandle->Instance==SPI6)
	{

		/* Peripheral clock disable */
		__HAL_RCC_SPI6_CLK_DISABLE();

		/**SPI6 GPIO Configuration    
		PG12     ------> SPI6_MISO
		PG13     ------> SPI6_SCK
		PG14     ------> SPI6_MOSI 
		*/
		HAL_GPIO_DeInit(GPIOG, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14);


	}
	if(spiHandle->Instance==SPI2)
	{
		/* Peripheral clock disable */
		__HAL_RCC_SPI2_CLK_DISABLE();

		/**SPI2 GPIO Configuration    
		PB13     ------> SPI2_SCK
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI 
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

	}
} 







/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

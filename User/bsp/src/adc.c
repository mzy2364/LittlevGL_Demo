/*
*******************************************************************************************************
*
* 文件名称 : adc.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : ADC驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "adc.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
static __IO uint16_t bat_adc_value = 0;


ADC_HandleTypeDef hadc3;

/* 函数声明 ---------------------------------------------------------*/


/**
  * @brief 电池对应的ADC3初始化
  * @param None
  * @retval	None
  */
void adc_light_init(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
	*/
	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	hadc3.Init.ScanConvMode = DISABLE;
	hadc3.Init.ContinuousConvMode = DISABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = DISABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc3) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
	*/
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	

}


/**
  * @brief 获取光敏电阻的ADC值
  * @param None
  * @retval	None
  */
uint16_t adc_light_get(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
	
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3,10);
	return HAL_ADC_GetValue(&hadc3);

}



/**
  * @brief ADC底层初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_Init()调用,主要完成时钟使能,IO配置
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(adcHandle->Instance==ADC3)
	{

		/* ADC3 clock enable */
		__HAL_RCC_ADC3_CLK_ENABLE();

		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**ADC3 GPIO Configuration    
		PF8     ------> ADC3_IN6
		PF9     ------> ADC3_IN7 
		PC1     ------> ADC3_IN11
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		
	}
}


/**
  * @brief ADC底层去初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_DeInit()调用,主要完成时钟禁能,IO配置清除
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

	if(adcHandle->Instance==ADC3)
	{

		/* Peripheral clock disable */
		__HAL_RCC_ADC3_CLK_DISABLE();

		/**ADC3 GPIO Configuration    
		PF8     ------> ADC3_IN6
		PF9     ------> ADC3_IN7 
		PC1     ------> ADC3_IN11
		*/
		HAL_GPIO_DeInit(GPIOF, GPIO_PIN_8|GPIO_PIN_9);
		
	}
} 







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

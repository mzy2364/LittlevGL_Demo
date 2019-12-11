/*
*******************************************************************************************************
*
* 文件名称 : fmc.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : FMC-SDRAM驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "fmc.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/


SDRAM_HandleTypeDef hsdram1;



/* 函数定义 ---------------------------------------------------------*/



/**
  * @brief FMC初始化
  * @param None
  * @retval	None
  */
void fmc_init(void)
{

	FMC_SDRAM_TimingTypeDef SdramTiming;

	/** Perform the SDRAM1 memory initialization sequence
	*/
	hsdram1.Instance = FMC_SDRAM_DEVICE;
	/* hsdram1.Init */
	hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
	/* SdramTiming */
	SdramTiming.LoadToActiveDelay = 2;
	SdramTiming.ExitSelfRefreshDelay = 8;
	SdramTiming.SelfRefreshTime = 6;
	SdramTiming.RowCycleDelay = 6;
	SdramTiming.WriteRecoveryTime = 2;
	SdramTiming.RPDelay = 2;
	SdramTiming.RCDDelay = 2;

	if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
	{
	Error_Handler( );
	}

	SDRAM_Initialization_Sequence(&hsdram1);
	
}


/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
	__IO uint32_t tmpmrd =0;
	FMC_SDRAM_CommandTypeDef Command;
	/* Configure a clock configuration enable command */
	Command.CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber 	 = 1;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

	/* Insert 100 ms delay */
	HAL_Delay(100);

	/* Configure a PALL (precharge all) command */ 
	Command.CommandMode 			 = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber 	 = 1;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);  

	/* Configure a Auto-Refresh command */ 
	Command.CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber 	 = 8;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

	/* Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_3           |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber 	 = 1;
	Command.ModeRegisterDefinition = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

	/* Set the refresh rate counter */
	/* (15.62 us x Freq) - 20 */
	/* Set the device refresh counter */
	HAL_SDRAM_ProgramRefreshRate(hsdram, 683); 
}


/**
  * @brief SDRAM读写测试,调用本函数前请确保printf函数有效
  * @param None
  * @retval	None
  */
void fmc_sdram_test(void)
{  
	uint32_t i=0;  	  
	uint32_t value=1;	
	uint32_t last_value=0;
	uint32_t t_start=0;	
	uint32_t t_end=0;
	uint32_t *pBuf;
	uint32_t size = (1024*1024*32/4);
	pBuf = (uint32_t *)SDRAM_BANK_ADDR;
	printf("开始写测试\r\n");
	printf("write start:%d\r\n",t_start = HAL_GetTick());
	for (i = 0; i <size/8; i++)
	{
		*pBuf++ = value++;
		*pBuf++ = value++;
		*pBuf++ = value++;
		*pBuf++ = value++;
		*pBuf++ = value++;
		*pBuf++ = value++;
		*pBuf++ = value++;
		*pBuf++ = value++;
	}
	printf("write end:%d\r\n",t_end = HAL_GetTick());
	printf("写耗时:%dms\r\n",(t_end-t_start));
	printf("写速度:%dMbyte/s\r\n",(32*1000/(t_end-t_start)));

	printf("开始读测试\r\n");
	printf("read start:%d\r\n",t_start = HAL_GetTick());
	pBuf = (uint32_t *)0xC0000000;
	for(i = 0; i <size/8; i++)
	{
		//不要开keil的优化
		value = *pBuf++;
		value = *pBuf++;
		value = *pBuf++;
		value = *pBuf++;
		value = *pBuf++;
		value = *pBuf++;
		value = *pBuf++;
		value = *pBuf++;
	}
	printf("read end:%d\r\n",t_end = HAL_GetTick());
	printf("读耗时:%dms\r\n",(t_end-t_start));
	printf("读速度:%dMbyte/s\r\n",(32*1000/(t_end-t_start)));

	printf("开始数据校验测试\r\n");
	pBuf = (uint32_t *)0xC0000000;
	for(i = 0; i <size; i++)
	{
		value = *pBuf++;
		if((value-last_value)!=1)
		{
			break;
		}
		last_value = value;
	}
	if(i<size)
	{
		printf("读取SDRAM出错，出错位置:%d\r\n",i);
	}
	else
	{
		printf("读取SDRAM正常\r\n");
	}

	
	
}	








/**
  * @brief SDRAM底层初始化函数
  * @param None
  * @retval	None
  * @note 调用FMC初始化
  */
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* sdramHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_ENABLE();

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/** FMC GPIO Configuration  
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC0   ------> FMC_SDNWE
	PC2   ------> FMC_SDNE0
	PC3   ------> FMC_SDCKE0
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG2   ------> FMC_A12
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	*/
	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12 
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4 
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
						  |GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}





/**
  * @brief SDRAM底层去初始化函数
  * @param None
  * @retval	None
  */
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* sdramHandle)
{
	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_DISABLE();

	/** FMC GPIO Configuration  
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC0   ------> FMC_SDNWE
	PC2   ------> FMC_SDNE0
	PC3   ------> FMC_SDCKE0
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG2   ------> FMC_A12
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	*/

	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12 
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);

	HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4 
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
						  |GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);


}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

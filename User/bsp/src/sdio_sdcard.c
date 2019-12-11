/*
*******************************************************************************************************
*
* 文件名称 : sdio_sdcard.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : SD卡驱动文件
*            该程序由官方的SD卡驱动移植
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "sdio_sdcard.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio_rx;
DMA_HandleTypeDef hdma_sdio_tx;

/* 字节对齐使用 */
__ALIGN_BEGIN static uint8_t scratch[BLOCKSIZE] __ALIGN_END;
static volatile  uint8_t  WriteStatus = 0, ReadStatus = 0;


/* 函数声明 ---------------------------------------------------------*/


/**
  * @brief  SD卡初始化
  * @param  None
  * @retval SD status
  */
uint8_t BSP_SD_Init(void)
{
	hsd.Instance = SDIO;
	hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
	hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
	hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
	hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
	hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
	hsd.Init.ClockDiv = 0;
	
	uint8_t sd_state = MSD_OK;
	/* Check if the SD card is plugged in the slot */
	if (BSP_SD_IsDetected() != SD_PRESENT)
	{
		return MSD_ERROR;
	}
	/* HAL SD initialization */
	sd_state = HAL_SD_Init(&hsd);
	/* Configure SD Bus width (4 bits mode selected) */
	if (sd_state == MSD_OK)
	{
		/* Enable wide operation */
		if (HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK)
		{
			sd_state = MSD_ERROR;
		}
	}

  return sd_state;
	
}

/**
  * @brief  Configures Interrupt mode for SD detection pin.
  * @retval Returns 0 in success otherwise 1. 
  */
uint8_t BSP_SD_ITConfig(void)
{  
  /* TBI: add user code here depending on the hardware configuration used */
  
  return (uint8_t)0;
}

/** @brief  SD detect IT treatment
  */
void BSP_SD_DetectIT(void)
{
  /* TBI: add user code here depending on the hardware configuration used */
}

/** @brief  SD detect IT detection callback
  */
__weak void BSP_SD_DetectCallback(void)
{
  /* NOTE: This function Should not be modified, when the callback is needed,
     the BSP_SD_DetectCallback could be implemented in the user file
  */ 
}

/**
  * @brief  Reads block(s) from a specified address in an SD card, in polling mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  ReadAddr: Address from where data is to be read  
  * @param  NumOfBlocks: Number of SD blocks to read 
  * @param  Timeout: Timeout for read operation
  * @retval SD status
  */
uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout)
{
  uint8_t sd_state = MSD_OK;
  
  if (HAL_SD_ReadBlocks(&hsd, (uint8_t *)pData, ReadAddr, NumOfBlocks, Timeout) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;  
}

/**
  * @brief  Writes block(s) to a specified address in an SD card, in polling mode. 
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  WriteAddr: Address from where data is to be written
  * @param  NumOfBlocks: Number of SD blocks to write
  * @param  Timeout: Timeout for write operation
  * @retval SD status
  */
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout)
{
  uint8_t sd_state = MSD_OK;
  
  if (HAL_SD_WriteBlocks(&hsd, (uint8_t *)pData, WriteAddr, NumOfBlocks, Timeout) != HAL_OK) 
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;  
}

/**
  * @brief  Reads block(s) from a specified address in an SD card, in DMA mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  ReadAddr: Address from where data is to be read
  * @param  NumOfBlocks: Number of SD blocks to read 
  * @retval SD status
  */
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks)
{
  uint8_t sd_state = MSD_OK;
  
  /* Read block(s) in DMA transfer mode */
  if (HAL_SD_ReadBlocks_DMA(&hsd, (uint8_t *)pData, ReadAddr, NumOfBlocks) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }
  
  return sd_state; 
}

/**
  * @brief  Writes block(s) to a specified address in an SD card, in DMA mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  WriteAddr: Address from where data is to be written
  * @param  NumOfBlocks: Number of SD blocks to write 
  * @retval SD status
  */
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks)
{
  uint8_t sd_state = MSD_OK;
  
  /* Write block(s) in DMA transfer mode */
  if (HAL_SD_WriteBlocks_DMA(&hsd, (uint8_t *)pData, WriteAddr, NumOfBlocks) != HAL_OK)
  {
    sd_state = MSD_ERROR;
  }
  
  return sd_state; 
}

/**
  * @brief  Erases the specified memory area of the given SD card. 
  * @param  StartAddr: Start byte address
  * @param  EndAddr: End byte address
  * @retval SD status
  */
uint8_t BSP_SD_Erase(uint32_t StartAddr, uint32_t EndAddr)
{
  uint8_t sd_state = MSD_OK;
  
  if (HAL_SD_Erase(&hsd, StartAddr, EndAddr) != HAL_OK)  
  {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}


/**
  * @brief  Handles SD card interrupt request.
  */
void BSP_SD_IRQHandler(void)
{
  HAL_SD_IRQHandler(&hsd);
}

/**
  * @brief  Handles SD DMA Tx transfer interrupt request.
  */
void BSP_SD_DMA_Tx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hsd.hdmatx); 
}

/**
  * @brief  Handles SD DMA Rx transfer interrupt request.
  */
void BSP_SD_DMA_Rx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hsd.hdmarx);
}

/**
  * @brief  Gets the current SD card data status.
  * @param  None
  * @retval Data transfer state.
  *          This value can be one of the following values:
  *            @arg  SD_TRANSFER_OK: No data transfer is acting
  *            @arg  SD_TRANSFER_BUSY: Data transfer is acting
  */
uint8_t BSP_SD_GetCardState(void)
{
  return ((HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

/**
  * @brief  Get SD information about specific SD card.
  * @param  CardInfo: Pointer to HAL_SD_CardInfoTypedef structure
  * @retval None 
  */
void BSP_SD_GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo)
{
  /* Get SD card Information */
  HAL_SD_GetCardInfo(&hsd, CardInfo);
}

/* USER CODE BEGIN BeforeCallBacksSection */
/* can be used to modify previous code / undefine following code / add code */
/* USER CODE END BeforeCallBacksSection */
/**
  * @brief SD Abort callbacks
  * @param hsd: SD handle
  * @retval None
  */
void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd)
{
  BSP_SD_AbortCallback();
}

/**
  * @brief Tx Transfer completed callback
  * @param hsd: SD handle
  * @retval None
  */
void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
  BSP_SD_WriteCpltCallback();
}

/**
  * @brief Rx Transfer completed callback
  * @param hsd: SD handle
  * @retval None
  */
void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
  BSP_SD_ReadCpltCallback();
}


/**
  * @brief BSP SD Abort callback
  * @retval None
  */
__weak void BSP_SD_AbortCallback(void)
{

}




/**
 * @brief  Detects if SD card is correctly plugged in the memory slot or not.
 * @param  None
 * @retval Returns if SD is detected or not
 */
uint8_t BSP_SD_IsDetected(void)
{
  __IO uint8_t status = SD_PRESENT;
	

  return status;
}





static int SD_CheckStatusWithTimeout(uint32_t timeout)
{
  uint32_t timer = HAL_GetTick();
  /* block until SDIO IP is ready again or a timeout occur */
  while(HAL_GetTick() - timer < timeout)
  {
    if (BSP_SD_GetCardState() == SD_TRANSFER_OK)
    {
      return 0;
    }
  }

  return -1;
}

/**
  * @brief  SD卡DMA写扇区
  * @param  buff-数据缓冲区
  * @param  sector-扇区地址
  * @param  count-扇区数量
  * @retval SD status
  * @note 该函数由CubeMX生成的Fatfs驱动移植而来,带字节对齐处理
  */
uint8_t BSP_SD_ReadDisk_DMA(uint8_t *buff, uint32_t sector, uint32_t count)
{
	uint8_t res = 1;
	uint32_t timeout;
	uint8_t ret;

	/*
	* ensure the SDCard is ready for a new operation
	*/

	if (SD_CheckStatusWithTimeout(SD_TIMEOUT) < 0)
	{
	return res;
	}

	if (!((uint32_t)buff & 0x3))
	{
		
		if(BSP_SD_ReadBlocks_DMA((uint32_t*)buff,(uint32_t)(sector),count) == MSD_OK)
		{
			ReadStatus = 0;
			/* Wait that the reading process is completed or a timeout occurs */
			timeout = HAL_GetTick();
			while((ReadStatus == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT))
			{
			}
			/* incase of a timeout return error */
			if (ReadStatus == 0)
			{
				res = 1;
			}
			else
			{
				ReadStatus = 0;
				timeout = HAL_GetTick();

				while((HAL_GetTick() - timeout) < SD_TIMEOUT)
				{
					if (BSP_SD_GetCardState() == SD_TRANSFER_OK)
					{
						res = 0;
						break;
					}
				}
			}
		}
		else 
		{
			/* Slow path, fetch each sector a part and memcpy to destination buffer */
		  
			int i;

			for (i = 0; i < count; i++) 
			{
				ret = BSP_SD_ReadBlocks_DMA((uint32_t*)scratch, (uint32_t)sector++, 1);
				if (ret == MSD_OK) 
				{
					/* wait until the read is successful or a timeout occurs */

					ReadStatus = 0;
					timeout = HAL_GetTick();
					while((ReadStatus == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT))
					{
					}
					if (ReadStatus == 0)
					{
						break;
					}
					memcpy(buff, scratch, BLOCKSIZE);
					buff += BLOCKSIZE;
				}
				else
				{
					break;
				}
			}

			if ((i == count) && (ret == MSD_OK))
				res = 0;
		}

	}

  return res;
}

/**
  * @brief  SD卡DMA读扇区
  * @param  buff-数据缓冲区
  * @param  sector-扇区地址
  * @param  count-扇区数量
  * @retval SD status
  * @note 该函数由CubeMX生成的Fatfs驱动移植而来,带字节对齐处理
  */
uint8_t BSP_SD_WriteDisk_DMA(const uint8_t *buff, uint32_t sector, uint32_t count)
{
	uint8_t res = 1;
	uint32_t timeout;
	uint8_t ret;
	int i;

	WriteStatus = 0;

	if (SD_CheckStatusWithTimeout(SD_TIMEOUT) < 0)
	{
		return res;
	}


	if (!((uint32_t)buff & 0x3))
	{

		if(BSP_SD_WriteBlocks_DMA((uint32_t*)buff,(uint32_t)(sector),count) == MSD_OK)
		{
			/* Wait that writing process is completed or a timeout occurs */

			timeout = HAL_GetTick();
			while((WriteStatus == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT))
			{
			}
			/* incase of a timeout return error */
			if (WriteStatus == 0)
			{
				res = 1;
			}
			else
			{
				WriteStatus = 0;
				timeout = HAL_GetTick();
				while((HAL_GetTick() - timeout) < SD_TIMEOUT)
				{
					if (BSP_SD_GetCardState() == SD_TRANSFER_OK)
					{
						res = 0;
						break;
					}
				}
			}
		}
		else
		{

		  for (i = 0; i < count; i++)
		  {
				WriteStatus = 0;
				ret = BSP_SD_WriteBlocks_DMA((uint32_t*)scratch, (uint32_t)sector++, 1);
				if (ret == MSD_OK) 
				{
					/* wait for a message from the queue or a timeout */
					timeout = HAL_GetTick();
					while((WriteStatus == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT))
					{
					}
					if (WriteStatus == 0)
					{
						break;
					}

					memcpy((void *)buff, (void *)scratch, BLOCKSIZE);
					buff += BLOCKSIZE;
				}	
				else
				{
					break;
				}
		  }
		  if ((i == count) && (ret == MSD_OK))
			res = 0;
		}

	}
	return res;
}





/**
  * @brief Tx Transfer completed callbacks
  * @param hsd: SD handle
  * @retval None
  */
void BSP_SD_WriteCpltCallback(void)
{
	WriteStatus = 1;
}

/**
  * @brief Rx Transfer completed callbacks
  * @param hsd: SD handle
  * @retval None
  */
void BSP_SD_ReadCpltCallback(void)
{
	ReadStatus = 1;
}


/**
  * @brief USART底层初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_Init()调用,主要完成时钟使能,IO配置
  */
void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(sdHandle->Instance==SDIO)
	{
		
		/* SDIO clock enable */
		__HAL_RCC_SDIO_CLK_ENABLE();
		  
		/* DMA controller clock enable */
		__HAL_RCC_DMA2_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**SDIO GPIO Configuration    
		PC8     ------> SDIO_D0
		PC9     ------> SDIO_D1
		PC10     ------> SDIO_D2
		PC11     ------> SDIO_D3
		PC12     ------> SDIO_CK
		PD2     ------> SDIO_CMD 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
							  |GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* SDIO DMA Init */
		/* SDIO_RX Init */
		hdma_sdio_rx.Instance = DMA2_Stream3;
		hdma_sdio_rx.Init.Channel = DMA_CHANNEL_4;
		hdma_sdio_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_sdio_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sdio_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sdio_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sdio_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sdio_rx.Init.Mode = DMA_PFCTRL;
		hdma_sdio_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sdio_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_sdio_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_sdio_rx.Init.MemBurst = DMA_MBURST_INC4;
		hdma_sdio_rx.Init.PeriphBurst = DMA_PBURST_INC4;
		if (HAL_DMA_Init(&hdma_sdio_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(sdHandle,hdmarx,hdma_sdio_rx);

		/* SDIO_TX Init */
		hdma_sdio_tx.Instance = DMA2_Stream6;
		hdma_sdio_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_sdio_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_sdio_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sdio_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sdio_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sdio_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sdio_tx.Init.Mode = DMA_PFCTRL;
		hdma_sdio_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sdio_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_sdio_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_sdio_tx.Init.MemBurst = DMA_MBURST_INC4;
		hdma_sdio_tx.Init.PeriphBurst = DMA_PBURST_INC4;
		if (HAL_DMA_Init(&hdma_sdio_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(sdHandle,hdmatx,hdma_sdio_tx);

		/* SDIO interrupt Init */
		HAL_NVIC_SetPriority(SDIO_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(SDIO_IRQn);
		/* USER CODE BEGIN SDIO_MspInit 1 */

		/* DMA interrupt init */
		/* DMA2_Stream3_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 6, 1);
		HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
		/* DMA2_Stream6_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 6, 1);
		HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

	}
}

/**
  * @brief SD底层去初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_DeInit()调用,主要完成时钟禁能,IO配置清除
  */
void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle)
{

	if(sdHandle->Instance==SDIO)
	{
		/* Peripheral clock disable */
		__HAL_RCC_SDIO_CLK_DISABLE();

		/**SDIO GPIO Configuration    
		PC8     ------> SDIO_D0
		PC9     ------> SDIO_D1
		PC10     ------> SDIO_D2
		PC11     ------> SDIO_D3
		PC12     ------> SDIO_CK
		PD2     ------> SDIO_CMD 
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
							  |GPIO_PIN_12);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

		/* SDIO DMA DeInit */
		HAL_DMA_DeInit(sdHandle->hdmarx);
		HAL_DMA_DeInit(sdHandle->hdmatx);

		/* SDIO interrupt Deinit */
		HAL_NVIC_DisableIRQ(SDIO_IRQn);


	}
} 





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* 文件名称 : sdio_sdcard.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : SD卡驱动文件
* 
*******************************************************************************************************
*/

#ifndef _SDIO_SDCARD_H
#define _SDIO_SDCARD_H


/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"


/* 宏定义 -----------------------------------------------------------*/

#define   MSD_OK                        ((uint8_t)0x00)
#define   MSD_ERROR                     ((uint8_t)0x01)

/** 
  * @brief  SD transfer state definition  
  */     
#define   SD_TRANSFER_OK                ((uint8_t)0x00)
#define   SD_TRANSFER_BUSY              ((uint8_t)0x01)

#define SD_PRESENT               ((uint8_t)0x01)
#define SD_NOT_PRESENT           ((uint8_t)0x00)
#define SD_TIMEOUT           ((uint32_t)100000000)

/** 
  * @brief SD Card information structure 
  */
#define BSP_SD_CardInfo HAL_SD_CardInfoTypeDef

/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/

uint8_t BSP_SD_Init(void);
uint8_t BSP_SD_ITConfig(void);
void    BSP_SD_DetectIT(void);
void    BSP_SD_DetectCallback(void);
uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_Erase(uint32_t StartAddr, uint32_t EndAddr);
void BSP_SD_IRQHandler(void);
void BSP_SD_DMA_Tx_IRQHandler(void);
void BSP_SD_DMA_Rx_IRQHandler(void);
uint8_t BSP_SD_GetCardState(void);
void    BSP_SD_GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo);
uint8_t BSP_SD_IsDetected(void);

uint8_t BSP_SD_ReadDisk_DMA(uint8_t *buff, uint32_t sector, uint32_t count);
uint8_t BSP_SD_WriteDisk_DMA(const uint8_t *buff, uint32_t sector, uint32_t count);


/* These functions can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void    BSP_SD_AbortCallback(void);
void    BSP_SD_WriteCpltCallback(void);
void    BSP_SD_ReadCpltCallback(void);





#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

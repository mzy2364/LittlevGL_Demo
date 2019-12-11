/*
*******************************************************************************************************
*
* 文件名称 : fmc.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : FMC驱动头文件
* 
*******************************************************************************************************
*/

#ifndef _FMC_H
#define _FMC_H


/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"



/* 宏定义 -----------------------------------------------------------*/


/* SDRAM地址分配 */
#define LCD_LAYER0_FRAME_BUFFER  ((uint32_t)0xC0000000)
#define LCD_LAYER1_FRAME_BUFFER  ((uint32_t)0xC0100000)


/* SDRAM起始地址 */
#define SDRAM_BANK_ADDR                          ((uint32_t)0xC0000000)

/* SDRAM大小 */
#define SDRAM_SIZE                               ((uint32_t)0x2000000)

/* SDRAM通讯时序配置 */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200) 



/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/

void fmc_init(void);
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram);
void fmc_sdram_test(void);








#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

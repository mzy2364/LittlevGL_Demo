/*
*******************************************************************************************************
*
* �ļ����� : fmc.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : FMC����ͷ�ļ�
* 
*******************************************************************************************************
*/

#ifndef _FMC_H
#define _FMC_H


/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"



/* �궨�� -----------------------------------------------------------*/


/* SDRAM��ַ���� */
#define LCD_LAYER0_FRAME_BUFFER  ((uint32_t)0xC0000000)
#define LCD_LAYER1_FRAME_BUFFER  ((uint32_t)0xC0100000)


/* SDRAM��ʼ��ַ */
#define SDRAM_BANK_ADDR                          ((uint32_t)0xC0000000)

/* SDRAM��С */
#define SDRAM_SIZE                               ((uint32_t)0x2000000)

/* SDRAMͨѶʱ������ */
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



/* ȫ�ֱ��� ----------------------------------------------------------*/


/* �������� ----------------------------------------------------------*/

void fmc_init(void);
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram);
void fmc_sdram_test(void);








#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

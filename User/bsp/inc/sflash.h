/*
*******************************************************************************************************
*
* 文件名称 : sflash.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : SPI-FLASH驱动头文件
* 
*******************************************************************************************************
*/

#ifndef _SFLASH_H
#define _SFLASH_H


/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"



/* 宏定义 -----------------------------------------------------------*/

/* 片选IO定义 */
#define FLASH_CS_PIN GPIO_PIN_8
#define FLASH_CS_GPIO_PORT GPIOI

/* SPI-FLASH指令表 */
#define SFlash_WriteEnable		0x06 
#define SFlash_WriteDisable		0x04 
#define SFlash_ReadStatusReg1		0x05 
#define SFlash_ReadStatusReg2		0x35 
#define SFlash_ReadStatusReg3		0x15 
#define SFlash_WriteStatusReg1    0x01 
#define SFlash_WriteStatusReg2    0x31 
#define SFlash_WriteStatusReg3    0x11 
#define SFlash_ReadData			0x03 
#define SFlash_FastReadData		0x0B 
#define SFlash_FastReadDual		0x3B 
#define SFlash_PageProgram		0x02 
#define SFlash_BlockErase			0xD8 
#define SFlash_SectorErase		0x20 
#define SFlash_ChipErase			0xC7 
#define SFlash_PowerDown			0xB9 
#define SFlash_ReleasePowerDown	0xAB 
#define SFlash_DeviceID			0xAB 
#define SFlash_ManufactDeviceID	0x90 
#define SFlash_JedecDeviceID		0x9F 
#define SFlash_Enable4ByteAddr    0xB7
#define SFlash_Exit4ByteAddr      0xE9

#define Dummy_Byte              0xFF
#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */
#define SFlash_PageSize			256		//页大小
#define SFlash_SecSize			4096	//扇区大小

/* FLASH的 ID */
#define XM25QH128_ID		0X207018


/* 全局变量 ----------------------------------------------------------*/



/* 函数声明 ----------------------------------------------------------*/

void sflash_init(void);
uint16_t sflash_read_device_id(void);
uint32_t sflash_read_id(void);
void sflash_read(uint8_t *pbuffer,uint32_t read_addr,uint32_t num_byte_to_read);
void sflash_write(uint8_t *pbuffer,uint32_t write_addr,uint32_t num_byte_to_write);
void sflash_write_page(uint8_t *pbuffer,uint32_t write_addr,uint16_t num_byte_to_write);
void sflash_write_no_check(uint8_t *pbuffer,uint32_t write_addr,uint16_t num_byte_to_write);
void sflash_erase_sector(uint32_t sector_addr);
void sflash_erase_chip(void);

void sflash_wait_busy(void);
void sflash_write_disenable(void);
void sflash_write_enable(void);
void sflash_erase_sector(uint32_t sector_addr);





#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

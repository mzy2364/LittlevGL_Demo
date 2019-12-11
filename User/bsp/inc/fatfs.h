/*
*******************************************************************************************************
*
* 文件名称 : fatfs.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : FATFS驱动文件
* 
*******************************************************************************************************
*/

#ifndef _FATFS_H
#define _FATFS_H


/* 头文件 -----------------------------------------------------------*/

#include "bsp.h"

#include "ff_gen_drv.h"
#include "ff.h"
#include "sflash_diskio.h"


/* 宏定义 -----------------------------------------------------------*/



/* 全局变量 ----------------------------------------------------------*/

extern uint8_t retSD;    /* Return value for SD */
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
extern FIL SDFile;       /* File object for SD */

extern uint8_t retSFLASH;    /* Return value for USER */
extern char SFLASHPath[4];   /* USER logical drive path */
extern FATFS SFLASHFatFS;    /* File system object for USER logical drive */
extern FIL SFLASHFile;       /* File object for USER */


/* 函数声明 ----------------------------------------------------------*/
void fatfs_init(void);
FRESULT scan_files (char* path);

#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

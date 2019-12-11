/*
*******************************************************************************************************
*
* �ļ����� : fatfs.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : FATFS�����ļ�
* 
*******************************************************************************************************
*/

#ifndef _FATFS_H
#define _FATFS_H


/* ͷ�ļ� -----------------------------------------------------------*/

#include "bsp.h"

#include "ff_gen_drv.h"
#include "ff.h"
#include "sflash_diskio.h"


/* �궨�� -----------------------------------------------------------*/



/* ȫ�ֱ��� ----------------------------------------------------------*/

extern uint8_t retSD;    /* Return value for SD */
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
extern FIL SDFile;       /* File object for SD */

extern uint8_t retSFLASH;    /* Return value for USER */
extern char SFLASHPath[4];   /* USER logical drive path */
extern FATFS SFLASHFatFS;    /* File system object for USER logical drive */
extern FIL SFLASHFile;       /* File object for USER */


/* �������� ----------------------------------------------------------*/
void fatfs_init(void);
FRESULT scan_files (char* path);

#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* 文件名称 : fatfs.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : FATFS驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "fatfs.h"
#include "sd_diskio.h"
#include "sflash_diskio.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

uint8_t retSFLASH;    /* Return value for USER */
char SFLASHPath[4];   /* USER logical drive path */
FATFS SFLASHFatFS;    /* File system object for USER logical drive */
FIL SFLASHFile;       /* File object for USER */




/* 函数声明 ---------------------------------------------------------*/


/**
  * @brief  FATFS初始化
  * @param  None
  * @retval None
  * @note 链接FATFS的驱动
  */
void fatfs_init(void)
{
	
	/*## FatFS: Link the SD driver ###########################*/
	retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

	/*## FatFS: Link the SFLASH driver ###########################*/
	/* 占位用 */
	retSFLASH = FATFS_LinkDriver(&SFLASH_Driver, SFLASHPath);

}


/**
  * @brief 递归扫描输入路径下的所有路径和文件并打印
  * @param path-需要扫描的路径
  * @retval	None
  */
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) 
		{
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) 
			{                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s\r\n", fno.fname);
                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } 
			else 
			{                                       /* It is a file. */
                printf("%s/%s\r\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}




/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
	
	
	/* 返回当前时间戳 */
	return  ((DWORD)(2000+19 - 1980) << 25)	/* Year  */
			| ((DWORD)8 << 21)				/* Month  */
			| ((DWORD)16 << 16)				/* Mday  */
			| ((DWORD)12 << 11)				/* Hour  */
			| ((DWORD)5 << 5)				  /* Min  */
			| ((DWORD)3 >> 1);				/* Sec  */
	
	
}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

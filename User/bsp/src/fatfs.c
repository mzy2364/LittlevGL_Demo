/*
*******************************************************************************************************
*
* �ļ����� : fatfs.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : FATFS�����ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "fatfs.h"
#include "sd_diskio.h"
#include "sflash_diskio.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/
uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

uint8_t retSFLASH;    /* Return value for USER */
char SFLASHPath[4];   /* USER logical drive path */
FATFS SFLASHFatFS;    /* File system object for USER logical drive */
FIL SFLASHFile;       /* File object for USER */




/* �������� ---------------------------------------------------------*/


/**
  * @brief  FATFS��ʼ��
  * @param  None
  * @retval None
  * @note ����FATFS������
  */
void fatfs_init(void)
{
	
	/*## FatFS: Link the SD driver ###########################*/
	retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

	/*## FatFS: Link the SFLASH driver ###########################*/
	/* ռλ�� */
	retSFLASH = FATFS_LinkDriver(&SFLASH_Driver, SFLASHPath);

}


/**
  * @brief �ݹ�ɨ������·���µ�����·�����ļ�����ӡ
  * @param path-��Ҫɨ���·��
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
	
	
	/* ���ص�ǰʱ��� */
	return  ((DWORD)(2000+19 - 1980) << 25)	/* Year  */
			| ((DWORD)8 << 21)				/* Month  */
			| ((DWORD)16 << 16)				/* Mday  */
			| ((DWORD)12 << 11)				/* Hour  */
			| ((DWORD)5 << 5)				  /* Min  */
			| ((DWORD)3 >> 1);				/* Sec  */
	
	
}







/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

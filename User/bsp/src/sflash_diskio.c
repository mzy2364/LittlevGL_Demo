/*
*******************************************************************************************************
*
* 文件名称 : sflash_diskio.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : FATFS的磁盘相关文件,FATFS的底层驱动,实现磁盘读写
* 
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "sflash_diskio.h"
#include <string.h>
#include "ff_gen_drv.h"

/* 宏定义 -----------------------------------------------------------*/



/* 变量 -------------------------------------------------------------*/

/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;


/* 函数声明 ---------------------------------------------------------*/

DSTATUS sflash_disk_initialize (BYTE pdrv);
DSTATUS sflash_disk_status (BYTE pdrv);
DRESULT sflash_disk_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  DRESULT sflash_disk_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);  
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT sflash_disk_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */


Diskio_drvTypeDef  SFLASH_Driver =
{
  sflash_disk_initialize,
  sflash_disk_status,
  sflash_disk_read, 
#if  _USE_WRITE
  sflash_disk_write,
#endif  /* _USE_WRITE == 1 */  
#if  _USE_IOCTL == 1
  sflash_disk_ioctl,
#endif /* _USE_IOCTL == 1 */
};



/**
  * @brief  Initializes a Drive
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS sflash_disk_initialize (
	BYTE pdrv           /* Physical drive nmuber to identify the drive */
)
{
  /* USER CODE BEGIN INIT */
    Stat = STA_NOINIT;
	sflash_init();
	Stat &= ~STA_NOINIT;
    return Stat;
  /* USER CODE END INIT */
}
 
/**
  * @brief  Gets Disk Status 
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS sflash_disk_status (
	BYTE pdrv       /* Physical drive number to identify the drive */
)
{
  /* USER CODE BEGIN STATUS */
    Stat = STA_NOINIT;
	if(sflash_read_id() == XM25QH128_ID)
		Stat &= ~STA_NOINIT;
    return Stat;
  /* USER CODE END STATUS */
}

/**
  * @brief  Reads Sector(s) 
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT sflash_disk_read (
	BYTE pdrv,      /* Physical drive nmuber to identify the drive */
	BYTE *buff,     /* Data buffer to store read data */
	DWORD sector,   /* Sector address in LBA */
	UINT count      /* Number of sectors to read */
)
{
  /* USER CODE BEGIN READ */
	sflash_read(buff,sector<<12,count<<12);
    return RES_OK;
  /* USER CODE END READ */
}

/**
  * @brief  Writes Sector(s)  
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT sflash_disk_write (
	BYTE pdrv,          /* Physical drive nmuber to identify the drive */
	const BYTE *buff,   /* Data to be written */
	DWORD sector,       /* Sector address in LBA */
	UINT count          /* Number of sectors to write */
)
{ 
  /* USER CODE BEGIN WRITE */
  /* USER CODE HERE */
	uint32_t write_addr; 
	write_addr = sector<<12;    
	sflash_write((uint8_t*)buff,write_addr,count<<12);
	
    return RES_OK;
  /* USER CODE END WRITE */
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation  
  * @param  pdrv: Physical drive number (0..)
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT sflash_disk_ioctl (
	BYTE pdrv,      /* Physical drive nmuber (0..) */
	BYTE cmd,       /* Control code */
	void *buff      /* Buffer to send/receive control data */
)
{
  /* USER CODE BEGIN IOCTL */
    DRESULT res = RES_ERROR;
	switch (cmd) 
	{
        /* 扇区数量：4096*2048/1024/1024=8(MB) */
        case GET_SECTOR_COUNT:
          *(DWORD * )buff = 2048;		
        break;
        /* 扇区大小  */
        case GET_SECTOR_SIZE :
          *(WORD * )buff = 4096;
        break;
        /* 同时擦除扇区个数 */
        case GET_BLOCK_SIZE :
          *(DWORD * )buff = 1;
        break;        
      }
    res = RES_OK;
    return res;
  /* USER CODE END IOCTL */
}
#endif /* _USE_IOCTL == 1 */






/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

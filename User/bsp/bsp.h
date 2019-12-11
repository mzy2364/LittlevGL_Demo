/*
*******************************************************************************************************
*
* 文件名称 : bsp.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : BSP头文件,该文件包含所有需要的头文件,其余文件只需包含这一个头文件即可
* 
*******************************************************************************************************
*/

#ifndef _BSP_H
#define _BSP_H


/* 头文件 -----------------------------------------------------------*/
/*C library*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*STM32&CMSIS*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"


/*BSP*/
#include "led.h"
#include "usart.h"
#include "key_fifo.h"
#include "wks.h"
#include "fmc.h"
#include "ltdc.h"
#include "delay.h"
#include "i2c.h"
#include "gt9147.h"
#include "sdio_sdcard.h"
#include "spi.h"
#include "sflash.h"
#include "fatfs.h"
#include "esp12s.h"
#include "rtc.h"
#include "setting.h"
#include "adc.h"


/*GUI*/
#include "lvgl.h"
#include "lv_port_disp_bison_board.h"
#include "lv_port_indev_bison_board.h"

/*RTOS*/
#include "rtthread.h"


/*FATFS*/
#include "ff.h"
#include "fatfs.h"
#include "ff_gen_drv.h"




/* 宏定义 -----------------------------------------------------------*/

#define FIRMWARE_VERSION "V1.0"		//固件版本

/*时钟选择*/
#define CLOCK_240M
#ifndef CLOCK_240M
#define CLOCK_192M
#endif





/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/

void bsp_init(void);
void print_logo(void);
void Error_Handler(void);
void SystemClock_Config(void);
void bsp_tim_init(void);



#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

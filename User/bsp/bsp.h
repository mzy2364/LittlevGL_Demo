/*
*******************************************************************************************************
*
* �ļ����� : bsp.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : BSPͷ�ļ�,���ļ�����������Ҫ��ͷ�ļ�,�����ļ�ֻ�������һ��ͷ�ļ�����
* 
*******************************************************************************************************
*/

#ifndef _BSP_H
#define _BSP_H


/* ͷ�ļ� -----------------------------------------------------------*/
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




/* �궨�� -----------------------------------------------------------*/

#define FIRMWARE_VERSION "V1.0"		//�̼��汾

/*ʱ��ѡ��*/
#define CLOCK_240M
#ifndef CLOCK_240M
#define CLOCK_192M
#endif





/* ȫ�ֱ��� ----------------------------------------------------------*/


/* �������� ----------------------------------------------------------*/

void bsp_init(void);
void print_logo(void);
void Error_Handler(void);
void SystemClock_Config(void);
void bsp_tim_init(void);



#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

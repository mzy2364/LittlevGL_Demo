/*
*******************************************************************************************************
*
* �ļ����� : gui_user.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : GUI �� RTOS ��Ӳ���Ľ����ļ���ʹ��ʱע������ MCU �˺�ģ������
* 
*******************************************************************************************************
*/

#ifndef _GUI_USER_H
#define _GUI_USER_H

/* ͷ�ļ� -----------------------------------------------------------*/
#include "lvgl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#if defined (__CC_ARM)
#include "bsp.h"
#include "task.h"
#endif

/* �궨�� -----------------------------------------------------------*/






/* ȫ�ֱ��� ----------------------------------------------------------*/

/* ����������ʽ���� */
extern lv_style_t style_cn_12;
extern lv_style_t style_cn_16;
extern lv_style_t style_cn_24;
extern lv_style_t style_cn_32;

/* ����ȫ�ֱ��� */
LV_FONT_DECLARE(gb2312_puhui12)
LV_FONT_DECLARE(gb2312_puhui16)
LV_FONT_DECLARE(gb2312_puhui24)
LV_FONT_DECLARE(gb2312_puhui32)

/* ͼƬȫ�ֱ��� */



/* �������� ----------------------------------------------------------*/


/* APP�������� */

void lv_app_main(void);

uint32_t color_change(uint32_t color);

uint8_t lv_load_user_font_from_file(void);	//��������
lv_img_dsc_t *lv_load_image_from_file(const char *file_name);
uint8_t lv_load_img_bin_from_file(lv_img_dsc_t *image, const char *file_name);
void lv_font_cn_style_init(void);

/* Ӳ��������غ��� */
void gui_hal_led_toggle(void);
void gui_hal_backlight(uint8_t light);
void gui_hal_led_set_color(uint32_t color);
uint32_t gui_hal_led_get_current_color(void);
uint8_t gui_hal_adc_light_get_ratio(void);
uint8_t gui_hal_cpuusage_get(void);






#endif



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/


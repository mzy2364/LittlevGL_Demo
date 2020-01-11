/*
*******************************************************************************************************
*
* 文件名称 : gui_user.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : GUI 与 RTOS 和硬件的交互文件，使用时注意区分 MCU 端和模拟器端
* 
*******************************************************************************************************
*/

#ifndef _GUI_USER_H
#define _GUI_USER_H

/* 头文件 -----------------------------------------------------------*/
#include "lvgl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#if defined (__CC_ARM)
#include "bsp.h"
#include "task.h"
#endif

/* 宏定义 -----------------------------------------------------------*/






/* 全局变量 ----------------------------------------------------------*/

/* 中文字体样式定义 */
extern lv_style_t style_cn_12;
extern lv_style_t style_cn_16;
extern lv_style_t style_cn_24;
extern lv_style_t style_cn_32;

/* 字体全局变量 */
LV_FONT_DECLARE(gb2312_puhui12)
LV_FONT_DECLARE(gb2312_puhui16)
LV_FONT_DECLARE(gb2312_puhui24)
LV_FONT_DECLARE(gb2312_puhui32)

/* 图片全局变量 */



/* 函数声明 ----------------------------------------------------------*/


/* APP函数声明 */

void lv_app_main(void);

uint32_t color_change(uint32_t color);

uint8_t lv_load_user_font_from_file(void);	//加载字体
lv_img_dsc_t *lv_load_image_from_file(const char *file_name);
uint8_t lv_load_img_bin_from_file(lv_img_dsc_t *image, const char *file_name);
void lv_font_cn_style_init(void);

/* 硬件操作相关函数 */
void gui_hal_led_toggle(void);
void gui_hal_backlight(uint8_t light);
void gui_hal_led_set_color(uint32_t color);
uint32_t gui_hal_led_get_current_color(void);
uint8_t gui_hal_adc_light_get_ratio(void);
uint8_t gui_hal_cpuusage_get(void);






#endif



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


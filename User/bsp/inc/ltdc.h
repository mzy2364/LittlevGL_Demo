/*
*******************************************************************************************************
*
* 文件名称 : ltdc.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : LTDC显示静态图片驱动文件
* 
*******************************************************************************************************
*/

#ifndef _LTDC_H
#define _LTDC_H


/* 头文件 -----------------------------------------------------------*/

#include "bsp.h"




/* 宏定义 -----------------------------------------------------------*/

/* 屏幕分辨率大小 */
#define XSIZE_PHYS_L0 480
#define YSIZE_PHYS_L0 800

#define XSIZE_PHYS_L1 400
#define YSIZE_PHYS_L1 220

/* 背光引脚 */
#define LCD_EN_PIN GPIO_PIN_1
#define LCD_EN_GPIO_PORT GPIOA


/* 颜色 */
#define LCD_COLOR_BLUE          ((uint32_t)0xFF0000FF)
#define LCD_COLOR_GREEN         ((uint32_t)0xFF00FF00)
#define LCD_COLOR_RED           ((uint32_t)0xFFFF0000)
#define LCD_COLOR_CYAN          ((uint32_t)0xFF00FFFF)
#define LCD_COLOR_MAGENTA       ((uint32_t)0xFFFF00FF)
#define LCD_COLOR_YELLOW        ((uint32_t)0xFFFFFF00)
#define LCD_COLOR_LIGHTBLUE     ((uint32_t)0xFF8080FF)
#define LCD_COLOR_LIGHTGREEN    ((uint32_t)0xFF80FF80)
#define LCD_COLOR_LIGHTRED      ((uint32_t)0xFFFF8080)
#define LCD_COLOR_LIGHTCYAN     ((uint32_t)0xFF80FFFF)
#define LCD_COLOR_LIGHTMAGENTA  ((uint32_t)0xFFFF80FF)
#define LCD_COLOR_LIGHTYELLOW   ((uint32_t)0xFFFFFF80)
#define LCD_COLOR_DARKBLUE      ((uint32_t)0xFF000080)
#define LCD_COLOR_DARKGREEN     ((uint32_t)0xFF008000)
#define LCD_COLOR_DARKRED       ((uint32_t)0xFF800000)
#define LCD_COLOR_DARKCYAN      ((uint32_t)0xFF008080)
#define LCD_COLOR_DARKMAGENTA   ((uint32_t)0xFF800080)
#define LCD_COLOR_DARKYELLOW    ((uint32_t)0xFF808000)
#define LCD_COLOR_WHITE         ((uint32_t)0xFFFFFFFF)
#define LCD_COLOR_LIGHTGRAY     ((uint32_t)0xFFD3D3D3)
#define LCD_COLOR_GRAY          ((uint32_t)0xFF808080)
#define LCD_COLOR_DARKGRAY      ((uint32_t)0xFF404040)
#define LCD_COLOR_BLACK         ((uint32_t)0xFF000000)
#define LCD_COLOR_BROWN         ((uint32_t)0xFFA52A2A)
#define LCD_COLOR_ORANGE        ((uint32_t)0xFFFFA500)
#define LCD_COLOR_TRANSPARENT   ((uint32_t)0xFF000000)


/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/


void ltdc_init(void);
void lcd_backlight(uint8_t light);

void ltdc_draw_point(uint16_t x,uint16_t y,uint32_t color,uint8_t layer);
uint32_t ltdc_read_point(uint16_t x,uint16_t y,uint8_t layer);
void ltdc_clear_layer(uint32_t color,uint8_t layer);
void ltdc_draw_logo(void);

void ltdc_draw_string(uint16_t x,uint16_t y,uint8_t *text,uint8_t size,uint32_t fontcolor,uint32_t bkcolor);
void ltdc_draw_char(uint16_t x,uint16_t y,uint8_t c,uint8_t size,uint32_t fontcolor,uint32_t bkcolor);
void ltdc_delete_layer1(void);
static void lcd_pwm_init(void);
void lcd_backlight(uint8_t light);





#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* 文件名称 : gt9147.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : GT9147触摸屏驱动文件
* 
*******************************************************************************************************
*/

#ifndef _GT9147_H
#define _GT9147_H


/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"


/* 宏定义 -----------------------------------------------------------*/

/* IO操作定义 */
#define CT_RST(n) (n?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET))

#define CT_INT	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)

/* GT9147-I2C地址 */
#define GT9147_ADDRESS	0xBB
//#define GT9147_ADDRESS	0x28


//#define GT9147_ADDR	0x5D
//#define GT9147_WR	0xBA
//#define GT9147_RD	0xBB

//#define GT9147_ADDR	0x14
//#define GT9147_WR	0x28
//#define GT9147_RD	0x29


/* GT9147部分寄存器定义 */
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校验和寄存器
#define GT_PID_REG 		0X8140   	//GT9147产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址  

#define TP_PRES_DOWN    0x80  //触屏被按下	  
#define TP_CATH_PRES    0x40  //有按键按下了 


/* 定义一个 */
typedef struct
{
	uint16_t x[5];
	uint16_t y[5];
	uint8_t ispressed;
}GT9147_PointTypeDef;



/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/
void gt9147_init(void);
uint8_t gt9147_scan(GT9147_PointTypeDef *scan_point);
uint8_t gt9147_is_pressed(void);
void gt9147_clear_pressed(void);









#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* �ļ����� : gt9147.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : GT9147�����������ļ�
* 
*******************************************************************************************************
*/

#ifndef _GT9147_H
#define _GT9147_H


/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"


/* �궨�� -----------------------------------------------------------*/

/* IO�������� */
#define CT_RST(n) (n?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET))

#define CT_INT	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)

/* GT9147-I2C��ַ */
#define GT9147_ADDRESS	0xBB
//#define GT9147_ADDRESS	0x28


//#define GT9147_ADDR	0x5D
//#define GT9147_WR	0xBA
//#define GT9147_RD	0xBB

//#define GT9147_ADDR	0x14
//#define GT9147_WR	0x28
//#define GT9147_RD	0x29


/* GT9147���ּĴ������� */
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  

#define TP_PRES_DOWN    0x80  //����������	  
#define TP_CATH_PRES    0x40  //�а��������� 


/* ����һ�� */
typedef struct
{
	uint16_t x[5];
	uint16_t y[5];
	uint8_t ispressed;
}GT9147_PointTypeDef;



/* ȫ�ֱ��� ----------------------------------------------------------*/


/* �������� ----------------------------------------------------------*/
void gt9147_init(void);
uint8_t gt9147_scan(GT9147_PointTypeDef *scan_point);
uint8_t gt9147_is_pressed(void);
void gt9147_clear_pressed(void);









#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* �ļ����� : wks.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : IOģ��Һ������Ҫ��SPI��ʼ��,��Һ�������Ҵ�����ֲ,����̫��ע��
* 
*******************************************************************************************************
*/



#ifndef _WKS_H
#define _WKS_H

/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"

/* �궨�� -----------------------------------------------------------*/

/* ����IO���� */
#define LCD_RST(n) (n?HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET))

#define LCD_CS(n) (n?HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET))

#define LCD_SCL(n) (n?HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET))

#define LCD_SDA(n) (n?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET))


/* �������� ----------------------------------------------------------*/

void LCD_initial(void);







#endif


/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

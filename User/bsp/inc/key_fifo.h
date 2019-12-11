/*
*******************************************************************************************************
*
* �ļ����� : key_fifo.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : ��������ͷ�ļ�
* 
*******************************************************************************************************
*/

#ifndef _KEY_FIFO_H
#define _KEY_FIFO_H



/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"



/* �궨�� -----------------------------------------------------------*/

/* �����˿ڶ��� */
#define KEY_WKUP_PIN GPIO_PIN_0
#define KEY_WKUP_GPIO_PORT GPIOA
#define KEY_WKUP_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()

#define KEY_RIGHT_PIN GPIO_PIN_2
#define KEY_RIGHT_GPIO_PORT GPIOH
#define KEY_RIGHT_CLK_ENABLE __HAL_RCC_GPIOH_CLK_ENABLE()

#define KEY_LEFT_PIN GPIO_PIN_7
#define KEY_LEFT_GPIO_PORT GPIOD
#define KEY_LEFT_CLK_ENABLE __HAL_RCC_GPIOD_CLK_ENABLE()


/* �������� */
#define KEY_COUNT 4
/* �����˲�ʱ�� ��λ10ms */
#define KEY_FILTER_TIME   5
/* ��������ʱ�� ��λ10ms */
#define KEY_LONG_TIME     100
/* ���尴��FIFO��������С */
#define KEY_FIFO_SIZE	4



/* typedef -----------------------------------------------------------*/

/* �����Ƿ��� */
typedef enum
{
	KEY_ISDOWN = 0,
	KEY_NOTDOWN,
}KEY_DOWN;


/* �������� */
typedef enum
{
	KEY_NONE = 0,
	
	KEY_LEFT_DOWN,
	KEY_LEFT_UP,
	KEY_LEFT_LONG,
	
	KEY_WKUP_DOWN,
	KEY_WKUP_UP,
	KEY_WKUP_LONG,
	
	KEY_RIGHT_DOWN,
	KEY_RIGHT_UP,
	KEY_RIGHT_LONG,
	
	KEY_POWER_DOWN,
	KEY_POWER_UP,
	KEY_POWER_LONG,
	
}KEY_ENUM;


/* �����ṹ�� */
typedef struct
{
	uint8_t (*IsKeyDownFunc)(void);		//�����Ƿ��µĺ���ָ��
	
	uint8_t Count;	//�˲���������
	uint16_t LongCount;	//����������
	uint16_t LongTime;	//�������µ�ʱ��
	uint8_t State;		//�����ĵ�ǰ״̬
	uint8_t RepeatSpeed;	//������������
	uint8_t RepeatCount;		//��������������	
	
	
}KEY_T;


/* fifo�ṹ�� */
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];        //����������
	uint8_t Read;                      //��ָ��
	uint8_t Write;                     //дָ��
	
}KEY_FIFO;




/* �������� ----------------------------------------------------------*/

/* �ⲿ���ú��� */
void key_fifo_init(void);
void key_clear(void);
uint8_t key_is_init(void);
void key_scan(void);
uint8_t key_get(void);


/* ���ڲ����ú��� */
void key_put(uint8_t keyCode);
static void key_gpio_config(void);
static void key_var_init(void);
static void key_detect(uint8_t i);
 
#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

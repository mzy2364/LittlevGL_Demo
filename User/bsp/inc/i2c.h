/*
*******************************************************************************************************
*
* �ļ����� : i2c.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : I2C�����ļ�
* 
*******************************************************************************************************
*/

#ifndef _I2C_H
#define _I2C_H


/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"

/* �궨�� -----------------------------------------------------------*/



/* ѡ�����I2C����Ӳ��I2C */
//#define SOFTWARE_I2C
#ifndef SOFTWARE_I2C
#define HARDWARE_I2C
#endif

/* SOFTWARE_I2C��IO���� */
#ifdef SOFTWARE_I2C
#define SDA_OUT(n)	(n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_8,GPIO_PIN_RESET))
#define SDA_IN		HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_8)
#define SCL_OUT(n)	(n?HAL_GPIO_WritePin(GPIOH,GPIO_PIN_7,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOH,GPIO_PIN_7,GPIO_PIN_RESET))
#endif

/* I2C�洢���ĵ�ַ���� */
#define I2C_MEMADD_8BIT            0x00000001U
#define I2C_MEMADD_16BIT           0x00000010U

/* typedef -----------------------------------------------------------*/
typedef enum{SOFT_I2C_OK=0,SOFT_I2C_ERR}SOFT_I2C_StatusTypeDef;




/* ȫ�ֱ��� ----------------------------------------------------------*/
#ifdef HARDWARE_I2C
//extern I2C_HandleTypeDef hi2c3;
#endif

/* �������� ----------------------------------------------------------*/

void i2c3_init(void);

uint8_t i2c3_master_send_data(uint16_t dev_addr,uint8_t *pbuffer,uint16_t len,uint32_t time_out);
uint8_t i2c3_master_receive_data(uint16_t dev_addr,uint8_t *pbuffer,uint16_t len,uint32_t time_out);
uint8_t i2c3_mem_write(uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_add_size, uint8_t *pbuffer, uint16_t len, uint32_t time_out);
uint8_t i2c3_mem_read(uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_add_size, uint8_t *pbuffer, uint16_t len, uint32_t time_out);


void soft_i2c_start(void);
void soft_i2c_stop(void);
uint8_t soft_i2c_wait_ack(uint32_t time_out);
void soft_i2c_ack(void);
void soft_i2c_no_ack(void);
void soft_i2c_send_byte(uint8_t byte);
uint8_t soft_i2c_receive_byte(void);












#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

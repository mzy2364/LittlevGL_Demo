/*
*******************************************************************************************************
*
* �ļ����� : esp12s.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : ESP12S WIFIģ����������
* 
*******************************************************************************************************
*/

#ifndef _ESP12S_H
#define _ESP12S_H


/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"


/* �궨�� -----------------------------------------------------------*/

/* ���ڻ��������ֵ */
#define ESP12S_BUF_MAX_LENGTH	512


#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־

/* GPIO���� */
#define NRF_PWR_PIN GPIO_PIN_4
#define NRF_PWR_GPIO_PORT GPIOH
#define ESP_EN_PIN GPIO_PIN_3
#define ESP_EN_GPIO_PORT GPIOG
#define ESP_RST_PIN GPIO_PIN_8
#define ESP_RST_GPIO_PORT GPIOA

/* Ĭ��WIFI�˺����� */
#define SSID	"mzy2364"
#define PWD		"mzy236464"

/* ���������� */
#define SERVER  "192.168.0.103"
#define PORT    "1500"



/* ʱ������� */
#define TIME_SERVER_IP		"39.108.149.228"
#define TIME_SERVER_PORT	"16900"



/* ȫ�ֱ��� ----------------------------------------------------------*/


/* �������� ----------------------------------------------------------*/

uint8_t esp12s_init(unsigned char *ssid,unsigned char *pwd);
uint8_t esp12s_connect_server(unsigned char *server_ip,unsigned char *server_port,unsigned char *key);
uint8_t esp12s_get_status(void);
uint8_t esp12s_join_ap(unsigned char *ssid,unsigned char *pwd);
uint8_t *esp12s_get_IPD(uint16_t  time_out);
void esp12s_send_data(unsigned char *data, uint16_t len);
uint8_t esp12s_wait_recive(void);
char *esp12s_buf_find(unsigned char *str);
void esp12s_en(uint8_t enable);
uint8_t esp12s_update_time(unsigned char *server_ip,unsigned char *server_port,unsigned char *key,RTC_DateTypeDef *date,RTC_TimeTypeDef *time);




#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

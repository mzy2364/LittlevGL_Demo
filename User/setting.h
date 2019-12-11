/*
*******************************************************************************************************
*
* �ļ����� : setting.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : ����һЩ������Ϣ,���ݴ洢��EEPROM����
* 
*******************************************************************************************************
*/

#ifndef _SETTING_H
#define _SETTING_H


/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"

/* �궨�� -----------------------------------------------------------*/

/* setting�ṹ�嶨�� */
typedef struct{
	uint8_t *wlan_ssid;         //WIFI����
	uint8_t *wlan_pwd;          //WIFI����
	uint8_t *server_ip;         //������IP
	uint8_t *server_port;       //�������˿�
	uint8_t backlight;          //��Ļ����
	uint8_t wlan_power;	        //WIFI����
	uint8_t wallpaper_index;    //��ֽ�ı��
	
}_SETTING;


/* ���ݴ洢��ַ���� */
#define SSID_ADDR	0
#define SSID_ADDR_MAXLEN	16
#define PWD_ADDR	16
#define PWD_ADDR_MAXLEN		16
#define SERVERIP_ADDR	32
#define SERVERIP_ADDR_MAXLEN	15
#define SERVERPORT_ADDR		48
#define SERVERPORT_ADDR_MAXLEN		5
#define BACKLIGHT_ADDR		53
#define BACKLIGHT_ADDR_MAXLEN		1
#define WLANPOWER_ADDR		54
#define WLANPOWER_ADDR_MAXLEN		1
#define WALLPAPER_ADDR		55
#define WALLPAPER_ADDR_MAXLEN		1


/* ȫ�ֱ��� ----------------------------------------------------------*/


/* �������� ----------------------------------------------------------*/

void setting_init(void);
void setting_read(_SETTING *setting);
void setting_write(_SETTING *setting);

#endif

/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

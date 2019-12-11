/*
*******************************************************************************************************
*
* 文件名称 : setting.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 处理一些配置信息,数据存储在EEPROM里面
* 
*******************************************************************************************************
*/

#ifndef _SETTING_H
#define _SETTING_H


/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"

/* 宏定义 -----------------------------------------------------------*/

/* setting结构体定义 */
typedef struct{
	uint8_t *wlan_ssid;         //WIFI名称
	uint8_t *wlan_pwd;          //WIFI密码
	uint8_t *server_ip;         //服务器IP
	uint8_t *server_port;       //服务器端口
	uint8_t backlight;          //屏幕背光
	uint8_t wlan_power;	        //WIFI开关
	uint8_t wallpaper_index;    //壁纸的编号
	
}_SETTING;


/* 数据存储地址定义 */
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


/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/

void setting_init(void);
void setting_read(_SETTING *setting);
void setting_write(_SETTING *setting);

#endif

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

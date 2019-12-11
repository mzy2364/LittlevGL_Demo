/*
*******************************************************************************************************
*
* 文件名称 : setting.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 处理一些配置信息,数据存储在EEPROM里面
* Warning  : 利用_SETTING定义新的结构体后,必须先read一次为结构体指针申请内存或者自行申请内存
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "setting.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
static __IO uint8_t _server_ip[16];
static __IO uint8_t _server_port[6];
static __IO uint8_t _wlan_ssid[17];
static __IO uint8_t _wlan_pwd[17];
static __IO uint8_t _backlight = 100;
static __IO uint8_t _wlan_power = 1;

static __IO _SETTING my_setting = {
	.wlan_ssid = (uint8_t *)_wlan_ssid,
	.wlan_pwd = (uint8_t *)_wlan_pwd,
	.server_ip = (uint8_t *)_server_ip,
	.server_port = (uint8_t *)_server_port,
	.backlight = 100,
	.wlan_power = 1,
	.wallpaper_index = 0
};



/* 函数声明 ---------------------------------------------------------*/

/**
  * @brief SETTING初始化
  * @param None
  * @retval	None
  * @note 初始化的时候从EEPROM读取配置信息,后面再READ的时候就直接从my_setting赋值
  */
void setting_init(void)
{
	eeprom_read(SSID_ADDR,my_setting.wlan_ssid,SSID_ADDR_MAXLEN);
	eeprom_read(PWD_ADDR,my_setting.wlan_pwd,PWD_ADDR_MAXLEN);
	eeprom_read(SERVERIP_ADDR,my_setting.server_ip,SERVERIP_ADDR_MAXLEN);
	eeprom_read(SERVERPORT_ADDR,my_setting.server_port,SERVERPORT_ADDR_MAXLEN);
	eeprom_read(BACKLIGHT_ADDR,(uint8_t *)&my_setting.backlight,BACKLIGHT_ADDR_MAXLEN);
	eeprom_read(WLANPOWER_ADDR,(uint8_t *)&my_setting.wlan_power,WLANPOWER_ADDR_MAXLEN);
	eeprom_read(WALLPAPER_ADDR,(uint8_t *)&my_setting.wallpaper_index,WALLPAPER_ADDR_MAXLEN);
	//printf("wlan_power:%d\r\n",my_setting.wlan_power);
	//printf("my_setting.backlight:%d\r\n",my_setting.backlight);
	//printf("my_setting.wallpaper_index:%d\r\n",my_setting.wallpaper_index);
	
	if(my_setting.backlight <= 0 || my_setting.backlight > 100 || my_setting.wlan_power > 1)
	{
		my_setting.backlight = 100;
		my_setting.wlan_power = 0;
		delay_ms(100);
		setting_write((_SETTING *)&my_setting);
	}

}



/**
  * @brief 从EEPROM读取配置信息
  * @param *setting-保存配置信息的结构体指针
  * @retval	None
  */
void setting_read(_SETTING *setting)
{
	/* 先读到my_setting里面再赋值过去,这样在应用中就不用为指针申请内存了 */
	
//	eeprom_read(SSID_ADDR,my_setting.wlan_ssid,SSID_ADDR_MAXLEN);
//	eeprom_read(PWD_ADDR,my_setting.wlan_pwd,PWD_ADDR_MAXLEN);
//	eeprom_read(SERVERIP_ADDR,my_setting.server_ip,SERVERIP_ADDR_MAXLEN);
//	eeprom_read(SERVERPORT_ADDR,my_setting.server_port,SERVERPORT_ADDR_MAXLEN);
//	eeprom_read(BACKLIGHT_ADDR,&my_setting.backlight,BACKLIGHT_ADDR_MAXLEN);
	
	setting->wlan_ssid = my_setting.wlan_ssid;
	setting->wlan_pwd = my_setting.wlan_pwd;
	setting->server_ip = my_setting.server_ip;
	setting->server_port = my_setting.server_port;
	setting->backlight = my_setting.backlight;
	setting->wlan_power = my_setting.wlan_power;
	setting->wallpaper_index = my_setting.wallpaper_index;
	
}

/**
  * @brief 向EEPROM写入配置信息
  * @param *setting-保存配置信息的结构体指针
  * @retval	None
  */
void setting_write(_SETTING *setting)
{
	
	my_setting.wlan_ssid = setting->wlan_ssid;
	my_setting.wlan_pwd =setting->wlan_pwd;
	my_setting.server_ip = setting->server_ip;
	my_setting.server_port = setting->server_port;
	my_setting.backlight = setting->backlight;
	my_setting.wlan_power = setting->wlan_power;
	my_setting.wallpaper_index = setting->wallpaper_index;
	
	eeprom_write(SSID_ADDR,my_setting.wlan_ssid,SSID_ADDR_MAXLEN);
	eeprom_write(PWD_ADDR,my_setting.wlan_pwd,PWD_ADDR_MAXLEN);
	eeprom_write(SERVERIP_ADDR,my_setting.server_ip,SERVERIP_ADDR_MAXLEN);
	eeprom_write(SERVERPORT_ADDR,my_setting.server_port,SERVERPORT_ADDR_MAXLEN);
	eeprom_write(BACKLIGHT_ADDR,(uint8_t *)&my_setting.backlight,BACKLIGHT_ADDR_MAXLEN);
	eeprom_write(WLANPOWER_ADDR,(uint8_t *)&my_setting.wlan_power,WLANPOWER_ADDR_MAXLEN);
	eeprom_write(WALLPAPER_ADDR,(uint8_t *)&my_setting.wallpaper_index,WALLPAPER_ADDR_MAXLEN);
	//printf("_wlan_power:%d\r\n",my_setting.wlan_power);
	
	
}



















/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

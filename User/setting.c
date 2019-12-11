/*
*******************************************************************************************************
*
* �ļ����� : setting.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : ����һЩ������Ϣ,���ݴ洢��EEPROM����
* Warning  : ����_SETTING�����µĽṹ���,������readһ��Ϊ�ṹ��ָ�������ڴ�������������ڴ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "setting.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/
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



/* �������� ---------------------------------------------------------*/

/**
  * @brief SETTING��ʼ��
  * @param None
  * @retval	None
  * @note ��ʼ����ʱ���EEPROM��ȡ������Ϣ,������READ��ʱ���ֱ�Ӵ�my_setting��ֵ
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
  * @brief ��EEPROM��ȡ������Ϣ
  * @param *setting-����������Ϣ�Ľṹ��ָ��
  * @retval	None
  */
void setting_read(_SETTING *setting)
{
	/* �ȶ���my_setting�����ٸ�ֵ��ȥ,������Ӧ���оͲ���Ϊָ�������ڴ��� */
	
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
  * @brief ��EEPROMд��������Ϣ
  * @param *setting-����������Ϣ�Ľṹ��ָ��
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



















/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

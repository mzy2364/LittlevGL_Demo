/*
*******************************************************************************************************
*
* 文件名称 : esp12s.h
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : ESP12S WIFI模块驱动例程
* 
*******************************************************************************************************
*/

#ifndef _ESP12S_H
#define _ESP12S_H


/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"


/* 宏定义 -----------------------------------------------------------*/

/* 串口缓冲区最大值 */
#define ESP12S_BUF_MAX_LENGTH	512


#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志

/* GPIO定义 */
#define NRF_PWR_PIN GPIO_PIN_4
#define NRF_PWR_GPIO_PORT GPIOH
#define ESP_EN_PIN GPIO_PIN_3
#define ESP_EN_GPIO_PORT GPIOG
#define ESP_RST_PIN GPIO_PIN_8
#define ESP_RST_GPIO_PORT GPIOA

/* 默认WIFI账号密码 */
#define SSID	"mzy2364"
#define PWD		"mzy236464"

/* 服务器参数 */
#define SERVER  "192.168.0.103"
#define PORT    "1500"



/* 时间服务器 */
#define TIME_SERVER_IP		"39.108.149.228"
#define TIME_SERVER_PORT	"16900"



/* 全局变量 ----------------------------------------------------------*/


/* 函数声明 ----------------------------------------------------------*/

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

/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

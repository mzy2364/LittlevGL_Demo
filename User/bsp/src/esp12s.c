/*
*******************************************************************************************************
*
* 文件名称 : esp12s.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : ESP12S WIFI模块驱动例程
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "esp12s.h"
#include <string.h>
#include <stdio.h>


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
uint8_t esp12s_buf[ESP12S_BUF_MAX_LENGTH];
uint16_t esp12s_cnt = 0, esp12s_cntPre = 0;




/* 函数声明 ---------------------------------------------------------*/


/**
  * @brief ESP12S对应的串口发送指定长度字符串
  * @param str-字符串指针
  * @param len-字符串长度
  * @retval	None
  */
void esp12s_uart_send_string(unsigned char *str,uint16_t len)
{
	usart6_send_string(str,len);
}


/**
  * @brief ESP12S使能(ESP12S内部默认使能)
  * @param enable-0去能 1使能
  * @retval	None
  */
void esp12s_en(uint8_t enable)
{
	HAL_GPIO_WritePin(ESP_EN_GPIO_PORT,ESP_EN_PIN,(GPIO_PinState)enable);
}

/**
  * @brief ESP12S复位
  * @param None
  * @retval	None
  */
void esp12s_rst(void)
{
	HAL_GPIO_WritePin(ESP_RST_GPIO_PORT,ESP_RST_PIN,GPIO_PIN_RESET);
	delay_ms(100);
	HAL_GPIO_WritePin(ESP_RST_GPIO_PORT,ESP_RST_PIN,GPIO_PIN_SET);
}

/**
  * @brief ESP12S端口配置
  * @param None
  * @retval	None
  */
void esp12s_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = NRF_PWR_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(NRF_PWR_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = ESP_EN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(ESP_EN_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = ESP_RST_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(ESP_RST_GPIO_PORT, &GPIO_InitStruct);
	
	/* 打开NRF电源 */
	HAL_GPIO_WritePin(NRF_PWR_GPIO_PORT,NRF_PWR_PIN,GPIO_PIN_SET);
	
//	HAL_GPIO_WritePin(ESP_EN_GPIO_PORT,ESP_EN_PIN,GPIO_PIN_SET);
//	
//	HAL_GPIO_WritePin(ESP_RST_GPIO_PORT,ESP_RST_PIN,GPIO_PIN_SET);
	
}


/**
  * @brief ESP12S串口配置
  * @param None
  * @retval	None
  */
void esp12s_usart_config(void)
{
	
}



/**
  * @brief 清空缓冲区
  * @param None
  * @retval	None
  */
void esp12s_clear()
{
	memset(esp12s_buf, 0, ESP12S_BUF_MAX_LENGTH);
	esp12s_cnt = 0;
}





/**
  * @brief 等待接收完成
  * @param None
  * @retval	REV_OK-接收完成		REV_WAIT-接收超时未完成
  * @note 循环调用检测是否接收完成
  */
uint8_t esp12s_wait_recive(void)
{

	if(esp12s_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return REV_WAIT;
		
	if(esp12s_cnt == esp12s_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
	{
		esp12s_cnt = 0;							//清0接收计数
			
		return REV_OK;								//返回接收完成标志
	}
		
	esp12s_cntPre = esp12s_cnt;					//置为相同
	
	return REV_WAIT;								//返回接收未完成标志

}



/**
  * @brief 发送命令
  * @param cmd-命令字符串
  * @param res-需要检查的返回指令
  * @retval	0-成功	1-失败
  */
uint8_t esp12s_send_cmd(unsigned char *cmd, unsigned char *res)
{
	
	uint8_t time_out = 200;

	esp12s_uart_send_string(cmd, strlen((const char *)cmd));
	
	while(time_out--)
	{
		if(esp12s_wait_recive() == REV_OK)							//如果收到数据
		{
			if(strstr((const char *)esp12s_buf, (const char *)res) != NULL)		//如果检索到关键词
			{
				esp12s_clear();									//清空缓存
				
				return 0;
			}
		}
		
		delay_ms(10);
	}
	
	return 1;

}



/**
  * @brief 发送数据
  * @param data-数据
  * @param len-长度
  * @retval None
  */
void esp12s_send_data(unsigned char *data, uint16_t len)
{

	uint8_t cmd_buf[32];
	
	esp12s_clear();								//清空接收缓存
	sprintf((char *)cmd_buf, "AT+CIPSEND=%d\r\n", len);		//发送命令
	if(!esp12s_send_cmd((unsigned char *)cmd_buf, (unsigned char *)">"))				//收到‘>’时可以发送数据
	{
		esp12s_uart_send_string(data, len);		//发送设备连接请求数据
	}

}


/**
  * @brief 获取WIFI接收的数据
  * @param time_out-等待的时间(单位:10ms)
  * @retval 平台返回的原始数据
  * @note 说明：不同网络设备返回的格式不同，需要去调试
  * @note 如ESP8266的返回格式为	"+IPD,x:yyy"	x代表数据长度，yyy是数据内容
  */
uint8_t *esp12s_get_IPD(uint16_t  time_out)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(esp12s_wait_recive() == REV_OK)								//如果接收完成
		{
			ptrIPD = strstr((const char *)esp12s_buf, "IPD,");				//搜索“IPD”头
			if(ptrIPD == NULL)											//如果没找到，可能是IPD头的延迟，还是需要等待一会，但不会超过设定的时间
			{
				//UsartPrintf(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//找到':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (uint8_t *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		delay_ms(5);													//延时等待
	} while(time_out--);
	
	return NULL;														//超时还未找到，返回空指针
}


/**
  * @brief ESP12S连接AP
  * @param ssid-wifi账号
  * @param pwd-wifi密码
  * @retval 0-成功  1-失败
  */
uint8_t esp12s_join_ap(unsigned char *ssid,unsigned char *pwd)
{
	uint8_t error=0;
	unsigned char ap_buf[64];
	//"AT+CWJAP=\"whyhs\",\"whyhs2015\"\r\n"
	sprintf((char *)ap_buf,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pwd);
	while(esp12s_send_cmd((unsigned char *)ap_buf, (unsigned char *)"GOT IP"))
	{
		if(error>=10)
			return 1;
		delay_ms(500);
		error++;
	}
	return 0;
}


/**
  * @brief 在ESP12S缓冲区查找对应的字符串
  * @param str-需要查找的字符串
  * @retval	查找结果
  */
char *esp12s_buf_find(unsigned char *str)
{
	
	return strstr((void*)esp12s_buf, (void*)str);
	
}


/**
  * @brief ESP12S初始化
  * @param ssid-wifi账号
  * @param pwd-wifi密码
  * @retval 0-成功  1-失败
  */
uint8_t esp12s_init(unsigned char *ssid,unsigned char *pwd)
{

	uint8_t error = 0;
	
	esp12s_gpio_config();
	
	esp12s_usart_config();
	
	esp12s_rst();
	
	printf("1. AT\r\n");
	while(esp12s_send_cmd((unsigned char *)"AT\r\n", (unsigned char *)"OK"))
	{
		if(error>=10)
			return 1;
		delay_ms(500);
		error++;
	}
	error=0;
	
	printf("2. ATE0\r\n");
	while(esp12s_send_cmd((unsigned char *)"ATE0\r\n", (unsigned char *)"OK"))
	{
		if(error>=10)
			return 1;
		delay_ms(500);
		error++;
	}
	error=0;
	
	printf("3. CWMODE\r\n");
	while(esp12s_send_cmd((unsigned char *)"AT+CWMODE=1\r\n", (unsigned char *)"OK"))
	{
		if(error>=10)
			return 1;
		delay_ms(500);
		error++;
	}
	error=0;
	
	printf("4. CWJAP\r\n");
	if(esp12s_join_ap(ssid,pwd)==1)	//连接失败
		return 1;

	printf("5. ESP12S Init OK\r\n");
	return 0;

}



/**
  * @brief ESP12S获取网络状态
  * @param None
  * @retval 2: station 已经连接AP 获得IP地址
  *         3: station 已经建立TCP或者UDP传输
  *         4: station 断开网络连接(仍然连接AP)
  *         5: station 未连接AP
  *         0:读取失败
  */
uint8_t esp12s_get_status(void)
{
	uint8_t error = 0;
	uint8_t status_buf[1];
	
	while(esp12s_send_cmd((unsigned char *)"AT+CIPSTATUS\r\n", (unsigned char *)"STATUS:"))
	{
		if(error++ >= 10)
			return 0;
		delay_ms(500);
	}
	
	if(memcpy(status_buf,(strstr((char *)esp12s_buf,"STATUS:")+7),1) != NULL)
	{
		switch(status_buf[0])
		{
			case '2':
				return 2;
			case '3':
				return 3;
			case '4':
				return 4;
			case '5':
				return 5;
			default:
				return 0;
		}
	}
	else
	{
		return 0;
	}
	
}



/**
  * @brief ESP12S连接服务器
  * @param server_ip-服务器IP地址
  * @param server_port-服务器端口
  * @param key-鉴权信息
  * @retval 0-成功	1-失败
  * @note 连接后应立即发送鉴权信息至服务器并等待服务器回复
  */
uint8_t esp12s_connect_server(unsigned char *server_ip,unsigned char *server_port,unsigned char *key)
{
	uint8_t server_buf[64];
	uint8_t *dataPtr;
	
	esp12s_send_cmd((unsigned char *)"AT+CIPCLOSE\r\n",NULL);
	
	sprintf((char *)server_buf,"AT+CIPSTART=\"TCP\",\"%s\",%s,\r\n",server_ip,server_port);
	
	if(esp12s_send_cmd(server_buf,(unsigned char *)"CONNECT"))
		return 1;
	return 0;

//	esp12s_send_data((void *)key,strlen((void *)key));
//	
//	dataPtr = esp12s_get_IPD(500);		//等待服务器响应
//	
//	if(dataPtr != NULL)
//	{
//		if(dataPtr[0]=='1')
//			return 0;
//		else
//			return 1;
//	}
//	else
//		return 1;
	
}



/**
  * @brief ESP12S获取北京时间
  * @param server_ip-服务器IP地址
  * @param server_port-服务器端口
  * @param key-鉴权信息
  * @param date-日期结构体指针
  * @param time-时间结构体指针
  * @retval 0-成功	1-失败
  * @note 连接后服务器会发送一条json数据
  */
uint8_t esp12s_update_time(unsigned char *server_ip,unsigned char *server_port,unsigned char *key,RTC_DateTypeDef *date,RTC_TimeTypeDef *time)
{
	uint8_t server_buf[64];
	uint8_t *dataPtr;
	
	esp12s_send_cmd((unsigned char *)"AT+CIPCLOSE\r\n",NULL);
	
	sprintf((char *)server_buf,"AT+CIPSTART=\"TCP\",\"%s\",%s,\r\n",server_ip,server_port);
	
	if(esp12s_send_cmd(server_buf,(unsigned char *)"CONNECT"))
		return 1;

//	esp12s_send_data((void *)key,strlen((void *)key));
//	
	dataPtr = esp12s_get_IPD(500);		//等待服务器响应
	
	if(dataPtr != NULL)
	{
		if(dataPtr[0]=='1')
			return 0;
		else
			return 1;
	}
	else
		return 1;
	
}





/**
  * @brief  USART6接收一字节数据
  * @param  c-接收的数据
  * @retval None
  * @note 该函数会被串口中断函数调用
  */
void usart6_put_char(uint8_t c)
{
	/* USART6接收一字节 */
	if(esp12s_cnt >= ESP12S_BUF_MAX_LENGTH)
		esp12s_cnt = 0;
	esp12s_buf[esp12s_cnt++] = c;
}



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

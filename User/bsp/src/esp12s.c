/*
*******************************************************************************************************
*
* �ļ����� : esp12s.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : ESP12S WIFIģ����������
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "esp12s.h"
#include <string.h>
#include <stdio.h>


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/
uint8_t esp12s_buf[ESP12S_BUF_MAX_LENGTH];
uint16_t esp12s_cnt = 0, esp12s_cntPre = 0;




/* �������� ---------------------------------------------------------*/


/**
  * @brief ESP12S��Ӧ�Ĵ��ڷ���ָ�������ַ���
  * @param str-�ַ���ָ��
  * @param len-�ַ�������
  * @retval	None
  */
void esp12s_uart_send_string(unsigned char *str,uint16_t len)
{
	usart6_send_string(str,len);
}


/**
  * @brief ESP12Sʹ��(ESP12S�ڲ�Ĭ��ʹ��)
  * @param enable-0ȥ�� 1ʹ��
  * @retval	None
  */
void esp12s_en(uint8_t enable)
{
	HAL_GPIO_WritePin(ESP_EN_GPIO_PORT,ESP_EN_PIN,(GPIO_PinState)enable);
}

/**
  * @brief ESP12S��λ
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
  * @brief ESP12S�˿�����
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
	
	/* ��NRF��Դ */
	HAL_GPIO_WritePin(NRF_PWR_GPIO_PORT,NRF_PWR_PIN,GPIO_PIN_SET);
	
//	HAL_GPIO_WritePin(ESP_EN_GPIO_PORT,ESP_EN_PIN,GPIO_PIN_SET);
//	
//	HAL_GPIO_WritePin(ESP_RST_GPIO_PORT,ESP_RST_PIN,GPIO_PIN_SET);
	
}


/**
  * @brief ESP12S��������
  * @param None
  * @retval	None
  */
void esp12s_usart_config(void)
{
	
}



/**
  * @brief ��ջ�����
  * @param None
  * @retval	None
  */
void esp12s_clear()
{
	memset(esp12s_buf, 0, ESP12S_BUF_MAX_LENGTH);
	esp12s_cnt = 0;
}





/**
  * @brief �ȴ��������
  * @param None
  * @retval	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
  * @note ѭ�����ü���Ƿ�������
  */
uint8_t esp12s_wait_recive(void)
{

	if(esp12s_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;
		
	if(esp12s_cnt == esp12s_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
	{
		esp12s_cnt = 0;							//��0���ռ���
			
		return REV_OK;								//���ؽ�����ɱ�־
	}
		
	esp12s_cntPre = esp12s_cnt;					//��Ϊ��ͬ
	
	return REV_WAIT;								//���ؽ���δ��ɱ�־

}



/**
  * @brief ��������
  * @param cmd-�����ַ���
  * @param res-��Ҫ���ķ���ָ��
  * @retval	0-�ɹ�	1-ʧ��
  */
uint8_t esp12s_send_cmd(unsigned char *cmd, unsigned char *res)
{
	
	uint8_t time_out = 200;

	esp12s_uart_send_string(cmd, strlen((const char *)cmd));
	
	while(time_out--)
	{
		if(esp12s_wait_recive() == REV_OK)							//����յ�����
		{
			if(strstr((const char *)esp12s_buf, (const char *)res) != NULL)		//����������ؼ���
			{
				esp12s_clear();									//��ջ���
				
				return 0;
			}
		}
		
		delay_ms(10);
	}
	
	return 1;

}



/**
  * @brief ��������
  * @param data-����
  * @param len-����
  * @retval None
  */
void esp12s_send_data(unsigned char *data, uint16_t len)
{

	uint8_t cmd_buf[32];
	
	esp12s_clear();								//��ս��ջ���
	sprintf((char *)cmd_buf, "AT+CIPSEND=%d\r\n", len);		//��������
	if(!esp12s_send_cmd((unsigned char *)cmd_buf, (unsigned char *)">"))				//�յ���>��ʱ���Է�������
	{
		esp12s_uart_send_string(data, len);		//�����豸������������
	}

}


/**
  * @brief ��ȡWIFI���յ�����
  * @param time_out-�ȴ���ʱ��(��λ:10ms)
  * @retval ƽ̨���ص�ԭʼ����
  * @note ˵������ͬ�����豸���صĸ�ʽ��ͬ����Ҫȥ����
  * @note ��ESP8266�ķ��ظ�ʽΪ	"+IPD,x:yyy"	x�������ݳ��ȣ�yyy����������
  */
uint8_t *esp12s_get_IPD(uint16_t  time_out)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(esp12s_wait_recive() == REV_OK)								//����������
		{
			ptrIPD = strstr((const char *)esp12s_buf, "IPD,");				//������IPD��ͷ
			if(ptrIPD == NULL)											//���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
			{
				//UsartPrintf(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//�ҵ�':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (uint8_t *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		delay_ms(5);													//��ʱ�ȴ�
	} while(time_out--);
	
	return NULL;														//��ʱ��δ�ҵ������ؿ�ָ��
}


/**
  * @brief ESP12S����AP
  * @param ssid-wifi�˺�
  * @param pwd-wifi����
  * @retval 0-�ɹ�  1-ʧ��
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
  * @brief ��ESP12S���������Ҷ�Ӧ���ַ���
  * @param str-��Ҫ���ҵ��ַ���
  * @retval	���ҽ��
  */
char *esp12s_buf_find(unsigned char *str)
{
	
	return strstr((void*)esp12s_buf, (void*)str);
	
}


/**
  * @brief ESP12S��ʼ��
  * @param ssid-wifi�˺�
  * @param pwd-wifi����
  * @retval 0-�ɹ�  1-ʧ��
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
	if(esp12s_join_ap(ssid,pwd)==1)	//����ʧ��
		return 1;

	printf("5. ESP12S Init OK\r\n");
	return 0;

}



/**
  * @brief ESP12S��ȡ����״̬
  * @param None
  * @retval 2: station �Ѿ�����AP ���IP��ַ
  *         3: station �Ѿ�����TCP����UDP����
  *         4: station �Ͽ���������(��Ȼ����AP)
  *         5: station δ����AP
  *         0:��ȡʧ��
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
  * @brief ESP12S���ӷ�����
  * @param server_ip-������IP��ַ
  * @param server_port-�������˿�
  * @param key-��Ȩ��Ϣ
  * @retval 0-�ɹ�	1-ʧ��
  * @note ���Ӻ�Ӧ�������ͼ�Ȩ��Ϣ�����������ȴ��������ظ�
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
//	dataPtr = esp12s_get_IPD(500);		//�ȴ���������Ӧ
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
  * @brief ESP12S��ȡ����ʱ��
  * @param server_ip-������IP��ַ
  * @param server_port-�������˿�
  * @param key-��Ȩ��Ϣ
  * @param date-���ڽṹ��ָ��
  * @param time-ʱ��ṹ��ָ��
  * @retval 0-�ɹ�	1-ʧ��
  * @note ���Ӻ�������ᷢ��һ��json����
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
	dataPtr = esp12s_get_IPD(500);		//�ȴ���������Ӧ
	
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
  * @brief  USART6����һ�ֽ�����
  * @param  c-���յ�����
  * @retval None
  * @note �ú����ᱻ�����жϺ�������
  */
void usart6_put_char(uint8_t c)
{
	/* USART6����һ�ֽ� */
	if(esp12s_cnt >= ESP12S_BUF_MAX_LENGTH)
		esp12s_cnt = 0;
	esp12s_buf[esp12s_cnt++] = c;
}



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* �ļ����� : gt9147.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : GT9147�����������ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "gt9147.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/
GT9147_PointTypeDef point = {0};

const uint16_t GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};

/* �������� ---------------------------------------------------------*/
static uint8_t gt9147_write_reg(uint16_t reg_addr,uint8_t *pdata,uint8_t len);
static uint8_t gt9147_read_reg(uint16_t reg_addr,uint8_t *pbuffer,uint8_t len);



/**
  * @brief GT9147��ʼ��
  * @param None
  * @retval	None
  */
void gt9147_init(void)
{
	uint8_t temp[4];
	uint8_t temp1 = 0;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*
	PB11 -->	CT_RST
	PB10 -->	CT_INT
	*/

	/*Configure GPIO pins : PB11 */
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PB10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	CT_RST(0);
	delay_ms(20);
	CT_RST(1);
	delay_ms(50);  
	gt9147_read_reg(GT_PID_REG,temp,4);
	//printf("TOUCH ID:%s\r\n",temp);
	temp[0] = 0x02;
	gt9147_write_reg(GT_CTRL_REG,temp,1);//��λ
	gt9147_read_reg(GT_CFGS_REG,temp,1);
	delay_ms(10);
	temp[0]=0X00;	 
	gt9147_write_reg(GT_CTRL_REG,temp,1);//������λ 


	gt9147_write_reg(GT_GSTID_REG,&temp1,1);

	/*Configure GPIO pin : PB10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  
}



/**
  * @brief GT9147ɨ��
  * @param scan_point-���津�����ݵĽṹ��
  * @retval	1-�д��� 0-�޴���
  */
uint8_t gt9147_scan(GT9147_PointTypeDef *scan_point)
{
	uint8_t status = 0;
	uint8_t temp = 0;
	uint8_t i = 0;
	uint8_t buf[4] = {0};
	uint8_t res = 0;
	
	gt9147_read_reg(GT_GSTID_REG,&status,1);
	if((status & 0x80) && ((status & 0x0f) < 6))
	{
		/* ���������־ */
		gt9147_write_reg(GT_GSTID_REG,&temp,1);
	}
	if((status & 0x0f) && ((status &0X0f) < 6))
	{
		for(i=0;i<(status&0x0f);i++)
		{
			gt9147_read_reg(GT9147_TPX_TBL[i],buf,4);
			point.x[i] = ((uint16_t)buf[1]<<8) + buf[0];
			point.y[i] = ((uint16_t)buf[3]<<8) + buf[2];
			scan_point->x[i] = point.x[i];
			scan_point->y[i] = point.y[i];
			
			//printf("x[%d]:%d,y[%d]:%d\r\n",i,point.x[i],i,point.y[i]);
		}
		res = 1;
		scan_point->ispressed = 1;
	}
	
	return res;
	
}

/**
  * @brief ��ѯGT9147�Ƿ��д���
  * @param None
  * @retval	1-�д��� 0-�޴���
  * @note ��������Բ��ϲ�ѯ�˺���,����һֱ����I2C�Ķ�ȡ,����˺�������ֵΪ1,�������̵���gt9147_clear_pressed()����
  */
uint8_t gt9147_is_pressed(void)
{
	return point.ispressed;
}

/**
  * @brief ���GT9147�Ĵ�����־λ
  * @param None
  * @retval	None
  */
void gt9147_clear_pressed(void)
{
	point.ispressed = 0;
}





/**
  * @brief GT9147�жϻص�����
  * @param None
  * @retval	None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_10)
	{
		point.ispressed = 1;
	}
}








/**
  * @brief GT9147д��ָ���������ݵ��Ĵ���
  * @param reg_addr-�Ĵ�����ַ
  * @param pdata-����
  * @param len-����
  * @retval	0-��ȡ�ɹ� other_value-��ȡʧ��
  * @note GT9147�ļĴ�����ַ��16λ��
  */
static uint8_t gt9147_write_reg(uint16_t reg_addr,uint8_t *pdata,uint8_t len)
{
	uint8_t reg_buf[2];
	reg_buf[0] = (reg_addr & 0XFF00)>>8;
	reg_buf[1] = (reg_addr & 0XFF);
	
	uint8_t length;
	length = len+2;
	uint8_t buf[length];
	buf[0] = (reg_addr & 0XFF00)>>8;
	buf[1] = (reg_addr & 0XFF);
	while(len--)
	{
		buf[len+2] = *pdata++;
	}
	
	return i2c3_master_send_data(GT9147_ADDRESS,buf,length,1000);
}

/**
  * @brief GT9147�ӼĴ�����ȡָ����������
  * @param reg_addr-�Ĵ�����ַ
  * @param pbuffer-���ݴ洢������
  * @param len-����
  * @retval	0-��ȡ�ɹ� other_value-��ȡʧ��
  * @note GT9147�ļĴ�����ַ��16λ��
  */
static uint8_t gt9147_read_reg(uint16_t reg_addr,uint8_t *pbuffer,uint8_t len)
{
	uint8_t reg_buf[2];
	reg_buf[0] = (reg_addr & 0XFF00)>>8;
	reg_buf[1] = (reg_addr & 0XFF);
	
	
	if(i2c3_master_send_data(GT9147_ADDRESS,reg_buf,2,1000) != 0)
	{
		return 1;
	}
	return i2c3_master_receive_data(GT9147_ADDRESS,pbuffer,len,1000);
	
	
}


/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

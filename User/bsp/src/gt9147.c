/*
*******************************************************************************************************
*
* 文件名称 : gt9147.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : GT9147触摸屏驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "gt9147.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
GT9147_PointTypeDef point = {0};

const uint16_t GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};

/* 函数声明 ---------------------------------------------------------*/
static uint8_t gt9147_write_reg(uint16_t reg_addr,uint8_t *pdata,uint8_t len);
static uint8_t gt9147_read_reg(uint16_t reg_addr,uint8_t *pbuffer,uint8_t len);



/**
  * @brief GT9147初始化
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
	gt9147_write_reg(GT_CTRL_REG,temp,1);//软复位
	gt9147_read_reg(GT_CFGS_REG,temp,1);
	delay_ms(10);
	temp[0]=0X00;	 
	gt9147_write_reg(GT_CTRL_REG,temp,1);//结束复位 


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
  * @brief GT9147扫描
  * @param scan_point-保存触摸数据的结构体
  * @retval	1-有触摸 0-无触摸
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
		/* 清除触摸标志 */
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
  * @brief 查询GT9147是否有触摸
  * @param None
  * @retval	1-有触摸 0-无触摸
  * @note 主程序可以不断查询此函数,避免一直进行I2C的读取,如果此函数返回值为1,必须立刻调用gt9147_clear_pressed()函数
  */
uint8_t gt9147_is_pressed(void)
{
	return point.ispressed;
}

/**
  * @brief 清除GT9147的触摸标志位
  * @param None
  * @retval	None
  */
void gt9147_clear_pressed(void)
{
	point.ispressed = 0;
}





/**
  * @brief GT9147中断回调函数
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
  * @brief GT9147写入指定长度数据到寄存器
  * @param reg_addr-寄存器地址
  * @param pdata-数据
  * @param len-长度
  * @retval	0-读取成功 other_value-读取失败
  * @note GT9147的寄存器地址是16位的
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
  * @brief GT9147从寄存器读取指定长度数据
  * @param reg_addr-寄存器地址
  * @param pbuffer-数据存储缓冲区
  * @param len-长度
  * @retval	0-读取成功 other_value-读取失败
  * @note GT9147的寄存器地址是16位的
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


/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

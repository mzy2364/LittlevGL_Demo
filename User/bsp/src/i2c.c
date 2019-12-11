/*
*******************************************************************************************************
*
* 文件名称 : i2c.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : I2C驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "i2c.h"


/* 宏定义 -----------------------------------------------------------*/
#ifdef HARDWARE_I2C
I2C_HandleTypeDef hi2c3;
#endif

/* 变量 -------------------------------------------------------------*/


/* 函数声明 ---------------------------------------------------------*/



/**
  * @brief I2C初始化函数
  * @param None
  * @retval	None
  */
void i2c3_init(void)
{
#ifdef HARDWARE_I2C
	hi2c3.Instance = I2C3;
	hi2c3.Init.ClockSpeed = 100000;
	hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c3.Init.OwnAddress1 = 0;
	hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c3.Init.OwnAddress2 = 0;
	hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c3) != HAL_OK)
	{
		Error_Handler();
	}
	/**Configure Analogue filter 
	*/
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}
	/**Configure Digital filter 
	*/
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
	{
		Error_Handler();
	}
#else
	
    /**I2C3 GPIO Configuration    
    PH7     ------> I2C3_SCL
    PH8     ------> I2C3_SDA 
    */
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOH_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;		//开漏输出
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
	
	SDA_OUT(1);
	SCL_OUT(1);

#endif	
}


/**
  * @brief 启用I2C发送数据
  * @param dev_addr-I2C从设备的地址
  * @param pbuffer-待发送的数据
  * @param len-数据长度
  * @param time_out-超时时间
  * @retval	0-发送成功 other_value-发送失败
  */
uint8_t i2c3_master_send_data(uint16_t dev_addr,uint8_t *pbuffer,uint16_t len,uint32_t time_out)
{
#ifdef HARDWARE_I2C
	return HAL_I2C_Master_Transmit(&hi2c3,dev_addr,pbuffer,len,1000);
	
#else
	dev_addr &= ~(1<<0);	//最低位清0，IIC写
	
	soft_i2c_start();
	
	soft_i2c_send_byte(dev_addr);
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;
	
	while(len)
	{
		soft_i2c_send_byte(*pbuffer);
		if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
			return SOFT_I2C_ERR;
		pbuffer ++ ;
		len -- ;
	}
	soft_i2c_stop();
	return SOFT_I2C_OK;
#endif
}


/**
  * @brief 启用I2C接收数据
  * @param dev_addr-I2C从设备的地址
  * @param pbuffer-接收数据缓冲区
  * @param len-数据长度
  * @param time_out-超时时间
  * @retval	0-接收成功 other_value-接收失败
  */
uint8_t i2c3_master_receive_data(uint16_t dev_addr,uint8_t *pbuffer,uint16_t len,uint32_t time_out)
{
#ifdef HARDWARE_I2C
	return HAL_I2C_Master_Receive(&hi2c3,dev_addr,(uint8_t *)pbuffer,len,1000);
#else
	dev_addr |= (1<<0);	//最低位置1，IIC读

	soft_i2c_start();
	
	soft_i2c_send_byte(dev_addr);
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;

	while(len)
	{
		*pbuffer = soft_i2c_receive_byte();
		pbuffer ++ ;
		len -- ;
		
		if(len == 0)
			soft_i2c_no_ack();
		else
			soft_i2c_ack();
	}
	soft_i2c_stop();
	
	return SOFT_I2C_OK;
	
#endif
}



/**
  * @brief 启用I2C向存储器写入一定长度的数据
  * @param dev_addr-I2C从设备的地址
  * @param mem_addr-存储器内部地址
  * @param mem_add_size-存储器地址长度(8位或者16位)
  * @param pbuffer-待写入的数据
  * @param len-数据长度
  * @param time_out-超时时间
  * @retval	0-写入成功 other_value-写入失败
  */
uint8_t i2c3_mem_write(uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_add_size, uint8_t *pbuffer, uint16_t len, uint32_t time_out)
{
#ifdef HARDWARE_I2C
	return HAL_I2C_Mem_Write(&hi2c3,dev_addr, mem_addr, mem_add_size, pbuffer, len, time_out);
#else
	
	//dev_addr <<= 1;		//7位IIC地址
	dev_addr &= ~(1<<0);	//最低位清0，IIC写
	
	soft_i2c_start();
	
	soft_i2c_send_byte(dev_addr);						//发送IIC设备地址
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;
	
	//发送IIC设备的MEM地址或者寄存器地址
	if(mem_add_size == I2C_MEMADD_16BIT)
	{
		soft_i2c_send_byte((mem_addr>>8)&0X00FF);
		if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
			return SOFT_I2C_ERR;
	}
	soft_i2c_send_byte(mem_addr & 0X00FF);						//发送IIC设备的MEM地址或者寄存器地址
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;
	
	
	//发送数据
	while(len)
	{
		soft_i2c_send_byte(*pbuffer);						//发送IIC设备的MEM地址或者寄存器地址
		if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
			return SOFT_I2C_ERR;
		
		pbuffer ++ ;
		len -- ;
		
		delay_us(10);

	}

	
	soft_i2c_stop();
	
	return SOFT_I2C_OK;
	
#endif
}




/**
  * @brief 启用I2C从储器读取一定长度的数据
  * @param dev_addr-I2C从设备的地址
  * @param mem_addr-存储器内部地址
  * @param mem_add_size-存储器地址长度(8位或者16位)
  * @param pbuffer-读取数据缓冲区
  * @param len-数据长度
  * @param time_out-超时时间
  * @retval	0-读取成功 other_value-读取失败
  */
uint8_t i2c3_mem_read(uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_add_size, uint8_t *pbuffer, uint16_t len, uint32_t time_out)
{
#ifdef HARDWARE_I2C
	return HAL_I2C_Mem_Read(&hi2c3,dev_addr, mem_addr, mem_add_size, pbuffer, len, time_out);
#else
	
	//dev_addr <<= 1;		//7位IIC地址
	dev_addr &= ~(1<<0);	//最低位清0，IIC写
	//dev_addr |= (1<<0);	//最低位置1，IIC读
	
	soft_i2c_start();
	
	soft_i2c_send_byte(dev_addr);						//发送IIC设备地址
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;
	
	//发送IIC设备的MEM地址或者寄存器地址
	if(mem_add_size == I2C_MEMADD_16BIT)
	{
		soft_i2c_send_byte((mem_addr>>8)&0X00FF);
		if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
			return SOFT_I2C_ERR;
	}
	soft_i2c_send_byte(mem_addr & 0X00FF);						//发送IIC设备的MEM地址或者寄存器地址
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;
	
	
	soft_i2c_start();
	
	dev_addr |= (1<<0);	//最低位置1，IIC读
	
	soft_i2c_send_byte(dev_addr);					//发送IIC设备的MEM地址或者寄存器地址
	if(soft_i2c_wait_ack(time_out) == SOFT_I2C_ERR)
		return SOFT_I2C_ERR;
	
	while(len)
	{
		
		*pbuffer = soft_i2c_receive_byte();
		pbuffer ++ ;
		len -- ;
		if(len == 0)
			soft_i2c_no_ack();
		else
			soft_i2c_ack();
		
	}
	
	soft_i2c_stop();
	
	return SOFT_I2C_OK;
	
#endif
}
















#ifdef SOFTWARE_I2C

/**
  * @brief I2C开始信号
  * @param None
  * @retval	None
  */
void soft_i2c_start(void)
{
	SDA_OUT(1);
	SCL_OUT(1);

	delay_us(5);
	
	SDA_OUT(0);
	delay_us(5);
	SCL_OUT(0);
}

/**
  * @brief I2C停止信号
  * @param None
  * @retval	None
  */
void soft_i2c_stop(void)
{
	SDA_OUT(0);
	SCL_OUT(0);
	delay_us(5);
	
	SCL_OUT(1);
	delay_us(5);
	SDA_OUT(1);
	delay_us(5);
}

/**
  * @brief I2C等待应答
  * @param time_out-等待的时间,单位5us
  * @retval	None
  */
uint8_t soft_i2c_wait_ack(uint32_t time_out)
{
	SDA_OUT(1);
	delay_us(5);
	SCL_OUT(1);
	delay_us(1);
	
	while(SDA_IN)	//如果读到SDA线为1，则等待。应答信号应是0
	{
		if(--time_out == 0)
		{
			soft_i2c_stop();	//超时未应答，停止总线
			return SOFT_I2C_ERR;
		}
		delay_us(5);
	}
	
	SCL_OUT(0);
	return SOFT_I2C_OK;
}


/**
  * @brief I2C发送应答
  * @param None
  * @retval	None
  */
void soft_i2c_ack(void)
{
	SCL_OUT(0);
	SDA_OUT(0);
	delay_us(5);
	SCL_OUT(1);
	delay_us(5);
	SCL_OUT(0);
}

/**
  * @brief I2C发送非应答
  * @param None
  * @retval	None
  */
void soft_i2c_no_ack(void)
{
	SCL_OUT(0);
	SDA_OUT(1);
	delay_us(5);
	SCL_OUT(1);
	delay_us(5);
	SCL_OUT(0);
}

/**
  * @brief I2C发送一字节数据
  * @param byte-待发送的数据
  * @retval	None
  */
void soft_i2c_send_byte(uint8_t byte)
{
	unsigned char i=0;
	
	SCL_OUT(0);
	
	for(i=0;i<8;i++)
	{
		SDA_OUT((byte & 0X80) >> 7);
		
		byte <<= 1;
		
		delay_us(5);
		SCL_OUT(1);
		delay_us(5);
		SCL_OUT(0);
	}
}

/**
  * @brief I2C接收一字节数据
  * @param None
  * @retval	接收到的数据
  */
uint8_t soft_i2c_receive_byte(void)
{
	unsigned char i = 0 , byte = 0;
	
	SDA_OUT(1);		//开漏状态下拉高SDA线以便读取输入数据
	
	for(i=0;i<8;i++)
	{
		SCL_OUT(0);
		delay_us(5);
		SCL_OUT(1);
		
		byte <<= 1;
		if(SDA_IN)
			byte ++ ;
		delay_us(5);	
	}
	return byte;
}
#endif




#ifdef HARDWARE_I2C
/**
  * @brief 硬件I2C底层初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_Init()调用,主要完成时钟使能,IO配置
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(i2cHandle->Instance==I2C3)
	{

		__HAL_RCC_GPIOH_CLK_ENABLE();
		/**I2C3 GPIO Configuration    
		PH7     ------> I2C3_SCL
		PH8     ------> I2C3_SDA 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

		/* I2C3 clock enable */
		__HAL_RCC_I2C3_CLK_ENABLE();
	}

}

/**
  * @brief 硬件I2C底层去初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_DeInit()调用,主要完成时钟禁能,IO配置清除
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{
	if(i2cHandle->Instance==I2C3)
	{
		/* Peripheral clock disable */
		__HAL_RCC_I2C3_CLK_DISABLE();

		/**I2C3 GPIO Configuration    
		PH7     ------> I2C3_SCL
		PH8     ------> I2C3_SDA 
		*/
		HAL_GPIO_DeInit(GPIOH, GPIO_PIN_7|GPIO_PIN_8);

	}
}
#endif























/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

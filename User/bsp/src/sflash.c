/*
*******************************************************************************************************
*
* 文件名称 : sflash.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : SPI-FLASH驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "sflash.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/

/* 定义个缓冲区供SPI-FLASH擦除时暂存数据 */
static __IO uint8_t sflash_buffer[4096];

/* 函数声明 ---------------------------------------------------------*/
static void sflash_gpio_config(void);
static void sflash_spi_config(void);
static void sflash_cs(uint8_t select);
static uint8_t sflash_spi_send_receive_byte(uint8_t txdata);


/**
  * @brief SPI-FLASH初始化
  * @param data-待写入数据的存储地址
  * @param addr-需要写入的SPI-FLASH的地址
  * @param len-长度,按页写入长度不大于SFlash_PageSize
  * @retval	None
  */
void sflash_init(void)
{
	sflash_gpio_config();
	
	sflash_spi_config();
	
	sflash_cs(1);

}

/**
  * @brief SPI-FLASH读取DEVICE_ID
  * @param None
  * @retval	读取到的DEVICE_ID
  */
uint16_t sflash_read_device_id(void)
{
	uint16_t device_id = 0;
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_ManufactDeviceID);
	sflash_spi_send_receive_byte(Dummy_Byte);
	sflash_spi_send_receive_byte(Dummy_Byte);
	sflash_spi_send_receive_byte(Dummy_Byte);
	
	device_id |= sflash_spi_send_receive_byte(Dummy_Byte)<<8;
	device_id |= sflash_spi_send_receive_byte(Dummy_Byte);
	
	sflash_cs(1);
	
	return device_id;
	
}


/**
  * @brief SPI-FLASH读取芯片类型ID
  * @param None
  * @retval	读取到的芯片ID
  * @note 正常情况下读取到的ID为XM25QH128_ID,此函数也可以判断SPI-FLASH是否正常连接
  */
uint32_t sflash_read_id(void)
{
	uint32_t id = 0;
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_JedecDeviceID);
	
	id |= sflash_spi_send_receive_byte(Dummy_Byte)<<16;	
	id |= sflash_spi_send_receive_byte(Dummy_Byte)<<8;	
	id |= sflash_spi_send_receive_byte(Dummy_Byte);
	
	sflash_cs(1);
	
	return id;

}

/**
  * @brief SPI-FLASH读取指定长度的数据
  * @param pbuffer-读取的数据的存储地址
  * @param read_addr-需要读取的SPI-FLASH的地址
  * @param num_byte_to_read-长度,支持任意长度读取
  * @retval	None
  */
void sflash_read(uint8_t *pbuffer,uint32_t read_addr,uint32_t num_byte_to_read)
{
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_ReadData);
	
	sflash_spi_send_receive_byte((read_addr & 0xFF0000)>>16);
	sflash_spi_send_receive_byte((read_addr & 0xFF00)>>8);
	sflash_spi_send_receive_byte((read_addr & 0xFF));
	
	while(num_byte_to_read--)
	{
		*pbuffer = sflash_spi_send_receive_byte(Dummy_Byte);
		pbuffer++;
	}
	
	sflash_cs(1);
	
}

/**
  * @brief SPI-FLASH读取指定长度的数据
  * @param pbuffer-待写入数据的存储地址
  * @param write_addr-需要写入的SPI-FLASH的地址
  * @param num_byte_to_write-长度,支持任意长度写入
  * @retval	该函数带擦除操作
  */
void sflash_write(uint8_t *pbuffer,uint32_t write_addr,uint32_t num_byte_to_write)
{

	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
	uint16_t i;    
	uint8_t *buf;	  
	buf = sflash_buffer;	     
	secpos = write_addr/SFlash_SecSize;//扇区地址  
	secoff = write_addr%SFlash_SecSize;//在扇区内的偏移
	secremain = SFlash_SecSize-secoff;//扇区剩余空间大小   
	if(num_byte_to_write <= secremain)
	{
		/* 写入数据小于一个扇区 */
		secremain = num_byte_to_write;
	}
	while(1) 
	{	
		sflash_read(buf,secpos*SFlash_SecSize,SFlash_SecSize);
		for(i=0;i<secremain;i++)
		{
			/* 校验数据 */
			if(buf[secoff+i]!=0XFF)
			{
				/* 需要擦除 */
				break;
			}				
		}
		if(i<secremain)
		{
			/* 准备擦除 */
			sflash_erase_sector(secpos*SFlash_SecSize);
			for(i=0;i<secremain;i++)	   //复制
			{
				buf[i+secoff]=pbuffer[i];	  
			}
			/* 写入整个扇区   */
			sflash_write_no_check(buf,secpos*SFlash_SecSize,SFlash_SecSize);

		}
		else 
		{
			/* 写已经擦除了的,直接写入扇区剩余区间 */
			sflash_write_no_check(pbuffer,write_addr,secremain);
		}			
		if(num_byte_to_write == secremain)
		{
			/* 写入结束了 */
			break;
		}
		else
		{
			/* 写入未结束 */
			
			secpos++;//扇区地址增1
			secoff = 0;//偏移位置为0 	 

			pbuffer += secremain;  //指针偏移
			write_addr += secremain;//写地址偏移	   
			num_byte_to_write -= secremain;				//字节数递减
			if(num_byte_to_write > SFlash_SecSize)
			{
				/* 下一个扇区还是写不完 */
				secremain = SFlash_SecSize;
			}
			else 
			{
				/* 下一个扇区可以写完了 */
				secremain = num_byte_to_write;
			}
		}	 
	};	

}


/**
  * @brief SPI-FLASH页写入
  * @param pbuffer-待写入数据的存储地址
  * @param write_addr-需要写入的SPI-FLASH的地址
  * @param num_byte_to_write-长度,按页写入长度不大于SFlash_PageSize
  * @retval	None
  */
void sflash_write_page(uint8_t *pbuffer,uint32_t write_addr,uint16_t num_byte_to_write)
{
	sflash_write_enable();
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_PageProgram);
	
	sflash_spi_send_receive_byte((write_addr & 0xFF0000)>>16);
	sflash_spi_send_receive_byte((write_addr & 0xFF00)>>8);
	sflash_spi_send_receive_byte((write_addr & 0xFF));
	
	if(num_byte_to_write > SFlash_PageSize)
	{
		num_byte_to_write = SFlash_PageSize;
	}
	
	while(num_byte_to_write--)
	{
		sflash_spi_send_receive_byte(*pbuffer);
		pbuffer++;
	}
	
	sflash_cs(1);
	
	sflash_wait_busy();
	
}




/**
  * @brief 在已经确保擦除的地址上面写指定长度的数据
  * @param pbuffer-待写入数据的存储地址
  * @param write_addr-需要写入的SPI-FLASH的地址
  * @param num_byte_to_write-长度,支持任意长度写入
  * @retval	None
  */
void sflash_write_no_check(uint8_t *pbuffer,uint32_t write_addr,uint16_t num_byte_to_write)
{
	uint8_t count;
	
	for(count=0;count<num_byte_to_write/SFlash_PageSize;count++)
	{
		sflash_write_page(pbuffer,write_addr,SFlash_PageSize);
		pbuffer += SFlash_PageSize;
		write_addr += SFlash_PageSize;
	}
	sflash_write_page(pbuffer,write_addr,num_byte_to_write%SFlash_PageSize);
	
}







/**
  * @brief SPI-FLASH擦除一个扇区
  * @param sector_addr-扇区地址
  * @retval	None
  */
void sflash_erase_sector(uint32_t sector_addr)
{
	
	sflash_write_enable();
	
	sflash_wait_busy();
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_SectorErase);
	
	sflash_spi_send_receive_byte((sector_addr & 0xFF0000)>>16);
	sflash_spi_send_receive_byte((sector_addr & 0xFF00)>>8);
	sflash_spi_send_receive_byte((sector_addr & 0xFF));
	
	sflash_cs(1);
	
	sflash_wait_busy();
	
}


/**
  * @brief SPI-FLASH全片擦除
  * @param None
  * @retval	None
  * @note 全片擦除时间在25-40S之间，测试的是28S
  */
void sflash_erase_chip(void)
{
	
	sflash_write_enable();
	
	sflash_wait_busy();
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_ChipErase);
	
	sflash_cs(1);
	
	/* 等待超时,由于擦除时间较长,等待超时的时间要设置大一点 */
	sflash_wait_busy();
	
}


/**
  * @brief SPI-FLASH写使能
  * @param None
  * @retval	None
  */
void sflash_write_enable(void)
{
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_WriteEnable);
	
	sflash_cs(1);
	
}

/**
  * @brief SPI-FLASH写去能
  * @param None
  * @retval	None
  */
void sflash_write_disenable(void)
{
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_WriteDisable);
	
	sflash_cs(1);
	
}


/**
  * @brief 等待SPI空闲
  * @param None
  * @retval	None
  */
void sflash_wait_busy(void)
{
	/* 超时时间 500ms */
	static uint32_t time_out=0x1FFFFFF;
	uint8_t status=0;
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_ReadStatusReg1);
	
	while(time_out--)
	{
		status = sflash_spi_send_receive_byte(Dummy_Byte);
		if((status & WIP_Flag) == 0)
		{
			break;
		}
	}
	
	sflash_cs(1);
	
}




/*
**********************************************************************
*以下是驱动接口函数
***********************************************************************
*/


/**
  * @brief 配置SPI-FLASH的SPI片选IO
  * @param None
  * @retval	None
  * @note 
  */
static void sflash_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOI_CLK_ENABLE();


	 /*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = FLASH_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStruct);
	
}


/**
  * @brief 配置SPI-FLASH所对应的SPI外设
  * @param None
  * @retval	None
  * @note 
  */
static void sflash_spi_config(void)
{
	spi6_init();
}


/**
  * @brief SPI-FLASH对应的SPI的片选
  * @param select-片选引脚输出的电平 1-不选 0-选中
  * @retval	None
  * @note 
  */
static void sflash_cs(uint8_t select)
{
	HAL_GPIO_WritePin(FLASH_CS_GPIO_PORT, FLASH_CS_PIN, (GPIO_PinState)select);
}


/**
  * @brief SPI-FLASH对应的SPI发送并接收一字节数据
  * @param txdata-待发送的数据
  * @retval	接收到的数据
  * @note 
  */
static uint8_t sflash_spi_send_receive_byte(uint8_t txdata)
{
	return spi6_send_receive_byte(txdata);
}



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

/*
*******************************************************************************************************
*
* �ļ����� : sflash.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : SPI-FLASH�����ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "sflash.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/

/* �������������SPI-FLASH����ʱ�ݴ����� */
static __IO uint8_t sflash_buffer[4096];

/* �������� ---------------------------------------------------------*/
static void sflash_gpio_config(void);
static void sflash_spi_config(void);
static void sflash_cs(uint8_t select);
static uint8_t sflash_spi_send_receive_byte(uint8_t txdata);


/**
  * @brief SPI-FLASH��ʼ��
  * @param data-��д�����ݵĴ洢��ַ
  * @param addr-��Ҫд���SPI-FLASH�ĵ�ַ
  * @param len-����,��ҳд�볤�Ȳ�����SFlash_PageSize
  * @retval	None
  */
void sflash_init(void)
{
	sflash_gpio_config();
	
	sflash_spi_config();
	
	sflash_cs(1);

}

/**
  * @brief SPI-FLASH��ȡDEVICE_ID
  * @param None
  * @retval	��ȡ����DEVICE_ID
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
  * @brief SPI-FLASH��ȡоƬ����ID
  * @param None
  * @retval	��ȡ����оƬID
  * @note ��������¶�ȡ����IDΪXM25QH128_ID,�˺���Ҳ�����ж�SPI-FLASH�Ƿ���������
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
  * @brief SPI-FLASH��ȡָ�����ȵ�����
  * @param pbuffer-��ȡ�����ݵĴ洢��ַ
  * @param read_addr-��Ҫ��ȡ��SPI-FLASH�ĵ�ַ
  * @param num_byte_to_read-����,֧�����ⳤ�ȶ�ȡ
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
  * @brief SPI-FLASH��ȡָ�����ȵ�����
  * @param pbuffer-��д�����ݵĴ洢��ַ
  * @param write_addr-��Ҫд���SPI-FLASH�ĵ�ַ
  * @param num_byte_to_write-����,֧�����ⳤ��д��
  * @retval	�ú�������������
  */
void sflash_write(uint8_t *pbuffer,uint32_t write_addr,uint32_t num_byte_to_write)
{

	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
	uint16_t i;    
	uint8_t *buf;	  
	buf = sflash_buffer;	     
	secpos = write_addr/SFlash_SecSize;//������ַ  
	secoff = write_addr%SFlash_SecSize;//�������ڵ�ƫ��
	secremain = SFlash_SecSize-secoff;//����ʣ��ռ��С   
	if(num_byte_to_write <= secremain)
	{
		/* д������С��һ������ */
		secremain = num_byte_to_write;
	}
	while(1) 
	{	
		sflash_read(buf,secpos*SFlash_SecSize,SFlash_SecSize);
		for(i=0;i<secremain;i++)
		{
			/* У������ */
			if(buf[secoff+i]!=0XFF)
			{
				/* ��Ҫ���� */
				break;
			}				
		}
		if(i<secremain)
		{
			/* ׼������ */
			sflash_erase_sector(secpos*SFlash_SecSize);
			for(i=0;i<secremain;i++)	   //����
			{
				buf[i+secoff]=pbuffer[i];	  
			}
			/* д����������   */
			sflash_write_no_check(buf,secpos*SFlash_SecSize,SFlash_SecSize);

		}
		else 
		{
			/* д�Ѿ������˵�,ֱ��д������ʣ������ */
			sflash_write_no_check(pbuffer,write_addr,secremain);
		}			
		if(num_byte_to_write == secremain)
		{
			/* д������� */
			break;
		}
		else
		{
			/* д��δ���� */
			
			secpos++;//������ַ��1
			secoff = 0;//ƫ��λ��Ϊ0 	 

			pbuffer += secremain;  //ָ��ƫ��
			write_addr += secremain;//д��ַƫ��	   
			num_byte_to_write -= secremain;				//�ֽ����ݼ�
			if(num_byte_to_write > SFlash_SecSize)
			{
				/* ��һ����������д���� */
				secremain = SFlash_SecSize;
			}
			else 
			{
				/* ��һ����������д���� */
				secremain = num_byte_to_write;
			}
		}	 
	};	

}


/**
  * @brief SPI-FLASHҳд��
  * @param pbuffer-��д�����ݵĴ洢��ַ
  * @param write_addr-��Ҫд���SPI-FLASH�ĵ�ַ
  * @param num_byte_to_write-����,��ҳд�볤�Ȳ�����SFlash_PageSize
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
  * @brief ���Ѿ�ȷ�������ĵ�ַ����дָ�����ȵ�����
  * @param pbuffer-��д�����ݵĴ洢��ַ
  * @param write_addr-��Ҫд���SPI-FLASH�ĵ�ַ
  * @param num_byte_to_write-����,֧�����ⳤ��д��
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
  * @brief SPI-FLASH����һ������
  * @param sector_addr-������ַ
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
  * @brief SPI-FLASHȫƬ����
  * @param None
  * @retval	None
  * @note ȫƬ����ʱ����25-40S֮�䣬���Ե���28S
  */
void sflash_erase_chip(void)
{
	
	sflash_write_enable();
	
	sflash_wait_busy();
	
	sflash_cs(0);
	
	sflash_spi_send_receive_byte(SFlash_ChipErase);
	
	sflash_cs(1);
	
	/* �ȴ���ʱ,���ڲ���ʱ��ϳ�,�ȴ���ʱ��ʱ��Ҫ���ô�һ�� */
	sflash_wait_busy();
	
}


/**
  * @brief SPI-FLASHдʹ��
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
  * @brief SPI-FLASHдȥ��
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
  * @brief �ȴ�SPI����
  * @param None
  * @retval	None
  */
void sflash_wait_busy(void)
{
	/* ��ʱʱ�� 500ms */
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
*�����������ӿں���
***********************************************************************
*/


/**
  * @brief ����SPI-FLASH��SPIƬѡIO
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
  * @brief ����SPI-FLASH����Ӧ��SPI����
  * @param None
  * @retval	None
  * @note 
  */
static void sflash_spi_config(void)
{
	spi6_init();
}


/**
  * @brief SPI-FLASH��Ӧ��SPI��Ƭѡ
  * @param select-Ƭѡ��������ĵ�ƽ 1-��ѡ 0-ѡ��
  * @retval	None
  * @note 
  */
static void sflash_cs(uint8_t select)
{
	HAL_GPIO_WritePin(FLASH_CS_GPIO_PORT, FLASH_CS_PIN, (GPIO_PinState)select);
}


/**
  * @brief SPI-FLASH��Ӧ��SPI���Ͳ�����һ�ֽ�����
  * @param txdata-�����͵�����
  * @retval	���յ�������
  * @note 
  */
static uint8_t sflash_spi_send_receive_byte(uint8_t txdata)
{
	return spi6_send_receive_byte(txdata);
}



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

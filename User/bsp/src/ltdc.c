/*
*******************************************************************************************************
*
* �ļ����� : ltdc.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : LTDC��ʾ��̬ͼƬ�����ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "ltdc.h"



/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/

/* logo���� */
extern const unsigned char _acrabbit[];
extern const unsigned char _actiaotu[];

/* ���� */
extern const unsigned char asc_32[95][64];

/* ������ */
LTDC_HandleTypeDef hltdc;

/* �������� ---------------------------------------------------------*/


/**
  * @brief LTDC��ʼ��
  * @param None
  * @retval	None
  * @note ��Ҫ��ɽṹ������
  */
void ltdc_init(void)
{
	
	
	LTDC_LayerCfgTypeDef pLayerCfg = {0};

	/* LTDC����,���²��ֲ�������Һ�������� */
	hltdc.Instance = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc.Init.HorizontalSync = 9;
	hltdc.Init.VerticalSync = 9;
	hltdc.Init.AccumulatedHBP = 29;
	hltdc.Init.AccumulatedVBP = 19;
	hltdc.Init.AccumulatedActiveW = 509;
	hltdc.Init.AccumulatedActiveH = 819;
	hltdc.Init.TotalWidth = 549;
	hltdc.Init.TotalHeigh = 834;
	hltdc.Init.Backcolor.Blue = 0;
	hltdc.Init.Backcolor.Green = 0;
	hltdc.Init.Backcolor.Red = 0;
	if (HAL_LTDC_Init(&hltdc) != HAL_OK)
	{
	Error_Handler();
	}
	
	/* LTDC������,���ｫ�㶨�嵽SDRAM��ַ */
	pLayerCfg.WindowX0 = 0;
	pLayerCfg.WindowX1 = XSIZE_PHYS_L0;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = YSIZE_PHYS_L0;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	pLayerCfg.FBStartAdress = (uint32_t)LCD_LAYER0_FRAME_BUFFER;
	pLayerCfg.ImageWidth = XSIZE_PHYS_L0;
	pLayerCfg.ImageHeight = YSIZE_PHYS_L0;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
	{
		Error_Handler();
	}
	

	/* LTDC������,���ｫ�㶨�嵽SDRAM��ַ */
	pLayerCfg.WindowX0 = 40;
	pLayerCfg.WindowX1 = 440;
	pLayerCfg.WindowY0 = 290;
	pLayerCfg.WindowY1 = 510;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	pLayerCfg.FBStartAdress = (uint32_t)LCD_LAYER1_FRAME_BUFFER;
	pLayerCfg.ImageWidth = XSIZE_PHYS_L1;
	pLayerCfg.ImageHeight = YSIZE_PHYS_L1;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
//	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 1) != HAL_OK)
//	{
//		Error_Handler();
//	}
	
	lcd_pwm_init();
	lcd_backlight(100);
	
}


/**
  * @brief LTDC����PWM��ʼ��
  * @param None
  * @retval	None
  * @note 1KHz�ı�������,�����üĴ�����Ҫ��Ϊ�˷�����ֲ,���з����Ŀ��ļ�����
  */
static void lcd_pwm_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**TIM2 GPIO Configuration    
	PA1     ------> TIM2_CH2 
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//ʹ�ܶ�ʱ��2��ʱ��
	RCC->APB1ENR |= 1<<0;
	//����Ԥ��Ƶֵ(500K�Ķ�ʱ��Ƶ��)
	TIM2->PSC = (SystemCoreClock/2)/500000-1;
	//�����Զ���װ��ֵ(500KƵ�� 500���Զ���װ��ֵ PWMΪ1K)
	TIM2->ARR = 500;
	
	//��������û�еĻ�Ԥ��Ƶ��ֵ����ȵ�����һ�θ����¼���Żᱻ����
	//���³�ʼ����ʱ�������������ɼĴ��������¼�,ȷ��Ԥ��Ƶֵ������
	TIM2->EGR |= (1<<0);
	//������±�־λ,��λ�ڷ��������¼�ʱͨ��Ӳ���� 1,����Ҫͨ���������
	TIM2->SR &= ~(1<<0);
	
	//TIM2��CH2����ΪPWM
	TIM2->CCMR1 |= 6 << 12;
	//����Ƚ�2Ԥװ��ʹ��
	TIM2->CCMR1 |= 1<<11;
	
	//�Ƚ� 2 ���ʹ��
	TIM2->CCER |= 1<<4;
	//CH2���������Ϊ�ߵ�ƽ��Ч
	TIM2->CCER &= ~(1<<5);
	
	//����ռ�ձ�
	TIM2->CCR2 = 0;
	
	//�Զ�����Ԥװ��ʹ��
	TIM2->CR1 |= 1<<7;
	//ʹ�ܶ�ʱ��
	TIM2->CR1 |= 1<<0;
	
}


/**
  * @brief ����LCD�ı���
  * @param light-10~100���ڱ��� 0�رձ���
  * @retval	None
  * @note 
  */
void lcd_backlight(uint8_t light)
{
	if(light == 0)
	{
		/* �رն�ʱ�� */
		TIM2->CR1 &= ~(1<<0);
		return;
	}
	else if(light <= 5)
	{
		light = 5;
	}
	
	float l;
	l = (float)light / 100.0f;
	l = l * l;
	TIM2->CCR2 = (uint32_t)(l * (float)(TIM2->ARR));
}




/**
  * @brief LTDC���㺯��
  * @param x-x����
  * @param y-y����
  * @param color-��ɫ
  * @param layer-��(0/1)
  * @retval	None
  * @note 
  */
void ltdc_draw_point(uint16_t x,uint16_t y,uint32_t color,uint8_t layer)
{
	*(__IO uint16_t*)(hltdc.LayerCfg[layer].FBStartAdress + (2*(y*hltdc.LayerCfg[layer].ImageWidth + x))) = (uint16_t)color;
}

/**
  * @brief LTDC���㺯��
  * @param x-x����
  * @param y-y����
  * @param layer-��(0/1)
  * @retval	��ȡ������ɫ
  * @note 
  */
uint32_t ltdc_read_point(uint16_t x,uint16_t y,uint8_t layer)
{
	
	return *(__IO uint16_t*)(hltdc.LayerCfg[layer].FBStartAdress + (2*(y*hltdc.LayerCfg[layer].ImageWidth + x)));
}

/**
  * @brief LTDC�����
  * @param color-��ɫ
  * @param layer-��(0/1)
  * @retval	None
  * @note 
  */
void ltdc_clear_layer(uint32_t color,uint8_t layer)
{
//	uint16_t x=0,y=0;
//	for(x=hltdc.LayerCfg[layer].WindowX0; x<hltdc.LayerCfg[layer].WindowX1; x++)
//	{
//		for(y=hltdc.LayerCfg[layer].WindowY0; y<hltdc.LayerCfg[layer].WindowY1; y++)
//		{
//			/* �ö�Ӧ����ɫ��� */
//			ltdc_draw_point(x,y,color,layer);
//			
//		}
//	}
	uint32_t timeout=0;
	
	__HAL_RCC_DMA2D_CLK_ENABLE();	//ʹ��DM2Dʱ��
	DMA2D->CR&=~(DMA2D_CR_START);	//��ֹͣDMA2D
	DMA2D->CR=DMA2D_R2M;			//�Ĵ������洢��ģʽ
	DMA2D->OPFCCR=LTDC_PIXEL_FORMAT_RGB565;	//������ɫ��ʽ
	DMA2D->OOR=0;				//������ƫ��
	
	DMA2D->OMAR=(uint32_t)(hltdc.LayerCfg[layer].FBStartAdress);				//����洢����ַ
	DMA2D->NLR=hltdc.LayerCfg[layer].ImageHeight|(hltdc.LayerCfg[layer].ImageWidth<<16);	//�趨�����Ĵ���
	DMA2D->OCOLR=color;						//�趨�����ɫ�Ĵ��� 
	DMA2D->CR|=DMA2D_CR_START;				//����DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//�ȴ��������
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//��ʱ�˳�
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;		//���������ɱ�־ 	  
}

/**
  * @brief �ڵ�2���������LOGO
  * @param None
  * @retval	None
  * @note �ڶ���ר��������ʾLOGO��,����LOGO��Ŀ����Ϊ�˽��GUI�ڼ���ǰ��һ�κ���ʱ��
  */
void ltdc_draw_logo(void)
{
	ltdc_clear_layer(LCD_COLOR_BLACK,1);
	
	uint32_t x=0, y=0;
	uint8_t temp;
	uint8_t i;
	

	for(y=0;y<YSIZE_PHYS_L1;y++)
	{
		for(x=0;x<XSIZE_PHYS_L1;)
		{
			//temp = _acrabbit[y*60+(x/8)];
			temp = _actiaotu[y*XSIZE_PHYS_L1/8+(x/8)];
			for(i=0;i<8;i++)
			{
				if(temp&0x80)
				{
					ltdc_draw_point(x,y,LCD_COLOR_WHITE,1);
				}
				else
				{
					ltdc_draw_point(x,y,LCD_COLOR_BLACK,1);
				}
				
				temp<<=1;
				x++;
			}

		}
	}
}


/**
  * @brief ɾ���ڶ���,(�ѵڶ����Alpha��Ϊ0,�ڶ���͸��)
  * @param None
  * @retval	None
  * @note �ڶ���ר��������ʾLOGO��,�ڼ����ڼ���ʾ��logo,�Ϳ��Խ���ɾ����
  */
void ltdc_delete_layer1(void)
{
	LTDC_LayerCfgTypeDef pLayerCfg = {0};
	
	/* LTDC������,���ｫ�㶨�嵽SDRAM��ַ */
	pLayerCfg.WindowX0 = 40;
	pLayerCfg.WindowX1 = 440;
	pLayerCfg.WindowY0 = 290;
	pLayerCfg.WindowY1 = 510;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	pLayerCfg.Alpha = 0;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	pLayerCfg.FBStartAdress = (uint32_t)LCD_LAYER1_FRAME_BUFFER;
	pLayerCfg.ImageWidth = XSIZE_PHYS_L1;
	pLayerCfg.ImageHeight = YSIZE_PHYS_L1;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 1) != HAL_OK)
	{
		Error_Handler();
	}
}





/**
  * @brief ���Ƶ����ַ�
  * @param x-x����
  * @param y-y����
  * @param c-�ַ�
  * @param size-�����С(16/24/32)
  * @param fontcolor-������ɫ
  * @param bkcolor-����ı���ɫ,͸�����ָò���Ϊ0
  * @retval	None
  * @note 
  */
void ltdc_draw_char(uint16_t x,uint16_t y,uint8_t c,uint8_t size,uint32_t fontcolor,uint32_t bkcolor)
{
	uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���

	c=c-' ';//�õ�ƫ�ƺ��ֵ(ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ�)

	for(t=0;t<csize;t++)
	{
		if(size==32)
		{
			temp = asc_32[c][t];
		}
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
			{
				
				ltdc_draw_point(x,y,fontcolor,0);
			}
			else if(bkcolor)
			{
				
				ltdc_draw_point(x,y,bkcolor,0);
			}
			else
			{
				
				ltdc_draw_point(x,y,ltdc_read_point(x,y,0),0);
			}
			
			temp<<=1;
			y++;
			if(y>=YSIZE_PHYS_L0)
			{
				/* �������� */
				return;
			}
			if((y-y0)==size)
			{
				y = y0;
				x++;
				if(x>=XSIZE_PHYS_L0)
				{
					/* �������� */
					return;
				}
				break;
			}
		}
	}
}



/**
  * @brief ���Ƶ����ַ�
  * @param x-x����
  * @param y-y����
  * @param pText-�ַ���ָ��
  * @param size-�����С(16/24/32)
  * @param fontcolor-������ɫ
  * @param bkcolor-����ı���ɫ,͸�����ָò���Ϊ0
  * @retval	None
  * @note 
  */
void ltdc_draw_string(uint16_t x,uint16_t y,uint8_t *text,uint8_t size,uint32_t fontcolor,uint32_t bkcolor)
{
	while(*text != 0)
	{
		ltdc_draw_char(x,y,*text,size,fontcolor,bkcolor);
		x+=size/2;
		if(x>=XSIZE_PHYS_L0)
		{
			y+=size;
			x=0;
		}
		text++;
	}
}








/**
  * @brief LTDC�ײ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_Init()����,��Ҫ���ʱ��ʹ��,IO����
  */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(ltdcHandle->Instance==LTDC)
	{

		/* LTDC clock enable */
		__HAL_RCC_LTDC_CLK_ENABLE();
		__HAL_RCC_DMA2D_CLK_ENABLE(); 

		__HAL_RCC_GPIOI_CLK_ENABLE();
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOG_CLK_ENABLE();
		/**LTDC GPIO Configuration    
		PI9     ------> LTDC_VSYNC
		PI10     ------> LTDC_HSYNC
		PF10     ------> LTDC_DE
		PH9     ------> LTDC_R3
		PH10     ------> LTDC_R4
		PH11     ------> LTDC_R5
		PH12     ------> LTDC_R6
		PG6     ------> LTDC_R7
		PG7     ------> LTDC_CLK
		PH13     ------> LTDC_G2
		PH14     ------> LTDC_G3
		PH15     ------> LTDC_G4
		PI0     ------> LTDC_G5
		PI1     ------> LTDC_G6
		PI2     ------> LTDC_G7
		PG11     ------> LTDC_B3
		PI4     ------> LTDC_B4
		PI5     ------> LTDC_B5
		PI6     ------> LTDC_B6
		PI7     ------> LTDC_B7 
		*/
		

		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1 
							  |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
							  |GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12 
							  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
		
		
//		/* ���ñ����GPIO */
//		GPIO_InitStruct.Pin = LCD_EN_PIN;
//		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//		GPIO_InitStruct.Pull = GPIO_NOPULL;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//		HAL_GPIO_Init(LCD_EN_GPIO_PORT, &GPIO_InitStruct);


	}
}


/**
  * @brief LTDC�ײ�ȥ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_DeInit()����,��Ҫ���ʱ�ӽ���,IO�������
  */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

	if(ltdcHandle->Instance==LTDC)
	{
		/* USER CODE BEGIN LTDC_MspDeInit 0 */

		/* USER CODE END LTDC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_LTDC_CLK_DISABLE();

		/**LTDC GPIO Configuration    
		PI9     ------> LTDC_VSYNC
		PI10     ------> LTDC_HSYNC
		PF10     ------> LTDC_DE
		PE14     ------> LTDC_CLK
		PH9     ------> LTDC_R3
		PH10     ------> LTDC_R4
		PH11     ------> LTDC_R5
		PH12     ------> LTDC_R6
		PG6     ------> LTDC_R7
		PH13     ------> LTDC_G2
		PH14     ------> LTDC_G3
		PH15     ------> LTDC_G4
		PI0     ------> LTDC_G5
		PI1     ------> LTDC_G6
		PI2     ------> LTDC_G7
		PG11     ------> LTDC_B3
		PI4     ------> LTDC_B4
		PI5     ------> LTDC_B5
		PI6     ------> LTDC_B6
		PI7     ------> LTDC_B7 
		*/
		HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1 
							  |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
							  |GPIO_PIN_7);

		HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_14);

		HAL_GPIO_DeInit(GPIOH, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12 
							  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

		HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_11);


	}
} 



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

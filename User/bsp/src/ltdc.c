/*
*******************************************************************************************************
*
* 文件名称 : ltdc.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : LTDC显示静态图片驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "ltdc.h"



/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/

/* logo数组 */
extern const unsigned char _acrabbit[];
extern const unsigned char _actiaotu[];

/* 字体 */
extern const unsigned char asc_32[95][64];

/* 外设句柄 */
LTDC_HandleTypeDef hltdc;

/* 函数定义 ---------------------------------------------------------*/


/**
  * @brief LTDC初始化
  * @param None
  * @retval	None
  * @note 主要完成结构体配置
  */
void ltdc_init(void)
{
	
	
	LTDC_LayerCfgTypeDef pLayerCfg = {0};

	/* LTDC配置,以下部分参数来自液晶屏厂家 */
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
	
	/* LTDC层配置,这里将层定义到SDRAM地址 */
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
	

	/* LTDC层配置,这里将层定义到SDRAM地址 */
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
  * @brief LTDC背光PWM初始化
  * @param None
  * @retval	None
  * @note 1KHz的背光驱动,这里用寄存器主要是为了方便移植,拜托繁琐的库文件复制
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
	
	
	//使能定时器2的时钟
	RCC->APB1ENR |= 1<<0;
	//设置预分频值(500K的定时器频率)
	TIM2->PSC = (SystemCoreClock/2)/500000-1;
	//设置自动重装载值(500K频率 500的自动重装载值 PWM为1K)
	TIM2->ARR = 500;
	
	//下面两步没有的话预分频的值必须等到产生一次更新事件后才会被采用
	//重新初始化定时器计数器并生成寄存器更新事件,确保预分频值被采用
	TIM2->EGR |= (1<<0);
	//清除更新标志位,该位在发生更新事件时通过硬件置 1,但需要通过软件清零
	TIM2->SR &= ~(1<<0);
	
	//TIM2的CH2配置为PWM
	TIM2->CCMR1 |= 6 << 12;
	//输出比较2预装载使能
	TIM2->CCMR1 |= 1<<11;
	
	//比较 2 输出使能
	TIM2->CCER |= 1<<4;
	//CH2输出极性设为高电平有效
	TIM2->CCER &= ~(1<<5);
	
	//设置占空比
	TIM2->CCR2 = 0;
	
	//自动重载预装载使能
	TIM2->CR1 |= 1<<7;
	//使能定时器
	TIM2->CR1 |= 1<<0;
	
}


/**
  * @brief 设置LCD的背光
  * @param light-10~100调节背光 0关闭背光
  * @retval	None
  * @note 
  */
void lcd_backlight(uint8_t light)
{
	if(light == 0)
	{
		/* 关闭定时器 */
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
  * @brief LTDC画点函数
  * @param x-x坐标
  * @param y-y坐标
  * @param color-颜色
  * @param layer-层(0/1)
  * @retval	None
  * @note 
  */
void ltdc_draw_point(uint16_t x,uint16_t y,uint32_t color,uint8_t layer)
{
	*(__IO uint16_t*)(hltdc.LayerCfg[layer].FBStartAdress + (2*(y*hltdc.LayerCfg[layer].ImageWidth + x))) = (uint16_t)color;
}

/**
  * @brief LTDC读点函数
  * @param x-x坐标
  * @param y-y坐标
  * @param layer-层(0/1)
  * @retval	读取到的颜色
  * @note 
  */
uint32_t ltdc_read_point(uint16_t x,uint16_t y,uint8_t layer)
{
	
	return *(__IO uint16_t*)(hltdc.LayerCfg[layer].FBStartAdress + (2*(y*hltdc.LayerCfg[layer].ImageWidth + x)));
}

/**
  * @brief LTDC清除层
  * @param color-颜色
  * @param layer-层(0/1)
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
//			/* 用对应的颜色打点 */
//			ltdc_draw_point(x,y,color,layer);
//			
//		}
//	}
	uint32_t timeout=0;
	
	__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
	DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
	DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
	DMA2D->OPFCCR=LTDC_PIXEL_FORMAT_RGB565;	//设置颜色格式
	DMA2D->OOR=0;				//设置行偏移
	
	DMA2D->OMAR=(uint32_t)(hltdc.LayerCfg[layer].FBStartAdress);				//输出存储器地址
	DMA2D->NLR=hltdc.LayerCfg[layer].ImageHeight|(hltdc.LayerCfg[layer].ImageWidth<<16);	//设定行数寄存器
	DMA2D->OCOLR=color;						//设定输出颜色寄存器 
	DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;		//清除传输完成标志 	  
}

/**
  * @brief 在第2层上面绘制LOGO
  * @param None
  * @retval	None
  * @note 第二层专门用于显示LOGO的,绘制LOGO的目的是为了解决GUI在加载前的一段黑屏时间
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
  * @brief 删除第二层,(把第二层的Alpha变为0,第二层透明)
  * @param None
  * @retval	None
  * @note 第二层专门用于显示LOGO的,在加载期间显示完logo,就可以将层删除了
  */
void ltdc_delete_layer1(void)
{
	LTDC_LayerCfgTypeDef pLayerCfg = {0};
	
	/* LTDC层配置,这里将层定义到SDRAM地址 */
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
  * @brief 绘制单个字符
  * @param x-x坐标
  * @param y-y坐标
  * @param c-字符
  * @param size-字体大小(16/24/32)
  * @param fontcolor-字体颜色
  * @param bkcolor-字体的背景色,透明文字该参数为0
  * @retval	None
  * @note 
  */
void ltdc_draw_char(uint16_t x,uint16_t y,uint8_t c,uint8_t size,uint32_t fontcolor,uint32_t bkcolor)
{
	uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数

	c=c-' ';//得到偏移后的值(ASCII字库是从空格开始取模，所以-' '就是对应字符的字库)

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
				/* 超区域了 */
				return;
			}
			if((y-y0)==size)
			{
				y = y0;
				x++;
				if(x>=XSIZE_PHYS_L0)
				{
					/* 超区域了 */
					return;
				}
				break;
			}
		}
	}
}



/**
  * @brief 绘制单个字符
  * @param x-x坐标
  * @param y-y坐标
  * @param pText-字符串指针
  * @param size-字体大小(16/24/32)
  * @param fontcolor-字体颜色
  * @param bkcolor-字体的背景色,透明文字该参数为0
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
  * @brief LTDC底层初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_Init()调用,主要完成时钟使能,IO配置
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
		
		
//		/* 配置背光的GPIO */
//		GPIO_InitStruct.Pin = LCD_EN_PIN;
//		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//		GPIO_InitStruct.Pull = GPIO_NOPULL;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//		HAL_GPIO_Init(LCD_EN_GPIO_PORT, &GPIO_InitStruct);


	}
}


/**
  * @brief LTDC底层去初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_DeInit()调用,主要完成时钟禁能,IO配置清除
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



/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

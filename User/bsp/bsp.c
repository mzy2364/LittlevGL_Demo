/*
*******************************************************************************************************
*
* 文件名称 : bsp.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : 野牛开发板板级支持包
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "bsp.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/


/* 函数声明 ---------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/



/**
  * @brief BSP硬件初始化,完成外设,时钟等初始化
  * @param None
  * @retval	None
  */
void bsp_init(void)
{
//	HAL_Init();              //HAL库初始化
//	SystemClock_Config();    //系统时钟初始化,时钟频率在bsp.h定义了
	
	bsp_tim_init();          //BSP时基初始化
	led_init();              //LED初始化
	usart_init();            //串口初始化
	key_fifo_init();         //按键FIFO初始化
	delay_tim_init();        //延时函数定时器初始化
	i2c3_init();             //I2C3初始化
	gt9147_init();           //GT9147初始化
	LCD_initial();           //液晶屏SPI初始化
	fmc_init();              //FMC_SDRAM初始化
	ltdc_init();             //LTDC初始化
	sflash_init();           //SPI_FLASH初始化
	setting_init();          //SETTING初始化
	fatfs_init();            //初始化文件系统	
	adc_light_init();	     //光敏ADC初始化
	
	ltdc_clear_layer(LCD_COLOR_BLACK,0);
	
	f_mount(&SDFatFS,"0:",0);
	f_mount(&SFLASHFatFS,"1:",0);

	
	
	
	print_logo();			 //打印logo
	
}


/**
  * @brief BSP时基初始化
  * @param None
  * @retval	None
  * @note 10ms的中断用于按键检测,RTOS可以使用软件定时器检测
  */
void bsp_tim_init(void)
{
	//打开定时器4的时钟
	RCC->APB1ENR |= 1<<2;
	//设置预分频值
	TIM4->PSC = (SystemCoreClock/2)/10000;
	//设置自动重装载值
	TIM4->ARR = 99;
	//下面两步没有的话预分频的值必须等到产生一次更新事件后才会被采用
	//重新初始化定时器计数器并生成寄存器更新事件,确保预分频值被采用
	TIM4->EGR |= (1<<0);
	//清除更新标志位,该位在发生更新事件时通过硬件置 1,但需要通过软件清零
	TIM4->SR &= ~(1<<0);
	//使能更新中断
	TIM4->DIER |= 1<<0;
	//使能定时器
	TIM4->CR1 |= 1<<0;
	//设置中断优先级
	HAL_NVIC_SetPriority(TIM4_IRQn, 15, 0);
	//使能中断
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}


void TIM4_IRQHandler(void)
{
	//定时器更新中断
	if(TIM4->SR & 0X01)
	{
		if(key_is_init())
		{
			key_scan();
		}
	}
	//清除更新标志
	TIM4->SR &= ~(1<<0);
	
}



/**
  * @brief 调用串口打印logo信息,使用前确保配置了printf
  * @param None
  * @retval	None
  */
void print_logo(void)
{
	printf("\r\nOpen Rabbit!\r\n");
	printf("FIRMWARE_VERSION:%s\r\n",FIRMWARE_VERSION);
	
}







/**
  * @brief 系统时钟配置
  * @retval None
  */
#ifdef CLOCK_192M
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef RTCPeriphClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  //SYSCLK = HSE/PLLM*PLLN/PLLP
  //SYSCLK = 25/25*384/2 = 192MHz
  //48MHz = HSE/PLLM*PLLN/PLLQ
  /**Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 132;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  //LCD-TFT clocks = HSE/PLLM*PLLSAIN/PLLSAIR/PLLSAIDivR
  //LCD-TFT clocks = 25/25*132/2/2 = 33MHz
  RTCPeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  RTCPeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&RTCPeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}
#endif
#ifdef CLOCK_240M
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef RTCPeriphClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 288;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 10;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  //SYSCLK = HSE/PLLM*PLLN/PLLP
  //SYSCLK = 25/15*288/2 = 240MHz
  //48MHz = HSE/PLLM*PLLN/PLLQ
  /**Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 78;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  //LCD-TFT clocks = HSE/PLLM*PLLSAIN/PLLSAIR/PLLSAIDivR
  //LCD-TFT clocks = 25/15*78/2/2 = 32.5MHz
  RTCPeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  RTCPeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&RTCPeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}
#endif

/**
  * @brief 硬件初始化错误进入到这里,继承于STM32的HAL库,只定义该函数
  * @param None
  * @retval	None
  */
void Error_Handler(void)
{
	/*do somthing*/
	
	
}


/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

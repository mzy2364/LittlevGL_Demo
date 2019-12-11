/*
*******************************************************************************************************
*
* �ļ����� : bsp.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : Ұţ������弶֧�ְ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/


/* �������� ---------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/



/**
  * @brief BSPӲ����ʼ��,�������,ʱ�ӵȳ�ʼ��
  * @param None
  * @retval	None
  */
void bsp_init(void)
{
//	HAL_Init();              //HAL���ʼ��
//	SystemClock_Config();    //ϵͳʱ�ӳ�ʼ��,ʱ��Ƶ����bsp.h������
	
	bsp_tim_init();          //BSPʱ����ʼ��
	led_init();              //LED��ʼ��
	usart_init();            //���ڳ�ʼ��
	key_fifo_init();         //����FIFO��ʼ��
	delay_tim_init();        //��ʱ������ʱ����ʼ��
	i2c3_init();             //I2C3��ʼ��
	gt9147_init();           //GT9147��ʼ��
	LCD_initial();           //Һ����SPI��ʼ��
	fmc_init();              //FMC_SDRAM��ʼ��
	ltdc_init();             //LTDC��ʼ��
	sflash_init();           //SPI_FLASH��ʼ��
	setting_init();          //SETTING��ʼ��
	fatfs_init();            //��ʼ���ļ�ϵͳ	
	adc_light_init();	     //����ADC��ʼ��
	
	ltdc_clear_layer(LCD_COLOR_BLACK,0);
	
	f_mount(&SDFatFS,"0:",0);
	f_mount(&SFLASHFatFS,"1:",0);

	
	
	
	print_logo();			 //��ӡlogo
	
}


/**
  * @brief BSPʱ����ʼ��
  * @param None
  * @retval	None
  * @note 10ms���ж����ڰ������,RTOS����ʹ�������ʱ�����
  */
void bsp_tim_init(void)
{
	//�򿪶�ʱ��4��ʱ��
	RCC->APB1ENR |= 1<<2;
	//����Ԥ��Ƶֵ
	TIM4->PSC = (SystemCoreClock/2)/10000;
	//�����Զ���װ��ֵ
	TIM4->ARR = 99;
	//��������û�еĻ�Ԥ��Ƶ��ֵ����ȵ�����һ�θ����¼���Żᱻ����
	//���³�ʼ����ʱ�������������ɼĴ��������¼�,ȷ��Ԥ��Ƶֵ������
	TIM4->EGR |= (1<<0);
	//������±�־λ,��λ�ڷ��������¼�ʱͨ��Ӳ���� 1,����Ҫͨ���������
	TIM4->SR &= ~(1<<0);
	//ʹ�ܸ����ж�
	TIM4->DIER |= 1<<0;
	//ʹ�ܶ�ʱ��
	TIM4->CR1 |= 1<<0;
	//�����ж����ȼ�
	HAL_NVIC_SetPriority(TIM4_IRQn, 15, 0);
	//ʹ���ж�
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}


void TIM4_IRQHandler(void)
{
	//��ʱ�������ж�
	if(TIM4->SR & 0X01)
	{
		if(key_is_init())
		{
			key_scan();
		}
	}
	//������±�־
	TIM4->SR &= ~(1<<0);
	
}



/**
  * @brief ���ô��ڴ�ӡlogo��Ϣ,ʹ��ǰȷ��������printf
  * @param None
  * @retval	None
  */
void print_logo(void)
{
	printf("\r\nOpen Rabbit!\r\n");
	printf("FIRMWARE_VERSION:%s\r\n",FIRMWARE_VERSION);
	
}







/**
  * @brief ϵͳʱ������
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
  * @brief Ӳ����ʼ��������뵽����,�̳���STM32��HAL��,ֻ����ú���
  * @param None
  * @retval	None
  */
void Error_Handler(void)
{
	/*do somthing*/
	
	
}


/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

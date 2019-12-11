/*
*******************************************************************************************************
*
* �ļ����� : rtc.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : RTC�����ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "rtc.h"


/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* �������� ---------------------------------------------------------*/



/**
  * @brief RTC��ʼ��
  * @param None
  * @retval	None
  */
void rtc_init(void)
{

	/** Initialize RTC Only 
	*/
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}

	
    if(HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR0)!=0XAAA0)//�Ƿ��һ������
    { 
        rtc_set_time(9,57,56);	        //����ʱ�� ,����ʵ��ʱ���޸�
		rtc_set_date(19,8,16,5);		                    //��������
        HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR0,0XAAA0);//����Ѿ���ʼ������
    }
	
}


/**
  * @brief ����RTC��ʱ��
  * @param hour-Сʱ
  * @param minute-����
  * @param second-��
  * @retval	None
  */
void rtc_set_time(uint8_t hour,uint8_t minute,uint8_t second)
{
	RTC_TimeTypeDef set_time= {0};
	
	set_time.Hours = hour;
	set_time.Minutes = minute;
	set_time.Seconds = second;
	set_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	set_time.StoreOperation = RTC_STOREOPERATION_RESET;
	
	HAL_RTC_SetTime(&hrtc, &set_time, RTC_FORMAT_BIN);
}

/**
  * @brief ����RTC������
  * @param year-���(2λ��  ʵ�����-2000)
  * @param month-�·�
  * @param date-����
  * @param week-����
  * @retval	None
  */
void rtc_set_date(uint8_t year,uint8_t month,uint8_t date,uint8_t week)
{
	
	RTC_DateTypeDef set_date= {0};
	
	set_date.WeekDay = week;
	set_date.Month = month;
	set_date.Date = date;
	set_date.Year = year;
	
	HAL_RTC_SetDate(&hrtc, &set_date, RTC_FORMAT_BIN);
	
}

/**
  * @brief ��ȡ��ǰRTC�����ں�ʱ��
  * @param date-�������ڵĽṹ��
  * @param time-����ʱ��Ľṹ��
  * @retval	None
  */
void rtc_current(RTC_DateTypeDef *date,RTC_TimeTypeDef *time)
{
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, date, RTC_FORMAT_BIN);
}




/**
  * @brief RTC�ײ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_Init()����,��Ҫ���ʱ��ʹ��,IO����
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

	if(rtcHandle->Instance==RTC)
	{
		/* RTC clock enable */
		__HAL_RCC_RTC_ENABLE();

		/* RTC interrupt Init */
		HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 3, 0);
		HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
	}
}


/**
  * @brief RTC�ײ�ȥ��ʼ������
  * @param None
  * @retval	None
  * @note �ú����ᱻHAL_xxx_DeInit()����,��Ҫ���ʱ�ӽ���,IO�������
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

	if(rtcHandle->Instance==RTC)
	{
		/* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();

		/* RTC interrupt Deinit */
		HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);
	}
} 









/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

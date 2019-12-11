/*
*******************************************************************************************************
*
* 文件名称 : rtc.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : RTC驱动文件
* 
*******************************************************************************************************
*/



/* 头文件 -----------------------------------------------------------*/
#include "rtc.h"


/* 宏定义 -----------------------------------------------------------*/


/* 变量 -------------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* 函数声明 ---------------------------------------------------------*/



/**
  * @brief RTC初始化
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

	
    if(HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR0)!=0XAAA0)//是否第一次配置
    { 
        rtc_set_time(9,57,56);	        //设置时间 ,根据实际时间修改
		rtc_set_date(19,8,16,5);		                    //设置日期
        HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR0,0XAAA0);//标记已经初始化过了
    }
	
}


/**
  * @brief 设置RTC的时间
  * @param hour-小时
  * @param minute-分钟
  * @param second-秒
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
  * @brief 设置RTC的日期
  * @param year-年份(2位数  实际年份-2000)
  * @param month-月份
  * @param date-日期
  * @param week-星期
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
  * @brief 获取当前RTC的日期和时间
  * @param date-保存日期的结构体
  * @param time-保存时间的结构体
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
  * @brief RTC底层初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_Init()调用,主要完成时钟使能,IO配置
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
  * @brief RTC底层去初始化函数
  * @param None
  * @retval	None
  * @note 该函数会被HAL_xxx_DeInit()调用,主要完成时钟禁能,IO配置清除
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









/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

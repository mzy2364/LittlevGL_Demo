/*
*******************************************************************************************************
*
* �ļ����� : board.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : RT-Thread�����ļ�
* 
*******************************************************************************************************
*/

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "bsp.h"

#include "stm32f4xx.h"
#include "board.h"
#include "usart.h"
#include "stm32f4xx_hal.h"


void _init(void)
{

}






void rt_hw_console_output(const char *str)
{
	//�����ٽ��
	rt_enter_critical();
	while(*str!='\0')
	{
		if(*str=='\n')
		{
			HAL_UART_Transmit(&huart1,(uint8_t*)"\r",1,1000);
			while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);
		}
		HAL_UART_Transmit(&huart1,(uint8_t*)str++,1,1000);
		while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);
	}
	//HAL_UART_Transmit(&Uart3Handle,(uint8_t*)str,sizeof(str),1000);
	//while(__HAL_UART_GET_FLAG(&Uart3Handle,UART_FLAG_TC)!=SET);
	//�˳��ٽ��
	rt_exit_critical();
}


#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
static uint32_t rt_heap[RT_HEAP_SIZE];	// heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif


/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    /* tick for HAL Library */
    HAL_IncTick();
	lv_tick_inc(1);
    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}



/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
	
	SCB->VTOR = FLASH_BASE | 0x10000;//����ƫ����
	
	HAL_Init();              //HAL���ʼ��
	SystemClock_Config();    //ϵͳʱ�ӳ�ʼ��,ʱ��Ƶ����bsp.h������
	
	//bsp_init();
	

	
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
	

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#else
    stm32_hw_usart_init();
#endif
	
#ifdef RT_USING_CONSOLE
    rt_console_set_device(CONSOLE_DEVICE);
#endif
	
}

/*@}*/


/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

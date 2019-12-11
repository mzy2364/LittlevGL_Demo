/*
*******************************************************************************************************
*
* �ļ����� : task.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : �������ļ�
* 
*******************************************************************************************************
*/



/* ͷ�ļ� -----------------------------------------------------------*/
#include "bsp.h"
#include "gui_user.h"
#include "task.h"

/* �궨�� -----------------------------------------------------------*/


/* ���� -------------------------------------------------------------*/


/* �������� ---------------------------------------------------------*/

/* RT-Thread��غ����ͱ��� */
static rt_thread_t key_thread = RT_NULL;
static void key_thread_entry(void *parameter);

static rt_thread_t gui_thread = RT_NULL;
static void gui_thread_entry(void *parameter);

static rt_thread_t idle_thread = RT_NULL;
static void idle_thread_entry(void *parameter);

/**
  * @brief main������
  * @param None
  * @retval	None
  */
void my_task_schedule(void)
{
	
	/* ��ֵԽС���ȼ�Խ��, 0����������ȼ� */
	
	
	
	
	
	
	/* ���������߳� */
	key_thread = rt_thread_create("key_thread",
									key_thread_entry,
									RT_NULL,
									512,
									2,
									20);
	rt_thread_startup(key_thread);	
	
	/* ����GUI�߳� */
	gui_thread = rt_thread_create("gui_thread",
									gui_thread_entry,
									RT_NULL,
									4096,
									2,
									20);
	rt_thread_startup(gui_thread);
	
	/* �����û������߳� */
	idle_thread = rt_thread_create("idle_thread",
									idle_thread_entry,
									RT_NULL,
									128,
									RT_THREAD_PRIORITY_MAX-1,
									20);
	rt_thread_startup(idle_thread);
	
	
	
}




/**
  * @brief GUI�̺߳���
  * @param parameter-�߳���ڲ���
  * @retval	None
  */
static void gui_thread_entry(void *parameter)
{

	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	lv_app_main();

	while(1)
	{
		lv_task_handler();
		rt_thread_delay(5);
	}
}



/**
  * @brief �����̺߳���
  * @param parameter-�߳���ڲ���
  * @retval	None
  */
static void key_thread_entry(void *parameter)
{
	uint8_t key;
	while(1)
	{
		
		key = key_get();
		switch(key)
		{
			case KEY_LEFT_DOWN:
				rt_kprintf("KEY_LEFT_DOWN\r\n");
				break;
			case KEY_LEFT_UP:
				rt_kprintf("KEY_LEFT_UP\r\n");
				break;
			case KEY_LEFT_LONG:
				rt_kprintf("KEY_LEFT_LONG\r\n");
				break;
			case KEY_WKUP_DOWN:
				rt_kprintf("KEY_WKUP_DOWN\r\n");
				break;
			case KEY_WKUP_UP:
				rt_kprintf("KEY_WKUP_UP\r\n");
				break;
			case KEY_WKUP_LONG:
				rt_kprintf("KEY_WKUP_LONG\r\n");
				break;
			case KEY_RIGHT_DOWN:
				rt_kprintf("KEY_RIGHT_DOWN\r\n");
				break;
			case KEY_RIGHT_UP:
				rt_kprintf("KEY_RIGHT_UP\r\n");
				break;
			case KEY_RIGHT_LONG:
				rt_kprintf("KEY_RIGHT_LONG\r\n");
				break;
			default:
				break;
		}
		rt_thread_delay(10);
	}
}


/**
  * @brief �û������̺߳���
  * @param parameter-�߳���ڲ���
  * @retval	None
  */
static void idle_thread_entry(void *parameter)
{
	while(1)
	{
		//iwdg_feed();
		rt_thread_delay(500);
	}
}



/*
		key = key_get();
		switch(key)
		{
			case KEY_LEFT_DOWN:
				printf("KEY_LEFT_DOWN\r\n");
				break;
			case KEY_LEFT_UP:
				printf("KEY_LEFT_UP\r\n");
				break;
			case KEY_LEFT_LONG:
				printf("KEY_LEFT_LONG\r\n");
				break;
			case KEY_WKUP_DOWN:
				printf("KEY_WKUP_DOWN\r\n");
				break;
			case KEY_WKUP_UP:
				printf("KEY_WKUP_UP\r\n");
				break;
			case KEY_WKUP_LONG:
				printf("KEY_WKUP_LONG\r\n");
				break;
			case KEY_RIGHT_DOWN:
				printf("KEY_RIGHT_DOWN\r\n");
				break;
			case KEY_RIGHT_UP:
				printf("KEY_RIGHT_UP\r\n");
				break;
			case KEY_RIGHT_LONG:
				printf("KEY_RIGHT_LONG\r\n");
				break;
			default:
				break;
		}
*/



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

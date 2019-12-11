/* RT-Thread config file */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

//#include "RTE_Components.h"


//RTT支持多少个优先级，取值范围8~256
#define RT_THREAD_PRIORITY_MAX  32
//表示操作系统每秒钟有多少个tick,tick只操作系统的时钟周期，默认为1000，即操作系统的时钟周期为1ms
#define RT_TICK_PER_SECOND	1000
//表示CPU处理数据需要多少字节对齐
#define RT_ALIGN_SIZE   4
//内核对象名字的最大长度
#define RT_NAME_MAX	   20
//使用rtt组件初始化，默认使能
#define RT_USING_COMPONENTS_INIT
//使用用户main函数，默认打开
#define RT_USING_USER_MAIN
//main线程栈大小，取值范围1-4086
#define RT_MAIN_THREAD_STACK_SIZE     512

//调试配置。包括了内核调试配置，组件调试配置和线程栈溢出检测，目前全部关闭
//#define RT_DEBUG
#define RT_DEBUG_INIT 0
//#define RT_USING_OVERFLOW_CHECK

//钩子函数配置
//#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK

//软件定时器配置，目前关闭，不使用软件定时器
#define RT_USING_TIMER_SOFT         0
#if RT_USING_TIMER_SOFT == 0
#undef RT_USING_TIMER_SOFT
#endif

#define RT_TIMER_THREAD_PRIO		4

#define RT_TIMER_THREAD_STACK_SIZE	512

#define RT_TIMER_TICK_PER_SECOND	100


//内部通信配置，包括信号量、互斥量、事件、邮箱和消息队列，根据需要配置。
#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

//内存管理配置
//表示是否使用内存池
#define RT_USING_MEMPOOL
//表示是否使用堆
#define RT_USING_HEAP
//表示是否使用小内存
#define RT_USING_SMALL_MEM
//表示是否使用极小内存
//#define RT_USING_TINY_SIZE

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
//RTT堆大小(=RT_HEAP_SIZE*4)
#define RT_HEAP_SIZE 256*50
#endif

//控制台配置
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE          128
#define RT_CONSOLE_DEVICE_NAME      "uart1"


#define RTE_FINSH_USING_MSH
//FINISH配置
#if defined(RTE_FINSH_USING_MSH)
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_USING_MSH_ONLY
#define __FINSH_THREAD_PRIORITY     5
#define FINSH_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 8 * __FINSH_THREAD_PRIORITY + 1)
#define FINSH_THREAD_STACK_SIZE     512
#define FINSH_HISTORY_LINES	        1
#define FINSH_USING_SYMTAB
#endif

//设备配置
#define RT_USING_DEVICE


#endif

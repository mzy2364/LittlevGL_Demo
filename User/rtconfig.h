/* RT-Thread config file */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

//#include "RTE_Components.h"


//RTT֧�ֶ��ٸ����ȼ���ȡֵ��Χ8~256
#define RT_THREAD_PRIORITY_MAX  32
//��ʾ����ϵͳÿ�����ж��ٸ�tick,tickֻ����ϵͳ��ʱ�����ڣ�Ĭ��Ϊ1000��������ϵͳ��ʱ������Ϊ1ms
#define RT_TICK_PER_SECOND	1000
//��ʾCPU����������Ҫ�����ֽڶ���
#define RT_ALIGN_SIZE   4
//�ں˶������ֵ���󳤶�
#define RT_NAME_MAX	   20
//ʹ��rtt�����ʼ����Ĭ��ʹ��
#define RT_USING_COMPONENTS_INIT
//ʹ���û�main������Ĭ�ϴ�
#define RT_USING_USER_MAIN
//main�߳�ջ��С��ȡֵ��Χ1-4086
#define RT_MAIN_THREAD_STACK_SIZE     512

//�������á��������ں˵������ã�����������ú��߳�ջ�����⣬Ŀǰȫ���ر�
//#define RT_DEBUG
#define RT_DEBUG_INIT 0
//#define RT_USING_OVERFLOW_CHECK

//���Ӻ�������
//#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK

//�����ʱ�����ã�Ŀǰ�رգ���ʹ�������ʱ��
#define RT_USING_TIMER_SOFT         0
#if RT_USING_TIMER_SOFT == 0
#undef RT_USING_TIMER_SOFT
#endif

#define RT_TIMER_THREAD_PRIO		4

#define RT_TIMER_THREAD_STACK_SIZE	512

#define RT_TIMER_TICK_PER_SECOND	100


//�ڲ�ͨ�����ã������ź��������������¼����������Ϣ���У�������Ҫ���á�
#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

//�ڴ��������
//��ʾ�Ƿ�ʹ���ڴ��
#define RT_USING_MEMPOOL
//��ʾ�Ƿ�ʹ�ö�
#define RT_USING_HEAP
//��ʾ�Ƿ�ʹ��С�ڴ�
#define RT_USING_SMALL_MEM
//��ʾ�Ƿ�ʹ�ü�С�ڴ�
//#define RT_USING_TINY_SIZE

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
//RTT�Ѵ�С(=RT_HEAP_SIZE*4)
#define RT_HEAP_SIZE 256*50
#endif

//����̨����
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE          128
#define RT_CONSOLE_DEVICE_NAME      "uart1"


#define RTE_FINSH_USING_MSH
//FINISH����
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

//�豸����
#define RT_USING_DEVICE


#endif

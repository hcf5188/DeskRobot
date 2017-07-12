
#include  "app_cfg.h"
#include  <cpu_core.h>
#include  <os.h>

#include  "lib_str.h"
#include  "system.h"

extern OS_STK Start_Task_Stk[TASK_STK_SIZE];


int  main (void)
{	                                             
	ALL_Init();	   //��ʼ�� 
	POWER_ON;      //����
	OSInit();
	OSTaskCreate((void (*)(void *))Start_Task,
				(void           *)0,
				(OS_STK         *)&Start_Task_Stk[TASK_STK_SIZE - 1],
				(INT8U           )START_TASK_PRIO); 
	OSStart(); 
}








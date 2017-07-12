#include "all_init.h"

void CPUCLK_Init(void)
{
	//����ϵͳʱ��
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
}
void SYSTICK_Init(void)
{
	ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / (INT32U)OS_TICKS_PER_SEC);
	SysTickIntRegister(OS_CPU_SysTickHandler);
	ROM_SysTickEnable();
}
void MortorTimerInit(void )
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);   //Timer0A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);   //Timer1A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2); 
	
//	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
//	//���ö�ʱ��װ��ֵ
//	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//1msһ���ж�
//	//����Timer2A�ж��¼�Ϊ��ʱ����ʱ
//	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//	//ʹ�� NVIC �е� TIMER2A
//	IntEnable(INT_TIMER0A);
//	IntPrioritySet(INT_TIMER0A,0xe0);
	//��ʱ��TIMER2Aʹ��	
	//TimerEnable(TIMER0_BASE, TIMER_A);
	
	TimerDisable(TIMER0_BASE, TIMER_A);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);	
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//	
//	TimerEnable(TIMER0_BASE, TIMER_A);

}
void TIMER_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);   //Timer1A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);   //Timer2A
	
	//����TIMER2��ʱ��
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
	//���ö�ʱ��װ��ֵ
	TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//1msһ���ж�
	//����Timer2A�ж��¼�Ϊ��ʱ����ʱ
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	//ʹ�� NVIC �е� TIMER2A
	IntEnable(INT_TIMER2A);
	IntPrioritySet(INT_TIMER2A,0xe0);
	//��ʱ��TIMER2Aʹ��	
	//TimerEnable(TIMER2_BASE, TIMER_A);
}











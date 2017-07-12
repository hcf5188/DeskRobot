#include "all_init.h"

void CPUCLK_Init(void)
{
	//配置系统时钟
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
//	//配置定时器装载值
//	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//1ms一次中断
//	//配置Timer2A中断事件为定时器超时
//	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//	//使能 NVIC 中的 TIMER2A
//	IntEnable(INT_TIMER0A);
//	IntPrioritySet(INT_TIMER0A,0xe0);
	//定时器TIMER2A使能	
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
	
	//配置TIMER2定时器
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
	//配置定时器装载值
	TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//1ms一次中断
	//配置Timer2A中断事件为定时器超时
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	//使能 NVIC 中的 TIMER2A
	IntEnable(INT_TIMER2A);
	IntPrioritySet(INT_TIMER2A,0xe0);
	//定时器TIMER2A使能	
	//TimerEnable(TIMER2_BASE, TIMER_A);
}











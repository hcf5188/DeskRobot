/************************************************
* Project Name : igo
* Function Name : INIT
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/
#ifndef __TIMER_FUNCTION_H__
#define __TIMER_FUNCTION_H__
extern void Timer0_Init(void);
extern void Timer1_Init(void);
extern void Timer2_Init(void);
extern void Timer0BIntHandler(void);
extern void Timer1BIntHandler(void);
extern void Timer2BIntHandler(void);
#endif


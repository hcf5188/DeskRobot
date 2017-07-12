/************************************************
* Project Name : igo
* Function Name : Serial
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/
#ifndef _UART0_COMPUTER_FUNCTION_H_
#define _UART0_COMPUTER_FUNCTION_H_

extern void HMI_To_Computer_Init(void);
extern void HMI_To_Computer_Bag(void);
extern void HMI_To_Computer_CRC_Bag(void);
extern void HMI_To_Computer_Send(void);
extern void HMI_To_Computer_Receive(void);
extern void HMI_To_Computer_Handle(void);

#endif

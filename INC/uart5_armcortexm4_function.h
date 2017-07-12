/************************************************
* Project Name : igo
* Function Name : Serial
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/
#ifndef _UART5_ARMCORTEXM4_FUNCTION_H_
#define _UART5_ARMCORTEXM4_FUNCTION_H_

#define UART5_Idle     0			
#define UART5_Address  1			
#define UART5_Cmd      2
#define UART5_Length   3
#define UART5_Data     4
#define UART5_Crc      5


extern void HMI_To_ARMCortexM4_Init(void);
extern void HMI_To_ARMCortexM4_Bag(void);
extern void HMI_To_ARMCortexM4_Send(void);
extern void HMI_To_ARMCortexM4_Receive(void);
extern void HMI_To_ARMCortexM4_Handle(void);

#endif

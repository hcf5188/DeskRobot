#ifndef __UART_FUNCTION_H__
#define __UART_FUNCTION_H__

extern void uart1_init(void);
extern void UART1Read(void);
extern void UART1_Send(void);
extern void UART1SendPack(void);
extern void UART1_Handle(void);

#define UART1_Idle     0			
#define UART1_Data_Rcv 1			
#define UART1_CRC      2		

extern void uart3_init(void);
extern void UART3Read(void);
extern void UART3_Send(void);
extern void UART3SendPack(void);
extern void UART3_Handle(void);

#define UART3_Idle     0			
#define UART3_Data_Rcv 1			
#define UART3_CRC      2	

#endif


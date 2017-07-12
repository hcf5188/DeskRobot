#include "all_init.h"


void BlueTooth_Handler(void);

void UART1_Init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	
	ROM_GPIOPinConfigure(GPIO_PC4_U1RX);
    ROM_GPIOPinConfigure(GPIO_PC5_U1TX);
	
	ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	
	ROM_UARTConfigSetExpClk(UART1_BASE, 
			ROM_SysCtlClockGet(), 
			115200,
           (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	//��ʹ�ܴ���FIFO
	ROM_UARTFIFODisable(UART1_BASE);
	//ʹ�ܴ��ڽ����жϺʹ��ڽ��ճ�ʱ�ж� 
	ROM_UARTIntEnable( UART1_BASE, UART_INT_RX | UART_INT_TX);// | UART_INT_RT);

	//����3 �жϴ�����   BlueTooth_Handler
	UARTIntRegister(UART1_BASE, BlueTooth_Handler);
	//ʹ�ܽ����ж�
	ROM_IntEnable( INT_UART1 );	
}
/****************************************************************
*		void UART1SendByte(uint8_t dat)
*��    ��: ����һ���ֽ�		
*�������: ��
*�������: ��
****************************************************************/
extern pCIR_QUEUE  UART1_Tx_Buf;
extern pSTORE      UART1_Rx_Buf;

void UART1SendByte(uint8_t dat)
{
#if OS_CRITICAL_METHOD == 3u           /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr = 0u;
#endif
	uint8_t data;
	if(CirQ_GetLength(UART1_Tx_Buf) > 0)
	{
		OS_ENTER_CRITICAL();
		CirQ_OnePush(UART1_Tx_Buf,dat);
		CirQ_Pop(UART1_Tx_Buf,&data);
		OS_EXIT_CRITICAL();
		
		UARTCharPut(UART1_BASE,data);
	}
	else
		UARTCharPut(UART1_BASE,dat);
}
/****************************************************************
*	uint8_t Uart_SendDatas(const uint8_t *s,uint8_t length)
*��    ��: ����һ���ַ���	
*�������: ��
*�������: uint8_t ������
****************************************************************/
uint8_t UART1SendDatas(const uint8_t *s,uint8_t length)
{
#if OS_CRITICAL_METHOD == 3u           /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr = 0u;
#endif
	uint8_t data;
	if((length < 1) || (length > 128))
	{
		return 1;
	}
	OS_ENTER_CRITICAL();
	if(CirQ_Pushs(UART1_Tx_Buf,s,length) != OK)
	{
		OS_EXIT_CRITICAL();
		return 2;
	}
	OS_EXIT_CRITICAL();
	if(CirQ_GetLength(UART1_Tx_Buf) > 0)
	{
		OS_ENTER_CRITICAL();
		CirQ_Pop(UART1_Tx_Buf,&data);
		OS_EXIT_CRITICAL();
		
		UARTCharPut(UART1_BASE,data);
	}
	return  0;
}

extern OS_EVENT *UART1_Q_Rx;
static uint32_t  uart1State;
//bool rxTimeOut  = 0;    //���ճ�ʱ��־
static uint8_t sendDat = 0;      //Ҫ���͵�����
static uint8_t receDat = 0;      //Ҫ���յ�����
uint8_t *pRx_Buf = NULL;  //���������ݣ�Ҫ���͵����ݰ�����
static uint8_t receLength = 0;   //�������ݳ���
static bool rxTimeOut = 0;       //���ڽ��ճ�ʱ��־  0 - δ��ʱ   1 - ��ʱ
void BlueTooth_Handler(void)
{
	OSIntEnter();
	uart1State = UARTIntStatus(UART1_BASE, true);
	UARTIntClear(UART1_BASE, uart1State);
	if((uart1State & UART_INT_TX) != 0)//��������ж�
	{
		if(CirQ_GetLength(UART1_Tx_Buf) > 0)
		{
			CirQ_Pop(UART1_Tx_Buf,&sendDat);
			UARTCharPut(UART1_BASE,sendDat);
		}
	}
	if((uart1State & UART_INT_RX) != 0) // ���ڽ����ж�
	{
		TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
		TimerEnable(TIMER2_BASE, TIMER_A);
		
		receDat = UARTCharGet(UART1_BASE);
		
		if(rxTimeOut)                     //�ж�֡ͷ
			Store_Clear(UART1_Rx_Buf);    //��ս��ջ�����
		
		Store_Push(UART1_Rx_Buf,receDat); //�����ݴ洢
		receLength = Store_Getlength(UART1_Rx_Buf);
		
		if(receLength >= 10)              //����������
		{
			pRx_Buf = UART1_Rx_Buf->base;
			UART1_Rx_Buf->base = Mem_malloc(10);
			Store_Clear(UART1_Rx_Buf);
			if(OSQPost(UART1_Q_Rx,pRx_Buf) != OS_ERR_NONE)//��Ϣ���п���������Ч����Ҫ�ͷţ���ֹ�ڴ�й©
				Mem_free(pRx_Buf);
			
			TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
			TimerDisable(TIMER2_BASE, TIMER_A);
		}
		rxTimeOut = 0;
	}
	OSIntExit();
}
static uint8_t  rxCount = 0;
void TIMER2A_Handler(void)           //���ڳ�ʱ�жϴ�����
{
	OSIntEnter();
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT); // ���־λ
	
	if(rxTimeOut == 0)
	{
		rxCount ++;
		if(rxCount>=3)
			rxTimeOut = 1;
	}
	else
	{
		rxCount =0;
		TimerDisable(TIMER2_BASE, TIMER_A);
	}
	OSIntExit();
}










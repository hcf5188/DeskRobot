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
	//不使能串口FIFO
	ROM_UARTFIFODisable(UART1_BASE);
	//使能串口接收中断和串口接收超时中断 
	ROM_UARTIntEnable( UART1_BASE, UART_INT_RX | UART_INT_TX);// | UART_INT_RT);

	//串口3 中断处理函数   BlueTooth_Handler
	UARTIntRegister(UART1_BASE, BlueTooth_Handler);
	//使能接收中断
	ROM_IntEnable( INT_UART1 );	
}
/****************************************************************
*		void UART1SendByte(uint8_t dat)
*描    述: 发送一个字节		
*输入参数: 无
*输出参数: 无
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
*描    述: 发送一个字符串	
*输入参数: 无
*输出参数: uint8_t 错误码
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
//bool rxTimeOut  = 0;    //接收超时标志
static uint8_t sendDat = 0;      //要发送的数据
static uint8_t receDat = 0;      //要接收的数据
uint8_t *pRx_Buf = NULL;  //接收完数据，要发送的数据包邮箱
static uint8_t receLength = 0;   //接收数据长度
static bool rxTimeOut = 0;       //串口接收超时标志  0 - 未超时   1 - 超时
void BlueTooth_Handler(void)
{
	OSIntEnter();
	uart1State = UARTIntStatus(UART1_BASE, true);
	UARTIntClear(UART1_BASE, uart1State);
	if((uart1State & UART_INT_TX) != 0)//发送完成中断
	{
		if(CirQ_GetLength(UART1_Tx_Buf) > 0)
		{
			CirQ_Pop(UART1_Tx_Buf,&sendDat);
			UARTCharPut(UART1_BASE,sendDat);
		}
	}
	if((uart1State & UART_INT_RX) != 0) // 串口接收中断
	{
		TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
		TimerEnable(TIMER2_BASE, TIMER_A);
		
		receDat = UARTCharGet(UART1_BASE);
		
		if(rxTimeOut)                     //判断帧头
			Store_Clear(UART1_Rx_Buf);    //清空接收缓冲区
		
		Store_Push(UART1_Rx_Buf,receDat); //将数据存储
		receLength = Store_Getlength(UART1_Rx_Buf);
		
		if(receLength >= 10)              //接收完数据
		{
			pRx_Buf = UART1_Rx_Buf->base;
			UART1_Rx_Buf->base = Mem_malloc(10);
			Store_Clear(UART1_Rx_Buf);
			if(OSQPost(UART1_Q_Rx,pRx_Buf) != OS_ERR_NONE)//消息队列可能满，无效的需要释放，防止内存泄漏
				Mem_free(pRx_Buf);
			
			TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
			TimerDisable(TIMER2_BASE, TIMER_A);
		}
		rxTimeOut = 0;
	}
	OSIntExit();
}
static uint8_t  rxCount = 0;
void TIMER2A_Handler(void)           //串口超时中断处理函数
{
	OSIntEnter();
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT); // 清标志位
	
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










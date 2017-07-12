

#include "all_init.h"


pCIR_QUEUE  UART1_Tx_Buf;
pSTORE      UART1_Rx_Buf;
/****************************************************************
*			void UART1_Init(void)
* 描	述 : 初始化串口1		
* 输入参数 : 无
* 返 回 值 : 无
****************************************************************/
void UART1_Init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	
	ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
    ROM_GPIOPinConfigure(GPIO_PB1_U1TX);
	
	ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	ROM_UARTConfigSetExpClk(UART1_BASE, 
			ROM_SysCtlClockGet(), 
			115200,
           (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	//不使能串口FIFO
	ROM_UARTFIFODisable(UART1_BASE);
	
	ROM_UARTIntEnable( UART1_BASE, UART_INT_RX);
	ROM_UARTIntEnable( UART1_BASE, UART_INT_TX);
	
	//中断函数
	UARTIntRegister(UART1_BASE, UART1_Handler);
	//使能接收中断
	ROM_IntEnable( INT_UART1 );
	
	UART1_Rx_Buf = Store_Init(128);//接受数据堆初始化
	UART1_Tx_Buf = Cir_Queue_Init(256);//发送循环队列初始化
	UARTCharPut(UART1_BASE,'\n');
}
/****************************************************************
*		void Uart_SendByte(uint8_t dat)
* 描	述 : 发送一个字节的数据 		
* 输入参数 : 无
* 返 回 值 : 无
****************************************************************/
extern OS_EVENT *Print_Mutex;
#define  PRINT_LENGTH   256
char PrintfBuf[PRINT_LENGTH];//打印输出缓冲区
uint8_t Robot_printf(char* fmt, ...)
{

	uint8_t err;
	va_list vp;
	va_start(vp,fmt);

	OSMutexPend(Print_Mutex,0,&err);
	vsnprintf(PrintfBuf,PRINT_LENGTH, fmt, vp);
	OSMutexPost(Print_Mutex);
    
	va_end(vp);
   
	return Uart_SendDatas(PrintfBuf,strlen(PrintfBuf));
}

/****************************************************************
*		void Uart_SendByte(uint8_t dat)
* 描	述 : 发送一个字节的数据 		
* 输入参数 : 无
* 返 回 值 : 无
****************************************************************/
void Uart_SendByte(uint8_t dat)
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
* 描	述 : 发送一个字符串	 		
* 输入参数 : 无
* 返 回 值 : uint8_t，错误码
****************************************************************/
uint8_t Uart_SendDatas(const char *s,uint8_t length)
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
/****************************************************************
*			void UART1_Handler(void)
* 描	述 : 串口1中断处理函数	 		
* 输入参数 : 无
* 返 回 值 : 无
****************************************************************/
extern OS_EVENT *UART1_Q_Rx;
static uint8_t   get_dat;
static uint8_t   send_dat;
static uint32_t  Uart_State;
const char end_send[2] = {'\r','\n'};
void UART1_Handler(void)
{

	uint8_t   *pRx_Buf = NULL;
	OSIntEnter();
	 
	
	Uart_State = UARTIntStatus(UART1_BASE, true);
	UARTIntClear(UART1_BASE, Uart_State);
	
	//接收中断
	if((Uart_State & UART_INT_TX) != 0)
	{
		if(CirQ_GetLength(UART1_Tx_Buf) > 0)
		{
			CirQ_Pop(UART1_Tx_Buf,&send_dat);
			UARTCharPut(UART1_BASE,send_dat);
		}
	}
	if((Uart_State & UART_INT_RX) != 0)//接收中断
	{
		
		UARTIntClear(UART1_BASE, UART_INT_RX);
		
		get_dat = UARTCharGet(UART1_BASE);
		
		if((get_dat >= 0x21) && (get_dat <= 0x7e))
		{		
			Store_Push(UART1_Rx_Buf,get_dat);
			Uart_SendByte(get_dat);
		}
		if(get_dat == '\n')
		{
			Store_Push(UART1_Rx_Buf,'\n');
			Store_Push(UART1_Rx_Buf,'\0');
			pRx_Buf = UART1_Rx_Buf->base;
			UART1_Rx_Buf->base = Mem_malloc(128);
			Store_Clear(UART1_Rx_Buf);
			Uart_SendDatas(end_send,2);
			if(OSQPost(UART1_Q_Rx,pRx_Buf) != OS_ERR_NONE)
				Mem_free(pRx_Buf);
		}
	}
	OSIntExit();
}






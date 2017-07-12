


#include "all_init.h"

#define  CAN0RXID    0x101
#define  CAN0TXID    0x100

#define CLEAE_CAN( A )   (*((volatile unsigned long  *)( (A) + 0x0008)) ) = 0
#define GET_CANERR( A )  (*((volatile unsigned long  *)( (A) + 0x0008)) )

tCANMsgObject CAN0_Rx_Message;
tCANMsgObject CAN0_Tx_Message;
	
uint8_t CAN0_Rece_data[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t CAN0_Send_data[8] = {0x03,0x11,0x44,0x33,0x66,0x55,0x88,0x77};

void CAN0_Init(void )
{
	uint8_t i = 0;

	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB );
	GPIOPinConfigure(GPIO_PB4_CAN0RX);
	GPIOPinConfigure(GPIO_PB5_CAN0TX);						 
	GPIOPinTypeCAN( GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 );	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);
	CANBitRateSet(CAN0_BASE, ROM_SysCtlClockGet(), 500000);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
	CANEnable(CAN0_BASE);
	
	CAN0_Rx_Message.ui32MsgID     = CAN0RXID;
	CAN0_Rx_Message.ui32MsgIDMask = 0xFFFFF;
	CAN0_Rx_Message.ui32Flags     = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER | MSG_OBJ_FIFO);
	CAN0_Rx_Message.ui32MsgLen    = sizeof(CAN0_Rece_data);
	for(i = 1;i < 17;i ++)
		CANMessageSet( CAN0_BASE, i, 
			&CAN0_Rx_Message, MSG_OBJ_TYPE_RX );
	
	CAN0_Tx_Message.ui32MsgID = CAN0TXID;
	CAN0_Tx_Message.ui32MsgIDMask = 0;
	CAN0_Tx_Message.ui32Flags = MSG_OBJ_FIFO;
	CAN0_Tx_Message.ui32MsgLen = sizeof(CAN0_Send_data);
	CAN0_Tx_Message.pui8MsgData = CAN0_Send_data;
	
	CANIntRegister(CAN0_BASE, CAN0_Handler);
}

int CAN0_Send_Deal( unsigned char *pSend1Buffer,
				   unsigned char send1Len ,
			       unsigned long msgID1)
{
	static unsigned char u1TxMsgObjNr = 17;
	tCANMsgObject MsgObjectTx;
	
	u1TxMsgObjNr ++;   
	if( u1TxMsgObjNr >32 )
		u1TxMsgObjNr = 17;
	
	MsgObjectTx.ui32Flags     = MSG_OBJ_FIFO;		
	MsgObjectTx.ui32MsgIDMask = 0;
	MsgObjectTx.ui32MsgID	  = msgID1;
	
	MsgObjectTx.ui32MsgLen	= send1Len;
	MsgObjectTx.pui8MsgData	= pSend1Buffer;
	
	CLEAE_CAN( CAN0_BASE );
	
	CANMessageSet( CAN0_BASE,u1TxMsgObjNr, 
						&MsgObjectTx, MSG_OBJ_TYPE_TX); 
    
	return send1Len;
}
extern OS_EVENT *CAN0_Q_Rx;
void CAN0_Handler(void)
{
	uint8_t        i = 0;
	tCANMsgObject  Rec_Buf;
    uint32_t       MsgObjID;
    uint32_t       NewData = 0;
	uint8_t        *Rx_Buffer;
	uint8_t        *Rx_Buffer1;
	
	OSIntEnter();
	
	Rx_Buffer = (uint8_t *)Mem_malloc(8);
    MsgObjID = CANIntStatus( CAN0_BASE, CAN_INT_STS_CAUSE );
	CANIntClear(CAN0_BASE, CAN_INT_INTID_STATUS );
	
	CLEAE_CAN( CAN0_BASE );
	if(MsgObjID != 0)
	{
		NewData  = CANStatusGet( CAN0_BASE, CAN_STS_NEWDAT );
		Rec_Buf.pui8MsgData = Rx_Buffer;
		if(NewData != 0)
		{
			for(i = 0;i < 32;i ++)
			{
				if(NewData & (1 << i))
				{
					CANMessageGet(CAN0_BASE,1+i,&Rec_Buf, true );
					Rx_Buffer1 = (uint8_t *)Mem_malloc(8);
					memcpy(Rx_Buffer1,Rx_Buffer,8);
					OSQPost(CAN0_Q_Rx,Rx_Buffer1);
					CANIntClear( CAN0_BASE,i + 1 );
				}
			}
		}
	}
	Mem_free(Rx_Buffer);

	OSIntExit();
}








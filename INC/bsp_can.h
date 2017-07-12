/**********************************************************************************************************
*                                          Can uC/OS II
*                          				  (c) Copyright , wh
*                                         All Rights Reserved
*										  Can.h										
* File    : bsp_can.h
* By      : wh
* Version : V1.0
* time    : 2015/12/23
***********************************************************************************************************/
#ifndef BSPCAN_H
#define BSPCAN_H

extern void CAN0_Handler (void);
extern void CAN1_Handler (void);

#define CLEAE_CAN( A )   (*((volatile unsigned long  *)( (A) + 0x0008)) ) = 0
#define GET_CANERR( A )  (*((volatile unsigned long  *)( (A) + 0x0008)) )

/*********************************************************************************************************
  ??????
*********************************************************************************************************/
typedef enum {
	CANBAUD_1M,
	CANBAUD_500K,
	CANBAUD_250K,
	CANBAUD_125K,
	CANBAUD_100k,
	CANBAUD_50k,
	CANBAUD_25k,
	CANBAUD_20k,
	CANBAUD_10k,
	CANBAUD_5k,
	CANBAUD_2k5,
}CANBAUD;

typedef enum {
	CAN_STD,			//???
	CAN_EXT,			//???
}CanMode;

typedef enum {
	Default_Status = 0,
	Ack_Status,
	Static_Status,

}can_status;

extern unsigned char can0_tx_status;
extern uint32_t speeddelaycnt;
/****************************************************                       
*				Init can0				
* Description:	
* Arguments  :   
* Returns    : 
*****************************************************/
extern void BSP_CAN_Init(void);
extern void BSP_CAN_SEND_TEST(void);
extern void Encoder_Change(void);
/****************************************************                       
*				CAN0 init_Can0				
* Description:	CAN0 ???
* Arguments  :   
* Returns    : 
*****************************************************/
void init_Can0( CANBAUD canBaud, 
			    CanMode canMod );

void init_Can1( CANBAUD canBaud, 
			    CanMode canMod );
/****************************************************                       
*				CAN0 ??????				
* Description:	ISR_CAN0Handler
* Arguments  :   
* Returns    : 
*****************************************************/
void ISR_CAN0Handler (void);
void ISR_CAN0HandlerEx (void);

/****************************************************                       
*				send_Can0Data				
* Description:	??
* Arguments  :   
* Returns    : 
*****************************************************/
int send_Can0Data( unsigned char *pSendBuffer,
				   unsigned char sendLen ,unsigned long msgID);


/****************************************************                       
*				CAN0 clear_Can0				
* Description:	CAN0 ?????
* Arguments  :   
* Returns    : 
*****************************************************/
extern void BSP_CAN_SEND_ACK(void);
extern void Can0_Function_TX_Handle(void);
extern void Can_Function_Handle(void);
/****************************************************                       
*				CAN1 init_Can1				
* Description:	CAN1 ???
* Arguments  :   
* Returns    : 
*****************************************************/
void init_Can1( CANBAUD canBaud, 
			    CanMode canMod );

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/****************************************************                       
*				ISR_CAN1Handler				
* Description:	??
* Arguments  :   
* Returns    : 
*****************************************************/
void ISR_CAN1Handler (void);
void ISR_CAN1HandlerEx (void);
/****************************************************                       
*				init_Can1				
* Description:	??
* Arguments  :   
* Returns    : 
*****************************************************/
int send_Can1Data( unsigned char *pSendBuffer,
				   unsigned char sendLen ,unsigned long msgID);

/****************************************************                       
*				CAN0 clear_Can1				
* Description:	CAN1 ?????
* Arguments  :   
* Returns    : 
*****************************************************/
void Can1_Speed_Wireless_Handle(void);
//////////////////////////////////////////////////////////////////////////
#define CLOSE_CAN0()	IntEnable(INT_CAN0)
#define OPEN_CAN0()		IntDisable(INT_CAN0)
#define CLOSE_CAN1()	IntEnable(INT_CAN1)
#define OPEN_CAN1()		IntDisable(INT_CAN1)


#endif//  BSPCAN_H

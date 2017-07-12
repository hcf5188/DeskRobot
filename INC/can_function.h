#ifndef  __CAN_FUNCTION_H__
#define  __CAN_FUNCTION_H__

#define WINDOWSPLATFORM_ID    0 //WindowsÆ½Ì¨
#define ANDROIDFLATBED_ID     1 //AndroidÆ½°å
#define CONTROLBOARD_ID       2 //¹¤¿Ø°å
#define CHASSISDRIVE_ID       4 //µ×ÅÌÇý¶¯°å
#define MOTORCONTROL_ID       5 //µç»ú¿ØÖÆ°å
#define FACERECOGNITION_ID    6 //ÒôÆµ°å
#define ARMINTERFACEBOARD_ID  7 //ÐØ²¿½Ó¿Ú°å
#define EYESLIGHTBOARD_ID     8 //ÑÛµÆ°å
#define MOUTHLIGHTBOARD_ID    9 //×ìµÆ°å

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
	CAN_STD,			
	CAN_EXT,			
}CanMode;

extern unsigned int reset_cnt;

extern void InitCAN0(void);
//extern void CAN0IntHandler(void);
//extern void CANErrorHandler(void);
extern void CAN0_Handler (void);
//extern void CANHandler(void);
extern void CAN_Hands_Bagandsend(void);
extern void CAN_Founction_Bagandsend(void);
extern void CAN_Send(void);
extern void init_Can0( CANBAUD canBaud, 
			    CanMode canMod );
extern void Can0_Read(void);
extern void Can0_SendPac(void);
extern void Can0_Function_TX_Handle(void);
extern void Can_Function_Handle(void);
extern int send_Can0Data( unsigned char *pSendBuffer,unsigned char sendLen ,unsigned long msgID);
//extern void Head_LeftOrRight_Follow_Control(void);
//extern void Head_UpOrDown_Follow_Control(void);
extern void Head_LeftOrRight_Follow_Control_Handle(void);
extern void Head_UpOrDown_Follow_Control_Handle(void);
#endif 




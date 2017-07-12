#ifndef  __CAN1_MOTOR_H__
#define  __CAN1_MOTOR_H__

#define INTERFACE   0
#define MOTORONE    1 
#define MOTORTWO    2 




#define M1_Read_S1    (ROM_GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_7) & GPIO_PIN_7)
#define M1_Read_S2    (ROM_GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_5) & GPIO_PIN_5)
#define M2_Read_S1    (ROM_GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6) & GPIO_PIN_6)
#define M2_Read_S2    (ROM_GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_4) & GPIO_PIN_4)

#define M1_Dir_Forward ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define M1_Dir_Reverse ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0)
#define M1_Disable     ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0)
#define M1_Enable      ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0)
#define M1_Pulse_High  ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define M1_Pulse_Low   ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0)

#define M2_Dir_Reverse ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6)
#define M2_Dir_Forward ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0)
#define M2_Disable     ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,GPIO_PIN_5)
#define M2_Enable      ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0)
#define M2_Pulse_High  ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define M2_Pulse_Low   ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0)


extern void InitCAN1(void);
//extern void CAN1IntHandler(void);
//extern void CAN1ErrorHandler(void);
extern void CAN1_Handler (void);
//extern void CAN1Handler(void);
extern void CAN1_Bag(void);
extern void CAN2_Bag(void);
//extern void CAN1_Send(void);
extern void BSP_CAN0_Init(void);
extern void BSP_CAN1_Init(void);
extern void Can1_Read(void);
extern void Can1_SendPac(void);
extern void Can1_Function_TX_Handle(void);
extern void Can1_Function_Handle(void);
extern int send_Can1Data( unsigned char *pSend1Buffer,
unsigned char send1Len ,unsigned long msgID1);
extern void CAN1_Hands_Bagandsend(void);
extern void CAN2_Hands_Bagandsend(void);
extern void CAN1_Founction_Bagandsend(void);
extern void CAN2_Founction_Bagandsend(void);
extern void Motor1PositionControl(unsigned int Motor1_Position_SetData);
extern void Motor2PositionControl(unsigned int Motor2_Position_SetData);
extern void Motor3PositionControl(unsigned int Motor3_Position_SetData);
#endif 




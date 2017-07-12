/*
************************************************************************************************

************************************************************************************************
*/

#ifndef __ALL_INIT_H__
#define __ALL_INIT_H__
#include "system.h"
#include "can.h"



//��Դ�����ػ�
#define POWER_ON    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define POWER_OFF   ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0)  
//��������ź�
#define AIN1_HIGH   ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define AIN1_LOW    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0) 
#define AIN2_HIGH   ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define AIN2_LOW    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0)
#define BIN1_HIGH   ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define BIN1_LOW    ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0)
#define BIN2_HIGH   ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define BIN2_LOW    ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0)
//�ĸ�������LED
#define LED1_OFF    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define LED1_ON     ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1, 0)
#define LED2_OFF    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define LED2_ON     ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0)
#define LED3_OFF    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define LED3_ON     ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0)
#define LED4_OFF    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define LED4_ON     ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0)
//��ɫLED
#define LED_R_ON    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_6)
#define LED_R_OFF     ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0)
#define LED_G_ON    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define LED_G_OFF     ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0)
#define LED_B_ON    ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define LED_B_OFF     ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0)


//��������
#define KEY1    (ROM_GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3) & GPIO_PIN_3)
#define KEY2    (ROM_GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_2) & GPIO_PIN_2)
#define KEY3    (ROM_GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_1) & GPIO_PIN_1)
#define KEY4    (ROM_GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0) & GPIO_PIN_0)
//ͷ����λ����
#define SW_LEFT    (ROM_GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_2) & GPIO_PIN_2)  //ͷ������λ
#define SW_RIGHT   (ROM_GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_3) & GPIO_PIN_3)  //ͷ������λ
//��������
#define ON_BT_HIGH   ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define ON_BT_LOW    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0, 0) 
#define OFF_BT_HIGH  ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define OFF_BT_LOW   ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0) 

void CPUCLK_Init(void);           //ϵͳʱ�ӳ�ʼ��
void SYSTICK_Init(void);          //uCOSʱ�ӵδ��ʼ��
void TIMER_Init(void);	          //���ڽ��ճ�ʱ��ʱ����ʼ��
void GPIO_Init(void);             //GPIO��ʼ��
void GLO_VAR_Init(void);          //ȫ�ֱ�����ʼ��

void MortorTimerInit(void );      //������巢����  ��ʱ����ʼ��


void UART1_Init(void);             //���ڳ�ʼ��115200
uint8_t UART1SendDatas(const uint8_t *s,uint8_t length);//�����ַ���
//uint8_t Robot_printf(char* fmt, ...);
void UART1SendByte(uint8_t dat);   //���͵����ֽ�

//void UART3_Init(void);

void I2C1_init(void);

#define FL3731_ADDR    0xEE

bool I2C0_Byte_Write(uint8_t addr,uint8_t ucAddr,uint8_t data);
bool I2C3_Byte_Write(uint8_t addr,uint8_t ucAddr,uint8_t data);
void EyeInit(void);

void ALL_Init(void);


#endif
































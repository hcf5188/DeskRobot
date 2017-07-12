#ifndef __ALL_DEAL_API_H__
#define __ALL_DEAL_API_H__

#include "all_init.h"
#include "system.h"


//�����۵ư� SDB
#define SDB_L_HIGH    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define SDB_L_LOW     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0)
#define SDB_R_HIGH    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define SDB_R_LOW     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0)




extern const uint8_t ledIndex[125];//�����۵ư�����
extern const uint8_t right_Eyes[125];
extern uint8_t ledRightBuffer[168];//�ҵư���ʾ������
extern uint8_t ledLeftBuffer [168];//��ư���ʾ������



void KeyDeal(void);//����LED���Գ���
void EyeControl(uint8_t *ptr,INT8U err,uint16_t *tim);//�۾������������
void ThreeLedDeal(uint8_t *ptr,INT8U err);   //��ɫLED��������

uint8_t CheckOut(uint8_t *p);//�Խ��ܵ����ݰ��������У��
bool BufferInCheck(uint8_t *p);//��Ҫ���͵����ݽ�����򣬲��������������һ���ֽ�

void DistanceMeasure(void);//������

void MotorControl(uint8_t *p,uint8_t err); //�������
void TIMER0A_Handler(void);
#endif



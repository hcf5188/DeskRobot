#ifndef __ALL_DEAL_API_H__
#define __ALL_DEAL_API_H__

#include "all_init.h"
#include "system.h"


//左右眼灯板 SDB
#define SDB_L_HIGH    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define SDB_L_LOW     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0)
#define SDB_R_HIGH    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, GPIO_PIN_5)
#define SDB_R_LOW     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, 0)




extern const uint8_t ledIndex[125];//左右眼灯板索引
extern const uint8_t right_Eyes[125];
extern uint8_t ledRightBuffer[168];//右灯板显示缓冲区
extern uint8_t ledLeftBuffer [168];//左灯板显示缓冲区



void KeyDeal(void);//按键LED测试程序
void EyeControl(uint8_t *ptr,INT8U err,uint16_t *tim);//眼睛表情控制中心
void ThreeLedDeal(uint8_t *ptr,INT8U err);   //三色LED控制中心

uint8_t CheckOut(uint8_t *p);//对接受的数据包进行异或校验
bool BufferInCheck(uint8_t *p);//对要发送的数据进行异或，并将结果填充至最后一个字节

void DistanceMeasure(void);//激光测距

void MotorControl(uint8_t *p,uint8_t err); //电机控制
void TIMER0A_Handler(void);
#endif



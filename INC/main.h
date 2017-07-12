#include <stdint.h>
#include <stdbool.h>
#include "hw_ints.h"
#include "hw_memmap.h"
#include "debug.h"
#include "fpu.h"
#include "gpio.h"
#include "interrupt.h"
#include "pin_map.h"
#include "rom.h"
#include "sysctl.h"
#include "uart.h"
#include "ssi.h"
#include "adc.h"
#include "uartstdio.h"
#include "SYSTEM.h"
//#include "SCI.h"
#include "nvSRAM.h"

void systemInit(void);
void singal_adc_ini(void);
void BatSocCacu(void);     // Bat soc
void gpio_ini(void);
void variable_Init(void);
void SysTickIntHandler(void);
void SaveEEProm(void);
void SysTick500us(void);
void SpdCtrl(void);
void BalCtrl(void);
void LoadDectCtrl(void);
void BitProcess(void);
void BitProcess1(void);
void BitProcess2(void);
void TickProcess(void);
void motorbaseadj(void);
void uart1_init(void);
void Uart4_init(void);
void Uart4_Recv(void);
void Uart4_CRC_Bag(void);
void Uart4_Bag(void);
void Uart4_Send(void);
void Uart4_Handle(void);

extern unsigned int BCCCheck(unsigned int length,unsigned int *param);
extern void EraseNVSRAM(void );
extern void READErrorAddress(unsigned int addr1, unsigned int addr2, unsigned int addr3,unsigned int tot_cnt, unsigned int *readDataArr );
extern void ReadFaultCode(void);
extern void ReadFaultRTC(void);
extern void ReadRTC(void);
extern void ReadSerialNumber(void);
extern void Sci4RxdProcess(void);
extern void SCISendDataBag(unsigned int txd_length,unsigned int *txd_param);
extern void WRITEErrorAddress(unsigned int addr1, unsigned int addr2, unsigned int addr3,unsigned int tot_cnt, unsigned int *data );/*******************nvSRAM ???????????********************/
extern void WriteRTC(void);
extern void WriteSerialNumber(void);
extern void StartRecorder(void); 
extern void SaveRecorderData(void);
extern void RTREADRTC (unsigned int RtcAddr,unsigned int StartNumber); 

#define LED_HI  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define LED_LO  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0) // PF2

#define PF3_HI  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define PF3_LO  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0) // PF3

//#define CS_HI   GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3)
//#define CS_LO   GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0) // PA3

#define NV_HI   GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_6, GPIO_PIN_6)
#define NV_LO   GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_6, 0) // PH6

#define MC_HI   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define MC_LO   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0)// PB2

#define INSU_HI   GPIOPinWrite(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define INSU_LO   GPIOPinWrite(GPIO_PORTJ_BASE, GPIO_PIN_0, 0)// PJ0



//#define SOC_INPUT  (HWREGB(GPIO_PORTF_BASE+GPIO_O_DATA) & GPIO_PIN_4) 


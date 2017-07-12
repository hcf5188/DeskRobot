#ifndef __SYSTEM_H__
#define __SYSTEM_H__
/****************************************************************************
                             head file
****************************************************************************/
#include <cstdlib>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <hw_memmap.h>
#include <debug.h>
#include <gpio.h>
#include <rom.h>
#include <sysctl.h>
#include <hw_flash.h>
#include <hw_ints.h>
#include <hw_sysctl.h>
#include <hw_types.h>
#include <hw_uart.h>
#include <hw_adc.h>
#include <hw_can.h>
#include <interrupt.h>
#include <eeprom.h>
#include <hw_eeprom.h>
#include <hw_gpio.h>
#include <hw_nvic.h>
#include <hw_i2c.h>
#include <hw_timer.h>
#include <i2c.h>
#include <can.h>
#include <interrupt.h>
#include <D:\TI\TivaWare_C_Series-2.1.0.12573\driverlib\cpu.h>
#include <timer.h>
#include <uart.h>
#include <pin_map.h>
#include <includes.h>
#include <systick.h>
#include <pwm.h>
#include <hw_pwm.h>
#include <adc.h>

#include "app_task.h"
#include "all_init.h"
#include "mem_api.h"
#include "all_deal_api.h"

/****************************************************************************
                            macro definition
****************************************************************************/

#ifdef MAINC
#define EXTN
#else 
#define EXTN extern 
#endif

#define DUBUG
//#define SUPERSONIN
//#define WIFI
//#define Simulate_IIC
//#define LEFTANDRIGHT
//#define UPANDDOWN
//typedef enum _BOOL { FALSE = 0, TRUE } BOOL;

typedef enum {IDLE,PRESS,RELEASE}KEYSTATES;


typedef union
{
	uint16_t word;
	uint8_t  byte[2];
}UintToUchar;

typedef union
{
	int16_t word;
	int8_t  byte[2];
}intToUchar;

typedef union
{
	uint32_t word;
    uint16_t byte16[2];
	uint8_t  byte[4];
}UlongToUchar;

typedef union
{
	int32_t word;
    int16_t byte16[2];
	uint8_t byte[4];
}longToUchar;
//定义故障状态位
typedef struct
{
	uint8_t Begin;        //存储头字节
	uint8_t Data[8];      //存储数据
	uint8_t CRC;          //存储校验值
}RECV_STRU;

typedef struct
{
	uint8_t Begin;		  //发送头字节
	uint8_t Data[8];      //发送数据包
	uint8_t CRC;		  //发送字节校验位 
}SEND_STRU;

typedef struct
{
	uint8_t Begin;     
	uint8_t Address;   
	uint8_t Cmd;
	uint8_t Length[2];
	uint8_t Data[6]; 
	uint8_t CRC;       
}RECV_ARMCORTEXM4_STRU;

typedef struct
{
	uint8_t Begin;
    uint8_t Address;
	uint8_t Cmd;
	uint8_t Length[2];
	uint8_t Data[6];   
	uint8_t CRC;		
}SENT_ARMCORTEXM4_STRU;

#pragma anon_unions
typedef union
{
	unsigned char byte;
	struct
	{
		unsigned CarType:3;      
		unsigned CarColour:3;  
		unsigned CarVersions:2;  
	};
}PARAMETER;


typedef union
{
	unsigned char byte;
	struct
	{
		unsigned LangeType:4; // 语言类型    
		unsigned VoiceType:4; // 语音类型 
	};
}CAR_VOICE;


#pragma anon_unions

typedef union tagFLAGBITS{
	uint16_t word[4];
	struct
	{
			unsigned fg0:1;
			unsigned fg1:1;
			unsigned fg2:1;
			unsigned fg3:1;
			unsigned fg4:1;
			unsigned fg5:1;
			unsigned fg6:1;
			unsigned fg7:1;
			unsigned fg8:1;
			unsigned fg9:1;
			unsigned fg10:1;
			unsigned fg11:1;
			unsigned fg12:1;
			unsigned fg13:1;
			unsigned fg14:1;
			unsigned fg15:1;
			unsigned fg16:1;
			unsigned fg17:1;
			unsigned fg18:1;
			unsigned fg19:1;
			unsigned fg20:1;
			unsigned fg21:1;
			unsigned fg22:1;
			unsigned fg23:1;
			unsigned fg24:1;
			unsigned fg25:1;
			unsigned fg26:1;
			unsigned fg27:1;
			unsigned fg28:1;
			unsigned fg29:1;
			unsigned fg30:1;
			unsigned fg31:1;
			unsigned fg32:1;
			unsigned fg33:1;
			unsigned fg34:1;
			unsigned fg35:1;
			unsigned fg36:1;
			unsigned fg37:1;
			unsigned fg38:1;
			unsigned fg39:1;
			unsigned fg40:1;
			unsigned fg41:1;
			unsigned fg42:1;
			unsigned fg43:1;
			unsigned fg44:1;
			unsigned fg45:1;
			unsigned fg46:1;
			unsigned fg47:1;
			unsigned fg48:1;
			unsigned fg49:1;
			unsigned fg50:1;
			unsigned fg51:1;
			unsigned fg52:1;
			unsigned fg53:1;
			unsigned fg54:1;
			unsigned fg55:1;
			unsigned fg56:1;
			unsigned fg57:1;
			unsigned fg58:1;
			unsigned fg59:1;
			unsigned fg60:1;
			unsigned fg61:1;
			unsigned fg62:1;
			unsigned fg63:1;
  };
}FLAGBITS;

EXTN FLAGBITS Flagbits;

#define LED_FANZHUAN       Flagbits.fg0  //LED 反转标志

#define no_use01           Flagbits.fg1  //  
#define no_use02           Flagbits.fg2  //  
#define no_use03           Flagbits.fg3  //  
#define no_use04           Flagbits.fg4  //
#define no_use05           Flagbits.fg5	 //
#define no_use06           Flagbits.fg6  //
#define no_use07           Flagbits.fg7  //
#define no_use08           Flagbits.fg8  //
#define no_use09           Flagbits.fg9  //
#define no_use10           Flagbits.fg10 //
#define no_use11           Flagbits.fg11 //	
#define no_use12           Flagbits.fg12 //
#define no_use13           Flagbits.fg13 //
#define no_use14           Flagbits.fg14 //
#define no_use15           Flagbits.fg15 //
#define no_use16           Flagbits.fg16 //
#define no_use17           Flagbits.fg17 //
#define no_use18           Flagbits.fg18 //
#define no_use19           Flagbits.fg19 //
#define no_use20           Flagbits.fg20 //
#define no_use21           Flagbits.fg21
#define no_use22           Flagbits.fg22
#define no_use23           Flagbits.fg23
#define no_use24           Flagbits.fg24
#define no_use25           Flagbits.fg25
#define no_use26           Flagbits.fg26
#define no_use27           Flagbits.fg27
#define no_use28           Flagbits.fg28
#define no_use29           Flagbits.fg29
#define no_use30           Flagbits.fg30
#define no_use31           Flagbits.fg31
#define no_use32           Flagbits.fg32
#define no_use33           Flagbits.fg33
#define no_use34           Flagbits.fg34
#define no_use35           Flagbits.fg35
#define no_use36           Flagbits.fg36
#define no_use37           Flagbits.fg37
#define no_use38           Flagbits.fg38
#define no_use39           Flagbits.fg39
#define no_use40           Flagbits.fg40
#define no_use41           Flagbits.fg41
#define no_use42           Flagbits.fg42
#define no_use43           Flagbits.fg43
#define no_use44           Flagbits.fg44
#define no_use45           Flagbits.fg45
#define no_use46           Flagbits.fg46
#define no_use47           Flagbits.fg47
#define no_use48           Flagbits.fg48
#define no_use49           Flagbits.fg49
#define no_use50           Flagbits.fg50
#define no_use51           Flagbits.fg51
#define no_use52           Flagbits.fg52
#define no_use53	       Flagbits.fg53
#define no_use54	       Flagbits.fg54
#define no_use55	       Flagbits.fg55
#define no_use56           Flagbits.fg56
#define no_use57           Flagbits.fg57
#define no_use58           Flagbits.fg58
#define no_use59           Flagbits.fg59
#define no_use60           Flagbits.fg60




#define SOFT_VERSION   10
#define HARD_VERSION   10

/****************************************************************************
                               variable
****************************************************************************/


#ifdef DUBUG

#endif


/************     系统全局变量      **********************/

EXTN  UintToUchar Given_Fre1 ;  //电机 1 给定频率


#endif


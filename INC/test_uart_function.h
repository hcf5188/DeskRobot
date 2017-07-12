#ifndef __TEST_UART_FUNCTION_H__
#define __TEST_UART_FUNCTION_H__

extern void UART0_init(void);
extern void UART0Read(void);
extern void UART0_Send(void);
extern void UART0SendPack(void);
extern void UART0_Handle(void);
extern void UART0SendPack2(void);
extern void UART0_Send2(void);

extern void TDRUART0_Send(void);
extern void TDRUART0SendPack(void);
extern void RealTimeUART0SendPack(void);
extern void Uart_Data_InBoot(unsigned char data,bool enable);
extern void Boot_handle(void);
extern void UART0_boot_Send(void);
extern void UART0BootPack(void); 


#define UART0_Idle     0			
#define UART0_Data_Rcv 1			
#define UART0_CRC      2	

#define UART0_BOOT_LenH     3
#define UART0_BOOT_LenL     4
#define UART0_BOOT_Data     5			
#define UART0_BOOT_CRC      6	
#define UART0_BOOT_Begin    7	
#define UART0_BOOT_Add      8
#define UART0_BOOT_Cmd      9

#define COM_RESET     0x15
#define COM_START     0x1a
#define COM_TRAS      0x1b
#define COM_END       0x1c
//参数调整命令
#define PARAM_ADI_COFFTA        0x01
#define PARAM_ADI_COFFTR        0x02
#define PARAM_ADI_COFFTV        0x03
#define PARAM_ADI_COFFTY        0x04
#define PARAM_ADI_COFFTT        0x05
//上位机界面命令
#define CAR_REAL_TIME_DATA      0x0A
#define PARAM_INIT              0x66
#define SENSOR_DEMA             0x61
#define TURN_DEMA               0x62
#define BLANCE_TEST             0x63
#define DEL_ERROR               0x64
#define CAR_INF_READ            0x70
#define CAR_INF_WRITE           0x71
#define CAR_STOP_CMD            0x7F
#define CAR_STATUS_READ         0x39
#define CAR_HISTORICAL1_DATA    0x35
#define CAR_HISTORICAL2_DATA    0x36
#define CAR_HISTORICAL3_DATA    0x37
#define CAR_HISTORICAL4_DATA    0x38

//行车记录仪命令
#define SET_CAR_CLOCK           0x30
#define SET_CAR_PARAM           0x44
#define READ_CAR_CLOCK          0x34
#define READ_CAR_PARAM          0x45
#define READ_ERROR_CODE         0x46
#define READ_ERROR_NUM          0x47

#define REMOTO_CTRL_MODE        0x69

#define SENSOR_DATA_READ        0xF0
#define TEST1_DATA_READ         0xF1
#define TEST2_DATA_READ         0xF2
#define TEST3_DATA_READ         0xF3
#define TEST4_DATA_READ         0xF4
#define TEST5_DATA_READ         0xF5
#define MOTLOADMODE             0xFB
#define MOTSPEEDMODE            0xFC
#define SUPERSONICWAVEMODE      0xFD

#define SENSOR_TEMP_DEMA        0xC5
#define SENSOR_TEMP_DATA_READ   0xC6
#define CLEAR_EEPROM            0xC7

extern uint8_t UART0RXPhase;
extern uint8_t UartTransfer;
extern void Read_SPIFlashSave_Total(uint8_t* pBuffer,uint8_t Index1);
void Boot_transfer(void);
//extern SEND_STRU3 SendBuf70 ;
#endif


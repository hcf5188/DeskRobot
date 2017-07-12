#include "all_deal_api.h"

#define D_TIME1    1000
#define D_TIME2    500
#define SCL_L_HIGH    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define SCL_L_LOW     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0)
#define SDA_L_HIGH    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define SDA_L_LOW     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0)
#define SDA_L_OUT     ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1)
#define SDA_L_IN      ROM_GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1)
#define SDA_L_READ    (ROM_GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_1) & GPIO_PIN_1)

void LedRightInit(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);//×óÑÛµÆ°åSCL
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);//×óÑÛµÆ°åSDA
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_4);//×óÑÛµÆ°åSDB_L
	
	SDB_L_HIGH;
	SDB_R_HIGH;//À­¸ßSDB
	SDB_L_HIGH;//À­¸ßSDB
}
static void RightDelay(long z)
{
	while(z--);
}
static void I2CStart(void)
{
	SDA_L_OUT;
	
	SDA_L_HIGH;
	SCL_L_HIGH;
	RightDelay(D_TIME1);
	SDA_L_LOW;
	RightDelay(D_TIME2);
	SCL_L_LOW;
}
static void I2CStop(void)
{
	SDA_L_OUT;
	
	SDA_L_LOW;
	SCL_L_LOW;
	RightDelay(D_TIME1);
	SCL_L_HIGH;
	RightDelay(D_TIME1);
	SDA_L_HIGH;
	RightDelay(D_TIME1);
}
static char TestAck(void)
{
	unsigned char ackFlag = 0;
	SCL_L_LOW;
	SDA_L_HIGH;
	SDA_L_IN;
	RightDelay(D_TIME2);
	SCL_L_HIGH;
	RightDelay(D_TIME2);
	if(SDA_L_READ == 0)
	{
		ackFlag = 0;
	}
	else
	{
		ackFlag = 1;
	}
	SCL_L_LOW;
	SDA_L_OUT;
	
	return ackFlag;
}
static void SendData(uint8_t dat)
{
	uint8_t count;
	for(count = 0;count<8;count++)
	{
		SCL_L_LOW;
		RightDelay(D_TIME2);
		if((dat&0x80)==0)
			SDA_L_LOW;
		else
			SDA_L_HIGH;
		SCL_L_HIGH;
		RightDelay(D_TIME2);
		dat = dat<<1;
	}
	SCL_L_LOW;
}
uint8_t RightSend(uint8_t addr,uint8_t cmd,uint8_t dat)
{
//	addr = addr >> 1;
	I2CStart();
	SendData(addr);
	if(TestAck()==1)
	{
		I2CStop();
		return 1;
	}
	SendData(cmd);
	if(TestAck()==1)
	{
		I2CStop();
		return 1;
	}
	SendData(dat);
	if(TestAck()==1)
	{
		I2CStop();
		return 1;
	}
	I2CStop();
	return 0;
}








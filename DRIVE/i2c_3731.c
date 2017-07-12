
#include "all_init.h"

//左眼灯板I2C驱动初始化
void I2C0_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    HWREG(I2C0_BASE + I2C_O_MCR) |= 0x010;
    I2CMasterInitExpClk(I2C0_BASE, ROM_SysCtlClockGet(), true);
	
	SDB_L_HIGH;//拉高SDB
}
//右眼灯板I2C驱动初始化
void I2C3_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    HWREG(I2C3_BASE + I2C_O_MCR) |= 0x010;
    I2CMasterInitExpClk(I2C3_BASE, ROM_SysCtlClockGet(), true);
	
	SDB_R_HIGH;//拉高SDB
	SDB_L_HIGH;//拉高SDB
}
bool WaitI2C0Finished(void )
{
	uint32_t wait_count = 0xffffff;
	while(I2CMasterBusy(I2C0_BASE)) 
	{
		if(wait_count == 0)
			return false;
		else wait_count--;    
	}  
	return true;
}
bool WaitI2C3Finished(void )
{
	uint32_t wait_count = 0xffffff;
	while(I2CMasterBusy(I2C3_BASE)) 
	{
		if(wait_count == 0)
			return false;
		else wait_count--;    
	}  
	return true;
}
bool I2C0_Byte_Write(uint8_t addr,uint8_t ucAddr,uint8_t data)
{
	addr = addr >> 1;
	I2CMasterSlaveAddrSet(I2C0_BASE,addr,false);//写入从机
	I2CMasterDataPut(I2C0_BASE,ucAddr);
	I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_BURST_SEND_START);
	if(!WaitI2C0Finished())
	{
		return(false);
	}   
	I2CMasterDataPut(I2C0_BASE, data);                            
	I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
	if(!WaitI2C0Finished())
	{
		return(false);
	}   
	return(true);
}
bool I2C3_Byte_Write(uint8_t addr,uint8_t ucAddr,uint8_t data)
{
	addr = addr >> 1;
	I2CMasterSlaveAddrSet(I2C3_BASE,addr,false);//写入从机
	I2CMasterDataPut(I2C3_BASE,ucAddr);
	I2CMasterControl(I2C3_BASE,I2C_MASTER_CMD_BURST_SEND_START);
	if(!WaitI2C3Finished())
	{
		return(false);
	}     
	I2CMasterDataPut(I2C3_BASE, data);                            
	I2CMasterControl(I2C3_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
	if(!WaitI2C3Finished())
	{
		return(false);
	} 
	return(true);
}
void FL3731_L_Init(void)
{
	uint8_t i;
	I2C0_Byte_Write(FL3731_ADDR,0xFD,0x0B);
	I2C0_Byte_Write(FL3731_ADDR,0x0A,0x01);
	I2C0_Byte_Write(FL3731_ADDR,0xFD,0x00);

	for(i = 0x00;i <0x12;i++)
	{
		I2C0_Byte_Write(FL3731_ADDR,i,0xFF);
	}
	for(i = 0x24;i <0xb4;i++)
	{
		I2C0_Byte_Write(FL3731_ADDR,i,0x00);
	}
}
void FL3731_R_Init(void)
{
	uint8_t i;
	//初始化配置
	I2C3_Byte_Write(FL3731_ADDR,0xFD,0x0B);
	I2C3_Byte_Write(FL3731_ADDR,0x0A,0x01);
	I2C3_Byte_Write(FL3731_ADDR,0xFD,0x00);
	//地址使能
	for(i = 0x00;i < 0x12;i++)
	{
		I2C3_Byte_Write(FL3731_ADDR,i,0xFF);
	}
	//全部灭
	for(i = 0x24;i <0xb4;i++)
	{
		I2C3_Byte_Write(FL3731_ADDR,i,0x00);
	}
	
}
//双眼灯板 初始化
void EyeInit(void)
{
	I2C3_init();
	I2C0_init();
	FL3731_L_Init();
	FL3731_R_Init();	
}









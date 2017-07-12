#include "all_init.h"



#define VL53L0X_MODEL_ID         0xc0
#define VL53L0X_REVISION_ID      0xc2
#define VL53L0X_PERIOD           0x50
#define VL53L0X_FINAL_PERIOD     0x70
#define VL53L0X_START            0x00
#define VL53L0X_INTERRUPT_STATUS 0x13
#define VL53L0X_RANGE_STATUS     0x14
#define address                  0x29




uint16_t bswap(uint8_t b[]);
uint16_t makeuint16(int lsb, int msb);
void write_byte_data(uint8_t data);
void write_byte_data_at(uint8_t reg, uint8_t data);
void write_word_data_at(uint8_t reg, uint16_t data);
uint8_t read_byte_data(void) ;
uint8_t read_byte_data_at(uint8_t reg);
uint16_t read_word_data_at(uint8_t reg);
void read_block_data_at(uint8_t reg, int sz) ;
uint16_t VL53L0X_decode_vcsel_period(short vcsel_period_reg) ;



//激光测距I2C驱动初始化
void I2C1_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);//使能I2C外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//使能PA端口
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);          //配置引脚复用
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);//配置I2C引脚
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    HWREG(I2C1_BASE + I2C_O_MCR) |= 0x010;//使能回送模式，用于调试
	//初始化并使能主机模式，使用系统时钟为I2C模块提供时钟频率，
	//主机模块传输速率为 100Kbps
    I2CMasterInitExpClk(I2C1_BASE, ROM_SysCtlClockGet(), true);
}
bool WaitI2C1Finished(void )
{
	uint32_t wait_count = 0xffffff;
	while(I2CMasterBusy(I2C1_BASE)) 
	{
		if(wait_count == 0)
			return false;
		else wait_count--;    
	}  
	return true;
}
extern OS_EVENT *distSem;
uint8_t gbuf[16];
uint16_t acnt = 0;
uint16_t scnt = 0;
uint16_t dist = 0;
uint8_t  val1 = 0;
uint8_t  DeviceRangeStatusInternal = 0;
uint8_t  val = 0;
static bool NEAE_OR_FAR = 0;//激光测距 远or近  标志
uint8_t disBuff[10] = {0xBB,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void DistanceMeasure(void) {
	static uint8_t rightCount = 0;//记录正确次数
	static uint8_t rightCount2 = 0;
	static uint8_t sendCount = 0;
	INT8U err = 0;
	val1 = read_byte_data_at(VL53L0X_REVISION_ID);

	val1 = read_byte_data_at(VL53L0X_MODEL_ID);
	val1 = read_byte_data_at(VL53L0X_PERIOD);
	val1 = read_byte_data_at(VL53L0X_FINAL_PERIOD);
	write_byte_data_at(VL53L0X_START, 0x01);
		
	val = read_byte_data_at(VL53L0X_RANGE_STATUS);
	
	read_block_data_at(0x14, 12);
	acnt = makeuint16(gbuf[7], gbuf[6]);
	scnt = makeuint16(gbuf[9], gbuf[8]);
	dist = makeuint16(gbuf[11], gbuf[10]);
	DeviceRangeStatusInternal = ((gbuf[0] & 0x78) >> 3);
	
	if((val == 94) && (dist < 860)&&(dist > 20))
	{
		rightCount2 ++;
		if(rightCount2 >=6)
			rightCount2 =6;
		if(rightCount < 10)
			rightCount++;
		if(NEAE_OR_FAR &&(rightCount2 >= 6))
		{
			rightCount = 10;
			rightCount2 = 6;
			disBuff[2] = 0x01;     //近距离标志
			disBuff[3] = dist/10;  //距离信息
			BufferInCheck(disBuff);//数据校验
			do{
				UART1SendDatas(disBuff,10);
				OSSemPend(distSem,3,&err);
				sendCount ++;
			}while((err == OS_ERR_TIMEOUT)&&(sendCount)<4);
			sendCount = 0;
			NEAE_OR_FAR = 0;
		}		
	}
	else
	{
		if(rightCount > 0)
			rightCount --;
		else rightCount = 0;
		if(rightCount2 > 0)
			rightCount2 --;
		if((!NEAE_OR_FAR) && (rightCount <= 0))
		{
			rightCount2 = 0;
			disBuff[2] = 0x00;      //近距离标志
			disBuff[3] = 150;       //距离信息
			BufferInCheck(disBuff); //数据校验
			do{
				UART1SendDatas(disBuff,10);
				OSSemPend(distSem,3,&err);
				sendCount ++;
			}while((err == OS_ERR_TIMEOUT)&&(sendCount)<4);
			sendCount = 0;
			NEAE_OR_FAR = 1;
		}		
	}	
}

uint16_t bswap(uint8_t b[]) {
  // Big Endian unsigned short to little endian unsigned short
  uint16_t val = ((b[0] << 8) & b[1]);
  return val;
}

uint16_t makeuint16(int lsb, int msb) {
    return ((msb & 0xFF) << 8) | (lsb & 0xFF);
}

void write_byte_data(uint8_t data) {
	
//  Wire.beginTransmission(address);
//  Wire.write(data);
//  Wire.endTransmission();
//	address = address >> 1;
	I2CMasterSlaveAddrSet(I2C1_BASE,address,false);//写入从机
	I2CMasterDataPut(I2C1_BASE,data);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_START);
	WaitI2C1Finished();
}

void write_byte_data_at(uint8_t reg, uint8_t data) {
//  write data word at address and register
//  Wire.beginTransmission(address);
//  Wire.write(reg);
//  Wire.write(data);
//  Wire.endTransmission();
	I2CMasterSlaveAddrSet(I2C1_BASE,address,false);//写入从机
	I2CMasterDataPut(I2C1_BASE,reg);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_START);
	WaitI2C1Finished();
	I2CMasterDataPut(I2C1_BASE,data);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
	WaitI2C1Finished();
}

void write_word_data_at(uint8_t reg, uint16_t data) {
  // write data word at address and register
  uint8_t b0 = (data &0xFF);
  uint8_t b1 = ((data >> 8) & 0xFF);
    
//  Wire.beginTransmission(address);
//  Wire.write(reg);
//  Wire.write(b0);
//  Wire.write(b1);
//  Wire.endTransmission();	
	I2CMasterSlaveAddrSet(I2C1_BASE,address,false);//写入从机
	I2CMasterDataPut(I2C1_BASE,reg);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_START);
	WaitI2C1Finished();
	I2CMasterDataPut(I2C1_BASE,b0);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_CONT);
	WaitI2C1Finished();
	I2CMasterDataPut(I2C1_BASE,b1);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);
	WaitI2C1Finished();
}

uint8_t read_byte_data() {
	uint8_t b;
	I2CMasterSlaveAddrSet(I2C1_BASE,address,true);//从测距模块中读取数据
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_SINGLE_RECEIVE);//主机单端接收
	b = I2CMasterDataGet(I2C1_BASE);
	return b;
}

uint8_t read_byte_data_at(uint8_t reg) {
//	write_byte_data((uint8_t)0x00);
//	write_byte_data(reg);
//	Wire.requestFrom(address, 1);
//	while (Wire.available() < 1) delay(1);
//	uint8_t b; = Wire.read();
	uint8_t b;
	I2CMasterSlaveAddrSet(I2C1_BASE,address,false);//写入从机
	I2CMasterDataPut(I2C1_BASE,reg);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_SINGLE_SEND);
	WaitI2C1Finished();
	I2CMasterSlaveAddrSet(I2C1_BASE,address,true);//读从机
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_SINGLE_RECEIVE);
	WaitI2C1Finished();
	b = I2CMasterDataGet(I2C1_BASE);
	
	return b;
}

uint16_t read_word_data_at(uint8_t reg) {
//	write_byte_data(reg);
//	Wire.requestFrom(address, 2);
//	while (Wire.available() < 2) 
//		delay(1);
	
	I2CMasterSlaveAddrSet(I2C1_BASE,address,false);//写入从机
	I2CMasterDataPut(I2C1_BASE,reg);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_SINGLE_SEND);
	WaitI2C1Finished();
	I2CMasterSlaveAddrSet(I2C1_BASE,address,true);//读从机
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_RECEIVE_START);
	WaitI2C1Finished();
	gbuf[0] = I2CMasterDataGet(I2C1_BASE);
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
	WaitI2C1Finished();
	gbuf[1] = I2CMasterDataGet(I2C1_BASE);
	return bswap(gbuf); 
}

void read_block_data_at(uint8_t reg, int sz) {
	int i = 0;
	I2CMasterSlaveAddrSet(I2C1_BASE,address,false);//写入从机
	I2CMasterDataPut(I2C1_BASE,reg);
	WaitI2C1Finished();
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_SINGLE_SEND);
	WaitI2C1Finished();
	I2CMasterSlaveAddrSet(I2C1_BASE,address,true);//读从机
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_RECEIVE_START);
//	write_byte_data(reg);
//	Wire.requestFrom(address, sz);
	for (i=0; i<sz-1; i++) {
		
		WaitI2C1Finished();
		I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_RECEIVE_CONT);
		gbuf[i] = I2CMasterDataGet(I2C1_BASE);
	}
	WaitI2C1Finished();
	I2CMasterControl(I2C1_BASE,I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
	gbuf[i] = I2CMasterDataGet(I2C1_BASE);
}


uint16_t VL53L0X_decode_vcsel_period(short vcsel_period_reg) {
	// Converts the encoded VCSEL period register value into the real
	// period in PLL clocks
	uint16_t vcsel_period_pclks = (vcsel_period_reg + 1) << 1;
	return vcsel_period_pclks;
}

















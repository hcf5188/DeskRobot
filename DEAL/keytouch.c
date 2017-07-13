

#include "all_deal_api.h"

static void KeyScan(void);
static void SoundDeal(void);
static void LocationDeal(void);

void KeyDeal(void)
{
	KeyScan();      //读键值
	SoundDeal();    //声音处理
	LocationDeal(); //头部位置处理
}

#define   SOUNDADD       0x01   //声音+
#define   SOUNDDEC       0x02   //声音-
#define   MOTORLEFT      0x04   //向左扭头
#define   MOTORRIGHT     0x08   //向右扭头

static uint8_t keyFlag  = 0x00;//按键标志
static uint8_t triger   = 0x00;//按下按键触发
static uint8_t cont     = 0x00;//按住不放
static uint8_t keyCountToOff = 0;//按键强制关机(音量- 连按5下，右转连按2下即可关机)

static void KeyScan(void)
{
	if(KEY1 !=0 )//声音增加按键
		keyFlag |= SOUNDADD;
	else 
		keyFlag &= (SOUNDADD^0xff);
	if(KEY2 !=0 )//声音降低按键
		keyFlag |= SOUNDDEC;
	else 
		keyFlag &= (SOUNDDEC^0xff);
	if(KEY3 !=0 )//头部左转
		keyFlag |= MOTORRIGHT;
	else 
		keyFlag &= (MOTORRIGHT^0xff);
	if(KEY4 !=0 )//头部右转
		keyFlag |= MOTORLEFT;
	else 
		keyFlag &= (MOTORLEFT^0xff);
	
	triger = keyFlag & (keyFlag ^ cont);//记录按下的触发
	cont = keyFlag;         //得到未释放的键值
	
	if(keyCountToOff >= 7)
		POWER_OFF;
}

bool SendSound(bool flag,uint8_t range);
#define   SEND_TIME       50    //长按，500ms变化一次
#define   RANGEADD       200    //长按, 2s   自增幅值
static void SoundDeal(void)
{
	static uint8_t souRange = 1;   //音量增加、减小幅值
	static uint16_t souCount = 0;  //长按计数
	//增加按键按下起始触发
	if(triger & SOUNDADD)
	{
		souRange = 1;
		souCount = 0;
		keyCountToOff = 0;
		SendSound(true,souRange);//增音量
	}//增加音量按键长按
	if(cont & SOUNDADD)
	{
		souCount++;
		if(souCount%SEND_TIME == (SEND_TIME - 1))
		{
			SendSound(true,souRange);
		}
		if(souCount%RANGEADD == (RANGEADD - 1))
		{
			souRange += 1;
			if(souRange > 5)
				souRange = 5;
		}
	}
	if(triger & SOUNDDEC)
	{
		souRange = 1;
		souCount = 0;
		SendSound(false,souRange);
		keyCountToOff ++;
		if(keyCountToOff > 5)
			keyCountToOff = 0;
	}
	if(cont & SOUNDDEC)
	{
		souCount++;
		if(souCount % SEND_TIME == (SEND_TIME - 1))
		{
			keyCountToOff = 0;
			SendSound(false,souRange);
		}
		if((souCount%RANGEADD == (RANGEADD - 1)) && (souRange < 10))
		{
			souRange += 1;
			if(souRange > 5)
				souRange = 5;
		}
	}
}
//发送语音处理包
extern OS_EVENT *soundSem; //发送音量，收到平板反馈后，通知声音处理成功
bool SendSound(bool flag,uint8_t range)//发送声音
{
	uint8_t *p;
	INT8U err = 0;
	uint8_t temp = 0;
	if((p = (uint8_t *)Mem_malloc(10)) == NULL)
		return false;
	
	*p = 0xBB;
	*(p+1) = 0x64;
	*(p+3) = range;
	if(flag)
	{
		*(p+2) = 0x01;        //音量加
		BufferInCheck(p);
	}
	else{
		*(p+2) = 0x02;        //音量减
		BufferInCheck(p);     //校验	
	}
	do{
		UART1SendDatas(p,10);
		OSSemPend(soundSem,2,&err); //等待
		temp ++;
	}while((err == OS_ERR_TIMEOUT)&&(temp)<4);
	
	if(Mem_free(p) != OS_ERR_NONE)//处理完数据包进行内存释放
	{
		while(1);//此处应有故障指示灯亮  表示内存泄露
	}
	return true;	
}//转向按键处理程序
static void SendMotor(bool direc);
#define KEY_TIME    8  //长按的发送周期

static void LocationDeal(void)
{
	static uint8_t locationCount = 0; //记录按下保持的时间

	if(triger & MOTORLEFT)   //轻按向右按键
	{
		SendMotor(false);
		locationCount = 0;	
		
		if(keyCountToOff > 4)
			keyCountToOff ++;
		else 
			keyCountToOff = 0;	
	}//向右按键长按
	if(cont & MOTORLEFT)
	{
		locationCount ++;
		if(locationCount >= KEY_TIME)
		{
			locationCount = 0;
			SendMotor(false);
		}
	}
	if(triger & MOTORRIGHT)   //轻按向左按键
	{
		SendMotor(true);
		locationCount = 0;	
		keyCountToOff = 0;
	}//向左按键长按
	if(cont & MOTORRIGHT)
	{
		locationCount ++;
		if(locationCount >= KEY_TIME - 1)
		{
			locationCount = 0;
			keyCountToOff = 0;
			SendMotor(true);
		}
	}
}
extern OS_EVENT *motor_Q;
#define STEPSGIVEN  30 //给定步数
static void SendMotor(bool direc)
{
	uint8_t *ptr = Mem_malloc(10);
		
	*ptr = 0xBB;
	*(ptr + 1) = (direc? 0x02:0x01);
	*(ptr + 2) = 0x64;
	*(ptr + 3) = STEPSGIVEN / 256;
	*(ptr + 4) = STEPSGIVEN % 256;
	OSQPost(motor_Q,ptr);
//	POWER_OFF;
//	*ptr = 0xAA;
//	*(ptr + 1) = 0x60;
//	*(ptr + 2) = 3;
//	*(ptr + 3) = 0;
//	*(ptr + 4) = 0;
//	OSQPost(motor_Q,ptr);
}


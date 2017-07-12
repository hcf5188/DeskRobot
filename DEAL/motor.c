#include "all_deal_api.h"


#define MOVERIGHT    1          //右转
#define MOVELEFT     2          //左转
#define MOVECENTER   3          //居中

#define TIMERCYCLE   100        //平板要走的定时器定时周期
#define KEY_CYCLE    100        //按键要走的定时器定时周期
#define IPADSTEPS    40         //平板一条指令的固定步数

#define TOTALSTEPS   550        //定义总的行程
#define DIRECCENTER  275        //头部居中的位置

static void ButtonTests(void);         //按键检测
static void StopMotor(void);           //停止电机运行
static void StartMotor(uint16_t tim);  //开始电机运行
static void IPadCmd(uint8_t *ptr);     //平板指令处理
static void KeyCmd(uint8_t *ptr);      //按键指令处理

static bool leftLimit  = false; //左限位记录状态  
static bool rightLimit = false; //右限位记录状态
static bool direction  = false; //电机运行方向       true-左转  false-右转
static bool isMotorRun = false; //电机是否正在运行   true-run   false-stop;


static uint8_t  cmdPrio = 0;      //指令优先级，数值越高，优先级越高
static uint16_t headLocation = 0; //当前头部所在位置  0-最左，500-最右
static uint16_t stepNum = 0;      //当前已走的步数
static uint16_t stepGiven = 0;    //给定步数


void MotorControl(uint8_t *ptr,uint8_t err)
{
	uint8_t temp1=0;
	temp1 = *ptr;
	ButtonTests();         //头部限位检测
	if(temp1 == 0xAA)
		IPadCmd(ptr);      //处理平板控制电机指令
	else if(temp1 == 0xBB)
		KeyCmd(ptr);       //处理按键控制电机指令
	
	Mem_free(ptr);         //释放数据包至空闲内存块
}

void IPadCmd(uint8_t *ptr) //平板发来的动作指令
{
	if(cmdPrio <= 4)       //平板的指令优先级为  4 
	{
		cmdPrio = 4;
		stepGiven = IPADSTEPS ;   //给定步数
		if(*(ptr + 2) == MOVERIGHT)
		{
			if(rightLimit)        //压到右限位
				*(ptr + 3) = 0x02;
			else                  //没压到限位
			{
				stepNum = direction?(7 - (stepNum % 8)):(stepNum % 8); // 此举是为了消除电机震荡现象
				
				stepGiven = IPADSTEPS + stepNum;
				direction = false;  //运行方向
				*(ptr + 3) = 0x01;  //执行成功
				if(!isMotorRun)
					StartMotor(TIMERCYCLE); //打开定时器
			}
		}
		else if(*(ptr + 2) == MOVELEFT)
		{
			if(leftLimit)//压到左限位
				*(ptr + 3) = 0x02;
			else          //没压到限位
			{
				stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
				
				stepGiven = IPADSTEPS + stepNum;
				direction = true;
				*(ptr + 3) = 0x01;              //执行成功
				if(!isMotorRun)
					StartMotor(TIMERCYCLE);     //打开定时器
			}
		}
		else if(*(ptr + 2) == MOVECENTER)       //居中指令
		{
			if(headLocation > DIRECCENTER)      //头部偏右
			{
				stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
				stepGiven = headLocation + stepNum - DIRECCENTER;
				direction = true;	
			}
			else if(headLocation < DIRECCENTER) //头部偏左
			{
				stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
				stepGiven = DIRECCENTER + stepNum - headLocation;
				direction = false;	
			}
			*(ptr + 3) = 0x01;                    //执行成功
			if(!isMotorRun)
				StartMotor(TIMERCYCLE);
		}
	}
	else{
		*(ptr + 2) = 0x00 + (direction?2:1); //当前转动状态
		*(ptr + 3) = 0x00;   //未执行
	}
	*ptr = 0xBB;             //回复帧头
	BufferInCheck(ptr);      //打包数据
	UART1SendDatas(ptr,10);  //回复平板
}
void KeyCmd(uint8_t *ptr)
{
	uint8_t temp = *(ptr + 1);
	uint16_t timerCycle = (uint16_t)*(ptr + 2); //给定频率
	stepGiven = *(ptr + 3);
	stepGiven <<=8;
	stepGiven += *(ptr + 4);          //给定步数
	switch(temp)
	{ 
		//位置信息
		case 0x00:break;
		//按键向右移动
		case MOVERIGHT:	if(cmdPrio <= 5){  //平板的指令优先级为  4 
						cmdPrio = 5;
						stepNum = direction?(7 - (stepNum % 8)):(stepNum % 8);
						
						stepGiven +=  stepNum;
						direction = false;
						stepNum = 0;      //初始步数为0 
						StartMotor(timerCycle);
					}
					break;
		//按键向左移动
		case MOVELEFT : if(cmdPrio <= 5){  //平板的指令优先级为  4 
						cmdPrio = 5;
						stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
						
						stepGiven +=  stepNum;
						direction = true;
						stepNum = 0;      //初始步数为0 
						StartMotor(timerCycle);
					}
					break;
		//其他状态信息
		default : break;
		
	}
}
void MotorMove(bool direc,uint16_t stepIndex)
{
	uint8_t temp = stepIndex%8;
	
	if(direc)//左转
	{
		switch(temp)
		{
			case 0:AIN1_HIGH;BIN1_LOW; AIN2_LOW; BIN2_LOW; break;
			case 1:AIN1_HIGH;BIN1_HIGH;AIN2_LOW; BIN2_LOW; break;
			case 2:AIN1_LOW; BIN1_HIGH;AIN2_LOW; BIN2_LOW; break;
			case 3:AIN1_LOW; BIN1_HIGH;AIN2_HIGH;BIN2_LOW; break;
			case 4:AIN1_LOW; BIN1_LOW; AIN2_HIGH;BIN2_LOW; break;
			case 5:AIN1_LOW; BIN1_LOW; AIN2_HIGH;BIN2_HIGH;break;
			case 6:AIN1_LOW; BIN1_LOW; AIN2_LOW; BIN2_HIGH;break;
			case 7:AIN1_HIGH;BIN1_LOW; AIN2_LOW; BIN2_HIGH;break;
			default:break;
		}
		if(headLocation > 0)
			headLocation --;
	}else//右转
	{
		switch(temp)
		{
			case 0:AIN1_HIGH;BIN1_LOW; AIN2_LOW; BIN2_HIGH;break;
			case 1:AIN1_LOW; BIN1_LOW; AIN2_LOW; BIN2_HIGH;break;
			case 2:AIN1_LOW; BIN1_LOW; AIN2_HIGH;BIN2_HIGH;break;
			case 3:AIN1_LOW; BIN1_LOW; AIN2_HIGH;BIN2_LOW; break;
			case 4:AIN1_LOW; BIN1_HIGH;AIN2_HIGH;BIN2_LOW; break;
			case 5:AIN1_LOW; BIN1_HIGH;AIN2_LOW; BIN2_LOW; break;
			case 6:AIN1_HIGH;BIN1_HIGH;AIN2_LOW; BIN2_LOW; break;
			case 7:AIN1_HIGH;BIN1_LOW; AIN2_LOW; BIN2_LOW; break;
			default:break;
		}
		if(headLocation < 550)
			headLocation ++;
	}
	ButtonTests();         //头部限位检测
	if(direc && leftLimit)
		StopMotor();       //关闭电机
	else if((!direc) && rightLimit)
		StopMotor();
}
//头部限位检测
static void ButtonTests(void)
{
	if(SW_LEFT == 0){      //压到左限位
		leftLimit = true;
		headLocation = 0;}
	else 
		leftLimit = false;
	
	if(SW_RIGHT == 0){     //压到右限位
		rightLimit = true;
		headLocation = TOTALSTEPS;}
	else 
		rightLimit = false;
}
static void StartMotor(uint16_t tim)      //启动电机
{
	TimerDisable(TIMER0_BASE, TIMER_A);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);	
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/tim);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);
	isMotorRun = true;
}
static void StopMotor(void)//关闭电机
{
	
	cmdPrio = 0;        //释放优先级
	isMotorRun = false;
	TimerDisable(TIMER0_BASE, TIMER_A);
	
}

void TIMER0A_Handler(void)//定时器  TIMER_0A  中断服务函数
{
	
	OSIntEnter();
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // 清标志位
	
	MotorMove(direction,stepNum);
	stepNum++;
	if(stepNum>=stepGiven)
		StopMotor();
	
	OSIntExit();
}













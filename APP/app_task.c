
#include "app_task.h"

//    任务堆栈
	   OS_STK       Start_Task_Stk[TASK_STK_SIZE];
static OS_STK		LED_Task_Stk[TASK_STK_SIZE];
static OS_STK		messageDealStk[TASK_STK_SIZE];
static OS_STK		motorControlStk[TASK_STK_SIZE];
static OS_STK		distanceStk[TASK_STK_SIZE];
static OS_STK		keyDealStk[TASK_STK_SIZE];
static OS_STK		threeLedStk[TASK_STK_SIZE];
static OS_STK       controlCenter[TASK_STK_SIZE];

//    任务声明
       void Start_Task(void *pp);
static void LED_Task(void *pp);
static void MessageCenterTask(void *pp);
static void MotorControlTask(void *pp);
static void DistanceTask(void *pp);
static void KeyDealTask(void *pp);
static void ThreeLedTask(void *pp);
static void ControlCenterTask(void *pp);  //任务控制中心(非常重要)

//    信号量指针
OS_EVENT *distSem;     //发送距离信息，正确接收的信号量
OS_EVENT *soundSem;    //发送音量，收到平板反馈后，通知声音处理成功
OS_EVENT *threeLed_Box;

OS_EVENT *UART1_Q_Rx;
OS_EVENT *motor_Q;     //发送电机控制的消息队列
OS_EVENT *led61Cmd_Q;


#define MOTOR_MESSAGES          10        //电机控制消息队列
#define UART1_RECE_MESSAGES     15        //定义串口接收消息队列长度
#define LED61CMD_MESSAGES       15        //定义眼灯板控制指令消息队列长度

void *Q_MOTOR[MOTOR_MESSAGES];            //定义电机控制帧消息指针数组
void *Q_UART1_Rece[UART1_RECE_MESSAGES];  //定义串口接收消息指针数组
void *led_Q_Cmd[LED61CMD_MESSAGES];       //定义LED眼灯板消息队列指针数组

/*******************************************************
*                       起始任务
********************************************************/
void  Start_Task (void *pp)
{
//	INT8U err;
	SYSTICK_Init();	  //系统滴答初始化
	MemBuf_Init();    //内存控制块初始化
	
	distSem    = OSSemCreate(0);    //信号量 - 距离
	soundSem   = OSSemCreate(0);    //信号量 - 声音
	
	threeLed_Box = OSMboxCreate(NULL);//
	
	motor_Q    = OSQCreate(&Q_MOTOR[0],MOTOR_MESSAGES);          //建立消息电机控制队列
	UART1_Q_Rx = OSQCreate(&Q_UART1_Rece[0],UART1_RECE_MESSAGES);//消息队列，用于串口1接收
	led61Cmd_Q = OSQCreate(led_Q_Cmd,LED61CMD_MESSAGES);         //消息队列，用于处理眼灯板控制数据包
	
	
	//  建立 任务控制中心
	OSTaskCreate((void (*)(void *))ControlCenterTask,
				 (void           *)0,
				 (OS_STK         *)&controlCenter[TASK_STK_SIZE - 1],
				 (INT8U           )CONTORLCENTER_TASK_PRIO);
	//  建立 眼灯板表情 闪烁的任务
	OSTaskCreate((void (*)(void *))LED_Task,
				 (void           *)0,
				 (OS_STK         *)&LED_Task_Stk[TASK_STK_SIZE - 1],
				 (INT8U           )LED_TASK_PRIO);
	//  建立 三色LED  闪烁的任务
	OSTaskCreate((void (*)(void *))ThreeLedTask,
				 (void           *)0,
				 (OS_STK         *)&threeLedStk[TASK_STK_SIZE - 1],
				 (INT8U           )THREELED_TASK_PRIO);
	//  建立信息处理中心任务
	OSTaskCreate((void (*)(void *))MessageCenterTask,
				 (void           *)0,
				 (OS_STK         *)&messageDealStk[TASK_STK_SIZE - 1],
				 (INT8U           )MESSAGE_TASK_PRIO);
	//  建立电机控制任务
	OSTaskCreate((void (*)(void *))MotorControlTask,
				 (void           *)0,
				 (OS_STK         *)&motorControlStk[TASK_STK_SIZE - 1],
				 (INT8U           )MOTOR_TASK_PRIO);
	//  建立激光测距任务
	OSTaskCreate((void (*)(void *))DistanceTask,
				 (void           *)0,
				 (OS_STK         *)&keyDealStk[TASK_STK_SIZE - 1],
				 (INT8U           )KEYDEAL_TASK_PRIO);
	//  建立触摸按键处理任务
	OSTaskCreate((void (*)(void *))KeyDealTask,
				 (void           *)0,
				 (OS_STK         *)&distanceStk[TASK_STK_SIZE - 1],
				 (INT8U           )DISTANCE_TASK_PRIO);
	OSTaskDel(START_TASK_PRIO); // 删除起始任务
}
/*******************************************************
*                       任务控制中心
********************************************************/
static void ControlCenterTask(void *pp)
{
	uint8_t *ptr = Mem_malloc(10);
	*ptr = 0xBB;
	*(ptr + 1) = 0x02;
	*(ptr + 2) = 0x64;
	*(ptr + 3) = 600 / 256;
	*(ptr + 4) = 600 % 256;
	OSQPost(motor_Q,ptr);
	while(1)
	{
		OSTimeDly(100);
	}
}
/*******************************************************
*                       LED眼灯板闪烁任务
********************************************************/
uint16_t tim = 0;
static void LED_Task(void *pp)
{	
	uint8_t *ptr = NULL;
	INT8U err;
	EyeInit();
	while(1)
	{
		ptr = OSQPend(led61Cmd_Q,2,&err);
		EyeControl(ptr,err,&tim);
		tim++;
	}
}
/*******************************************************
*                      三色 LED 闪烁任务
********************************************************/

static void ThreeLedTask(void *pp)
{	
	uint8_t *ptr = NULL;
	INT8U  err;
	while(1)
	{
		ptr = OSMboxPend(threeLed_Box,10,&err);
		ThreeLedDeal(ptr,err);
	}
}
/*******************************************************
*                       电机控制任务
********************************************************/
uint8_t *pMotorBuffer = NULL;    //接收电机控制帧

static void MotorControlTask(void *pp)
{	
	INT8U errMotor;
	MortorTimerInit();           //电机定时器初始化
	
	while(1)
	{
		pMotorBuffer =  OSQPend(motor_Q,0,&errMotor);
		MotorControl(pMotorBuffer,errMotor);	
	}
}/*******************************************************
*                       激光测距任务
********************************************************/

static void DistanceTask(void *pp)
{	
	I2C1_init();	
	while(1)
	{
		OSTimeDly(16);      //150ms测试一次
		DistanceMeasure();  
	}
}
/*******************************************************
*                       按键处理任务
****************************************************	****/
static void KeyDealTask(void *pp)
{	
	while(1)
	{
		OSTimeDly(2);      //10ms测试一次
		KeyDeal(); 
	}
}
/*******************************************************
*                      串口数据处理任务
********************************************************/
static uint8_t *pTxBuf = NULL;//指向邮箱内存
static uint8_t err_uart;
pCIR_QUEUE  UART1_Tx_Buf;     //发送缓冲区
pSTORE      UART1_Rx_Buf;     //接收缓冲区
static uint8_t cmdRx = 0;     //数据包指令
extern void Replay55Cmd(uint8_t *p);
static void MessageCenterTask(void *pp)// 信息处理中心
{
	
	UART1_Init();           //串口1初始化
	TIMER_Init();           //定时器超时初始化
	UART1_Rx_Buf = Store_Init(10);          //接收数据堆初始化
	UART1_Tx_Buf = Cir_Queue_Init(256);     //发送循环队列初始化
	while(1)
	{
		pTxBuf = OSQPend(UART1_Q_Rx,0,&err_uart);   //从循环队列中提取串口数据包
		if(err_uart == OS_ERR_NONE)
		{	
			cmdRx = CheckOut(pTxBuf);//校验数据，得到指令
			switch(cmdRx)
			{
				case 0x00:  break;                                   //无效数据包
				case 0x55:  Replay55Cmd(pTxBuf);break;               //上电握手指令
				case 0x60:  OSQPost(motor_Q,pTxBuf);continue;        //电机控制指令
				case 0x61:  OSQPost(led61Cmd_Q,pTxBuf);continue;;    //眼灯板控制指令
				case 0x62:  OSMboxPost(threeLed_Box,pTxBuf);continue;//三色状态灯控制指令			
				case 0x63:  if(OSSemAccept(distSem)<=0)
								OSSemPost(distSem); break;               //回复距离包，通知接收成功
				case 0x64:  if(OSSemAccept(soundSem)<=0)
								OSSemPost(soundSem);break;               //回复音量发送包，通知系统:平板接收成功
				default  :  ;break;
			}
			if(Mem_free(pTxBuf) != OS_ERR_NONE)//处理完数据包进行内存释放
			{
				//while(1);//此处应有故障指示灯亮  表示内存泄露
			}
		}
	}
}







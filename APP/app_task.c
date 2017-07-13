
#include "app_task.h"

//    �����ջ
	   OS_STK       Start_Task_Stk[TASK_STK_SIZE];
static OS_STK		LED_Task_Stk[TASK_STK_SIZE];
static OS_STK		messageDealStk[TASK_STK_SIZE];
static OS_STK		motorControlStk[TASK_STK_SIZE];
static OS_STK		distanceStk[TASK_STK_SIZE];
static OS_STK		keyDealStk[TASK_STK_SIZE];
static OS_STK		threeLedStk[TASK_STK_SIZE];
static OS_STK       controlCenter[TASK_STK_SIZE];

//    ��������
       void Start_Task(void *pp);
static void LED_Task(void *pp);
static void MessageCenterTask(void *pp);
static void MotorControlTask(void *pp);
static void DistanceTask(void *pp);
static void KeyDealTask(void *pp);
static void ThreeLedTask(void *pp);
static void ControlCenterTask(void *pp);  //�����������(�ǳ���Ҫ)

//    �ź���ָ��
OS_EVENT *distSem;     //���;�����Ϣ����ȷ���յ��ź���
OS_EVENT *soundSem;    //�����������յ�ƽ�巴����֪ͨ��������ɹ�
OS_EVENT *threeLed_Box;

OS_EVENT *UART1_Q_Rx;
OS_EVENT *motor_Q;     //���͵�����Ƶ���Ϣ����
OS_EVENT *led61Cmd_Q;


#define MOTOR_MESSAGES          10        //���������Ϣ����
#define UART1_RECE_MESSAGES     15        //���崮�ڽ�����Ϣ���г���
#define LED61CMD_MESSAGES       15        //�����۵ư����ָ����Ϣ���г���

void *Q_MOTOR[MOTOR_MESSAGES];            //����������֡��Ϣָ������
void *Q_UART1_Rece[UART1_RECE_MESSAGES];  //���崮�ڽ�����Ϣָ������
void *led_Q_Cmd[LED61CMD_MESSAGES];       //����LED�۵ư���Ϣ����ָ������

/*******************************************************
*                       ��ʼ����
********************************************************/
void  Start_Task (void *pp)
{
//	INT8U err;
	SYSTICK_Init();	  //ϵͳ�δ��ʼ��
	MemBuf_Init();    //�ڴ���ƿ��ʼ��
	
	distSem    = OSSemCreate(0);    //�ź��� - ����
	soundSem   = OSSemCreate(0);    //�ź��� - ����
	
	threeLed_Box = OSMboxCreate(NULL);//
	
	motor_Q    = OSQCreate(&Q_MOTOR[0],MOTOR_MESSAGES);          //������Ϣ������ƶ���
	UART1_Q_Rx = OSQCreate(&Q_UART1_Rece[0],UART1_RECE_MESSAGES);//��Ϣ���У����ڴ���1����
	led61Cmd_Q = OSQCreate(led_Q_Cmd,LED61CMD_MESSAGES);         //��Ϣ���У����ڴ����۵ư�������ݰ�
	
	
	//  ���� �����������
	OSTaskCreate((void (*)(void *))ControlCenterTask,
				 (void           *)0,
				 (OS_STK         *)&controlCenter[TASK_STK_SIZE - 1],
				 (INT8U           )CONTORLCENTER_TASK_PRIO);
	//  ���� �۵ư���� ��˸������
	OSTaskCreate((void (*)(void *))LED_Task,
				 (void           *)0,
				 (OS_STK         *)&LED_Task_Stk[TASK_STK_SIZE - 1],
				 (INT8U           )LED_TASK_PRIO);
	//  ���� ��ɫLED  ��˸������
	OSTaskCreate((void (*)(void *))ThreeLedTask,
				 (void           *)0,
				 (OS_STK         *)&threeLedStk[TASK_STK_SIZE - 1],
				 (INT8U           )THREELED_TASK_PRIO);
	//  ������Ϣ������������
	OSTaskCreate((void (*)(void *))MessageCenterTask,
				 (void           *)0,
				 (OS_STK         *)&messageDealStk[TASK_STK_SIZE - 1],
				 (INT8U           )MESSAGE_TASK_PRIO);
	//  ���������������
	OSTaskCreate((void (*)(void *))MotorControlTask,
				 (void           *)0,
				 (OS_STK         *)&motorControlStk[TASK_STK_SIZE - 1],
				 (INT8U           )MOTOR_TASK_PRIO);
	//  ��������������
	OSTaskCreate((void (*)(void *))DistanceTask,
				 (void           *)0,
				 (OS_STK         *)&keyDealStk[TASK_STK_SIZE - 1],
				 (INT8U           )KEYDEAL_TASK_PRIO);
	//  ��������������������
	OSTaskCreate((void (*)(void *))KeyDealTask,
				 (void           *)0,
				 (OS_STK         *)&distanceStk[TASK_STK_SIZE - 1],
				 (INT8U           )DISTANCE_TASK_PRIO);
	OSTaskDel(START_TASK_PRIO); // ɾ����ʼ����
}
/*******************************************************
*                       �����������
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
*                       LED�۵ư���˸����
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
*                      ��ɫ LED ��˸����
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
*                       �����������
********************************************************/
uint8_t *pMotorBuffer = NULL;    //���յ������֡

static void MotorControlTask(void *pp)
{	
	INT8U errMotor;
	MortorTimerInit();           //�����ʱ����ʼ��
	
	while(1)
	{
		pMotorBuffer =  OSQPend(motor_Q,0,&errMotor);
		MotorControl(pMotorBuffer,errMotor);	
	}
}/*******************************************************
*                       ����������
********************************************************/

static void DistanceTask(void *pp)
{	
	I2C1_init();	
	while(1)
	{
		OSTimeDly(16);      //150ms����һ��
		DistanceMeasure();  
	}
}
/*******************************************************
*                       ������������
****************************************************	****/
static void KeyDealTask(void *pp)
{	
	while(1)
	{
		OSTimeDly(2);      //10ms����һ��
		KeyDeal(); 
	}
}
/*******************************************************
*                      �������ݴ�������
********************************************************/
static uint8_t *pTxBuf = NULL;//ָ�������ڴ�
static uint8_t err_uart;
pCIR_QUEUE  UART1_Tx_Buf;     //���ͻ�����
pSTORE      UART1_Rx_Buf;     //���ջ�����
static uint8_t cmdRx = 0;     //���ݰ�ָ��
extern void Replay55Cmd(uint8_t *p);
static void MessageCenterTask(void *pp)// ��Ϣ��������
{
	
	UART1_Init();           //����1��ʼ��
	TIMER_Init();           //��ʱ����ʱ��ʼ��
	UART1_Rx_Buf = Store_Init(10);          //�������ݶѳ�ʼ��
	UART1_Tx_Buf = Cir_Queue_Init(256);     //����ѭ�����г�ʼ��
	while(1)
	{
		pTxBuf = OSQPend(UART1_Q_Rx,0,&err_uart);   //��ѭ����������ȡ�������ݰ�
		if(err_uart == OS_ERR_NONE)
		{	
			cmdRx = CheckOut(pTxBuf);//У�����ݣ��õ�ָ��
			switch(cmdRx)
			{
				case 0x00:  break;                                   //��Ч���ݰ�
				case 0x55:  Replay55Cmd(pTxBuf);break;               //�ϵ�����ָ��
				case 0x60:  OSQPost(motor_Q,pTxBuf);continue;        //�������ָ��
				case 0x61:  OSQPost(led61Cmd_Q,pTxBuf);continue;;    //�۵ư����ָ��
				case 0x62:  OSMboxPost(threeLed_Box,pTxBuf);continue;//��ɫ״̬�ƿ���ָ��			
				case 0x63:  if(OSSemAccept(distSem)<=0)
								OSSemPost(distSem); break;               //�ظ��������֪ͨ���ճɹ�
				case 0x64:  if(OSSemAccept(soundSem)<=0)
								OSSemPost(soundSem);break;               //�ظ��������Ͱ���֪ͨϵͳ:ƽ����ճɹ�
				default  :  ;break;
			}
			if(Mem_free(pTxBuf) != OS_ERR_NONE)//���������ݰ������ڴ��ͷ�
			{
				//while(1);//�˴�Ӧ�й���ָʾ����  ��ʾ�ڴ�й¶
			}
		}
	}
}







#include "all_deal_api.h"


#define MOVERIGHT    1          //��ת
#define MOVELEFT     2          //��ת
#define MOVECENTER   3          //����

#define TIMERCYCLE   100        //ƽ��Ҫ�ߵĶ�ʱ����ʱ����
#define KEY_CYCLE    100        //����Ҫ�ߵĶ�ʱ����ʱ����
#define IPADSTEPS    40         //ƽ��һ��ָ��Ĺ̶�����

#define TOTALSTEPS   550        //�����ܵ��г�
#define DIRECCENTER  275        //ͷ�����е�λ��

static void ButtonTests(void);         //�������
static void StopMotor(void);           //ֹͣ�������
static void StartMotor(uint16_t tim);  //��ʼ�������
static void IPadCmd(uint8_t *ptr);     //ƽ��ָ���
static void KeyCmd(uint8_t *ptr);      //����ָ���

static bool leftLimit  = false; //����λ��¼״̬  
static bool rightLimit = false; //����λ��¼״̬
static bool direction  = false; //������з���       true-��ת  false-��ת
static bool isMotorRun = false; //����Ƿ���������   true-run   false-stop;


static uint8_t  cmdPrio = 0;      //ָ�����ȼ�����ֵԽ�ߣ����ȼ�Խ��
static uint16_t headLocation = 0; //��ǰͷ������λ��  0-����500-����
static uint16_t stepNum = 0;      //��ǰ���ߵĲ���
static uint16_t stepGiven = 0;    //��������


void MotorControl(uint8_t *ptr,uint8_t err)
{
	uint8_t temp1=0;
	temp1 = *ptr;
	ButtonTests();         //ͷ����λ���
	if(temp1 == 0xAA)
		IPadCmd(ptr);      //����ƽ����Ƶ��ָ��
	else if(temp1 == 0xBB)
		KeyCmd(ptr);       //���������Ƶ��ָ��
	
	Mem_free(ptr);         //�ͷ����ݰ��������ڴ��
}

void IPadCmd(uint8_t *ptr) //ƽ�巢���Ķ���ָ��
{
	if(cmdPrio <= 4)       //ƽ���ָ�����ȼ�Ϊ  4 
	{
		cmdPrio = 4;
		stepGiven = IPADSTEPS ;   //��������
		if(*(ptr + 2) == MOVERIGHT)
		{
			if(rightLimit)        //ѹ������λ
				*(ptr + 3) = 0x02;
			else                  //ûѹ����λ
			{
				stepNum = direction?(7 - (stepNum % 8)):(stepNum % 8); // �˾���Ϊ���������������
				
				stepGiven = IPADSTEPS + stepNum;
				direction = false;  //���з���
				*(ptr + 3) = 0x01;  //ִ�гɹ�
				if(!isMotorRun)
					StartMotor(TIMERCYCLE); //�򿪶�ʱ��
			}
		}
		else if(*(ptr + 2) == MOVELEFT)
		{
			if(leftLimit)//ѹ������λ
				*(ptr + 3) = 0x02;
			else          //ûѹ����λ
			{
				stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
				
				stepGiven = IPADSTEPS + stepNum;
				direction = true;
				*(ptr + 3) = 0x01;              //ִ�гɹ�
				if(!isMotorRun)
					StartMotor(TIMERCYCLE);     //�򿪶�ʱ��
			}
		}
		else if(*(ptr + 2) == MOVECENTER)       //����ָ��
		{
			if(headLocation > DIRECCENTER)      //ͷ��ƫ��
			{
				stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
				stepGiven = headLocation + stepNum - DIRECCENTER;
				direction = true;	
			}
			else if(headLocation < DIRECCENTER) //ͷ��ƫ��
			{
				stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
				stepGiven = DIRECCENTER + stepNum - headLocation;
				direction = false;	
			}
			*(ptr + 3) = 0x01;                    //ִ�гɹ�
			if(!isMotorRun)
				StartMotor(TIMERCYCLE);
		}
	}
	else{
		*(ptr + 2) = 0x00 + (direction?2:1); //��ǰת��״̬
		*(ptr + 3) = 0x00;   //δִ��
	}
	*ptr = 0xBB;             //�ظ�֡ͷ
	BufferInCheck(ptr);      //�������
	UART1SendDatas(ptr,10);  //�ظ�ƽ��
}
void KeyCmd(uint8_t *ptr)
{
	uint8_t temp = *(ptr + 1);
	uint16_t timerCycle = (uint16_t)*(ptr + 2); //����Ƶ��
	stepGiven = *(ptr + 3);
	stepGiven <<=8;
	stepGiven += *(ptr + 4);          //��������
	switch(temp)
	{ 
		//λ����Ϣ
		case 0x00:break;
		//���������ƶ�
		case MOVERIGHT:	if(cmdPrio <= 5){  //ƽ���ָ�����ȼ�Ϊ  4 
						cmdPrio = 5;
						stepNum = direction?(7 - (stepNum % 8)):(stepNum % 8);
						
						stepGiven +=  stepNum;
						direction = false;
						stepNum = 0;      //��ʼ����Ϊ0 
						StartMotor(timerCycle);
					}
					break;
		//���������ƶ�
		case MOVELEFT : if(cmdPrio <= 5){  //ƽ���ָ�����ȼ�Ϊ  4 
						cmdPrio = 5;
						stepNum = direction?(stepNum % 8):(7 - (stepNum % 8));
						
						stepGiven +=  stepNum;
						direction = true;
						stepNum = 0;      //��ʼ����Ϊ0 
						StartMotor(timerCycle);
					}
					break;
		//����״̬��Ϣ
		default : break;
		
	}
}
void MotorMove(bool direc,uint16_t stepIndex)
{
	uint8_t temp = stepIndex%8;
	
	if(direc)//��ת
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
	}else//��ת
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
	ButtonTests();         //ͷ����λ���
	if(direc && leftLimit)
		StopMotor();       //�رյ��
	else if((!direc) && rightLimit)
		StopMotor();
}
//ͷ����λ���
static void ButtonTests(void)
{
	if(SW_LEFT == 0){      //ѹ������λ
		leftLimit = true;
		headLocation = 0;}
	else 
		leftLimit = false;
	
	if(SW_RIGHT == 0){     //ѹ������λ
		rightLimit = true;
		headLocation = TOTALSTEPS;}
	else 
		rightLimit = false;
}
static void StartMotor(uint16_t tim)      //�������
{
	TimerDisable(TIMER0_BASE, TIMER_A);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);	
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/tim);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);
	isMotorRun = true;
}
static void StopMotor(void)//�رյ��
{
	
	cmdPrio = 0;        //�ͷ����ȼ�
	isMotorRun = false;
	TimerDisable(TIMER0_BASE, TIMER_A);
	
}

void TIMER0A_Handler(void)//��ʱ��  TIMER_0A  �жϷ�����
{
	
	OSIntEnter();
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // ���־λ
	
	MotorMove(direction,stepNum);
	stepNum++;
	if(stepNum>=stepGiven)
		StopMotor();
	
	OSIntExit();
}













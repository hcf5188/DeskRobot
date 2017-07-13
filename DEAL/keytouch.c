

#include "all_deal_api.h"

static void KeyScan(void);
static void SoundDeal(void);
static void LocationDeal(void);

void KeyDeal(void)
{
	KeyScan();      //����ֵ
	SoundDeal();    //��������
	LocationDeal(); //ͷ��λ�ô���
}

#define   SOUNDADD       0x01   //����+
#define   SOUNDDEC       0x02   //����-
#define   MOTORLEFT      0x04   //����Ťͷ
#define   MOTORRIGHT     0x08   //����Ťͷ

static uint8_t keyFlag  = 0x00;//������־
static uint8_t triger   = 0x00;//���°�������
static uint8_t cont     = 0x00;//��ס����
static uint8_t keyCountToOff = 0;//����ǿ�ƹػ�(����- ����5�£���ת����2�¼��ɹػ�)

static void KeyScan(void)
{
	if(KEY1 !=0 )//�������Ӱ���
		keyFlag |= SOUNDADD;
	else 
		keyFlag &= (SOUNDADD^0xff);
	if(KEY2 !=0 )//�������Ͱ���
		keyFlag |= SOUNDDEC;
	else 
		keyFlag &= (SOUNDDEC^0xff);
	if(KEY3 !=0 )//ͷ����ת
		keyFlag |= MOTORRIGHT;
	else 
		keyFlag &= (MOTORRIGHT^0xff);
	if(KEY4 !=0 )//ͷ����ת
		keyFlag |= MOTORLEFT;
	else 
		keyFlag &= (MOTORLEFT^0xff);
	
	triger = keyFlag & (keyFlag ^ cont);//��¼���µĴ���
	cont = keyFlag;         //�õ�δ�ͷŵļ�ֵ
	
	if(keyCountToOff >= 7)
		POWER_OFF;
}

bool SendSound(bool flag,uint8_t range);
#define   SEND_TIME       50    //������500ms�仯һ��
#define   RANGEADD       200    //����, 2s   ������ֵ
static void SoundDeal(void)
{
	static uint8_t souRange = 1;   //�������ӡ���С��ֵ
	static uint16_t souCount = 0;  //��������
	//���Ӱ���������ʼ����
	if(triger & SOUNDADD)
	{
		souRange = 1;
		souCount = 0;
		keyCountToOff = 0;
		SendSound(true,souRange);//������
	}//����������������
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
//�������������
extern OS_EVENT *soundSem; //�����������յ�ƽ�巴����֪ͨ��������ɹ�
bool SendSound(bool flag,uint8_t range)//��������
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
		*(p+2) = 0x01;        //������
		BufferInCheck(p);
	}
	else{
		*(p+2) = 0x02;        //������
		BufferInCheck(p);     //У��	
	}
	do{
		UART1SendDatas(p,10);
		OSSemPend(soundSem,2,&err); //�ȴ�
		temp ++;
	}while((err == OS_ERR_TIMEOUT)&&(temp)<4);
	
	if(Mem_free(p) != OS_ERR_NONE)//���������ݰ������ڴ��ͷ�
	{
		while(1);//�˴�Ӧ�й���ָʾ����  ��ʾ�ڴ�й¶
	}
	return true;	
}//ת�򰴼��������
static void SendMotor(bool direc);
#define KEY_TIME    8  //�����ķ�������

static void LocationDeal(void)
{
	static uint8_t locationCount = 0; //��¼���±��ֵ�ʱ��

	if(triger & MOTORLEFT)   //�ᰴ���Ұ���
	{
		SendMotor(false);
		locationCount = 0;	
		
		if(keyCountToOff > 4)
			keyCountToOff ++;
		else 
			keyCountToOff = 0;	
	}//���Ұ�������
	if(cont & MOTORLEFT)
	{
		locationCount ++;
		if(locationCount >= KEY_TIME)
		{
			locationCount = 0;
			SendMotor(false);
		}
	}
	if(triger & MOTORRIGHT)   //�ᰴ���󰴼�
	{
		SendMotor(true);
		locationCount = 0;	
		keyCountToOff = 0;
	}//���󰴼�����
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
#define STEPSGIVEN  30 //��������
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


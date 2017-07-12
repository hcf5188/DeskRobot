/*******************************************************************
* 
* drv_timer.h 
* 
* 
********************************************************************/
#ifndef 	DRV_TIMER_H
#define 	DRV_TIMER_H

/******************      Ƶ�ʱ仯��ֵ         ******************/

#define   MOTOR_ONE_LIMIT11    100   //������� 1  ����Ƶ�ʱ仯��ֵ
#define   MOTOR_ONE_LIMIT12    300   //������� 1  ��ֹͣƵ�ʱ仯��ֵ

#define   MOTOR_ONE_LIMIT21     40   //������� 1  ����Ƶ�ʱ仯��ֵ
#define   MOTOR_ONE_LIMIT22     30   //ƫ����� 2  ��ֹͣƵ�ʱ仯��ֵ

/******************     ����ͣ��غ�    ************************/

#define FRE_MIN_LIMIT1   5000
#define FRE_MAX_LIMIT1   30000

#define FRE_MIN_LIMIT2   1250
#define FRE_MAX_LIMIT2   7500

#define   SOFT_FRE_START_MIN1    2000   //���1����������ʼƵ��
#define   SOFT_FRE_START_NUM1    300   //������Ƶ�ʱ仯�Ĵ���
#define   SOFT_FRE_START_TIME1   1     //������Ƶ�ʸ���ʱ��(ms)
#define   SOFT_FRE_STOP_MIN1     1000    //���1��ֹͣ�����Ƶ��
#define   SOFT_FRE_STOP_NUM1     300   //��ֹͣƵ�ʱ仯�Ĵ���
#define   SOFT_FRE_STOP_TIME1    1     //��ֹͣƵ�ʸ���ʱ��(ms)

#define   SOFT_FRE_START_MIN2    1000   //���2����������ʼƵ��
#define   SOFT_FRE_START_NUM2    300   //������Ƶ�ʱ仯�Ĵ���
#define   SOFT_FRE_START_TIME2   1     //������Ƶ�ʸ���ʱ��(ms)
#define   SOFT_FRE_STOP_MIN2     1000   //���2��ֹͣ�����Ƶ��
#define   SOFT_FRE_STOP_NUM2     300   //��ֹͣƵ�ʱ仯�Ĵ���
#define   SOFT_FRE_STOP_TIME2    1     //��ֹͣƵ�ʸ���ʱ��(ms)

/***********************      ������    *****************************/
#define   CURVEPOINT_MAX    (79)
#define   TIMER_PERIPH_STEPMOTOR1                 (SYSCTL_PERIPH_TIMER0)
#define   TIMER_BASE_STEPMOTOR1                   (TIMER0_BASE)
#define   TIMER_ITEM_STEPMOTOR1                   (TIMER_A)
#define   TIMER_CONFIG_STEPMOTOR1                 (TIMER_CFG_PERIODIC )       
#define   TIMER_PERIPH_INIT_STEPMOTOR1            (INT_TIMER0A)
#define   TIMER_STATE_INIT_STEPMOTOR1             (TIMER_TIMA_TIMEOUT)

#define   TIMER_PERIPH_STEPMOTOR2                 (SYSCTL_PERIPH_TIMER1)
#define   TIMER_BASE_STEPMOTOR2                   (TIMER1_BASE)
#define   TIMER_ITEM_STEPMOTOR2                   (TIMER_A)
#define   TIMER_CONFIG_STEPMOTOR2                 (TIMER_CFG_PERIODIC )        
#define   TIMER_PERIPH_INIT_STEPMOTOR2            (INT_TIMER1A)
#define   TIMER_STATE_INIT_STEPMOTOR2             (TIMER_TIMA_TIMEOUT)

/********************     ������г���        **********************/



#endif


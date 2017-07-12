/*******************************************************************
* 
* drv_timer.h 
* 
* 
********************************************************************/
#ifndef 	DRV_TIMER_H
#define 	DRV_TIMER_H

/******************      频率变化幅值         ******************/

#define   MOTOR_ONE_LIMIT11    100   //腰部电机 1  软起动频率变化幅值
#define   MOTOR_ONE_LIMIT12    300   //腰部电机 1  软停止频率变化幅值

#define   MOTOR_ONE_LIMIT21     40   //腰部电机 1  软起动频率变化幅值
#define   MOTOR_ONE_LIMIT22     30   //偏航电机 2  软停止频率变化幅值

/******************     软启停相关宏    ************************/

#define FRE_MIN_LIMIT1   5000
#define FRE_MAX_LIMIT1   30000

#define FRE_MIN_LIMIT2   1250
#define FRE_MAX_LIMIT2   7500

#define   SOFT_FRE_START_MIN1    2000   //电机1软启动的起始频率
#define   SOFT_FRE_START_NUM1    300   //软启动频率变化的次数
#define   SOFT_FRE_START_TIME1   1     //软启动频率更替时间(ms)
#define   SOFT_FRE_STOP_MIN1     1000    //电机1软停止的最后频率
#define   SOFT_FRE_STOP_NUM1     300   //软停止频率变化的次数
#define   SOFT_FRE_STOP_TIME1    1     //软停止频率更替时间(ms)

#define   SOFT_FRE_START_MIN2    1000   //电机2软启动的起始频率
#define   SOFT_FRE_START_NUM2    300   //软启动频率变化的次数
#define   SOFT_FRE_START_TIME2   1     //软启动频率更替时间(ms)
#define   SOFT_FRE_STOP_MIN2     1000   //电机2软停止的最后频率
#define   SOFT_FRE_STOP_NUM2     300   //软停止频率变化的次数
#define   SOFT_FRE_STOP_TIME2    1     //软停止频率更替时间(ms)

/***********************      宏配置    *****************************/
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

/********************     电机运行程序        **********************/



#endif


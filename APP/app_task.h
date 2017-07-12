
#ifndef __APP_TASK_H__
#define __APP_TASK_H__


#include  "app_cfg.h"
#include  <cpu_core.h>
#include  <os.h>

#include  "lib_str.h"
#include  "system.h"
/**********************************************************
*                      �����ջ��С      
**********************************************************/
#define TASK_STK_SIZE               64u

/**********************************************************
*                 �������ź������ȼ�       
**********************************************************/


/**********************************************************
*                      �������ȼ�       
**********************************************************/


#define MESSAGE_TASK_PRIO			11u  //
#define CONTORLCENTER_TASK_PRIO		12u
#define THREELED_TASK_PRIO          13u
#define MOTOR_TASK_PRIO             14u
#define DISTANCE_TASK_PRIO          15u
#define KEYDEAL_TASK_PRIO           16u
#define LED_TASK_PRIO				25u
#define START_TASK_PRIO             30u

/**********************************************************
*                       ��������
***********************************************************/
void Start_Task(void *p_arg);




#endif





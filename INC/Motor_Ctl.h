//**********************************************************************************/
//**** Filename: Motor_Ctl.h                           *****************************/
//**** Company : Shanghai New Century Robot Co.,LTD    *****************************/
//**** Auther  : wmi                                   *****************************/
//**** Date    : 2014.5.30                             *****************************/
//**********************************************************************************/
    #include "system.h"
		
extern  void  ADC0_Sample(void);
extern  void  VelCal_1(void);
extern  void  Motor1_Vector_CTL(void);
extern  void  ADC1_Sample(void);
extern  void  VelCal_2(void);
extern  void  Motor2_Vector_CTL(void);
extern  void  ADC0_Det(void);
extern  void  ADC1_Det(void);
extern  void  Cont_Det1(void); 
extern  void  Cont_Det2(void); 
extern  void  MotorVelCtl2(void);
extern  void  MotorVelCtl1(void);
extern  int16_t abs(int16_t x);

  //Globle Variable Define
	
//extern   int16_t  Sint16_theta;								
//extern   int16_t   CosTheta;									
extern   int16_t   KP_IQ,KP_ID;
extern   int16_t   KI_IQ,KI_ID;
extern   int16_t   VPCOF,VICOF;
extern   int16_t   pre_angle;
extern   uint16_t Theta;
extern   int16_t  eTheta;
//extern   int16_t ATAN[8192];
//extern   int16_t  SinTable[1024];
//extern   int16_t  sin_table[512];
extern   int16_t   i_v,i_w;

//extern  uint32_t  ADCB_Value[4],ADCA_Value[4];
		
//Motor1 Variables  
extern int32_t 	XiidA , XiiqA;			// 积分调节器输出误差累积		
extern int16_t  VdRefA,VqRefA;
extern int16_t MtMotTheaCorA;
extern int16_t IvBaseA,IwBaseA;
//extern uint16_t Theta_olda;
extern int16_t speedA_step;
extern int16_t speedA_old;
extern int16_t OldErrorIdA;
extern int16_t OldErrorIqA;
extern int16_t M1ActuSpeed;
extern int16_t FirstA;
extern int16_t FaultA;
extern uint16_t Theta_oldA;
extern int16_t  speed_oldA;
extern int16_t  iq_ref;
extern int16_t   UV1,VV1,WV1;
extern int16_t   UV2,VV2,WV2;
extern int16_t   H1zero,H2zero;
extern int16_t   theab,theac;
extern int16_t   M1_iq;
extern int16_t   thea1_b,thea1_c;

extern int16_t	Hall1_err;             // 2012.2.18
extern int16_t	Curr1_err ;
extern int16_t	Fault_Inv1;
extern int32_t  VSCALEA;
extern int32_t  VINTGA;
extern int16_t  Vel_refA;
extern int16_t   IREFA, IRFE_oldA;
	
//Motor2 Variables  		
		
extern int32_t	XiidB, XiiqB ;			// 积分调节器输出误差累积		
extern int16_t  VdRefB,VqRefB;
extern int16_t MtMotTheaCorB;
extern int16_t IvBaseB,IwBaseB;
//extern uint16_t Theta_oldb;
extern int16_t speedB_step;
extern int16_t speedB_old;
extern int16_t OldErrorIdB;
extern int16_t OldErrorIqB;
extern int16_t M2ActuSpeed;
extern int16_t FirstB;
extern uint16_t Theta_oldB;
extern int16_t speed_oldB;
extern int16_t FaultB;
extern int16_t iq2_ref;
extern int16_t	Hall2_err ;            // 2012.2.18
extern int16_t	Curr2_err ;
extern int16_t	Fault_Inv2;
extern int32_t  VSCALEB;
extern int32_t  VINTGB;
extern int16_t  Vel_refB;
extern int16_t   IREFB, IRFE_oldB;
extern int16_t   M2_iq;
extern int16_t   thea2_b,thea2_c;

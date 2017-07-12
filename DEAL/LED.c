#include "all_deal_api.h"

extern const uint8_t led_ON[16];
extern const uint8_t led_OFF[16];

static void EyeAction0(uint16_t *tim);  //正常眼睛，包括眨眼睛
static void EyeAction1(void);           //调试用，全亮、全灭、单个循环点亮
static void EyeAction2(uint16_t *tim);  //跳动的心
static void EyeAction3(uint16_t *tim);  //微笑
static void EyeAction4(uint16_t *tim);
//眼睛表情总指挥
void EyeControl(uint8_t *ptr,INT8U err,uint16_t *tim)
{
	static uint8_t eyeNum = 4;//记忆动作编号
	static uint8_t numMem = 4;
	if((ptr != NULL) && (err != OS_ERR_TIMEOUT))
	{
		eyeNum = *(ptr + 3);
		if(numMem != eyeNum)
		{
			numMem = eyeNum;
			*tim = 0;
		}
		Mem_free(ptr);
	}
	switch(eyeNum)
	{
		case 0: EyeAction1();break;      //调试用
		case 1: EyeAction0(tim);break;   //正常状态下的眼睛
		case 2: EyeAction3(tim);break;   //微笑
		case 3: EyeAction2(tim);break;   //跳动的心
		case 4: EyeAction4(tim);break;
		default:break;
	}
}
#define EYES_ON   0x2F
#define EYESOFF   0x00
static void EyeLight(const uint8_t rightRef[],const uint8_t leftRef[])
{
	uint8_t i,j,rightState,leftState,isEyeOn;
	for(i=0;i<15;i++)
	{
		rightState = rightRef[i];
		leftState  = leftRef[i] ;
		for(j=0;j<8;j++)
		{
			isEyeOn = (rightState&0x01)==0x01?EYES_ON:EYESOFF;
			I2C0_Byte_Write(FL3731_ADDR,right_Eyes[ i*8+j ],isEyeOn);
			rightState = rightState>>1;
			
			isEyeOn = (leftState&0x01)==0x01?EYES_ON:EYESOFF;
			I2C3_Byte_Write(FL3731_ADDR,right_Eyes[ i*8+j ],isEyeOn);
			leftState = leftState>>1;
		}
	}
	rightState = rightRef[i];
	leftState  = leftRef[i] ;
	for(j=0;j<5;j++)
	{
		isEyeOn = (rightState&0x01)==0x01?EYES_ON:EYESOFF;
		I2C0_Byte_Write(FL3731_ADDR,right_Eyes[ i*8+j ],isEyeOn);
		rightState = rightState>>1;
		
		isEyeOn = (leftState&0x01)==0x01?EYES_ON:EYESOFF;
		I2C3_Byte_Write(FL3731_ADDR,right_Eyes[ i*8+j ],isEyeOn);
		leftState = leftState>>1;
	}	
}
/*******************     表情1：正常表情  眨眼睛    *****************/
extern const uint8_t ledRight1_0[16];
extern const uint8_t ledRight1_1[16];
extern const uint8_t ledRight1_2[16];							
extern const uint8_t ledRight1_3[16];
extern const uint8_t ledRight1_4[16];
static void EyeAction0(uint16_t *tim)
{
	uint16_t timTemp = *tim;
	switch(timTemp)
	{
		case   0: case  84: case 259:
		case   1: EyeLight(ledRight1_0,ledRight1_0);break;
		case  83: case 252: case 258: case 260: case 266: 
		case  70: EyeLight(ledRight1_1,ledRight1_1);break;
		case  82: case 253: case 257: case 261: case 265: 
		case  71: EyeLight(ledRight1_2,ledRight1_2);break;
		case  81: case 254: case 262: case 256: case 264: 
		case  72: EyeLight(ledRight1_3,ledRight1_3);break;
		case 255: case 263:
		case  80: EyeLight(ledRight1_4,ledRight1_4);break;
		default:if(timTemp >266) 
					*tim = 0;  break;
	}
}
//调试用，全亮、全灭、一个一个点亮
static void EyeAction1(void)
{
	int i = 0;
	for(i=0;i<125;i++)
	{
		I2C0_Byte_Write(FL3731_ADDR,right_Eyes[i],0x1f);
		I2C3_Byte_Write(FL3731_ADDR,right_Eyes[i],0x1f);
	}
	OSTimeDly(400);
	for(i=0;i<125;i++)
	{
		I2C0_Byte_Write(FL3731_ADDR,right_Eyes[i],0x00);
		I2C3_Byte_Write(FL3731_ADDR,right_Eyes[i],0x00);
	}
	OSTimeDly(100);
	for(i=0;i<125;i++)
	{
		I2C0_Byte_Write(FL3731_ADDR,right_Eyes[i],0x1f);
		I2C3_Byte_Write(FL3731_ADDR,right_Eyes[i],0x1f);
		OSTimeDly(100);
		I2C0_Byte_Write(FL3731_ADDR,right_Eyes[i],0x00);
		I2C3_Byte_Write(FL3731_ADDR,right_Eyes[i],0x00);
	}
}
//表情2：跳动的心
extern const uint8_t ledRight2_0[16];
extern const uint8_t ledRight2_1[16];
extern const uint8_t ledRight2_2[16];
extern const uint8_t ledLeft2_0[16];
extern const uint8_t ledLeft2_1[16];
extern const uint8_t ledLeft2_2[16];
static void EyeAction2(uint16_t *tim)
{
	uint16_t timTemp = *tim;
	switch(timTemp)
	{
		case  40: case  80: case  120: case  160: 
		case  1: EyeLight(ledLeft2_0,ledRight2_0);break;
		case  39:  case   59: case   79: case   99: case  119: 
		case  139: case  159: case  179: case  199: 
		case  19: EyeLight(led_OFF,led_OFF);break;
		case  60:case  100:
		case  20: EyeLight(ledLeft2_1,ledRight2_1);break;
		case  180: 
		case  140: EyeLight(ledLeft2_2,ledRight2_2);break;

		default:if(timTemp >=200) *tim = 0;break;
	}
}
//表情3：微笑
extern const uint8_t ledRight3_0[16];
extern const uint8_t ledRight3_1[16];
extern const uint8_t ledLeft3_0[16];
extern const uint8_t ledLeft3_1[16];
static void EyeAction3(uint16_t *tim)
{
	uint16_t timTemp = *tim;
	switch(timTemp)
	{
		case  0:
	    case  1:EyeLight(ledLeft3_0,ledRight3_0);break;
		case  9: EyeLight(led_OFF,led_OFF);break;
		case  10:EyeLight(ledLeft3_1,ledRight3_1);break;
		case  19: EyeLight(led_OFF,led_OFF);break;
		default:if(timTemp >=20) *tim = 0;break;
	}
	
}
//表情4：初始化表情
extern uint8_t center0[16];
extern uint8_t centerr0[16];extern uint8_t centerl0[16];
extern uint8_t centerr1[16];extern uint8_t centerl1[16];
extern uint8_t centerr2[16];extern uint8_t centerl2[16];
extern uint8_t centerr3[16];extern uint8_t centerl3[16];
extern uint8_t centerr4[16];extern uint8_t centerl4[16];
extern uint8_t centerr5[16];extern uint8_t centerl5[16];
extern uint8_t centerr6[16];extern uint8_t centerl6[16];
extern uint8_t centerr7[16];extern uint8_t centerl7[16];
extern uint8_t right1[16];extern uint8_t left1[16];
extern uint8_t right2[16];extern uint8_t left2[16];
extern uint8_t right3[16];extern uint8_t left3[16];
extern uint8_t right4[16];extern uint8_t left4[16];
extern uint8_t right5[16];extern uint8_t left5[16];
extern uint8_t right6[16];extern uint8_t left6[16];
extern uint8_t right7[16];extern uint8_t left7[16];
extern uint8_t right8[16];extern uint8_t left8[16];
extern uint8_t right9[16];extern uint8_t left9[16];
extern uint8_t right10[16];extern uint8_t left10[16];
extern uint8_t right11[16];extern uint8_t left11[16];
extern uint8_t right12[16];extern uint8_t left12[16];
extern OS_EVENT *led61Cmd_Q;	
static void EyeAction4(uint16_t *tim)
{
	static uint8_t i= 0;
	uint8_t *ptr;
	uint16_t timTemp = *tim;
	switch(timTemp)
	{
		
		case   1:EyeLight(center0,center0);break;
		case   30:EyeLight(centerr0,centerl0);break;
		case   40:EyeLight(centerr1,centerl1);break;
		case   50:EyeLight(centerr2,centerl2);break;
		case   60:EyeLight(centerr3,centerl3);break;
		case   70:EyeLight(centerr4,centerl4);break;
		case   80:EyeLight(centerr5,centerl5);break;
		case   90:EyeLight(centerr6,centerl6);break;
		case  100:EyeLight(centerr7,centerl7);break;
		
	    case  110:EyeLight(right5,left1);break;
		case  120:EyeLight(right6,left2);break;
		case  130:EyeLight(right7,left3);break;
		case  140:EyeLight(right8,left4);break;
		case  150:EyeLight(right1,left5);break;
		case  160:EyeLight(right2,left6);break;
		case  170:EyeLight(right3,left7);break;
		case  180:EyeLight(right4,left8);break;
		
		case  191:EyeLight(right9,left9);break;
		case  201:EyeLight(right10,left10);break;
		case  211:EyeLight(right11,left11);break;
		case  221:EyeLight(right12,left12);break;
		
		default:if((timTemp >=190)&&(i<4)){
					*tim = 109;i++;	
				}else if((timTemp > 221)&&(i>=4)){
					i=0;*tim=0;
					ptr = Mem_malloc(10);
					*ptr = 0xaa;*(ptr + 1) = 0x61;*(ptr + 2) = 0x01;*(ptr + 3) = 0x01;
					OSQPost(led61Cmd_Q,ptr);
				}break;
	}
}

//三色LED、关机操作
void ThreeLedDeal(uint8_t *ptr,INT8U err)
{
	static uint8_t state = 2;		
	uint8_t cmd = 0;          //取得控制命令;
	uint16_t  delay=0;
	if((ptr != NULL)&&(err == OS_ERR_NONE))
	{
		cmd = *(ptr + 2);
		if(cmd == 0x02)       //控制状态灯
			state = *(ptr + 3);
		else if(cmd == 0x03)  //关机指令
		{
			delay = *(ptr + 3);
			delay = 1000 * delay;
			OSTimeDly(delay);
			POWER_OFF;
		}
		Mem_free(ptr);
	}
	switch(state)
	{
		case 0x00:LED_R_OFF;LED_G_OFF;LED_B_OFF;break; //三色全灭
		case 0x01:LED_R_ON ;LED_G_OFF;LED_B_OFF;break; //
		case 0x02:LED_R_OFF;LED_G_ON ;LED_B_OFF;break; //
		case 0x03:LED_R_OFF;LED_G_OFF;LED_B_ON ;break; //
		case 0x04:LED_R_ON ;LED_G_ON ;LED_B_OFF;break; //
		case 0x05:LED_R_ON ;LED_G_OFF;LED_B_ON ;break; //
		case 0x06:LED_R_OFF;LED_G_ON ;LED_B_ON ;break; //
		case 0x07:LED_R_ON ;LED_G_ON ;LED_B_ON ;break; //
		default:  break;
	}
}
	
	

























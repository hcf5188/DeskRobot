/*************************************************************
  *��Ŀ����: Human Computer Interface
  *�汾˵����V3.0
  *�ļ�����: lightcontrol  file
  *Ŀ��оƬ: PIC32MX534F064H
  *Ӳ    ����qu.xj
  *ϵͳʱ��: 10MHZ(PLL*8��80MHZ)
  *������λ: New Century Robot Co.,Ltd
  *������  ��Liuxh
  *����ʱ�䣺2013-9-27
  *����˵����                     
**************************************************************/

#ifndef __LIGHTCONTROL_H_
#define __LIGHTCONTROL_H_
 
//0x01 ����˵�� 0x02 ����˵�� 0x03 û����˵��
//0x04 ����˵�� 0x05 ��ŭ˵�� 
//0x11 ����     0x12 ����     0x13 û����
//0x14 ����     0x15 ��ŭ
//0x16 ˼��
//0x17 
 
#define IS31FL3731  0xE8
#define PWM_VALUE 0x7F

extern void Left_Eyes_Expression_Scanning_Control(unsigned char *I2C_Lefteyes_Current_Status_Light);
extern void Right_Eyes_Expression_Scanning_Control(unsigned char *I2C_Righteyes_Current_Status_Light);
extern void Refresh_Content_Change(void);
extern void Left_Unzip_Handle(void);
extern void Right_Unzip_Handle(void);
extern void Mouth_Unzip_Handle(void);
extern void Rearrange_Handle(unsigned char *I2C_Lefteyes_Current_Status_Light,unsigned char *I2C_Righteyes_Current_Status_Light);
extern void Mouth_Rearrange_Handle(unsigned char *I2C_Mouth_Current_Status_Light);
extern void Eyes_Expression_Scanning_Control(void);
extern void Mouth_Expression_Scanning_Control(void);
extern void Mouth_Control_IS31FL3731(void);
#endif



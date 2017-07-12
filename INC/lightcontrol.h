/*************************************************************
  *项目名称: Human Computer Interface
  *版本说明：V3.0
  *文件名称: lightcontrol  file
  *目标芯片: PIC32MX534F064H
  *硬    件：qu.xj
  *系统时钟: 10MHZ(PLL*8：80MHZ)
  *开发单位: New Century Robot Co.,Ltd
  *创建人  ：Liuxh
  *创建时间：2013-9-27
  *其他说明：                     
**************************************************************/

#ifndef __LIGHTCONTROL_H_
#define __LIGHTCONTROL_H_
 
//0x01 卖萌说话 0x02 高兴说话 0x03 没表情说话
//0x04 悲伤说话 0x05 愤怒说话 
//0x11 卖萌     0x12 高兴     0x13 没表情
//0x14 悲伤     0x15 愤怒
//0x16 思考
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



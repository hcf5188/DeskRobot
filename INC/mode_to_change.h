/************************************************
* Project Name : igo
* Function Name : INIT
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/

#ifndef MODE_TO_CHANGE_H
#define	MODE_TO_CHANGE_H
#define BUTTON_TWO    0x01
#define BUTTON_ONE    0x02
#define BUTTON_THREE  0x03

extern void YuYin_Handle_Function(void);
extern void ModeChangeExecution(void);
extern void Error_Process(void);
extern void Amplify_Volume(unsigned char VolumeValue);
extern void Volume_Reduction(void);

extern unsigned char KeyScan(void);
extern void KeyProcess(void);
#endif


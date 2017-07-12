/************************************************
* Project Name : igo
* Function Name : INIT
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/
#ifndef __I2C_FUNCTION_H__
#define __I2C_FUNCTION_H__


#define GYROADD     0x68//0xD0
#define GYROADD1    0x69//0xD0
#define GSENSORADD  0x1C//0x38
/* l3g4200d gyroscope registers */
#define ST_WHO_AM_I        0x0F

#define ST_CTRL_REG1       0x20    /* CTRL REG1 */
#define ST_CTRL_REG2       0x21    /* CTRL REG2 */
#define ST_CTRL_REG3       0x22    /* CTRL_REG3 */
#define ST_CTRL_REG4       0x23    /* CTRL_REG4 */
#define ST_CTRL_REG5       0x24    /* CTRL_REG5 */


/* freescale MMA8451Q registers */
#define FS_WHO_AM_I        0x0D

#define XYZ_DARA_CFG       0x0E
#define FS_CTRL_REG1       0x2A    /* CTRL REG1 */
#define FS_CTRL_REG2       0x2B    /* CTRL REG2 */
#define FS_CTRL_REG3       0x2C    /* CTRL_REG3 */
#define FS_CTRL_REG4       0x2D    /* CTRL_REG4 */
#define FS_CTRL_REG5       0x2E    /* CTRL_REG5 */

//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			  0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	MPU_WHO_AM_I  0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
//#define	SlaveAddress	0xD2//0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ


#define TILT_Q  56.0f

extern void I2C0_init(void);
extern void I2C1_init(void);
extern void I2C2_init(void);
extern void I2C3_init(void);
extern void I2C4_init(void);
extern void I2C5_init(void);
extern bool WaitI2C1Finished(void);
extern bool WaitI2C0Finished(void);
extern bool WaitI2C2Finished(void);
extern bool WaitI2C3Finished(void);
extern bool WaitI2C4Finished(void);
extern bool WaitI2C5Finished(void);
extern bool I2C_Read(uint8_t ControlByte, uint8_t ucAddr, uint8_t *pucData,uint32_t ulCount);
extern bool I2C_Write1(uint8_t ControlByte1, uint8_t ucAddr1, uint8_t putdata1);
extern bool I2C_Write0(uint8_t ControlByte0, uint8_t ucAddr0, uint8_t putdata0);
extern bool I2C_Write2(uint8_t ControlByte2, uint8_t ucAddr2, uint8_t putdata2);
extern bool I2C_Write3(uint8_t ControlByte3, uint8_t ucAddr3, uint8_t putdata3);
extern bool I2C_Write4(uint8_t ControlByte4, uint8_t ucAddr4, uint8_t putdata4);
extern bool I2C_Write5(uint8_t ControlByte5, uint8_t ucAddr5, uint8_t putdata5);

extern bool I2C_Write1_N(uint8_t ControlByte1, uint8_t ucAddr1, uint8_t *pucData1, uint8_t ulCount1);
extern bool I2C_Write0_N(uint8_t ControlByte0, uint8_t ucAddr0, uint8_t *pucData0, uint8_t ulCount0);
extern bool I2C_Write2_N(uint8_t ControlByte2, uint8_t ucAddr2, uint8_t *pucData2, uint8_t ulCount2);
extern bool I2C_Write3_N(uint8_t ControlByte3, uint8_t ucAddr3, uint8_t *pucData3, uint8_t ulCount3);
extern bool I2C_Write4_N(uint8_t ControlByte4, uint8_t ucAddr4, uint8_t *pucData4, uint8_t ulCount4);
extern bool I2C_Write5_N(uint8_t ControlByte5, uint8_t ucAddr5, uint8_t *pucData5, uint8_t ulCount5);

extern void sesnor_init(void);
extern void I2C_Handle_Gyro(void);
extern void I2C_Handle_GSensor(void);
extern void Sensor_Init(void);

extern void Kalman_Filter(float Gyro_X,float Angle_X,float Gyro_Y,float Angle_Y);
extern void Acc_GetAngle(void);

//extern uint32_t Test_eeprom_int_data[8];

extern float SIN_Table[41];

extern float gyrobuf[3];
extern float acltbuf[3];
extern int32_t gyroxtmp;
extern int32_t gyroytmp;
extern int32_t gyroztmp;

extern int32_t tiltx;
extern int32_t tilty;

extern float anglex;
extern float angley;
extern float anglez;
extern volatile float Kalman_Tilt_X, Kalman_Tilt_GX; 	//Kalman�˲����ⲿ��Ҫ���õı���
extern volatile float Kalman_Tilt_Y, Kalman_Tilt_GY; 	//Kalman�˲����ⲿ��Ҫ���õı���
extern  float Kalman_Tilt_X_send,Kalman_Tilt_Y_send;

extern int16_t HighgyroBate[3];
extern int16_t LowgyroBate[3];
extern int8_t HighTempData;
extern int8_t LowTempData;

#define EQU_VALUE   80.0f

#define SENSOR_EEPROM_BASE 416

#endif



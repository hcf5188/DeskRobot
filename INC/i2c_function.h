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
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			  0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
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
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	MPU_WHO_AM_I  0x75	//IIC地址寄存器(默认数值0x68，只读)
//#define	SlaveAddress	0xD2//0xD0	//IIC写入时的地址字节数据，+1为读取


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
extern volatile float Kalman_Tilt_X, Kalman_Tilt_GX; 	//Kalman滤波，外部需要引用的变量
extern volatile float Kalman_Tilt_Y, Kalman_Tilt_GY; 	//Kalman滤波，外部需要引用的变量
extern  float Kalman_Tilt_X_send,Kalman_Tilt_Y_send;

extern int16_t HighgyroBate[3];
extern int16_t LowgyroBate[3];
extern int8_t HighTempData;
extern int8_t LowTempData;

#define EQU_VALUE   80.0f

#define SENSOR_EEPROM_BASE 416

#endif



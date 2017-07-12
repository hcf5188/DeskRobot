/**********************************************************************************************************
*										  drv_I2C.h										
* File    : drv_I2C.h
* By      : 
* Version : V1.0
* time    : 
***********************************************************************************************************/
#ifndef  __AM2321_H__
#define  __AM2321_H__

#define I2C0SCL_PERIPH          (SYSCTL_PERIPH_GPIOB)
#define I2C0SCL_PORT            (GPIO_PORTB_BASE)
#define I2C0SCL_PIN             (GPIO_PIN_2)
#define I2C0SCL_GPIOPINMUX      (GPIO_PB2_I2C0SCL)
#define I2C0SDA_PERIPH          (SYSCTL_PERIPH_GPIOB)
#define I2C0SDA_PORT            (GPIO_PORTB_BASE)
#define I2C0SDA_PIN             (GPIO_PIN_3)
#define I2C0SDA_GPIOPINMUX      (GPIO_PB3_I2C0SDA)

#define I2C1SCL_PERIPH          (SYSCTL_PERIPH_GPIOA)
#define I2C1SCL_PORT            (GPIO_PORTA_BASE)
#define I2C1SCL_PIN             (GPIO_PIN_6)
#define I2C1SCL_GPIOPINMUX      (GPIO_PA6_I2C1SCL)
#define I2C1SDA_PERIPH          (SYSCTL_PERIPH_GPIOA)
#define I2C1SDA_PORT            (GPIO_PORTA_BASE)
#define I2C1SDA_PIN             (GPIO_PIN_7)
#define I2C1SDA_GPIOPINMUX      (GPIO_PA7_I2C1SDA)

//#define ONE_PERIPH          (SYSCTL_PERIPH_GPIOG)
//#define ONE_PORT            (GPIO_PORTG_BASE)
//#define ONE_PIN             (GPIO_PIN_5)

#define THESYSCLCOK 50000000

typedef enum {
	I2C_INT,
	I2C_ASK,
}I2CDATAMODE;


/******************************************************                       
*				init_I2CM				
* Description:	 I2C主机初始化,硬件初始化		   
* Arguments  :   
* Returns    : 
********************************************************/
//void init_I2CM( I2CDATAMODE mode );

extern void I2C0_Tempaure_Wet_Handle(void);

extern void init_I2CM0(void);


#endif  //  __LM3S_I2CM_H__


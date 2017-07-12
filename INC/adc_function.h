/************************************************
* Project Name : igo
* Function Name : INIT
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/
#ifndef __ADC_FUNCTION_H__
#define __ADC_FUNCTION_H__

#define  ADCSequDataGet(S,A)				ADCSequenceDataGet( ADC0_BASE,(S), (A) )
#define ADC_AIN1_PD_BASE  GPIO_PORTE_BASE
#define ADC_ANI1_PIN      GPIO_PIN_0

#define ADC_AIN2_PD_BASE  GPIO_PORTE_BASE
#define ADC_ANI2_PIN      GPIO_PIN_1
extern void init_Adc(void);
extern void init_AdcSequence(unsigned int ui32Base, unsigned long SequenceNumber );
extern void ADC_Handle(void);

#endif




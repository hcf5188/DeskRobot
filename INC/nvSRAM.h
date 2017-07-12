#include "hw_memmap.h"
#include "gpio.h"

#ifndef __NVSRAM_H
#define __NVSRAM_H
// Cypress Semiconductor Corporation
// Cypress鈥�Source Code: Copyright 2010, Cypress Semiconductor Corporation.
// This Source Code (software and/or firmware) is owned by Cypress Semiconductor
// Corporation (Cypress) and is protected by and subject to worldwide patent 
// protection (United States and foreign), United States copyright laws and 
// international treaty provisions. Cypress hereby grants to licensee a personal,
// non-exclusive, non-transferable license to copy, use, modify, create 
// derivative works of, and compile the Cypress Source Code and derivative works
// for the sole purpose of creating custom software and or firmware in support
// of licensee product to be used only in conjunction with a Cypress integrated
// circuit as specified in the applicable agreement. Any reproduction,
// modification, translation, compilation, or representation of this Source Code
// except as specified above is prohibited without the express written
// permission of Cypress. 
// Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
// REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Cypress reserves the right to make changes without further notice to the
// materials described herein. Cypress does not assume any liability arising
// out of the application or use of any product or circuit described herein.
// Cypress does not authorize its products for use as critical components in
// life-support systems where a malfunction or failure may reasonably be expected
// to result in significant injury to the user. The inclusion of Cypress鈥�product
// in a life-support systems application implies that the manufacturer assumes
// all risk of such use and in doing so indemnifies Cypress against all charges.
//
// Use may be limited by and subject to the applicable Cypress software license
// agreement.
///////////////////////////////////////////////////////////////////////////////////


/************Main Memory Access Functions************/
//void nvSRAMBURSTWRITE(unsigned int addr1, unsigned int addr2, unsigned int addr3,unsigned int total_count, unsigned int* data );
//void nvSRAMBURSTREAD(unsigned int addr1, unsigned int addr2, unsigned int addr3, unsigned int total_count, unsigned int * readDataArr);

/************nvSRAM NV Function********/
void nvSRAMSTORE(void);                                 
void nvSRAMRECALL(void);											 
void AutoStoreEnable(void);
void AutoStoreDisable(void);

/************Status Register Access Functions************/
void WRSR(unsigned int data1);
unsigned int RDSR(void);
void WREN(void);				
void WRDI(void);			

/************RTC Register Access Functions************/

//unsigned char RDRTC (unsigned int RtcAddr)
void WRRTC(unsigned int Addr, unsigned int Data);

/****************************************************************************
                            macro definition
****************************************************************************/
#define CS_HI     GPIOPinWrite(GPIO_PORTA_BASE, 0x00000008, 0x00000008)
#define CS_LO     GPIOPinWrite(GPIO_PORTA_BASE, 0x00000008, 0)

#endif

	

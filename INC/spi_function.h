/************************************************
* Project Name : igo
* Function Name : INIT
* Function Function :
* Hardware Designers : Quxj
* Software Designers : Liuxh
* Design Time : 2015.06.18
* Modify records :None
************************************************/
#ifndef __SPI_FUNCTION_H__
#define __SPI_FUNCTION_H__

//SPI Flash 每页的大小
#define SPI_FLASH_PageSize    256
//SPI Flash 每区的大小
#define SPI_FLASH_SectorSize  4096


#define WRITE      0x02  /* Write to Memory instruction */
#define WRSR       0x01  /* Write Status Register instruction */
#define WREN       0x06  /* Write enable instruction */
#define WRDN       0x04  /* Write disenable instruction */

#define READ       0x03  /* Read from Memory instruction */
#define RDSR       0x05  /* Read Status Register instruction  */
#define RDID       0x9F  /* Read identification */
//#define SE         0xD8  /* Sector Erase instruction */
#define SE         0x20  /* Sector Erase instruction */
#define BE         0xc7  /* Bulk Erase instruction */

#define WIP_Flag   0x01  /* Write In Progress (WIP) flag */
#define WEL_Flag   0x02  /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xA5	//FLASH   发送时序波形

extern void Spi_Init(void);
extern void SPI_FLASH_SectorErase(uint32_t SectorAddr);
extern void SPI_FLASH_BulkErase(void);
extern void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
extern void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
extern void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
extern uint32_t SPI_FLASH_ReadID(void);
extern void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
extern void SPI_FLASH_WriteRegister(unsigned char WriteStatus);

/*----- Low layer function -----*/
extern uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
extern void SPI_FLASH_WriteEnable(void);
extern void SPI_FLASH_WaitForWriteEnd(void);

extern uint32_t SPI_FLASH_ReadByte(void);
extern uint32_t SPI_FLASH_SendByte(uint32_t byte);

extern void spi_comm(unsigned char address,unsigned char data);
extern void SPI_Bag(void);
extern void SPI_Send(void);
#endif

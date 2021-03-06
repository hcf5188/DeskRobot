/************************************************************
*公司名称:       宁波GQY视讯股份有限公司
*文件名称: api_mem.c
*作者姓名: HongCf
*文件内容: 内存操作(内存申请、释放、初始化)
*编写日期: 2017-4-30
*************************************************************/

#include "mem_api.h"

OS_MEM	*pMemBuf_16B;
OS_MEM	*pMemBuf_32B;
OS_MEM  *pMemBuf_64B;
OS_MEM	*pMemBuf_128B;
OS_MEM	*pMemBuf_256B;

uint8_t MemBuf_16B[MEM_16B_ROW][MEM_16B_COL];
uint8_t MemBuf_32B[MEM_32B_ROW][MEM_32B_COL];
uint8_t MemBuf_64B[MEM_64B_ROW][MEM_64B_COL];
uint8_t MemBuf_128B[MEM_128B_ROW][MEM_128B_COL];
uint8_t MemBuf_256B[MEM_256B_ROW][MEM_256B_COL];

/****************************************************************
*			void	*Mem_malloc(uint16_t size)
* 描	述 : 获取一个内存块首地址			 		
* 输入参数 : 需要内存块的长度
* 返 回 值 : void * ,内存块第2个字节地址
****************************************************************/
void *Mem_malloc(uint16_t size)
{
	uint8_t err;
	uint16_t *ptr;
	
	if(size < 1)
		return NULL;
	else if(size <= MEM_16B_COL - 2)
	{
		if((ptr = OSMemGet(pMemBuf_16B,&err)) != NULL)
		{
			*ptr = MEM_16B_COL;
			return ptr + 1;
		}
		else 
			return NULL;
	}else if(size <= MEM_32B_COL - 2)
	{
		if((ptr = OSMemGet(pMemBuf_32B,&err)) != NULL)
		{
			*ptr = MEM_32B_COL;
			return ptr + 1;
		}
		else 
			return NULL;
	}else if(size <= MEM_64B_COL - 2)
	{
		if((ptr = OSMemGet(pMemBuf_64B,&err)) != NULL)
		{
			*ptr = MEM_64B_COL;
			return ptr + 1;
		}
		else 
			return NULL;
	}else if(size <= MEM_128B_COL - 2)
	{
		if((ptr = OSMemGet(pMemBuf_128B,&err)) != NULL)
		{
			*ptr = MEM_128B_COL;
			return ptr + 1;
		}
		else 
			return NULL;
	}else if(size <= MEM_256B_COL - 2)
	{
		if((ptr = OSMemGet(pMemBuf_256B,&err)) != NULL)
		{
			*ptr = MEM_256B_COL;
			return ptr + 1;
		}
		else 
			return NULL;
	}
	return NULL;
}
/****************************************************************
*			uint8_t Mem_free(void *ptr)
* 描	述 : 释放一个内存块			 		
* 输入参数 : 指向该内存块的指针
* 返 回 值 : uint8_t ,错误信息
****************************************************************/
uint8_t Mem_free(void *ptr)
{
	uint16_t *ptr_free = ptr;
	if(ptr_free == NULL)
		return 1;
	
	ptr_free = ptr_free - 1;
	switch(*ptr_free)
	{
		case MEM_16B_COL: 
			return OSMemPut(pMemBuf_16B,ptr_free);
		case MEM_32B_COL: 
			return OSMemPut(pMemBuf_32B,ptr_free);
		case MEM_64B_COL: 
			return OSMemPut(pMemBuf_64B,ptr_free);
		case MEM_128B_COL: 
			return OSMemPut(pMemBuf_128B,ptr_free);
		case MEM_256B_COL: 
			return OSMemPut(pMemBuf_256B,ptr_free);
		default :
			return 255;
	}
}
/****************************************************************
*			uint8_t MemBuf_Init(void)
* 描	述 : 初始化内存管理		 		
* 输入参数 : 无
* 返 回 值 : uint8_t，错误码
****************************************************************/
uint8_t MemBuf_Init(void)
{
	uint8_t err;
	
	pMemBuf_16B = OSMemCreate(MemBuf_16B,MEM_16B_ROW,MEM_16B_COL,&err);
	if(err != OS_ERR_NONE)
		return err;
	
	pMemBuf_32B = OSMemCreate(MemBuf_32B,MEM_32B_ROW,MEM_32B_COL,&err);
	if(err != OS_ERR_NONE)
		return err;
	
	pMemBuf_64B = OSMemCreate(MemBuf_64B,MEM_64B_ROW,MEM_64B_COL,&err);
	if(err != OS_ERR_NONE)
		return err;
	
	pMemBuf_128B = OSMemCreate(MemBuf_128B,MEM_128B_ROW,MEM_128B_COL,&err);
	if(err != OS_ERR_NONE)
		return err;
	
	pMemBuf_256B = OSMemCreate(MemBuf_256B,MEM_256B_ROW,MEM_256B_COL,&err);
	if(err != OS_ERR_NONE)
		return err;
	
	return err;
}




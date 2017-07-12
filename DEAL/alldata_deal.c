#include "all_deal_api.h"


/*********************************************************************************
						uint8_t CheckOut(uint8_t *p)
描    述：对数据包进行异或校验，通过返回指令，不通过返回 0
输入参数：数据包头地址
返回参数：0 -  无效数据包     指令  - 有效数据包
***********************************************************************************/
uint8_t CheckOut(uint8_t *p)
{
	uint8_t i=0;
	uint8_t temp = *p;
	if(*p != 0xaa)//判断帧头
		return 0x00;
	
	for(i= 1;i<9;i++)  //校验各字节
		temp = temp ^ (*(p + i));

	if(temp != *(p + 9))//判断校验字节
		return 0x00;
	return *(p + 1);
}
/*********************************************************************************
						uint8_t CheckOut(uint8_t *p)
描    述：对数据包进行异或校验，通过返回指令，不通过返回 0
输入参数：数据包头地址
返回参数：false -  无效数据包     true  - 校验成功
***********************************************************************************/
bool BufferInCheck(uint8_t *p)
{
	uint8_t i=0;
	uint8_t temp = *p;
	if(*p != 0xBB)   //判断帧头
		return false;
	for(i= 1;i<9;i++)  //校验各字节
		temp = temp ^ (*(p + i));

	*(p + 9) = temp;
	
	return true;
}

void Replay55Cmd(uint8_t *p)
{
	*p = 0xBB;
	*(p + 2) = 0x00; //软件版本  H
	*(p + 3) = 0x01; //软件版本  L
	*(p + 4) = 0x01; //硬件版本
	
	BufferInCheck(p);
	
	UART1SendDatas(p,10);
}






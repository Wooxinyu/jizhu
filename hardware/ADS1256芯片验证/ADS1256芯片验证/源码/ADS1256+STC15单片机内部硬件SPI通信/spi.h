#include"stc15f2k60s2.h"
#define SPIF  ( SPSTAT & 0x80 )  //SPI传输完成标志。查询SPIF是否置位，SPIF不能进行位操作

/*通信端口设置-------------------------------------------------------
sbit SCLK = P1^7;
sbit MISO = P1^6;
sbit MOSI = P1^5;
sbit SS   = P1^4;  //SPI主从选择IO口，此地未用
--------------------------------------------------------------------*/

unsigned char SPI_RecData=0;
void Init_SPI();
unsigned char SPI_SendByte(unsigned char SPI_SendData);

/*---------------------------------------------------------
*函数名：Init_SPI
*函数功能：SPI初始化，SPI的工作方式，不使用SPI中断方式
*输入参数：无
*返回参数：无
----------------------------------------------------------*/

void Init_SPI()
{
	SPCTL = 0xd5; //1101 0101:SPI使能、数据高位在前、CLK空闲时为低电平、下降沿采集数据、CPU_CLK/16。
	              //bit7：/SS引脚忽略控制位。bit6：SPI使能位。bit5：设定SPI数据发送顺序。bit4：主从选择。
				  //bit3：SPI时钟极性设置。bit2：SPI时钟相位选择。bit1 bit0：SPI时钟速率控制位。见792页
	SPSTAT = 0xc0;//SPI状态控制位的SPDAT.7和SPDAT.6：SPIF,ECOL.写11，可以将中断标志清零。注意是写1才清零
}

/*---------------------------------------------------------
*函数名：SPI_SendByte
*函数功能：SPI发射接收一体程序
*输入参数：SPI_SendData，经主机发给从机的数据
*返回参数：从机发给主机的数据
----------------------------------------------------------*/

unsigned char SPI_SendByte(unsigned char SPI_SendData)

{
	SPDAT= SPI_SendData; //将串口接收的数据装入SPI数据寄存器
	while(!SPIF);        //等待发送完毕
	SPSTAT = 0xc0;       //清除中断标志，和写冲突标志，注意是对应位写1才能清零
	SPI_RecData = SPDAT;
	return  SPI_RecData;
}


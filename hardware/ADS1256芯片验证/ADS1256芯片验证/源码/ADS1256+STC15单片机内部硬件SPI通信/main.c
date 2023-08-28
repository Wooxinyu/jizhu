//单片机STC15F2K60S2，内部11.0592晶振，串口9600。

#include"stc15f2k60s2.h"
#include "spi.h"
#include <string.h>

sbit ADS_SCLK  =  P1^5; 
sbit ADS_DIN   =  P1^3; 
sbit ADS_DOUT  =  P1^4;  
sbit ADS_DRDY  =  P1^6; 
sbit ADS_CS    =  P1^1; 
sbit ADS_REST  =  P1^2; 
sbit  LED2 = P5^5;

unsigned long ADS1256ReadData(void);
unsigned char SPI_SendByte(unsigned char SPI_SendData);

void ADS1256_Init(void);
void ADS_sum(unsigned char road);
void sendStr(unsigned char *s);
void sendChar(unsigned char ch);


void Delay(unsigned int dal)
{
	unsigned int i;
	for(i = 0;i < dal;i ++);
}

void sendChar(unsigned char ch)
{
	SBUF = ch;
	while(TI == 0);
	TI = 0;
}

void sendStr(unsigned char *s)
{   while(*s!='\0')         
 {  sendChar(*s);
    s++;       }   }
    



void inteReceive (void) interrupt 4 using 1
{	if(RI == 1)
	{ 	RI = 0;   }
	              }

void main()
{  	
	P1M0 = 0x00;
  P1M1 = 0x00;     
	SCON = 0x50;          //串口设置频率9600  	   
	TMOD = 0x20;         //8位 自动重装载定时器                
	AUXR =0X40;		       //开启1T模式   
	TH1 = TL1 = 0xDC;	   //设置波特率为9600 
  TR1 = 1;             //开启定时器1                                                      
	ES = 1;              //开串口中断
	EA = 1;
	
	
	Init_SPI();	   //硬件SPI通信设置
	ADS1256_Init();

	while(1)
	{
		ADS_sum(0x00 | 0x08);		
		Delay(65535);
		sendChar(0x0a);	
		Delay(65535);
		ADS_sum(0x10 | 0x08);				
	  Delay(65535);
		sendChar(0x0a);	
		Delay(65535);					
	  sendChar(0x0a);
    Delay(65535);		
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
		Delay(65535);
	 
		LED2 =~LED2;   }   }


void ADS1256WREG(unsigned char regaddr,unsigned char databyte)
{   ADS_CS = 0;
	  while(ADS_DRDY);//DRDY为低时才能写寄存器 
    SPI_SendByte(0x50 | (regaddr & 0xF));
    SPI_SendByte(0);    
    SPI_SendByte(databyte); 
	  ADS_CS = 1;       }

unsigned long ADS1256ReadData(void)  
{
    unsigned char i=0;
    unsigned long sum=0;
	  unsigned long r=0;
	
	ADS_CS = 0;
	while(ADS_DRDY); 
	SPI_SendByte(0xfc);
	SPI_SendByte(0x00);	               
	SPI_SendByte(0x01);
	ADS_SCLK = 0;

  for(i=0;i<3;i++)
{ sum = sum << 8;
	r = SPI_SendByte(0);  
	sum |= r;      }
	ADS_CS = 1;		 
  return sum;    }


//初始化
void ADS1256_Init(void)
{  
	ADS_CS = 0;
  ADS_REST = 1;
	ADS1256WREG(0x00,0x06);  // 高位在前、校准、使用缓冲  
	ADS1256WREG(0x01,0x08);  // 初始化端口A0为‘+’，AINCOM位‘-’
	ADS1256WREG(0x02,0x01);  // 放大倍数2,根据输入端分压电阻选择
	ADS1256WREG(0x03,0x13);  // 数据5sps
	ADS1256WREG(0x04,0x00);  // IO状态输入
	Delay(10);
	ADS_CS = 1;      }
	
	
 


//读取ADS1256数据

void ADS_sum(unsigned char road)
{
	unsigned long results=0;
	unsigned long Result_sum=0;
	unsigned long fVoltage;
	unsigned char buf[10],i,rod;

	ADS1256WREG(0x01,road);		//设置通道
  SPI_SendByte(0xf0);    //偏移和增益自动校准
  SPI_SendByte(0xf3);    //系统失调校准
  SPI_SendByte(0xf4);    //系统增益校准

	   

	ADS1256ReadData();//读取AD值，数据丢弃。根据手册P21 本次读取的数据是上一次转换的值
	ADS1256ReadData();//读取AD值，数据丢弃。
	results = ADS1256ReadData();//返回24位数据。
	
	Result_sum =  results >> 4;
	if(Result_sum<0x80000)    
	{
		fVoltage=Result_sum*952;  //954=2*2.5/2^19*100000000   2.5为基准电压  100000000为为了计算的准确性转换为整形计算
		                          //952是电压基准实际测量为2.498V
		buf[0]=(unsigned char)(fVoltage/100000000);
		buf[0]=buf[0]+0x30;
		buf[1]='.';
		buf[2]=(unsigned char)((fVoltage%100000000)/10000000);
		buf[2]=buf[2]+0x30;
		buf[3]=(unsigned char)((fVoltage%10000000)/1000000);
		buf[3]=buf[3]+0x30;
		buf[4]=(unsigned char)(fVoltage%1000000/100000);
		buf[4]=buf[4]+0x30;
		buf[5]=(unsigned char)(fVoltage%100000/10000);
		buf[5]=buf[5]+0x30;    
		buf[6]='V';			       
		buf[7]=0x20;	            }
	 else	
{ 	buf[0]=0+0x30;
		buf[1]='.';
		buf[2]=0+0x30;
		buf[3]=0+0x30;
		buf[4]=0+0x30;
		buf[5]=0+0x30;     
		buf[6]='V';			         
		buf[7]=0x20;
	                           }
	
	 
	if(road/16 == 0)					
	rod = (0 + 0x30);				//进行通道-1计算
	else 
  rod = ((road/16  + 0x30) );
  sendStr("第");
	sendChar(rod);
	sendStr("路：");
	i=0;
	while(i<10)
{ sendChar(buf[i]);
	i++;              }  
	                  }



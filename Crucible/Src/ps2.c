#include "ps2.h"
#include "other_functions.h"

#define DELAY_TIME  delay_us(5);
uint16_t Handkey;  // 按键值读取，零时存储
uint8_t Comd[2]={0x01,0x42};	//开始命令。请求数据
uint8_t Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
uint16_t MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//按键值与按键明

void PS2_Cmd(uint8_t CMD)
{
	volatile uint16_t ref=0x01;
	Data[1]=0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;
		}
		else DO_L;
		
		CLK_H;                       
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if(DI)
		Data[1] = ref|Data[1];
		
	}
	delay_us(16);
}

uint8_t PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);
	PS2_Cmd(Comd[1]);
	CS_H;
	if(Data[1]==0X73) return 0;
	else return 1;
}

void PS2_ReadData(void)
{
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;
	CS_L;
	PS2_Cmd(Comd[0]);  
	PS2_Cmd(Comd[1]);  
	for(byte=2;byte<9;byte++)        
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
		      if(DI)
		      Data[byte] = ref|Data[byte];
		}
        delay_us(16);
	}
	CS_H;
}
void PS2_ClearData()
{
	uint8_t a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
//主要功能函数
uint8_t PS2_DataKey()
{
	uint8_t index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];    
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0; 
}	

//得到一个摇杆的模拟量	 范围0~256
uint8_t PS2_AnologData(uint8_t button)
{
	return Data[button];
}
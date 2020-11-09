#ifndef __VL53L0_I2C_H
#define __VL53L0_I2C_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


#include "sys.h"



//IO��������
#define VL_SDA_IN()  {GPIOG->CRH&=0X0FFFFFFF;GPIOG->CRH|=(uint32_t)8<<28;}
#define VL_SDA_OUT() {GPIOG->CRH&=0X0FFFFFFF;GPIOG->CRH|=(uint32_t)3<<28;}


//IO��������	 
#define VL_IIC_SCL    PBout(3)      //SCL
#define VL_IIC_SDA    PGout(15) 	//SDA	 
#define VL_READ_SDA   PGin(15) 		//����SDA 

//״̬
#define STATUS_OK       0x00
#define STATUS_FAIL     0x01

//IIC��������


u8 VL53L0X_write_byte(u8 address,u8 index,u8 data);              //IICдһ��8λ����
u8 VL53L0X_write_word(u8 address,u8 index,u16 data);             //IICдһ��16λ����
u8 VL53L0X_write_dword(u8 address,u8 index,u32 data);            //IICдһ��32λ����
u8 VL53L0X_write_multi(u8 address, u8 index,u8 *pdata,u16 count);//IIC����д

u8 VL53L0X_read_byte(u8 address,u8 index,u8 *pdata);             //IIC��һ��8λ����
u8 VL53L0X_read_word(u8 address,u8 index,u16 *pdata);            //IIC��һ��16λ����
u8 VL53L0X_read_dword(u8 address,u8 index,u32 *pdata);           //IIC��һ��32λ����
u8 VL53L0X_read_multi(u8 address,u8 index,u8 *pdata,u16 count);  //IIC������


#endif 



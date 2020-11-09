#ifndef __ALARM_H
#define __ALARM_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "vl53l0x.h"



void vl53l0x_interrupt_test(VL53L0X_Dev_t *dev,u8 mode);


#endif 

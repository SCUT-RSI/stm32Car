#ifndef __ps2_H
#define __ps2_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define DI    HAL_GPIO_ReadPin(CRL_IN_GPIO_Port,CRL_IN_Pin)

#define DO_H  HAL_GPIO_WritePin(CRL_OUT_GPIO_Port,CRL_OUT_Pin,GPIO_PIN_SET)
#define DO_L  HAL_GPIO_WritePin(CRL_OUT_GPIO_Port,CRL_OUT_Pin,GPIO_PIN_RESET)

#define CS_H  HAL_GPIO_WritePin(CRL_CS_GPIO_Port,CRL_CS_Pin,GPIO_PIN_SET)
#define CS_L  HAL_GPIO_WritePin(CRL_CS_GPIO_Port,CRL_CS_Pin,GPIO_PIN_RESET)
 
#define CLK_H HAL_GPIO_WritePin(CRL_CLK_GPIO_Port,CRL_CLK_Pin,GPIO_PIN_SET)
#define CLK_L HAL_GPIO_WritePin(CRL_CLK_GPIO_Port,CRL_CLK_Pin,GPIO_PIN_RESET)

//按钮意义宏定义

#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16

#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16

//摇杆XY

#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

uint8_t PS2_DataKey();

#endif
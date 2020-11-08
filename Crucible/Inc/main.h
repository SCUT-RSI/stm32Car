/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEFT_MOTOR_EN_Pin GPIO_PIN_1
#define LEFT_MOTOR_EN_GPIO_Port GPIOF
#define LEFT_MOTOR_DIR_Pin GPIO_PIN_2
#define LEFT_MOTOR_DIR_GPIO_Port GPIOF
#define RIGHT_MOTOR_EN_Pin GPIO_PIN_3
#define RIGHT_MOTOR_EN_GPIO_Port GPIOF
#define RIGHT_MOTOR_DIR_Pin GPIO_PIN_4
#define RIGHT_MOTOR_DIR_GPIO_Port GPIOF
#define LEFT_DOOR_PWM_Pin GPIO_PIN_0
#define LEFT_DOOR_PWM_GPIO_Port GPIOA
#define RIGHT_DOOR_PWM_Pin GPIO_PIN_1
#define RIGHT_DOOR_PWM_GPIO_Port GPIOA
#define RIGHT_MOTOR_PWM_Pin GPIO_PIN_2
#define RIGHT_MOTOR_PWM_GPIO_Port GPIOA
#define LEFT_MOTOR_PWM_Pin GPIO_PIN_3
#define LEFT_MOTOR_PWM_GPIO_Port GPIOA
#define LEFT_CATCH_PWM_Pin GPIO_PIN_6
#define LEFT_CATCH_PWM_GPIO_Port GPIOA
#define RIGHT_CATCH_PWM_Pin GPIO_PIN_7
#define RIGHT_CATCH_PWM_GPIO_Port GPIOA
#define OPEN_DOOR_PWM_Pin GPIO_PIN_0
#define OPEN_DOOR_PWM_GPIO_Port GPIOB
#define CRL_CLK_Pin GPIO_PIN_11
#define CRL_CLK_GPIO_Port GPIOE
#define CRL_CS_Pin GPIO_PIN_12
#define CRL_CS_GPIO_Port GPIOE
#define CRL_OUT_Pin GPIO_PIN_13
#define CRL_OUT_GPIO_Port GPIOE
#define CRL_IN_Pin GPIO_PIN_14
#define CRL_IN_GPIO_Port GPIOE
#define LF_PWM_Pin GPIO_PIN_12
#define LF_PWM_GPIO_Port GPIOD
#define LB_PWM_Pin GPIO_PIN_13
#define LB_PWM_GPIO_Port GPIOD
#define RF_PWM_Pin GPIO_PIN_14
#define RF_PWM_GPIO_Port GPIOD
#define RB_PWM_Pin GPIO_PIN_15
#define RB_PWM_GPIO_Port GPIOD
#define RB_MOTOR_IN1_Pin GPIO_PIN_10
#define RB_MOTOR_IN1_GPIO_Port GPIOC
#define RB_MOTOR_IN2_Pin GPIO_PIN_11
#define RB_MOTOR_IN2_GPIO_Port GPIOC
#define RF_MOTOR_IN1_Pin GPIO_PIN_12
#define RF_MOTOR_IN1_GPIO_Port GPIOC
#define RF_MOTOR_IN2_Pin GPIO_PIN_0
#define RF_MOTOR_IN2_GPIO_Port GPIOD
#define LB_MOTOR_IN1_Pin GPIO_PIN_1
#define LB_MOTOR_IN1_GPIO_Port GPIOD
#define LB_MOTOR_IN2_Pin GPIO_PIN_2
#define LB_MOTOR_IN2_GPIO_Port GPIOD
#define LF_MOTOR_IN1_Pin GPIO_PIN_3
#define LF_MOTOR_IN1_GPIO_Port GPIOD
#define LF_MOTOR_IN2_Pin GPIO_PIN_4
#define LF_MOTOR_IN2_GPIO_Port GPIOD
#define SF_LAZER_SC_Pin GPIO_PIN_12
#define SF_LAZER_SC_GPIO_Port GPIOG
#define SB_LAZER_SC_Pin GPIO_PIN_13
#define SB_LAZER_SC_GPIO_Port GPIOG
#define B_LAZER_SC_Pin GPIO_PIN_14
#define B_LAZER_SC_GPIO_Port GPIOG
#define LAZER_SDA_Pin GPIO_PIN_15
#define LAZER_SDA_GPIO_Port GPIOG
#define LAZER_CLK_Pin GPIO_PIN_3
#define LAZER_CLK_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

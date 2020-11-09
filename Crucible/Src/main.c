/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "vl53l0x.h"
#include "vl53l0x_gen.h"
#include "motor_B.h"
#include "motor_D.h"
#include "motor.h"
#include "ps2.h"
#include "other_functions.h"
#include "lcg_functions.h"
#include "zbw_functions.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern VL53L0X_RangingMeasurementData_t RangingMeasurementData;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  
  
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  uint8_t POLE_RX=0;
  uint8_t POLE_RY=0;
  uint8_t POLE_LX=0;
  uint8_t POLE_LY=0;
  B_LAZER_Xshut=0;
  SB_LAZER_Xshut=0;
  SF_LAZER_Xshut=0;
  vl53l0x_init(&vl53l0x_dev0,0);
  vl53l0x_init(&vl53l0x_dev1,1);
  vl53l0x_init(&vl53l0x_dev2,2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 
	  /***遥控按键·***/
	  switch(PS2_DataKey())
	  {
		  case PSB_SELECT: 
			  printf("1");
			  break;
		  case PSB_L3: printf("2");
			  break;
		  case PSB_R3: printf("3");
			  break;
		  case PSB_START: printf("4");
			  break;
		  case PSB_PAD_UP: printf("5");
			  break;
		  case PSB_PAD_RIGHT: printf("6");
			  break;
		  case PSB_PAD_DOWN: printf("7");
			  break;
		  case PSB_PAD_LEFT: printf("8");
			  break;
		  case PSB_L2: printf("9");
			  catch_2();
			  break;
		  case PSB_R2: printf("10");
			  release_1();
			  break;
		  case PSB_L1: printf("11");
			  catch_1();
			  break;
		  case PSB_R1: printf("12");
			  release_2();
			  break;
		  case PSB_GREEN: printf("13");
			  break;
		  case PSB_RED: printf("14");
			  break;
		  case PSB_BLUE: printf("15");
			  break;
		  case PSB_PINK: printf("16");
			  break;
		  case 0: 
			  POLE_RX=PS2_AnologData(PSS_RX);
			  POLE_RY=PS2_AnologData(PSS_RY);
			  POLE_LX=PS2_AnologData(PSS_LX);
			  POLE_LY=PS2_AnologData(PSS_LY);
			  if(POLE_LX != 128||POLE_LY != 128||POLE_RX != 128 ||POLE_RY != 128)
			  {
				if(POLE_LX>=64&&POLE_LX<=191&&POLE_LY>178)
				{
					move_backward();
					printf("后");		
				}
				else if(POLE_LX>=64&&POLE_LX<=191&&POLE_LY<50)
				{
					move_forward();
					printf("前");
				}
				else if(POLE_LY>=64&&POLE_LY<=191&&POLE_LX<50)
				{
					move_left();
					printf("左");
				}
				else if(POLE_LY>=64&&POLE_LY<=191&&POLE_LX>178)
				{
					move_right();
					printf("右");
				}
				else if(POLE_RY>=64&&POLE_RY<=191&&POLE_RX>178)
				{
					move_Scircle();
					printf("右转");
				}
				else if(POLE_RY>=64&&POLE_RY<=191&&POLE_RX<50)
				{
					move_Ncircle();
					printf("左转");
				}
			  }
			  break;
		  }
	  HAL_Delay(10);

		  
	  
	  
	  
	  
	 
	  
	  
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

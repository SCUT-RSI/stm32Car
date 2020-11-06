#include "motor_D.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

void catch_fk(void)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,L_PWM_CLOSE);
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,R_PWM_CLOSE);
}

void open_door(void)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,D_PWM_OPEN);
}

void open_front_door(void)
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,FL_PWM_OPEN);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,FR_PWM_OPEN);
}

void release_fk(void)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,L_PWM_OPEN);
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,R_PWM_OPEN);
}

void close_door(void)
{
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,D_PWM_CLOSE);
}

void close_front_door(void)
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,FL_PWM_CLOSE);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,FR_PWM_CLOSE);
}
#include "motor_B.h"
#include "other_functions.h"
#include "tim.h"
#include <stdio.h>
#include <math.h>


speedRampData srd;
int stepPosition = 0;
struct GLOBAL_FLAGS status = {FALSE, FALSE,TRUE};


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM5)
	{ 
		unsigned int new_step_delay;
		static int last_accel_delay;
		static  unsigned int step_count =0;
		static int rest =0;
		//修改重装载寄存器
		//修改占空比
		
		TIM5->CCR1=(srd.step_delay >> 1) ;
		TIM5->CCR2=(srd.step_delay >> 1) ;
		TIM5->ARR=srd.step_delay;
		if(status.out_ena != TRUE)
		{
			srd.run_state=STOP;
		}
		switch(srd.run_state)
		{
			case STOP:
				step_count=0;
				rest=0;
				HAL_TIM_Base_Stop(&htim5);
				status.running=FALSE;
				break;
			case ACCEL:
				TIM5->CCER |= 1<<12;
				MSD_StepCounter(srd.dir);
				step_count++;
				srd.accel_count++;
				new_step_delay = srd.step_delay - (((2 * (long)srd.step_delay) 
								+ rest)/(4 * srd.accel_count + 1));
				rest = ((2 * (long)srd.step_delay)+rest)%(4 * srd.accel_count + 1);
				if(step_count >= srd.decel_start) {
				srd.accel_count = srd.decel_val;
				srd.run_state = DECEL;
				}
				else if(new_step_delay <= srd.min_delay) {
				last_accel_delay = new_step_delay;
				new_step_delay = srd.min_delay;
				rest = 0;
				srd.run_state = RUN;
				  }
				break;
			case RUN:
				  TIM5->CCER |= 1<<12;
				  MSD_StepCounter(srd.dir);
				  step_count++;
				  new_step_delay = srd.min_delay;
				  if(step_count >= srd.decel_start) 
				  {
					srd.accel_count = srd.decel_val;
			   
					new_step_delay = last_accel_delay;
					srd.run_state = DECEL;
				  }
			    break;
			case DECEL:
				  TIM5->CCER |= 1<<12;
				  MSD_StepCounter(srd.dir);
				  step_count++;
				  srd.accel_count++;
				  new_step_delay = srd.step_delay - (((2 * (long)srd.step_delay) 
                       + rest)/(4 * srd.accel_count + 1));
				  rest = ((2 * (long)srd.step_delay)+rest)%(4 * srd.accel_count + 1);
				  if(srd.accel_count >= 0)
				  {
					srd.run_state = STOP;
				  }
				  break;
				}
		srd.step_delay = new_step_delay;
		}
	}

//步数记录器
void MSD_StepCounter(signed char inc)
{
 
  if(inc == ACW)
  {
    stepPosition--;
  }
  else
  {
    stepPosition++;
  }
}
/*  以给定的步数移动步进电机
 *  通过计算加速到最大速度，以给定的步数开始减速
 *  如果加速度和减速度很小，步进电机会移动很慢，还没达到最大速度就要开始减速
 *  移动的步数 (正数为顺时针，负数为逆时针).
 *  加速度,如果取值为100，实际值为100*0.01*rad/sec^2=1rad/sec^2
 *  减速度,如果取值为100，实际值为100*0.01*rad/sec^2=1rad/sec^2
 *  最大速度,如果取值为100，实际值为100*0.01*rad/sec=1rad/sec
 */
void MOTER_MOVE(int step, uint32_t accel, uint32_t decel, uint32_t speed)
{
	uint32_t max_s_st;
	uint32_t accel_speed;
	if(step<0)
	{
		srd.dir =ACW;
		step=-step;
		HAL_GPIO_WritePin(LEFT_MOTOR_DIR_GPIO_Port,LEFT_MOTOR_DIR_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RIGHT_MOTOR_DIR_GPIO_Port,RIGHT_MOTOR_DIR_Pin,GPIO_PIN_RESET);
	}
	else
	{
		srd.dir=CW;
		HAL_GPIO_WritePin(LEFT_MOTOR_DIR_GPIO_Port,LEFT_MOTOR_DIR_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(RIGHT_MOTOR_DIR_GPIO_Port,RIGHT_MOTOR_DIR_Pin,GPIO_PIN_SET);
	}
	//电机运动方向设置ACW逆时针，CW顺时针
	if(step == 1)
	{
		srd.accel_count= -1;
		srd.run_state=DECEL;
		srd.step_delay = 1000;
	}
	else if(step !=0)
	{
		srd.min_delay = A_T_x100 / speed;
		srd.step_delay = (T1_FREQ_148 * sqrt(A_SQ / accel))/100;
		max_s_st = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
		  if(max_s_st == 0)
		{
			max_s_st = 1;
		}
		accel_speed = ((long)step*decel) / (accel+decel);
		    if(accel_speed == 0)
		{
			accel_speed = 1;
		}
		if(accel_speed <= max_s_st)
		{
			srd.decel_val = accel_speed - step;
		}
		else
		{
			srd.decel_val = -(long)(max_s_st*accel/decel);
		}
		if(srd.decel_val == 0)
		{
			srd.decel_val = -1;
		}
		srd.decel_start = step + srd.decel_val;
		if(srd.step_delay <= srd.min_delay)
		{
			srd.step_delay = srd.min_delay;
			srd.run_state = RUN;
		}
		else
	    {
			srd.run_state = ACCEL;
		}
		srd.accel_count = 0;
		status.running = TRUE;
		HAL_TIM_Base_Start_IT(&htim5);
		HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
	}
}

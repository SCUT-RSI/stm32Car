#include "lcg_functions.h"
#include "vl53l0x.h"
#include "motor_B.h"
#include "motor_D.h"
#include "motor.h"
#include "ps2.h"
#include "other_functions.h"
#include "zbw_functions.h"



void catch_1(void)
{
	// 校准函数
	while(calibration_cube())
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(10);
	}
	// 舵机松
	release_fk();
	// 丝杆低
	// 步进电机由很高下降到低� 10cm 需计算
	MOTER_MOVE(3000,3000,3000,3000);
	// 舵机紧
	catch_fk();
	// 丝杆  低-->很高
		// CW
	MOTER_MOVE(3000,3000,3000,3000);
}

void catch_2(void)
{
	// 校准函数
	while(calibration_cube())
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(10);
	}
	// 舵机松
	release_fk();
	// 丝杆低
	// 步进电机由很高下降到低� 10cm 需计算
	MOTER_MOVE(3000,3000,3000,3000);
	// 舵机紧
	catch_fk();
	// 丝杆  低-->中
	MOTER_MOVE(3000,3000,3000,3000);
}

void release_1(void)
{
	release_fk();
	open_door();
	
	// 车子向后移动
	move_backward();
	
	close_door();
	// 丝杆 中-->很高
	MOTER_MOVE(3000,3000,3000,3000);
	catch_fk();
	
}

void release_2(void)
{
	release_fk();
	open_door();
	move_backward();
	close_door();
	catch_fk();
}


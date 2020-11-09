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
	// У׼����
	while(calibration_cube())
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(10);
	}
	// �����
	release_fk();
	// ˿�˵�
	// ��������ɺܸ��½������ 10cm �����
	MOTER_MOVE(3000,3000,3000,3000);
	// �����
	catch_fk();
	// ˿��  ��-->�ܸ�
		// CW
	MOTER_MOVE(3000,3000,3000,3000);
}

void catch_2(void)
{
	// У׼����
	while(calibration_cube())
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(10);
	}
	// �����
	release_fk();
	// ˿�˵�
	// ��������ɺܸ��½������ 10cm �����
	MOTER_MOVE(3000,3000,3000,3000);
	// �����
	catch_fk();
	// ˿��  ��-->��
	MOTER_MOVE(3000,3000,3000,3000);
}

void release_1(void)
{
	release_fk();
	open_door();
	
	// ��������ƶ�
	move_backward();
	
	close_door();
	// ˿�� ��-->�ܸ�
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


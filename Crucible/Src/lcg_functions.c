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
	// Ð£×¼º¯Êý
	while(calibration_cube())
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(10);
	}
	// ¶æ»úËÉ
	release_fk();
	// Ë¿¸ËµÍ
	// ²½½øµç»úÓÉºÜ¸ßÏÂ½µµ½µÍë 10cm Ðè¼ÆËã
	MOTER_MOVE(3000,3000,3000,3000);
	// ¶æ»ú½ô
	catch_fk();
	// Ë¿¸Ë  µÍ-->ºÜ¸ß
		// CW
	MOTER_MOVE(3000,3000,3000,3000);
}

void catch_2(void)
{
	// Ð£×¼º¯Êý
	while(calibration_cube())
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(10);
	}
	// ¶æ»úËÉ
	release_fk();
	// Ë¿¸ËµÍ
	// ²½½øµç»úÓÉºÜ¸ßÏÂ½µµ½µÍë 10cm Ðè¼ÆËã
	MOTER_MOVE(3000,3000,3000,3000);
	// ¶æ»ú½ô
	catch_fk();
	// Ë¿¸Ë  µÍ-->ÖÐ
	MOTER_MOVE(3000,3000,3000,3000);
}

void release_1(void)
{
	release_fk();
	open_door();
	
	// ³µ×ÓÏòºóÒÆ¶¯
	move_backward();
	
	close_door();
	// Ë¿¸Ë ÖÐ-->ºÜ¸ß
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


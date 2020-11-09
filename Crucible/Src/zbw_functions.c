#include "zbw_functions.h"
#include "vl53l0x.h"
#include "vl53l0x_gen.h"
#include "motor_B.h"
#include "motor_D.h"
#include "motor.h"
#include "ps2.h"
#include "other_functions.h"
#include "lcg_functions.h"
uint16_t SF_DISTANCE=0,SB_DISTANCE=0,B_DISTANCE=0;

//Ð£×¼·½¿é
uint8_t calibration_cube(void)
{
	SF_DISTANCE=vl53l0x_general_start(&vl53l0x_dev2,Default_Mode);
	SB_DISTANCE=vl53l0x_general_start(&vl53l0x_dev1,Default_Mode);
	if(SB_DISTANCE-SF_DISTANCE>=3)
	{
		move_Scircle();
	}
	else if(SB_DISTANCE-SF_DISTANCE<=-3)
	{
		move_Ncircle();
	}
	else if(SB_DISTANCE>48&&SF_DISTANCE>48)
	{
		move_right();
	}
	else if(SB_DISTANCE<45&&SF_DISTANCE<45)
	{
		move_left();
	}
	else if((SB_DISTANCE>=45&&SB_DISTANCE<=48)&&(SF_DISTANCE>=45&&SF_DISTANCE<=48))
	{
		B_DISTANCE=vl53l0x_general_start(&vl53l0x_dev0,Default_Mode);
		if(B_DISTANCE>45)
		{
			move_forward();
		}
		else if(B_DISTANCE<43)
		{
			move_backward();
		}
		else if(B_DISTANCE>=43&&B_DISTANCE<=45)
		{
			stop();
			return 0;
		}
		return 1;
	}
																
}


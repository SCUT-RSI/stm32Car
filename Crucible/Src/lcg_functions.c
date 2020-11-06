#include "lcg_functions.h"
#include "vl53l0x.h"
#include "motor_B.h"
#include "motor_D.h"
#include "motor.h"
#include "ps2.h"
#include "other_functions.h"
#include "zbw_functions.h"





// ³õÊ¼»¯
void car_init(void);
// Ò»¼ü×¥È¡·½¿é_1  ×¥È¡Ç°Ãæ¼¸¿é
void catch_1(void);
// Ò»¼ü×¥È¡·½¿é_2  ×¥È¡×îºóÒ»¿é
void catch_2(void);
// Ò»¼üÊÍ·Å1_·ÅÖÃµÍÆ½Ì¨
void release_1(void);
// Ò»¼üÊÍ·Å2_·ÅÖÃ¸ßÆ½Ì¨
void release_2(void);






void catch_1(void)
{
	// Ð£×¼º¯Êý
	jiaozhun();
	// ¶æ»úËÉ
	release_fk();
	// Ë¿¸ËµÍ
		// ÉèÖÃ·½Ïò CCW ÄæÊ±Õë£¬CWË³Ê±Õë ÔÝ¶¨ACWÎªË¿¸ËÏÂ½µ
		MSD_StepCounter(ACW);
		// ²½½øµç»úÓÉºÜ¸ßÏÂ½µµ½µÍë 10cm Ðè¼ÆËã
		MOTER_MOVE(3000,3000,3000,3000);
	// ¶æ»ú½ô
	catch_fk();
	// Ë¿¸Ë  µÍ-->ºÜ¸ß
		// CW
		MSD_StepCounter(CW);
		MOTER_MOVE(3000,3000,3000,3000);
}

void catch_2(void)
{
	// Ð£×¼º¯Êý
	jiaozhun();
	// ¶æ»úËÉ
	release_fk();
	// Ë¿¸ËµÍ
		// ÉèÖÃ·½Ïò CCW ÄæÊ±Õë£¬CWË³Ê±Õë ÔÝ¶¨CCWÎªË¿¸ËÏÂ½µ
		MSD_StepCounter(ACW);
		// ²½½øµç»úÓÉºÜ¸ßÏÂ½µµ½µÍë 10cm Ðè¼ÆËã
		MOTER_MOVE(3000,3000,3000,3000);
	// ¶æ»ú½ô
	catch_fk();
	// Ë¿¸Ë  µÍ-->ÖÐ
		// CW
		MSD_StepCounter(CW);
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
	MSD_StepCounter(CW);
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


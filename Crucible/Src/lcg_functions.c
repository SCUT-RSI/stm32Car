#include "lcg_functions.h"
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
		// ÉèÖÃ·½Ïò CCW ÄæÊ±Õë£¬CWË³Ê±Õë ÔÝ¶¨CCWÎªË¿¸ËÏÂ½µ
		MSD_StepCounter("CCW");
		// ²½½øµç»úÓÉºÜ¸ßÏÂ½µµ½µÍë 10cm Ðè¼ÆËã
		MOTER_MOVE();
	// ¶æ»ú½ô
	catch_fk();
	// Ë¿¸Ë  µÍ-->ºÜ¸ß
		// CW
		MSD_StepCounter("CW");
		MOTER_MOVE();
}

void catch_2(void)
{
	// Ð£×¼º¯Êý
	jiaozhun();
	// ¶æ»úËÉ
	release_fk();
	// Ë¿¸ËµÍ
		// ÉèÖÃ·½Ïò CCW ÄæÊ±Õë£¬CWË³Ê±Õë ÔÝ¶¨CCWÎªË¿¸ËÏÂ½µ
		MSD_StepCounter("CCW");
		// ²½½øµç»úÓÉºÜ¸ßÏÂ½µµ½µÍë 10cm Ðè¼ÆËã
		MOTER_MOVE();
	// ¶æ»ú½ô
	catch_fk();
	// Ë¿¸Ë  µÍ-->ÖÐ
		// CW
		MSD_StepCounter("CW");
		MOTER_MOVE();
}

void release_1(void)
{
	release_fk();
	open_door();
	
	// ³µ×ÓÏòºóÒÆ¶¯
	move_backward();
	
	close_door();
	// Ë¿¸Ë ÖÐ-->ºÜ¸ß
	MSD_StepCounter("CW");
	MOTER_MOVE();
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
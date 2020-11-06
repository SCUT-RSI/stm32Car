#include "lcg_functions.h"
#include "vl53l0x.h"
#include "motor_B.h"
#include "motor_D.h"
#include "motor.h"
#include "ps2.h"
#include "other_functions.h"
#include "zbw_functions.h"





// ��ʼ��
void car_init(void);
// һ��ץȡ����_1  ץȡǰ�漸��
void catch_1(void);
// һ��ץȡ����_2  ץȡ���һ��
void catch_2(void);
// һ���ͷ�1_���õ�ƽ̨
void release_1(void);
// һ���ͷ�2_���ø�ƽ̨
void release_2(void);






void catch_1(void)
{
	// У׼����
	jiaozhun();
	// �����
	release_fk();
	// ˿�˵�
		// ���÷��� CCW ��ʱ�룬CW˳ʱ�� �ݶ�ACWΪ˿���½�
		MSD_StepCounter(ACW);
		// ��������ɺܸ��½������ 10cm �����
		MOTER_MOVE(3000,3000,3000,3000);
	// �����
	catch_fk();
	// ˿��  ��-->�ܸ�
		// CW
		MSD_StepCounter(CW);
		MOTER_MOVE(3000,3000,3000,3000);
}

void catch_2(void)
{
	// У׼����
	jiaozhun();
	// �����
	release_fk();
	// ˿�˵�
		// ���÷��� CCW ��ʱ�룬CW˳ʱ�� �ݶ�CCWΪ˿���½�
		MSD_StepCounter(ACW);
		// ��������ɺܸ��½������ 10cm �����
		MOTER_MOVE(3000,3000,3000,3000);
	// �����
	catch_fk();
	// ˿��  ��-->��
		// CW
		MSD_StepCounter(CW);
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


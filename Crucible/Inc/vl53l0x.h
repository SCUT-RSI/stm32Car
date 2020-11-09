#ifndef __VL53L0X_H
#define __VL53L0X_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_gen.h"
#include "sys.h"





//���������ID
#define B	0
#define SB	1
#define SF	2
//VL53L0X�������ϵ�Ĭ��IIC��ַΪ0X52(���������λ)
#define VL53L0X_Addr 0x52

//����Xshut��ƽ,�Ӷ�ʹ��VL53L0X���� 1:ʹ�� 0:�ر�
#define B_LAZER_Xshut PGout(14)
#define SB_LAZER_Xshut PGout(13)
#define SF_LAZER_Xshut PGout(12)

//ʹ��2.8V IO��ƽģʽ
#define USE_I2C_2V8  1

//����ģʽ
#define Default_Mode   0// Ĭ��
#define HIGH_ACCURACY  1//�߾���
#define LONG_RANGE     2//������
#define HIGH_SPEED     3//����

//vl53l0xģʽ���ò�����
typedef __packed struct
{
	FixPoint1616_t signalLimit;    //Signal������ֵ 
	FixPoint1616_t sigmaLimit;     //Sigmal������ֵ
	uint32_t timingBudget;         //����ʱ������
	uint8_t preRangeVcselPeriod ;  //VCSEL��������
	uint8_t finalRangeVcselPeriod ;//VCSEL�������ڷ�Χ
	
}mode_data;

extern mode_data Mode_data[];
extern VL53L0X_Dev_t vl53l0x_dev;
extern VL53L0X_DeviceInfo_t vl53l0x_dev_info;
extern VL53L0X_Dev_t vl53l0x_dev0;
extern VL53L0X_Dev_t vl53l0x_dev1;
extern VL53L0X_Dev_t vl53l0x_dev2;
//vl53l0x������У׼��Ϣ�ṹ�嶨��
typedef __packed struct
{
	uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
	uint8_t  isApertureSpads;             //ApertureSpadsֵ
	uint8_t  VhvSettings;                 //VhvSettingsֵ
	uint8_t  PhaseCal;                    //PhaseCalֵ
	uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
	uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
	uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
	int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
	uint32_t refSpadCount;                //refSpadCountֵ
	
}_vl53l0x_adjust;

extern _vl53l0x_adjust Vl53l0x_data;

VL53L0X_Error vl53l0x_init(VL53L0X_Dev_t *dev,uint8_t ID);//��ʼ��vl53l0x
void print_pal_error(VL53L0X_Error Status);//������Ϣ��ӡ
void vl53l0x_reset(VL53L0X_Dev_t *dev);//vl53l0x��λ

void vl53l0x_info(void);//��ȡvl53l0x�豸ID��Ϣ
#endif



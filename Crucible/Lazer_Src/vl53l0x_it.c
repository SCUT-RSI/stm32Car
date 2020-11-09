#include "vl53l0x_it.h"


//�����޾���ֵ ��λ:mm
#define Thresh_Low  60
#define Thresh_High 150
VL53L0X_RangingMeasurementData_t RangingMeasurementData;
//�ж�ģʽ�����ṹ��
typedef struct 
{
     const int VL53L0X_Mode;//ģʽ
	 uint32_t ThreshLow;    //����ֵ
	 uint32_t ThreshHigh;   //����ֵ
}AlrmMode_t; 

AlrmMode_t AlarmModes ={
	
     VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_OUT,// value < thresh_low OR value > thresh_high
	 Thresh_Low<<16,
	 Thresh_High<<16
};





//�ⲿ�жϷ�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	VL53L0X_GetRangingMeasurementData(&vl53l0x_dev,&RangingMeasurementData);//��ȡ��������
	printf("d: %3d mm\r\n",RangingMeasurementData.RangeMilliMeter);
	HAL_Delay(70);
	VL53L0X_ClearInterruptMask(&vl53l0x_dev,0);//���VL53L0X�жϱ�־λ 
}

extern uint8_t AjustOK;
extern mode_data Mode_data[];

//vl53l0x�жϲ���ģʽ����
//dev:�豸I2C�����ṹ��
//mode: 0:Ĭ��;1:�߾���;2:������;3:����
void vl53l0x_interrupt_start(VL53L0X_Dev_t *dev,uint8_t mode)
{
	 uint8_t VhvSettings;
	 uint8_t PhaseCal;
	 uint32_t refSpadCount;
	 uint8_t isApertureSpads;
	 VL53L0X_Error status=VL53L0X_ERROR_NONE;//����״̬
	 

	 

     vl53l0x_reset(dev);//��λvl53l0x(Ƶ���л�����ģʽ���׵��²ɼ��������ݲ�׼���������һ����)
		
	 status = VL53L0X_StaticInit(dev);
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 
	 status = VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);//Ref�ο�У׼
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_PerformRefSpadManagement(dev, &refSpadCount, &isApertureSpads);//ִ�вο�SPAD����
	 if(status!=VL53L0X_ERROR_NONE) goto error;
     HAL_Delay(2);		 
	 status = VL53L0X_SetDeviceMode(dev,VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);//ʹ����������ģʽ
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetInterMeasurementPeriodMilliSeconds(dev,Mode_data[mode].timingBudget);//�����ڲ����ڲ���ʱ��
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetLimitCheckEnable(dev,VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,1);//ʹ��SIGMA��Χ���
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetLimitCheckEnable(dev,VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,1);//ʹ���ź����ʷ�Χ���
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetLimitCheckValue(dev,VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,Mode_data[mode].sigmaLimit);//�趨SIGMA��Χ
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2); 
	 status = VL53L0X_SetLimitCheckValue(dev,VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,Mode_data[mode].signalLimit);//�趨�ź����ʷ�Χ��Χ
	 if(status!=VL53L0X_ERROR_NONE) goto error; 
	 HAL_Delay(2);
	 status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev,Mode_data[mode].timingBudget);//�趨��������ʱ��
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2); 
	 status = VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, Mode_data[mode].preRangeVcselPeriod);//�趨VCSEL��������
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, Mode_data[mode].finalRangeVcselPeriod);//�趨VCSEL�������ڷ�Χ
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_StopMeasurement(dev);//ֹͣ����
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetInterruptThresholds(dev,VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,AlarmModes.ThreshLow, AlarmModes.ThreshHigh);//�趨�����ж��ϡ�����ֵ
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetGpioConfig(dev,0,VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,AlarmModes.VL53L0X_Mode,VL53L0X_INTERRUPTPOLARITY_LOW);//�趨�����ж�ģʽ �½���
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_ClearInterruptMask(dev,0);//���VL53L0X�жϱ�־λ
	 HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	 
	 error://������Ϣ
	 if(status!=VL53L0X_ERROR_NONE)
	 {
		print_pal_error(status);
		return ;
	 }


	 VL53L0X_StartMeasurement(dev);//��������
}


//vl53l0x�жϲ���ģʽ����
//dev:�豸I2C�����ṹ��
//mode:����ģʽ
void vl53l0x_interrupt_test(VL53L0X_Dev_t *dev, u8 mode)
{
	vl53l0x_interrupt_start(dev,mode);
	
	
}

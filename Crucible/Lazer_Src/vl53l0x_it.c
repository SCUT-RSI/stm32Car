#include "vl53l0x_it.h"


//上下限距离值 单位:mm
#define Thresh_Low  60
#define Thresh_High 150
VL53L0X_RangingMeasurementData_t RangingMeasurementData;
//中断模式参数结构体
typedef struct 
{
     const int VL53L0X_Mode;//模式
	 uint32_t ThreshLow;    //下限值
	 uint32_t ThreshHigh;   //上限值
}AlrmMode_t; 

AlrmMode_t AlarmModes ={
	
     VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_OUT,// value < thresh_low OR value > thresh_high
	 Thresh_Low<<16,
	 Thresh_High<<16
};





//外部中断服务函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	VL53L0X_GetRangingMeasurementData(&vl53l0x_dev,&RangingMeasurementData);//获取测量距离
	printf("d: %3d mm\r\n",RangingMeasurementData.RangeMilliMeter);
	HAL_Delay(70);
	VL53L0X_ClearInterruptMask(&vl53l0x_dev,0);//清除VL53L0X中断标志位 
}

extern uint8_t AjustOK;
extern mode_data Mode_data[];

//vl53l0x中断测量模式测试
//dev:设备I2C参数结构体
//mode: 0:默认;1:高精度;2:长距离;3:高速
void vl53l0x_interrupt_start(VL53L0X_Dev_t *dev,uint8_t mode)
{
	 uint8_t VhvSettings;
	 uint8_t PhaseCal;
	 uint32_t refSpadCount;
	 uint8_t isApertureSpads;
	 VL53L0X_Error status=VL53L0X_ERROR_NONE;//工作状态
	 

	 

     vl53l0x_reset(dev);//复位vl53l0x(频繁切换工作模式容易导致采集距离数据不准，需加上这一代码)
		
	 status = VL53L0X_StaticInit(dev);
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 
	 status = VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);//Ref参考校准
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_PerformRefSpadManagement(dev, &refSpadCount, &isApertureSpads);//执行参考SPAD管理
	 if(status!=VL53L0X_ERROR_NONE) goto error;
     HAL_Delay(2);		 
	 status = VL53L0X_SetDeviceMode(dev,VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);//使能连续测量模式
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetInterMeasurementPeriodMilliSeconds(dev,Mode_data[mode].timingBudget);//设置内部周期测量时间
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetLimitCheckEnable(dev,VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,1);//使能SIGMA范围检查
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetLimitCheckEnable(dev,VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,1);//使能信号速率范围检查
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetLimitCheckValue(dev,VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,Mode_data[mode].sigmaLimit);//设定SIGMA范围
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2); 
	 status = VL53L0X_SetLimitCheckValue(dev,VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,Mode_data[mode].signalLimit);//设定信号速率范围范围
	 if(status!=VL53L0X_ERROR_NONE) goto error; 
	 HAL_Delay(2);
	 status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev,Mode_data[mode].timingBudget);//设定完整测距最长时间
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2); 
	 status = VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, Mode_data[mode].preRangeVcselPeriod);//设定VCSEL脉冲周期
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, Mode_data[mode].finalRangeVcselPeriod);//设定VCSEL脉冲周期范围
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_StopMeasurement(dev);//停止测量
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetInterruptThresholds(dev,VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,AlarmModes.ThreshLow, AlarmModes.ThreshHigh);//设定触发中断上、下限值
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_SetGpioConfig(dev,0,VL53L0X_DEVICEMODE_CONTINUOUS_RANGING,AlarmModes.VL53L0X_Mode,VL53L0X_INTERRUPTPOLARITY_LOW);//设定触发中断模式 下降沿
	 if(status!=VL53L0X_ERROR_NONE) goto error;
	 HAL_Delay(2);
	 status = VL53L0X_ClearInterruptMask(dev,0);//清除VL53L0X中断标志位
	 HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	 
	 error://错误信息
	 if(status!=VL53L0X_ERROR_NONE)
	 {
		print_pal_error(status);
		return ;
	 }


	 VL53L0X_StartMeasurement(dev);//启动测量
}


//vl53l0x中断测量模式测试
//dev:设备I2C参数结构体
//mode:测量模式
void vl53l0x_interrupt_test(VL53L0X_Dev_t *dev, u8 mode)
{
	vl53l0x_interrupt_start(dev,mode);
	
	
}

/*
 * PL_sensor.h
 *
 *  Created on: Apr 4, 2023
 *      Author: Ryu
 */

#ifndef INC_PL_SENSOR_H_
#define INC_PL_SENSOR_H_
#include "stm32f4xx_hal.h"
#include "BaseSencing.h"

namespace module
{
	class PL_sensor : public BaseSencing
	{
		uint16_t g_sensor_on[5];
		uint16_t g_sensor_off[5];
		uint16_t g_sensor_now[5];
		uint16_t g_sensor_now_bu[5];
		uint16_t g_sensor_now_diff[5];
		uint16_t g_ADCBuffer[5];
		uint16_t adc_value=0;
		int AD_step=0;


	public:
		void pl_callback_getSensor(void);//dma終了の割り込みで呼ばれる関数(adc.cppで呼ばれる)
		void pl_interupt_getSensor(void);//ADCを開始し、TIM6の割り込みで呼ばれる関数
		void sensor_input();//センサー値をInputDataに入力する関数(TIM6の割り込みで呼ばれる)
	};
}

#endif /* INC_PL_SENSOR_H_ */

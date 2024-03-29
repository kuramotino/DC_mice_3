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
#define DIFF_QUEUE_SIZE 10
#define DIFF_DIAG_QUEUE_SIZE 10

namespace module
{
	class PL_sensor : public BaseSencing
	{
		uint16_t g_sensor_on[5];
		uint16_t g_sensor_off[5];
		uint16_t g_sensor_now[5];
		uint16_t g_sensor_now_bu[5];
		int16_t g_sensor_now_diff[5];
		uint16_t g_ADCBuffer[5];
		uint16_t adc_value=0;
		int logcount=0;
		int AD_step=0;
		float diff_queue_r[DIFF_QUEUE_SIZE];
		float diff_queue_l[DIFF_QUEUE_SIZE];
		float diff_queue_diag_r[DIFF_DIAG_QUEUE_SIZE];
		float diff_queue_diag_l[DIFF_DIAG_QUEUE_SIZE];
		int diff_count_r=0;
		int diff_count_l=0;
		int diff_count_diag_r=0;
		int diff_count_diag_l=0;
	public:
		uint16_t log_sensor_lr[5][1200];
		float log_diff_lr[2][1200];
		float log_diff_diag_lr[2][1200];
		bool log_flag=false;


	public:
		void pl_callback_getSensor(void);//dma終了の割り込みで呼ばれる関数(adc.cppで呼ばれる)
		void pl_interupt_getSensor(void);//ADCを開始し、TIM6の割り込みで呼ばれる関数
		void sensor_input();//センサー値をInputDataに入力する関数(TIM6の割り込みで呼ばれる)
		void setDiffqueue(bool isR,bool isSide);//now_diffをqueueにセットする
		float getDiffqueue(bool isR,bool isSide);//now_diffの積分値を返す関数
	};
}

#endif /* INC_PL_SENSOR_H_ */

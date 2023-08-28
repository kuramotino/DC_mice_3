/*
 * PL_sensor.c
 *
 *  Created on: Apr 4, 2023
 *      Author: Ryu
 */
#include <main.h>
#include "adc.h"
#include "stdio.h"
#include "PL_sensor.h"
#include "math.h"

namespace module
{
	/*DMAがスタートしたら実行するコード*//*******************************************************************/
	void module::PL_sensor::pl_callback_getSensor(void)//dma終了の割り込みで呼ばれる関数(adc.cppで呼ばれる)
	{
		int j;
		//HAL_GPIO_WritePin(ILED5_GPIO_Port,ILED5_Pin,GPIO_PIN_SET);
		HAL_ADC_Stop_DMA(&hadc1);
		switch(AD_step) {
	    	case 0:
	    		g_sensor_off[0] = g_ADCBuffer[0];
	    		g_sensor_off[1] = g_ADCBuffer[1];
	    		g_sensor_off[2] = g_ADCBuffer[2];
	    		g_sensor_off[3] = g_ADCBuffer[3];
	    		g_sensor_off[4] = g_ADCBuffer[4];
	    		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	    		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
	    		for(j = 0; j <= 500; j++) {
	    		}
	    		break;
	    	case 1:
	    		g_sensor_off[0] = g_ADCBuffer[0];
	    		g_sensor_off[1] = g_ADCBuffer[1];
	    		g_sensor_on[2] = g_ADCBuffer[2];
	    		g_sensor_off[3] = g_ADCBuffer[3];
	    		g_sensor_off[4] = g_ADCBuffer[4];
	    		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
				for(j = 0; j <= 500; j++) {
				}
				break;
	    	case 2:
	    		g_sensor_on[0] = g_ADCBuffer[0];
	    		g_sensor_off[1] = g_ADCBuffer[1];
	    		g_sensor_off[2] = g_ADCBuffer[2];
	    		g_sensor_off[3] = g_ADCBuffer[3];
	    		g_sensor_on[4] = g_ADCBuffer[4];
	    		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_SET);
	    		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
				for(j = 0; j <= 500; j++) {
				}
				break;
	    	case 3:
	    		g_sensor_off[0] = g_ADCBuffer[0];
	    		g_sensor_on[1] = g_ADCBuffer[1];
	    		g_sensor_off[2] = g_ADCBuffer[2];
	    		g_sensor_off[3] = g_ADCBuffer[3];
	    		g_sensor_off[4] = g_ADCBuffer[4];
	    		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,GPIO_PIN_SET);
	    		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
	    		for(j = 0; j <= 500; j++) {
	    		}
	    		break;
	    	case 4:
	    		g_sensor_off[0] = g_ADCBuffer[0];
	    		g_sensor_off[1] = g_ADCBuffer[1];
	    		g_sensor_off[2] = g_ADCBuffer[2];
	    		g_sensor_on[3] = g_ADCBuffer[3];
	    		g_sensor_off[4] = g_ADCBuffer[4];
	    		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,GPIO_PIN_RESET);
	    		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
	    		for(j = 0; j <= 500; j++) {
	    		}
	    		break;
		}


		AD_step++;

		if(AD_step!= 5) {
			HAL_ADC_Start_DMA(&hadc1, (uint32_t *)g_ADCBuffer,sizeof(g_ADCBuffer) / sizeof(uint16_t));
		} else{
			AD_step= 0;
		}
	}
	/*******************************************************************/
	/*割り込み用動作関数(センサー取得)(interupt_calSensor)*//*******************************************************************/
	/*センサーの情報を取得する割り込み関数．*//*******************************************************************/
	void module::PL_sensor::pl_interupt_getSensor(void)//ADCを開始し、TIM6の割り込みで呼ばれる関数
	{
		//HAL_GPIO_WritePin(ILED8_GPIO_Port,ILED8_Pin,GPIO_PIN_SET);
	    	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)g_ADCBuffer,sizeof(g_ADCBuffer) / sizeof(uint16_t));
	    	g_sensor_now[0]=g_sensor_on[0]-g_sensor_off[0];
	    	g_sensor_now[1]=g_sensor_on[1]-g_sensor_off[1];
	    	g_sensor_now[2]=g_sensor_on[2]-g_sensor_off[2];
	    	g_sensor_now[3]=g_sensor_on[3]-g_sensor_off[3];
	    	g_sensor_now[4]=g_sensor_on[4]-g_sensor_off[4];

	    	g_sensor_now_diff[0]=g_sensor_now_bu[0]-g_sensor_now[0];
	    	g_sensor_now_diff[1]=g_sensor_now_bu[1]-g_sensor_now[1];
	    	g_sensor_now_diff[2]=g_sensor_now_bu[2]-g_sensor_now[2];
	    	g_sensor_now_diff[3]=g_sensor_now_bu[3]-g_sensor_now[3];
	    	g_sensor_now_diff[4]=g_sensor_now_bu[4]-g_sensor_now[4];

	    	g_sensor_now_bu[0]=g_sensor_now[0];
	    	g_sensor_now_bu[1]=g_sensor_now[1];
	    	g_sensor_now_bu[2]=g_sensor_now[2];
	    	g_sensor_now_bu[3]=g_sensor_now[3];
	    	g_sensor_now_bu[4]=g_sensor_now[4];
	}

	void module::PL_sensor::sensor_input(void)//センサー値をInputDataに入力する関数(TIM6の割り込みで呼ばれる)
	{
		for(int i=0;i<5;i++)
		{
			g_sensor_now[i]=(g_sensor_now[i]>30000) ? 0 : g_sensor_now[i];
			my_input->g_sensor_now[i]=g_sensor_now[i];
			my_input->g_sensor_on[i]=g_sensor_on[i];
			my_input->g_sensor_off[i]=g_sensor_off[i];
			my_input->g_sensor_now_diff[i]=g_sensor_now_diff[i];
		}
		setDiffqueue(true);
		setDiffqueue(false);
		my_input->g_sensor_diff_sum_r=getDiffqueue(true);
		my_input->g_sensor_diff_sum_l=getDiffqueue(false);
		if(logcount<1200 && log_flag)
		{
//			if(logcount%5==0)
//			{
				log_sensor_lr[0][logcount]=g_sensor_now[0];
				log_sensor_lr[1][logcount]=g_sensor_now[1];
				log_sensor_lr[2][logcount]=g_sensor_now[2];
				log_sensor_lr[3][logcount]=g_sensor_now[3];
				log_sensor_lr[4][logcount]=g_sensor_now[4];
				log_diff_lr[0][logcount]=my_input->g_sensor_diff_sum_l;
				log_diff_lr[1][logcount]=my_input->g_sensor_diff_sum_r;
//			}
			logcount++;
		}
	}

	void module::PL_sensor::setDiffqueue(bool isR)//now_diffをqueueにセットする関数
	{
		if(isR)
		{
			if(diff_count_r!=DIFF_QUEUE_SIZE-1)
			{
				diff_queue_r[DIFF_QUEUE_SIZE-1-diff_count_r]=g_sensor_now_diff[4];
				diff_count_r++;
			}
			else
			{
				for(int i=DIFF_QUEUE_SIZE-2;i>=0;i--)
				{
					diff_queue_r[i+1]=diff_queue_r[i];
				}
				diff_queue_r[0]=g_sensor_now_diff[4];
			}
		}
		else
		{
			if(diff_count_l!=DIFF_QUEUE_SIZE-1)
			{
				diff_queue_l[DIFF_QUEUE_SIZE-1-diff_count_l]=g_sensor_now_diff[0];
				diff_count_l++;
			}
			else
			{
				for(int i=DIFF_QUEUE_SIZE-2;i>=0;i--)
				{
					diff_queue_l[i+1]=diff_queue_l[i];
				}
				diff_queue_l[0]=g_sensor_now_diff[0];
			}
		}
	}

	float module::PL_sensor::getDiffqueue(bool isR)//now_diffの積分値を返す関数
	{
		if(isR)
		{
			float sum=0;
			for(int i=0;i<DIFF_QUEUE_SIZE;i++)
			{
				sum+=fabs(diff_queue_r[i]);
			}
			return sum;
		}
		else
		{
			float sum=0;
			for(int i=0;i<DIFF_QUEUE_SIZE;i++)
			{
				sum+=fabs(diff_queue_l[i]);
			}
			return sum;
		}
	}
}

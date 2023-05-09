/*
 * encoder.c
 *
 *  Created on: Mar 27, 2023
 *      Author: Ryu
 */
#include <main.h>
#include "encoder.h"
#include "tim.h"
#include "stm32f4xx_hal.h"
#include "BaseSencing.h"
#include "math.h"

namespace module
{
	void module::Enc::pl_encoder_init(void){
		HAL_TIM_Base_Start_IT(&htim1);//1エンコーダーR
		HAL_TIM_Base_Start_IT(&htim8);//2エンコーダーL

		HAL_TIM_Encoder_MspInit(&htim1);//1エンコーダーR
		HAL_TIM_Encoder_MspInit(&htim8);//2エンコーダーL

		HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
		HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);
	}

	int16_t module::Enc::pl_count_encoderR(void) {
		int16_t count = 0;
		uint16_t enc_count = TIM1->CNT;
		TIM1->CNT = 0;

		if (enc_count > 32767) {
			count = (int16_t) enc_count;
		} else {
			count = (int16_t) enc_count;
		}

		return count;
	}

	int16_t module::Enc::pl_count_encoderL(void) {
		int16_t count = 0;
		uint16_t enc_count = TIM8->CNT;
		TIM8->CNT = 0;

		if (enc_count > 32767) {
			count = -(int16_t) enc_count;
		} else {
			count = -(int16_t) enc_count;
		}

		return count;
	}

	void module::Enc::sensor_input()//機体の速度を計算してInputDataに入力する
	{
		enc_count_r=pl_count_encoderR();
		enc_count_l=pl_count_encoderL();
		sum_enc_r+=enc_count_r;
		sum_enc_l+=enc_count_l;
		enc_v_R=(float)enc_count_r*180/72896/0.001;//2*PI*TaiyaDirmeterをかける71896
		enc_v_L=(float)enc_count_l*180/71673/0.001;//2*PI*TaiayDirmeterをかける70673
		v_encoder=fabs((enc_v_R+enc_v_L)/2);//1重心の速度を求める

		my_input->v_encoder=v_encoder;
		my_input->enc_v_L=enc_v_L;
		my_input->enc_v_R=enc_v_R;
		my_input->enc_v_L_sum=sum_enc_l;
		my_input->enc_v_R_sum=sum_enc_r;
		my_input->enc_L_sum+=(int)enc_count_l;
		my_input->enc_R_sum+=(int)enc_count_r;
	}
}


/*
 * encoder.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Ryu
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f4xx_hal.h"
#include "BaseSencing.h"

namespace module
{
	class Enc : public BaseSencing
	{
		int16_t sum_enc_r=0;//1右エンコーダの合計カウント数
		int16_t sum_enc_l=0;//1左エンコーダの合計カウント数
		int16_t enc_count_r=0;//1右エンコーダのカウント数
		int16_t enc_count_l=0;//1左エンコーダのカウント数
		float v_encoder;//エンコーダから取得した機体の速度
		float enc_v_R;//エンコーダから取得した右タイヤの速度
		float enc_v_L;//エンコーダから取得した左タイヤの速度

	public:
		void pl_encoder_init();//encoderの初期設定
		int16_t pl_count_encoderR(void);//右のエンコーダのカウント読み取り
		int16_t pl_count_encoderL(void);//左のエンコーダのカウント読み取り
		void sensor_input();//センサー値をInputDataに入力する関数
	};
}

#endif /* INC_ENCODER_H_ */

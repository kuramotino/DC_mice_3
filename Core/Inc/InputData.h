/*
 * InputData.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */

#ifndef INC_INPUTDATA_H_
#define INC_INPUTDATA_H_
#include "stdio.h"

namespace controll
{
	class InputData
	{
	public:
		float v_encoder;//エンコーダから取得した機体の速度
		float enc_v_R;//エンコーダから取得した右タイヤの速度
		float enc_v_L;//エンコーダから取得した左タイヤの速度
		int16_t enc_v_R_sum;//右エンコーダの合計値
		int16_t enc_v_L_sum;//左エンコーダの合計値
		float x_ac_gyro;//x軸の加速度
		float y_ac_gyro;//y軸の加速度
		int enc_R_sum;//右エンコーダの合計値
		int enc_L_sum;//左エンコーダの合計値
		float omega_gyro;//ジャイロから取得した機体の角速度
		uint16_t g_sensor_on[5];//1点灯時の光センサーのAD値
		uint16_t g_sensor_off[5];//2消灯時の光センサーのAD値
		uint16_t g_sensor_now[5];//3現在の光センサーのAD値
		uint16_t g_sensor_now_diff[5];//4現在の光センサーのAD値変化(前-後)
		uint16_t LEFT_SLESHOLD=120;//1左壁のセンサー閾値
		uint16_t FRONT_SLESHOLD=100;//2前壁のセンサー閾値
		uint16_t RIGHT_SLESHOLD=60;//3右壁のセンサー閾値
	};
}


#endif /* INC_INPUTDATA_H_ */

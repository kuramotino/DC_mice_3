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
		float deg_gyro=0;//gyroから取得した機体の角度
		uint8_t who_am_i;
		uint16_t g_sensor_on[5];//1点灯時の光センサーのAD値
		uint16_t g_sensor_off[5];//2消灯時の光センサーのAD値
		uint16_t g_sensor_now[5];//3現在の光センサーのAD値
		int16_t g_sensor_now_diff[5];//4現在の光センサーのAD値変化(前-後)
		float g_sensor_diff_sum_r;//5現在のセンサー4の変化量の積分値
		float g_sensor_diff_sum_l;//6現在のセンサー0の変化量の積分値
		float g_sensor_diff_sum_diag_r;//7現在のセンサー3の変化量の積分値
		float g_sensor_diff_sum_diag_l;//8現在のセンサー1の変化量の積分値
		uint16_t LEFT_SLESHOLD=120;//1左壁のセンサー閾値
		uint16_t FRONT_SLESHOLD=50;//2前壁のセンサー閾値/80
		uint16_t RIGHT_SLESHOLD=80;//3右壁のセンサー閾値
		uint16_t LEFT_SIDE_SLESHOLD=400;//4左側面のセンサー閾値
		uint16_t RIGHT_SIDE_SLESHOLD=300;//5右側面のセンサー閾値
	};
}


#endif /* INC_INPUTDATA_H_ */

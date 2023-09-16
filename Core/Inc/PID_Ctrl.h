/*
 * PID_Ctrl.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */

#ifndef INC_PID_CTRL_H_
#define INC_PID_CTRL_H_
#include "BaseCtrl.h"

namespace controll
{
	class PID_Ctrl : public BaseCtrl
	{
		float fb_stra;
		float fb_turn;
		float v_encoder;//エンコーダから求めた速度
		float omega_gyro;//ジャイロから求めた角速度
		float now_v;//kasokuから得た速度
		float now_omega;//kasokuから得た角速度

		float enc_error;//エンコーダの差分
		float enc_sigma_error;//エンコーダの差分の和
		float enc_old_error;//前回のエンコーダの差分
		float enc_delta_error;//前回と今回のerrorの差分

		float gy_error;//ジャイロの差分
		float gy_sigma_error;//ジャイロの差分の和
		float gy_old_error;//前回のジャイロの差分
		float gy_delta_error;//前回と今回のerrorの差分

		float gy_wall_pid;//角速度に入れる壁制御量
		float gy_diagwall_pid=0;//角速度に入れる壁制御量

		float V_bat=8.4;//8.4V:電源電圧

		float Ksp=40;//1直進時の直進成分のPゲイン15
		float Ksi=0.5;//1直進時の直進成分のIゲイン1
		float Ksd=0;//1直進時の直進成分のDゲイン0
		float K_st_tu_p=15;//1直進時の回転成分のPゲイン15
		float K_st_tu_i=0.01;//1直進時の回転成分のIゲイン1
		float K_st_tu_d=0;//1直進時の回転成分のDゲイン0

		float Ktp=15;//2回転時の回転成分のPゲイン17//10/10/15/10
		float Kti=0.01;//2回転時の回転成分のIゲイン0.45//2/3/0.55/0.1
		float Ktd=0;//2回転時の回転成分のDゲイン112//50/45/0/0
		float K_tu_st_p=40;//1回転時の直進成分のPゲイン5/15
		float K_tu_st_i=0.5;//1回転時の直進成分のIゲイン0.05/1
		float K_tu_st_d=-20;//1回転時の直進成分のDゲイン/30

		float K_tu_senkai_p=15;//2超信地旋回時の回転成分のPゲイン17/5/12.5
		float K_tu_senkai_i=0.0;//2超信地旋回時の回転成分のIゲイン2/0.09/0.05
		float K_tu_senkai_d=0;//2超信地旋回時の回転成分のDゲイン0.25/0/0.25
		float K_senkai_p=15;//1超信地旋回時の直進成分のPゲイン5
		float K_senkai_i=1;//1超信地旋回時の直進成分のIゲイン0.1
		float K_senkai_d=0;//1超信地旋回時の直進成分のDゲイン0


	public:
		float log_enc[1200];
		float log_enc_r[1200];
		float log_enc_l[1200];
		float log_gyro[1200];
		int log_count=0;

	public:
		void transmit_PID();//pwmに求めたpid値を送る関数
		void get_enc_gyro();//kasokuとinputdataから速度、角速度、計算した速度を取得する
		void PID();//PID値を計算する
		void updata(Command cm);//overrideする
		void receive(float message);//壁制御の角速度を取得する、Wall_Controllから呼ばれる
		void transmit(float message);//壁制御の角速度を取得する、Diag_Wall_Controllから呼ばれる
	};
}

#endif /* INC_PID_CTRL_H_ */

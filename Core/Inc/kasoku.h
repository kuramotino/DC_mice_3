/*
 * kasoku.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */

#ifndef INC_KASOKU_H_
#define INC_KASOKU_H_
#include "BaseCommand.h"
#include "PWM_Output.h"

namespace controll
{


	class kasoku
	{
		bool isKasokuEnd=true;//加速が終わったかどうか
		bool isBreak=false;//breakをかけるか
		enum now_v_status v_status;//現在の速度の状態

		float now_x=0;//現在の位置
		float dt=0.001;//刻み時間1ms
		float target_a;//加速度
		float target_v_start;//初速度
		float now_v=0;//現在の速度
		float target_v_max;//最大速度
		float target_v_end;//終端速度
		float pre_target_v_end;//前回の終端速度
		float target_x;//目標距離
		float xde;//減速距離
		float axde;//加速距離

		Command now_cm;//現在のコマンド
		PWM_Out* my_pwm;//pwmのオブジェクト

		float add_back_offset=0;//1後距離の補正量
		float break_wall_offset=0;//2壁切れ後の距離

	public:
		float now_v_log[1200];
		float now_x_log[1200];
		int log_count=0;


	public:
		kasoku();//kasokuクラスのコンストラクタ
		void set_kasoku();//台形加速に必要なパラメータを設定する関数
		void daikei();//台形加速を行う関数
		void add_pwm(PWM_Out* pwm);//pwm_outオブジェクトを登録する
		void updata(Command cm);//コマンドを更新する(CommandExecuterに呼ばれる)
		void transmit_pwm();//pwm_outに計算した速度と位置とフラグを送る関数
		float show_v();//now_vを返す関数(PID_Ctrlに呼ばれる)
		float show_x();//now_xを返す関数(PID_Ctrlに呼ばれる)
		void Receive_Back_Offset(float bu_offset);//BackOffsetをセットする関数(Back_Offset_Ctrlに呼ばれる)
		void Receive_Wall_Break_Offset(float bu_offset);//Wall_Break_Offsetをセットする関数(Break_Wall_Ctrlに呼ばれる)
		void Set_Pre_v();//Pre_vをセットする関数(Break_Wall_Ctrlに呼ばれる)
		bool Ret_KasokuEnd();//kasokuEndを返す関数(Break_Wall_Ctrlに呼ばれる)
	};
}


#endif /* INC_KASOKU_H_ */

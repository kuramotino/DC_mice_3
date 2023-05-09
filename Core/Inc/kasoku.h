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

		float now_x=0;//現在の位置
		float dt=0.001;//刻み時間1ms
		float target_a;//加速度
		float target_v_start;//初速度
		float now_v=0;//現在の速度
		float target_v_max;//最大速度
		float target_v_end;//終端速度
		float target_x;//目標距離
		float xde;//減速距離

		Command now_cm;//現在のコマンド
		PWM_Out* my_pwm;//pwmのオブジェクト

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
	};
}


#endif /* INC_KASOKU_H_ */

/*
 * kasoku.cpp
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */
#include "kasoku.h"
#include "BaseCommand.h"
#include "PWM_Output.h"

namespace controll
{
	controll::kasoku::kasoku(void)//kasokuclassのコンストラクタ
	{
		isKasokuEnd=true;
		dt=0.001;
		now_x=0;
		now_v=0;
	}

	void controll::kasoku::set_kasoku()//台形加速をスタートさせる関数
	{
		v_status=accel;
		isKasokuEnd=false;
		now_x=0;
		target_a=now_cm.bu_tar_a;//加速度
		target_v_start=now_cm.bu_tar_v_start;//初速度
		now_v=target_v_start;
		target_v_max=now_cm.bu_tar_v_max;//最大速度
		target_v_end=now_cm.bu_tar_v_end;//終端速度
		target_x=(now_cm.isSetBackOffset) ? now_cm.bu_tar_x+add_back_offset : now_cm.bu_tar_x;//目標距離
		add_back_offset=(target_x!=now_cm.bu_tar_x) ? 0 : add_back_offset;//もし使ったら後距離の補正量をリセット
		target_x=(now_cm.isBreakWallStra)?break_wall_offset:target_x;//壁切れ後の直進なら距離を変更
		break_wall_offset=(now_cm.isBreakWallStra && target_x!=now_cm.bu_tar_x) ? 0 : break_wall_offset;//もし使ったなら壁切れ後の距離をリセット
		xde=(target_v_max*target_v_max-target_v_end*target_v_end)/(2*target_a);//減速距離の計算
	}

	void controll::kasoku::daikei()//台形加速を行う
	{
		if(isKasokuEnd==false)
		{
			if(now_v<target_v_max&&target_x-now_x>xde)//1加速区間
			{
				now_x+=now_v*dt;
				now_v+=target_a*dt;
				now_v=(now_v>target_v_max) ? target_v_max : now_v;
				v_status=accel;
			}
			else if(target_x-now_x>xde)//2定速区間
			{
				now_x+=now_v*dt;
				v_status=constant;
			}
			else if(now_v>target_v_end)//3減速区間
			{
				now_x+=now_v*dt;
				now_v-=target_a*dt;
				v_status=deceleration;
			}
			else
			{
				isKasokuEnd=true;
				if(now_v<=0)
				{
					isBreak=true;
				}
				else
				{
					isBreak=false;
				}
			}

		if(log_count!=1200)
			{
				now_v_log[log_count]=now_v;
				now_x_log[log_count]=now_x;
				log_count++;
			}
		}
	}

	void controll::kasoku::add_pwm(PWM_Out* pwm)//pwm_outオブジェクトを登録する
	{
		my_pwm=pwm;
	}

	void controll::kasoku::updata(Command cm)//コマンドを更新する(CommandExecuterに呼ばれる)
	{
		now_cm=cm;
		isKasokuEnd=now_cm.isStop;
		if(isKasokuEnd==false)
		{
			set_kasoku();
		}
	}

	void controll::kasoku::transmit_pwm()//pwm_outに計算した速度と位置をと加速が終了したかどうかのフラグを送る関数
	{
			my_pwm->updata_x_v(now_x, now_v,isKasokuEnd,isBreak,v_status);
	}

	float controll::kasoku::show_v()//now_vを返す関数(PID_Ctrlに呼ばれる)
	{
		return now_v;
	}

	float controll::kasoku::show_x()//now_xを返す関数(PID_Ctrlに呼ばれる)
	{
		return now_x;
	}

	void controll::kasoku::Receive_Back_Offset(float bu_offset)//BackOffsetをセットする関数(Back_Offset_Ctrlに呼ばれる)
	{
		add_back_offset=bu_offset;
	}

	void controll::kasoku::Receive_Wall_Break_Offset(float bu_offset)//Wall_Break_Offsetをセットする関数(Break_Wall_Ctrlに呼ばれる)
	{
		break_wall_offset=bu_offset;
	}

}


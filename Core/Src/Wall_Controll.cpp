/*
 * Wall_Controll.cpp
 *
 *  Created on: 2023/05/03
 *      Author: Ryu
 */
#include "Wall_Controll.h"

namespace controll
{
	void controll::Wall_Ctrl::updata(Command cm)//overrideする
	{
		now_cm=cm;
		isStop=(now_cm.isWall_PID_Stop || now_cm.isStop);
	}

	void controll::Wall_Ctrl::transmit_Wall_PID()//壁制御の制御量を求めpid_ctrlに送信する関数(TIM6割り込みで呼ばれる)
	{
		if(isStop==false)
		{
		//bitの決定
			if((g_WallControllStatus & 0b10) == 0b10)//1前回左壁あり(1bit目が1)
			{
				if(my_input->g_sensor_now[1]<THRESHOLD_L || my_input->g_sensor_now_diff[1]>THRESHOLD_DIFF_L)//今回左壁がなし
				{
					g_WallControllStatus=g_WallControllStatus & 0b01;//1bit目を0にする
				}
			}
			else//2前回左壁なし(1bit目が0)
			{
				if(my_input->g_sensor_now[1]>THRESHOLD_L && my_input->g_sensor_now_diff[1]<THRESHOLD_DIFF_L)//今回左壁あり
				{
					//g_WallControllStatus=g_WallControllStatus | 0b10;//1bit目を1にする
					wall_ctrl_counter[0]++;
				}
				else
				{
					wall_ctrl_counter[0]=0;
				}

				if(wall_ctrl_counter[0]>wall_ctrl_count[0])
				{
					g_WallControllStatus=g_WallControllStatus | 0b10;//1bit目を1にする
					wall_ctrl_counter[0]=0;
				}

			}
			if((g_WallControllStatus & 0b01) == 0b01)//3前回右壁あり(2bit目が1)
			{
				if(my_input->g_sensor_now[3]<THRESHOLD_R || my_input->g_sensor_now_diff[3]>THRESHOLD_DIFF_R)//今回右壁なし
				{
					g_WallControllStatus=g_WallControllStatus & 0b10;//2bit目を0にする
				}
			}
			else//4前回右壁なし(2bit目が0)
			{
				if(my_input->g_sensor_now[3]>THRESHOLD_R && my_input->g_sensor_now_diff[3]<THRESHOLD_DIFF_R)//今回右壁あり
				{
					//g_WallControllStatus=g_WallControllStatus | 0b01;//2bit目を1にする
					wall_ctrl_counter[1]++;
				}
				else
				{
					wall_ctrl_counter[1]=0;
				}

				if(wall_ctrl_counter[1]>wall_ctrl_count[1])
				{
					g_WallControllStatus=g_WallControllStatus | 0b01;//2bit目を1にする
					wall_ctrl_counter[1]=0;
				}

			}

		//2制御量の決定
			float r_diff=((float)(my_input->g_sensor_now[3])-CENTER_R);
			float l_diff=((float)(my_input->g_sensor_now[1])-CENTER_L);

			if((g_WallControllStatus | 0b01) == 0b01)//1左壁なし
			{
				if((g_WallControllStatus | 0b10) == 0b10)//1右壁なし
				{
					//1両壁なし
					PID_Wall=0.0;
				}
				else//2右壁あり
				{
					//2左壁なし
					PID_Wall=my_input->v_encoder/500*R_SENSOR_GAIN*2*r_diff;
				}
			}
			else//2左壁あり
			{
				if((g_WallControllStatus | 0b10) == 0b10)//1右壁なし
				{
					//3右壁なし
					if(l_diff>3000)
					{
						PID_Wall=my_input->v_encoder/500*L_SENSOR_GAIN*-2*0;
					}
					else
					{
						PID_Wall=my_input->v_encoder/500*L_SENSOR_GAIN*-2*l_diff;
					}
				}
				else//2右壁あり
				{
					//4両壁あり
					if(l_diff>3000)
					{
						PID_Wall=my_input->v_encoder/500*(L_SENSOR_GAIN*-1*0+(R_SENSOR_GAIN)*r_diff);
					}
					else
					{
						PID_Wall=my_input->v_encoder/500*(L_SENSOR_GAIN*-1*l_diff+R_SENSOR_GAIN*r_diff);
					}
				}
			}

			transmit(PID_Wall);//pidに制御量を送信する
		}
	}

	void controll::Wall_Ctrl::SetPIDCtrl(BaseCtrl* pid)
	{
		pid_ctrl=pid;
	}

	void controll::Wall_Ctrl::receive(float message)
	{

	}

	void controll::Wall_Ctrl::transmit(float message)//PID_Ctrlに壁制御量を送信する
	{
		pid_ctrl->receive(message);
	}
}


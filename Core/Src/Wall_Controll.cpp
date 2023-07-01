/*
 * Wall_Controll.cpp
 *
 *  Created on: 2023/05/03
 *      Author: Ryu
 */
#include "Wall_Controll.h"
#include "math.h"

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
			setDiffqueue(true);
			setDiffqueue(false);
			float r_diff_sum=getDiffqueue(true);
			float l_diff_sum=getDiffqueue(false);
		//bitの決定
			if((g_WallControllStatus & 0b10) == 0b10)//1前回左壁あり(1bit目が1)
			{
				if(my_input->g_sensor_now[1]<THRESHOLD_L || fabs(l_diff_sum)>THRESHOLD_DIFF_L)//今回左壁がなし
				{
					g_WallControllStatus=g_WallControllStatus & 0b01;//1bit目を0にする
				}
			}
			else//2前回左壁なし(1bit目が0)
			{
				if(my_input->g_sensor_now[1]>THRESHOLD_L && fabs(l_diff_sum)<THRESHOLD_DIFF_L)//今回左壁あり
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
				if(my_input->g_sensor_now[3]<THRESHOLD_R || fabs(r_diff_sum)>THRESHOLD_DIFF_R)//今回右壁なし
				{
					g_WallControllStatus=g_WallControllStatus & 0b10;//2bit目を0にする
				}
			}
			else//4前回右壁なし(2bit目が0)
			{
				if(my_input->g_sensor_now[3]>THRESHOLD_R && fabs(r_diff_sum)<THRESHOLD_DIFF_R)//今回右壁あり
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
//			float r_diff=((float)(my_input->g_sensor_now[3])-CENTER_R);
//			float l_diff=((float)(my_input->g_sensor_now[1])-CENTER_L);
			float r_diff=(-1*(float)ADtoMeter(my_input->g_sensor_now[3],true)+(float)ADtoMeter(CENTER_R,true));
			float l_diff=(-1*ADtoMeter(my_input->g_sensor_now[1],false)+ADtoMeter(CENTER_L,false));

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
//					if(l_diff>80)
//					{
//						PID_Wall=my_input->v_encoder/500*L_SENSOR_GAIN*-2*10;
//					}
//					else
//					{
						PID_Wall=my_input->v_encoder/500*L_SENSOR_GAIN*-2*l_diff;
//					}
				}
				else//2右壁あり
				{
					//4両壁あり
//					if(l_diff>80)
//					{
//						PID_Wall=my_input->v_encoder/500*(L_SENSOR_GAIN*-1*10+(R_SENSOR_GAIN)*r_diff);
//					}
//					else
//					{
						PID_Wall=my_input->v_encoder/500*(L_SENSOR_GAIN*-1*l_diff+R_SENSOR_GAIN*r_diff);
//					}
				}
			}

			transmit(PID_Wall);//pidに制御量を送信する

			if(wall_counter<1200 && wall_log_flag)
			{
				wall_ctrl_log[wall_counter]=g_WallControllStatus;
				wall_r_diff[wall_counter]=my_input->g_sensor_now_diff[3];
				wall_l_diff[wall_counter]=my_input->g_sensor_now_diff[1];
				wall_r_meter[wall_counter]=r_diff;
				wall_l_meter[wall_counter]=l_diff;
				wall_counter++;
			}
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

	float controll::Wall_Ctrl::ADtoMeter(float ad,bool isR)//距離変換を行う関数
	{
		if(!isR)
		{
			//1左壁ありの時
			float dif=CENTER_L-ABS_CENTER_L;
			float adc=(float)(ad)+dif;

			//2左壁との距離を計算
			float len=Side_L_ADtoX[0]+Side_L_ADtoX[1]*adc+Side_L_ADtoX[2]*adc*adc+Side_L_ADtoX[3]*adc*adc*adc+Side_L_ADtoX[4]*adc*adc*adc*adc;
			len=(adc>520) ? -1*len : len;
			return len;
		}
		else if(isR)
		{
			//1右壁ありの時
			float dif=CENTER_R-ABS_CENTER_R;
			float adc=(float)(ad)+dif;

			//2右壁との距離を計算
			float len=Side_R_ADtoX[0]+Side_R_ADtoX[1]*adc+Side_R_ADtoX[2]*adc*adc+Side_R_ADtoX[3]*adc*adc*adc+Side_R_ADtoX[4]*adc*adc*adc*adc;
			return len;
		}
	}

	void controll::Wall_Ctrl::setDiffqueue(bool isR)//now_diffをqueueにセットする関数
	{
		if(isR)
		{
			if(diff_count_r!=DIFF_QUEUE_SIZE-1)
			{
				diff_queue_r[DIFF_QUEUE_SIZE-1-diff_count_r]=my_input->g_sensor_now_diff[3];
				diff_count_r++;
			}
			else
			{
				for(int i=DIFF_QUEUE_SIZE-2;i>=0;i--)
				{
					diff_queue_r[i+1]=diff_queue_r[i];
				}
				diff_queue_r[0]=my_input->g_sensor_now_diff[3];
			}
		}
		else
		{
			if(diff_count_l!=DIFF_QUEUE_SIZE-1)
			{
				diff_queue_l[DIFF_QUEUE_SIZE-1-diff_count_l]=my_input->g_sensor_now_diff[1];
				diff_count_l++;
			}
			else
			{
				for(int i=DIFF_QUEUE_SIZE-2;i>=0;i--)
				{
					diff_queue_l[i+1]=diff_queue_l[i];
				}
				diff_queue_l[0]=my_input->g_sensor_now_diff[1];
			}
		}
	}

	float controll::Wall_Ctrl::getDiffqueue(bool isR)//now_diffの積分値を返す関数
	{
		if(isR)
		{
			float sum=0;
			for(int i=0;i<DIFF_QUEUE_SIZE;i++)
			{
				sum+=diff_queue_r[i];
			}
			return sum;
		}
		else
		{
			float sum=0;
			for(int i=0;i<DIFF_QUEUE_SIZE;i++)
			{
				sum+=diff_queue_l[i];
			}
			return sum;
		}
	}
}


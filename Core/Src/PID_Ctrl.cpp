/*
 * PID_Ctrl.cpp
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */
#include "PID_Ctrl.h"
#include "math.h"

namespace controll
{
	void controll::PID_Ctrl::transmit_PID()
	{
		if(isStop==false)
		{
			my_pwm->updata_PID(fb_stra, fb_turn);
		}
	}

	void controll::PID_Ctrl::get_enc_gyro()
	{
		omega_gyro=my_input->omega_gyro;
		//omega_gyro=omega_gyro*(3.14/180);//degからradに変換
		v_encoder=my_input->v_encoder;
		if(now_cm.isSenkai==true)
		{
			v_encoder=(my_input->enc_v_R+my_input->enc_v_L)/2;
		}

		if(now_cm.isTurn==true)
		{
			now_v=now_cm.gv;
			now_omega=my_kasoku->show_v();
		}
		else
		{
			now_v=my_kasoku->show_v();
			now_omega=0;
		}
	}

	void controll::PID_Ctrl::PID()
	{
		if(isStop==false)
		{
			get_enc_gyro();
			float ccw=1;
			if(now_cm.MoveVec==true)//前進、左回転の時
			{
				ccw=1;
			}
			else//後進、右回転の時
			{
				ccw=-1;
			}

			if(now_cm.isTurn==false)
			{
				enc_error=now_v-v_encoder;
				enc_delta_error=enc_error-enc_old_error;
				enc_old_error=enc_error;
				enc_sigma_error+=enc_error;
				fb_stra=1/V_bat/(10*10*10)*(Ksp*enc_error+Ksi*enc_sigma_error+Ksd*enc_delta_error);

				gy_error=now_omega-ccw*omega_gyro;
				gy_delta_error=gy_error-gy_old_error;
				gy_old_error=gy_error;
				gy_sigma_error+=gy_error;
				fb_turn=1/V_bat/(10*10*10)*(K_st_tu_p*gy_error+K_st_tu_i*gy_sigma_error+K_st_tu_d*gy_delta_error);
			}
			else
			{
				if(now_cm.isSenkai==true)
				{
					if(my_input->enc_v_R>my_input->enc_v_L)//右回転
					{
						enc_error=-1*(my_input->enc_v_R+my_input->enc_v_L);
						enc_delta_error=enc_error-enc_old_error;
						enc_old_error=enc_error;
						enc_sigma_error+=enc_error;
						fb_stra=1/V_bat/(10*10*10)*(K_senkai_p*enc_error+K_senkai_i*enc_sigma_error+K_senkai_d*enc_delta_error);
					}
					else//左回転
					{
						enc_error=-1*(my_input->enc_v_R+my_input->enc_v_L);
						enc_delta_error=enc_error-enc_old_error;
						enc_old_error=enc_error;
						enc_sigma_error+=enc_error;
						fb_stra=1/V_bat/(10*10*10)*(K_senkai_p*enc_error+K_senkai_i*enc_sigma_error+K_senkai_d*enc_delta_error);
					}
				}
				else
				{
					enc_error=now_v-v_encoder;
					enc_delta_error=enc_error-enc_old_error;
					enc_old_error=enc_error;
					enc_sigma_error+=enc_error;
					fb_stra=1/V_bat/(10*10*10)*(K_tu_st_p*enc_error+K_tu_st_i*enc_sigma_error+K_tu_st_d*enc_delta_error);
				}

				gy_error=now_omega-ccw*omega_gyro;
				gy_delta_error=gy_error-gy_old_error;
				gy_old_error=gy_error;
				gy_sigma_error+=gy_error;
				fb_turn=1/V_bat/(10*10*10)*(Ktp*gy_error+Kti*gy_sigma_error+Ktd*gy_delta_error);
			}

			if(log_count!=1200)
			{
				log_enc[log_count]=my_input->v_encoder;
				log_gyro[log_count]=omega_gyro;
				log_count++;
			}

			transmit_PID();//後で必ず戻す事!
		}
	}

	void controll::PID_Ctrl::updata(Command cm)//overrideする
	{
		now_cm=cm;
		isStop=(now_cm.isPID_Stop || now_cm.isStop);
		//if(now_cm.isFailStop || now_cm.isBreakStop)
		//{
			enc_old_error=0;
			enc_sigma_error=0;
			gy_old_error=0;
			gy_sigma_error=0;
		//}
	}
}


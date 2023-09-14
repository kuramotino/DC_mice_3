/*
 * FailSafe.cpp
 *
 *  Created on: 2023/04/27
 *      Author: Ryu
 */
#include "FailSafe.h"
#include "math.h"
#include "Init_Controll_Objs.h"

namespace controll
{
	void controll::FailSafe::FailStop()//速度、角速度を監視し、FailSafeをかける関数
	{
//		if(!now_cm.isTurn)
//		{
//			v_logical=(fabs(my_input->v_encoder>-my_kasoku->show_v())>threshold_v);
//		}
//		else
//		{
//			v_logical=(fabs(fabs(my_input->omega_gyro)>-my_kasoku->show_v())>threshold_omega);
//		}

		accel_logical_y=(my_input->y_ac_gyro<threshold_accel_y);
		//enc_logical=(fabs((my_input->enc_v_R-my_input->enc_v_L))>threshold_enc);
		if(!now_cm.isTurn && !now_cm.MoveVec)
		{
			accel_logical_y=false;
		}
		who_logical=(my_input->who_am_i!=0x98)?true:false;
		//zero_gyro_logical=(my_input->omega_gyro==0)?true:false;

		if(v_logical||accel_logical_y||enc_logical||who_logical)
		{
			status_off(Abnormal_End);
			led_obj.set_all_led(0b111111111);
			isFail=true;
		}
	}
}


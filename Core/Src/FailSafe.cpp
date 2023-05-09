/*
 * FailSafe.cpp
 *
 *  Created on: 2023/04/27
 *      Author: Ryu
 */
#include "FailSafe.h"

namespace controll
{
	void controll::FailSafe::FailStop()//速度、角速度を監視し、FailSafeをかける関数
	{
		if((my_input->v_encoder>threshold_v || my_input->v_encoder<-1*threshold_v) || (my_input->omega_gyro>threshold_omega || my_input->omega_gyro<-1*threshold_omega))
		{
			status_off(Abnormal_End);
		}
	}
}


/*
 * Break_Wall_Ctrl.cpp
 *
 *  Created on: 2023/07/08
 *      Author: Ryu
 */
#include "Break_Wall_Ctrl.h"
#include "math.h"

namespace controll
{
	void controll::Break_Wall_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isBreakWall) || now_cm.isStop);
		isRWall=(my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD)?true:false;
		isLWall=(my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD)?true:false;
	}

	void controll::Break_Wall_Ctrl::BreakWall()
	{

		if(isStop==false && isLWall)
		{
			if(my_input->g_sensor_now[1]<my_input->LEFT_SLESHOLD)
			{
				my_kasoku->Receive_Wall_Break_Offset(l_offset);
				status_off(Forced_End);
			}
		}
		else if(isStop==false && isRWall)
		{
			if(my_input->g_sensor_now[3]<my_input->RIGHT_SLESHOLD)
			{
				my_kasoku->Receive_Wall_Break_Offset(r_offset);
				 status_off(Forced_End);
			}
		}
	}
}


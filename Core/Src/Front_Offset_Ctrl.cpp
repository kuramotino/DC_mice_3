/*
 * Front_Offset_Ctrl.cpp
 *
 *  Created on: 2023/06/19
 *      Author: Ryu
 */
#include "Front_Offset_Ctrl.h"
#include "math.h"

namespace controll
{
	void controll::Front_Offset_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isFrontOffset) || now_cm.isStop);
		offset_x=now_cm.offset_x;
	}

	void controll::Front_Offset_Ctrl::BreakFrontOffset()
	{
		if(isStop==false && my_input->g_sensor_now[2]>my_input->FRONT_SLESHOLD)
		{
			if(my_input->g_sensor_now[2]>turn_start_ad)
			{
				sub_back_offset_ctrl=(my_kasoku->show_x()<offset_x)?-1*fabs(offset_x-my_kasoku->show_x()):0;
				transmit(sub_back_offset_ctrl);
				status_off(Forced_End);
			}
		}
		else if(isStop==false)
		{
			if(my_kasoku->show_x()>offset_x)
			{
				transmit(0);
				status_off(Forced_End);
			}
		}
	}

	void controll::Front_Offset_Ctrl::transmit(float message)
	{
		my_back->receive(message);
	}

	void controll::Front_Offset_Ctrl::SetBackOffset(BaseCtrl* back_obj)
	{
		my_back=back_obj;
	}
}


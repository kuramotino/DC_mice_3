/*
 * Senkai_Offset_Ctrl.cpp
 *
 *  Created on: 2023/07/08
 *      Author: Ryu
 */
#include "Senkai_Offset_Ctrl.h"
#include "math.h"

namespace controll
{
	void controll::Senkai_Offset_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isSenkaiOffset) || now_cm.isStop);
	}

	void controll::Senkai_Offset_Ctrl::BreakFrontOffset()
	{
		if(isStop==false && my_input->g_sensor_now[2]>my_input->FRONT_SLESHOLD)
		{
			if(my_input->g_sensor_now[2]>turn_start_ad)
			{
//				sub_back_offset_ctrl=(my_kasoku->show_x()<10)?-1*fabs(10-my_kasoku->show_x()):0;
//				transmit(sub_back_offset_ctrl);
				status_off(Forced_End);
			}
		}
		else if(isStop==false)
		{
			if(my_kasoku->show_x()>offset_x)
			{
				//transmit(0);
				status_off(Forced_End);
			}
		}
	}

	void controll::Senkai_Offset_Ctrl::transmit(float message)
	{
		my_back->receive(message);
	}

	void controll::Senkai_Offset_Ctrl::SetBackOffset(BaseCtrl* back_obj)
	{
		my_back=back_obj;
	}
}




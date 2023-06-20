/*
 * Front_Offset_Ctrl.cpp
 *
 *  Created on: 2023/06/19
 *      Author: Ryu
 */
#include "Front_Offset_Ctrl.h"

namespace controll
{
	void controll::Front_Offset_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isFrontOffset) || now_cm.isStop);
	}

	void controll::Front_Offset_Ctrl::BreakFrontOffset()
	{
		if(isStop==false && my_input->g_sensor_now[2]>my_input->FRONT_SLESHOLD)
		{
			if(my_input->g_sensor_now[2]>turn_start_ad)
			{
				status_off(Forced_End);
			}
		}
		else if(isStop==false)
		{
			if(my_kasoku->show_x()>10)
			{
				status_off(Forced_End);
			}
		}
	}
}


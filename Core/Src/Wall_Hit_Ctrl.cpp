/*
 * Wall_Hit_Ctrl.cpp
 *
 *  Created on: 2023/07/28
 *      Author: Ryu
 */
#include "Wall_Hit_Ctrl.h"

namespace controll
{
	void controll::Wall_Hit_Ctrl::updata(Command* cm)
	{
		if(cm->isHitWall)
		{
			Set_Wall_Status();
		}
	}

	void controll::Wall_Hit_Ctrl::Set_Wall_Status()
	{
		if(my_input->g_sensor_now[2]>my_input->FRONT_SLESHOLD)//1前壁有り
		{
			if(my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD)//2左壁有り
			{
				my_ctrlwin->Set_HitStatus(2);
			}
			else if(my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD)//3右壁有り
			{
				my_ctrlwin->Set_HitStatus(3);
			}
			else//1前壁のみ
			{
				my_ctrlwin->Set_HitStatus(1);
			}
		}
		else//0壁あて無し
		{
			my_ctrlwin->Set_HitStatus(0);
		}
	}
}

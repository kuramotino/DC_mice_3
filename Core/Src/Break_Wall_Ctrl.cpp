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
		isRSIDE=(my_input->g_sensor_now[4]>my_input->RIGHT_SIDE_SLESHOLD)?true:false;
		isLSIDE=(my_input->g_sensor_now[0]>my_input->LEFT_SIDE_SLESHOLD)?true:false;
		isRWall=(my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD)?true:false;
		isLWall=(my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD)?true:false;
		isRecursive=(now_cm.isBreakWall && now_cm.isBreakWallStra)?true:false;
		end_pos=(now_cm.isFrontOffset) ? now_cm.offset_x+now_cm.breakwall_start_offset : now_cm.bu_tar_x+now_cm.breakwall_start_offset;
		if(isRecursive && !preRecursive && !now_cm.isStop)
		{
			my_kasoku->Receive_Wall_Break_Offset(now_cm.bu_tar_x);
			blocknum=0;
			sum_x=now_cm.breakwall_start_offset;
		}

		preRecursive=(!now_cm.isStop)?isRecursive:preRecursive;
	}

	void controll::Break_Wall_Ctrl::BreakWall()
	{
		if(isStop==false)
		{
			if(isRecursive)
			{
				sum_x+=my_kasoku->show_v()*0.001;
				blocknum=(int)(sum_x/180);
			}
			else
			{
				sum_x=0;
				blocknum=0;
			}

			if(my_input->g_sensor_now[1]<my_input->LEFT_SLESHOLD && isLWall)
			{
				sum_x=(isRecursive)?l_offset+180*blocknum:sum_x;
				end_pos=(end_pos-l_offset-180*blocknum<=0) ? l_offset + 180*blocknum : end_pos;
				my_kasoku->Receive_Wall_Break_Offset(end_pos-l_offset-180*blocknum);
				my_kasoku->Set_Pre_v();
				status_off(Forced_End);
			}
			else if(my_input->g_sensor_now[3]<my_input->RIGHT_SLESHOLD && isRWall)
			{
				sum_x=(isRecursive)?r_offset+180*blocknum:sum_x;
				end_pos=(end_pos-r_offset-180*blocknum<=0) ? r_offset + 180*blocknum : end_pos;
				my_kasoku->Receive_Wall_Break_Offset(end_pos-r_offset-180*blocknum);
				my_kasoku->Set_Pre_v();
				status_off(Forced_End);
			}
			else if(my_input->g_sensor_now[0]<my_input->LEFT_SIDE_SLESHOLD && isLSIDE)
			{
				sum_x=(isRecursive)?l_side_offset+180*blocknum:sum_x;
				end_pos=(end_pos-l_side_offset-180*blocknum<=0) ? l_side_offset + 180*blocknum : end_pos;
				my_kasoku->Receive_Wall_Break_Offset(end_pos-l_side_offset-180*blocknum);
				my_kasoku->Set_Pre_v();
				status_off(Forced_End);
			}
			else if(my_input->g_sensor_now[4]<my_input->RIGHT_SIDE_SLESHOLD && isRSIDE)
			{
				sum_x=(isRecursive)?r_side_offset+180*blocknum:sum_x;
				end_pos=(end_pos-r_side_offset-180*blocknum<=0) ? r_side_offset + 180*blocknum : end_pos;
				my_kasoku->Receive_Wall_Break_Offset(end_pos-r_side_offset-180*blocknum);
				my_kasoku->Set_Pre_v();
				status_off(Forced_End);
			}

			if(now_cm.bu_tar_x<=(sum_x-now_cm.breakwall_start_offset))
			{
				my_ctrlwin->Set_ContinueStra(false);
			}
		}
	}
}


/*
 * Break_Wall_Ctrl.cpp
 *
 *  Created on: 2023/07/08
 *      Author: Ryu
 */
#include "Break_Wall_Ctrl.h"
#include "math.h"
#include "Init_Controll_Objs.h"

namespace controll
{
	void controll::Break_Wall_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isBreakWall) || now_cm.isStop);
		isRecursive=(now_cm.isBreakWall && now_cm.isBreakWallStra)?true:false;
		end_pos=(now_cm.isFrontOffset) ? now_cm.offset_x+now_cm.breakwall_start_offset : now_cm.bu_tar_x+now_cm.breakwall_start_offset;
		if(isRecursive && !preRecursive && !now_cm.isStop)
		{
			my_kasoku->Receive_Wall_Break_Offset(now_cm.bu_tar_x);
			blocknum=0;
			//sum_x=now_cm.breakwall_start_offset;
			sum_x=0;
			OKPollDetect=true;
			isWallBreaked=false;
			isdxBreak=false;
			polldetecttimer=0.0;
		}
		OKPollDetect=(!isRecursive && !now_cm.isStop)?true:OKPollDetect;
		polldetecttimer=(!isRecursive && !now_cm.isStop)?0.0:polldetecttimer;
		isWallBreaked=(!isRecursive && !now_cm.isStop)?false:isWallBreaked;
		isdxBreak=(!isRecursive && !now_cm.isStop)?false:isdxBreak;

		preRecursive=(!now_cm.isStop)?isRecursive:preRecursive;
	}

	void controll::Break_Wall_Ctrl::BreakWall()
	{
		if(isStop==false)
		{
			if(isRecursive)
			{
				sum_x+=my_kasoku->show_v()*0.001;
				blocknum=(!isWallBreaked)?(int)(((int)(sum_x))/((int)(180))):(int)(((int)(sum_x)-(int)(90))/((int)(180)));
			}
			else
			{
				sum_x=0;
				blocknum=0;
				//polldetecttimer=0.0;
				//OKPollDetect=true;
			}

			if(now_cm.bu_tar_x+now_cm.breakwall_start_offset-sum_x<=threshold_sum_x && isWallBreaked && !isdxBreak)
			{
				isdxBreak=true;
				isExistWall_R=(my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD)?true:false;
				isExistWall_L=(my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD)?true:false;
//				if(isExistWall_R || isExistWall_L)
//				{
//					sum_x-=diag_breakwall_offset;
//					float set_break_x=end_pos-sum_x;
//					set_break_x=(set_break_x<=0)?0:set_break_x;
//					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
//					my_kasoku->Set_Pre_v();
//					status_off(Forced_End);
//				}
			}
			else if((now_cm.bu_tar_x-sum_x<=threshold_sum_x && !isWallBreaked && !isdxBreak) || (!isRecursive && !isWallBreaked && !isdxBreak))
			{
				isdxBreak=true;
				isExistWall_R=(my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD)?true:false;
				isExistWall_L=(my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD)?true:false;
//				if(isExistWall_R)//debug
//				{
//					led_obj.set_all_led(0b10000000);
//				}
//				if(isExistWall_R || isExistWall_L)
//				{
//					sum_x-=diag_breakwall_offset;
//					float set_break_x=now_cm.bu_tar_x-sum_x;
//					set_break_x=(set_break_x<=0)?0:set_break_x;
//					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
//					my_kasoku->Set_Pre_v();
//					status_off(Forced_End);
//				}
			}

			if(my_input->g_sensor_diff_sum_l>my_input->LEFT_SIDE_SLESHOLD && OKPollDetect && !isdxBreak)//sensor0が左の柱を検知したとき
			{
				if(isRecursive || (!isRecursive && !now_cm.isUseDiagSensor))
				{
					blocknum=(!isWallBreaked)?(int)(((int)(sum_x))/((int)(180))):(int)(((int)(sum_x)-(int)(90))/((int)(180)));
					led_obj.set_all_led(0b01000000);
					OKPollDetect=false;
					isWallBreaked=true;
					sum_x=(isRecursive)?l_side_offset+180*blocknum:sum_x;
					float set_break_x=end_pos-l_side_offset-180*blocknum;
					set_break_x=(set_break_x<=0)?0:set_break_x;
					set_break_x=(!isRecursive)?now_cm.breakwall_left_offset:set_break_x;
					//set_break_x=(!isRecursive)?set_break_x:2000;
					//end_pos=(end_pos-l_side_offset-180*blocknum<=0) ? l_side_offset + 180*blocknum : end_pos;
					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
					my_kasoku->Set_Pre_v();
					status_off(Forced_End);
				}
			}
			else if(my_input->g_sensor_diff_sum_r>my_input->RIGHT_SIDE_SLESHOLD && OKPollDetect && !isdxBreak)//sensor4が右の柱を検知したとき
			{
				if(isRecursive || (!isRecursive && !now_cm.isUseDiagSensor))
				{
					blocknum=(!isWallBreaked)?(int)(((int)(sum_x))/((int)(180))):(int)(((int)(sum_x)-(int)(90))/((int)(180)));
					led_obj.set_all_led(0b10000000);
					OKPollDetect=false;
					isWallBreaked=true;
					sum_x=(isRecursive)?r_side_offset+180*blocknum:sum_x;
					float set_break_x=end_pos-r_side_offset-180*blocknum;
					set_break_x=(set_break_x<=0)?0:set_break_x;
					set_break_x=(!isRecursive)?now_cm.breakwall_right_offset:set_break_x;
					//set_break_x=(!isRecursive)?set_break_x:2000;
					//end_pos=(end_pos-r_side_offset-180*blocknum<=0) ? r_side_offset + 180*blocknum : end_pos;
					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
					my_kasoku->Set_Pre_v();
					status_off(Forced_End);
				}
			}
			else if(my_input->g_sensor_now[1]<my_input->LEFT_DIAG_SLESHOLD && isExistWall_L && isdxBreak)//sensor1が左の壁切れを検知したとき
			{
				if(isRecursive || (!isRecursive && now_cm.isUseDiagSensor))
				{
					blocknum=(!isWallBreaked)?(int)(((int)(sum_x)+(int)(80))/((int)(180))):(int)(((int)(sum_x))/((int)(180)));
					led_obj.set_all_led(0b01000000);
					isWallBreaked=true;
					isExistWall_R=false;
					isExistWall_L=false;
					sum_x=(isRecursive)?l_diag_offset+180*blocknum:sum_x;
					float set_break_x=end_pos-l_diag_offset-180*blocknum;
					set_break_x=(set_break_x<=0)?0:set_break_x;
					set_break_x=(!isRecursive)?now_cm.breakwall_left_offset:set_break_x;
					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
					my_kasoku->Set_Pre_v();
					status_off(Forced_End);
				}
			}
			else if(my_input->g_sensor_now[3]<my_input->RIGHT_DIAG_SLESHOLD && isExistWall_R && isdxBreak)//sensor3が右の壁切れを検知したとき
			{
				if(isRecursive || (!isRecursive && now_cm.isUseDiagSensor))
				{
					blocknum=(!isWallBreaked)?(int)(((int)(sum_x)+(int)(80))/((int)(180))):(int)(((int)(sum_x))/((int)(180)));
					led_obj.set_all_led(0b10000000);
					isWallBreaked=true;
					isExistWall_L=false;
					isExistWall_R=false;
					sum_x=(isRecursive)?r_diag_offset+180*blocknum:sum_x;
					float set_break_x=end_pos-r_diag_offset-180*blocknum;
					set_break_x=(set_break_x<=0)?0:set_break_x;
					set_break_x=(!isRecursive)?now_cm.breakwall_right_offset:set_break_x;
					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
					my_kasoku->Set_Pre_v();
					status_off(Forced_End);
				}
			}

			if(!OKPollDetect && isRecursive)
			{
				if(polldetecttimer>90.0)
				{
					polldetecttimer=0.0;
					OKPollDetect=true;
				}
				else
				{
					polldetecttimer+=my_kasoku->show_v()*0.001;
				}
			}

			if(now_cm.bu_tar_x<=(sum_x-now_cm.breakwall_start_offset) && isWallBreaked)
			{
				my_ctrlwin->Set_ContinueStra(false);
				//preRecursive=false;//debug
			}
			else if(now_cm.bu_tar_x<=sum_x && !isWallBreaked)
			{
				my_ctrlwin->Set_ContinueStra(false);
			}
		}
	}
}


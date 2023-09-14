#include "Diag_BW_Ctrl.h"
#include "math.h"
#include "Init_Controll_Objs.h"

namespace controll
{
	void controll::Diag_BW_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isDiagBreakWall) || now_cm.isStop);
		isRecursive=(now_cm.isDiagBreakWall && now_cm.isDiagBreakWallStra)?true:false;
		end_pos=now_cm.bu_tar_x;
		if(isRecursive && !preRecursive && !now_cm.isStop)
		{
			my_kasoku->Receive_Wall_Break_Offset(now_cm.bu_tar_x);
			blocknum=0;
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

	void controll::Diag_BW_Ctrl::DiagBreakWall()
	{
		if(isStop==false)
		{
			if(isRecursive)
			{
				sum_x+=my_kasoku->show_v()*0.001;
				blocknum=(int)(((int)(sum_x))/((int)(127)));
			}
			else
			{
				sum_x=0;
				blocknum=0;
			}

			if(end_pos-sum_x<=threshold_sum_x && !isdxBreak)
			{
				isdxBreak=true;
			}

			if(my_input->g_sensor_diff_sum_l>my_input->LEFT_POLL_SIDE_SLESHOLD && OKPollDetect && !isdxBreak)//sensor0が左の柱を検知したとき
			{
				if(isRecursive || (!isRecursive && !now_cm.isUseDiagSensor))
				{
					blocknum=(int)(((int)(sum_x))/((int)(127)));
					led_obj.set_all_led(0b01000000);
					OKPollDetect=false;
					isWallBreaked=true;
					sum_x=(isRecursive)?l_side_offset+127*blocknum:sum_x;
					float set_break_x=end_pos-l_side_offset-127*blocknum;
					set_break_x=(set_break_x<=0)?0:set_break_x;
					set_break_x=(!isRecursive)?now_cm.breakwall_left_offset:set_break_x;
					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
					my_kasoku->Set_Pre_v();
					status_off(Forced_End);
				}
			}
			else if(my_input->g_sensor_diff_sum_r>my_input->RIGHT_POLL_SIDE_SLESHOLD && OKPollDetect && !isdxBreak)//sensor4が右の柱を検知したとき
			{
				if(isRecursive || (!isRecursive && !now_cm.isUseDiagSensor))
				{
					blocknum=(int)(((int)(sum_x))/((int)(127)));
					led_obj.set_all_led(0b10000000);
					OKPollDetect=false;
					isWallBreaked=true;
					sum_x=(isRecursive)?r_side_offset+127*blocknum:sum_x;
					float set_break_x=end_pos-r_side_offset-127*blocknum;
					set_break_x=(set_break_x<=0)?0:set_break_x;
					set_break_x=(!isRecursive)?now_cm.breakwall_right_offset:set_break_x;
					my_kasoku->Receive_Wall_Break_Offset(set_break_x);
					my_kasoku->Set_Pre_v();
					status_off(Forced_End);
				}
			}
			else if(my_input->g_sensor_now_diff[1]>my_input->LEFT_POLL_DIAG_SLESHOLD && OKPollDetect && !isdxBreak)//sensor1が左の壁切れを検知したとき
			{
				if(isRecursive || (!isRecursive && now_cm.isUseDiagSensor))
				{
					if(sum_x>diag_bw_th_x || !isRecursive)
					{
						blocknum=(int)(((int)(sum_x))/((int)(127)));
						led_obj.set_all_led(0b01000000);
						OKPollDetect=false;
						isWallBreaked=true;
						sum_x=(isRecursive)?l_diag_offset+127*blocknum:sum_x;
						float set_break_x=end_pos-l_diag_offset-127*blocknum;
						set_break_x=(set_break_x<=0)?0:set_break_x;
						set_break_x=(!isRecursive)?now_cm.breakwall_left_offset:set_break_x;
						my_kasoku->Receive_Wall_Break_Offset(set_break_x);
						my_kasoku->Set_Pre_v();
						status_off(Forced_End);
						BW_Status=2;
					}
					else
					{
						OKPollDetect=false;
					}
				}
			}
			else if(my_input->g_sensor_now_diff[3]>my_input->RIGHT_POLL_DIAG_SLESHOLD && OKPollDetect && !isdxBreak)//sensor3が右の壁切れを検知したとき
			{
				if(isRecursive || (!isRecursive && now_cm.isUseDiagSensor))
				{
					if(sum_x>diag_bw_th_x || !isRecursive)
					{
						blocknum=(int)(((int)(sum_x))/((int)(127)));
						led_obj.set_all_led(0b10000000);
						OKPollDetect=false;
						isWallBreaked=true;
						sum_x=(isRecursive)?r_diag_offset+127*blocknum:sum_x;
						float set_break_x=end_pos-r_diag_offset-127*blocknum;
						set_break_x=(set_break_x<=0)?0:set_break_x;
						set_break_x=(!isRecursive)?now_cm.breakwall_right_offset:set_break_x;
						my_kasoku->Receive_Wall_Break_Offset(set_break_x);
						my_kasoku->Set_Pre_v();
						status_off(Forced_End);
						BW_Status=1;
					}
					else
					{
						OKPollDetect=false;
					}
				}
			}

			if(!OKPollDetect && isRecursive)
			{
				if(polldetecttimer>40.0)
				{
					polldetecttimer=0.0;
					OKPollDetect=true;
				}
				else
				{
					polldetecttimer+=my_kasoku->show_v()*0.001;
				}
			}

			if(end_pos<=sum_x)
			{
				my_ctrlwin->Set_ContinueStra(false);
			}
		}
	}

	int controll::Diag_BW_Ctrl::RetData()
	{
		int bu_status=BW_Status;
		BW_Status=0;
		return bu_status;
	}
}

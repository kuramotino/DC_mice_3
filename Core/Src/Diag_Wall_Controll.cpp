/*
 * Diag_Wall_Controll.cpp
 *
 *  Created on: 2023/09/03
 *      Author: Ryu
 */
#include "Diag_Wall_Controll.h"

namespace controll
{
	void controll::Diag_Wall_Ctrl::updata(Command* cm)//overrideする
	{
		now_cm=cm;
		isStop=(!now_cm->isDiagWallPID || now_cm->isStop);
	}

	void controll::Diag_Wall_Ctrl::transmit_DiagWall_PID()
	{
		if(!isStop)
		{
			Polling_BW();
			if(BW_Ctrl_Status==1)//1右で壁切れが起こったとき
			{
				DecideALLCtrlSensor(true);
				sum_x+=my_kasoku->show_v()*0.001;
				if(sum_x>125)
				{
					BW_Ctrl_Status=0;
				}

				float l_side_err=SIDE_L_SENSOR_GAIN*RetError(MetertoAD(sum_x,false,true,true),my_input->g_sensor_now[0]);
				float l_diag_err=DIAG_L_SENSOR_GAIN*RetError(MetertoAD(sum_x,false,false,true),my_input->g_sensor_now[1]);
				float r_diag_err=DIAG_R_SENSOR_GAIN*RetError(MetertoAD(sum_x,true,false,true),my_input->g_sensor_now[3]);
				float r_side_err=SIDE_R_SENSOR_GAIN*RetError(MetertoAD(sum_x,true,true,true),my_input->g_sensor_now[4]);
				l_side_err=(!isCtrlSideL)?0:l_side_err;
				l_diag_err=(!isCtrlDiagL)?0:l_diag_err;
				r_diag_err=(!isCtrlDiagR)?0:r_diag_err;
				r_side_err=(!isCtrlSideR)?0:r_side_err;

				l_side_err=(!isCtrlSideR)?2*l_side_err:l_side_err;
				l_diag_err=(!isCtrlDiagR)?2*l_diag_err:l_diag_err;
				r_diag_err=(!isCtrlDiagL)?2*r_diag_err:r_diag_err;
				r_side_err=(!isCtrlSideL)?2*r_side_err:r_side_err;

				float err=r_side_err+r_diag_err-l_diag_err-l_side_err;
				pid_ctrl->transmit(err);

			}
			else if(BW_Ctrl_Status==2)//2左で壁切れが起こったとき
			{
				DecideALLCtrlSensor(false);
				sum_x+=my_kasoku->show_v()*0.001;
				if(sum_x>132)
				{
					BW_Ctrl_Status=0;
				}

				float l_side_err=SIDE_L_SENSOR_GAIN*RetError(MetertoAD(sum_x,false,true,false),my_input->g_sensor_now[0]);
				float l_diag_err=DIAG_L_SENSOR_GAIN*RetError(MetertoAD(sum_x,false,false,false),my_input->g_sensor_now[1]);
				float r_diag_err=DIAG_R_SENSOR_GAIN*RetError(MetertoAD(sum_x,true,false,false),my_input->g_sensor_now[3]);
				float r_side_err=SIDE_R_SENSOR_GAIN*RetError(MetertoAD(sum_x,true,true,false),my_input->g_sensor_now[4]);
				l_side_err=(!isCtrlSideL)?0:l_side_err;
				l_diag_err=(!isCtrlDiagL)?0:l_diag_err;
				r_diag_err=(!isCtrlDiagR)?0:r_diag_err;
				r_side_err=(!isCtrlSideR)?0:r_side_err;

				l_side_err=(!isCtrlSideR)?2*l_side_err:l_side_err;
				l_diag_err=(!isCtrlDiagR)?2*l_diag_err:l_diag_err;
				r_diag_err=(!isCtrlDiagL)?2*r_diag_err:r_diag_err;
				r_side_err=(!isCtrlSideL)?2*r_side_err:r_side_err;

				float err=r_side_err+r_diag_err-l_diag_err-l_side_err;
				pid_ctrl->transmit(err);

			}
			else
			{
				pid_ctrl->transmit(0);
			}
		}
	}

	void controll::Diag_Wall_Ctrl::SetPIDCtrl(BaseCtrl* pid)
	{
		pid_ctrl=pid;
	}

	void controll::Diag_Wall_Ctrl::SetDiagBW(BaseCtrl* diag)
	{
		diag_bw=diag;
	}

	float controll::Diag_Wall_Ctrl::MetertoAD(float x,bool isR,bool isSide,bool bw_R)
	{
		if(bw_R)
		{
			if(isR)
			{
				if(isSide)
				{
					float ad=R_BW_Side_R_XtoAD[0]+R_BW_Side_R_XtoAD[1]*x+R_BW_Side_R_XtoAD[2]*x*x+R_BW_Side_R_XtoAD[3]*x*x*x+R_BW_SIDE_R_offset;
					return ad;
				}
				else
				{
					float ad=R_BW_Diag_R_XtoAD[0]+R_BW_Diag_R_XtoAD[1]*x+R_BW_Diag_R_XtoAD[2]*x*x+R_BW_Diag_R_XtoAD[3]*x*x*x;
					return ad;
				}
			}
			else
			{
				if(isSide)
				{
					float ad=R_BW_Side_L_XtoAD[0]+R_BW_Side_L_XtoAD[1]*x+R_BW_Side_L_XtoAD[2]*x*x+R_BW_Side_L_XtoAD[3]*x*x*x+R_BW_SIDE_L_offset;
					return ad;
				}
				else
				{
					float ad=R_BW_Diag_L_XtoAD[0]+R_BW_Diag_L_XtoAD[1]*x+R_BW_Diag_L_XtoAD[2]*x*x+R_BW_Diag_L_XtoAD[3]*x*x*x;
					return ad;
				}
			}

		}
		else
		{
			if(isR)
			{
				if(isSide)
				{
					float ad=L_BW_Side_R_XtoAD[0]+L_BW_Side_R_XtoAD[1]*x+L_BW_Side_R_XtoAD[2]*x*x+L_BW_Side_R_XtoAD[3]*x*x*x+L_BW_SIDE_R_offset;
					return ad;
				}
				else
				{
					float ad=L_BW_Diag_R_XtoAD[0]+L_BW_Diag_R_XtoAD[1]*x+L_BW_Diag_R_XtoAD[2]*x*x+L_BW_Diag_R_XtoAD[3]*x*x*x;
					return ad;
				}
			}
			else
			{
				if(isSide)
				{
					float ad=L_BW_Side_L_XtoAD[0]+L_BW_Side_L_XtoAD[1]*x+L_BW_Side_L_XtoAD[2]*x*x+L_BW_Side_L_XtoAD[3]*x*x*x+L_BW_Side_L_XtoAD[4]*x*x*x*x+L_BW_SIDE_L_offset;
					return ad;
				}
				else
				{
					float ad=L_BW_Diag_L_XtoAD[0]+L_BW_Diag_L_XtoAD[1]*x+L_BW_Diag_L_XtoAD[2]*x*x+L_BW_Diag_L_XtoAD[3]*x*x*x;
					return ad;
				}
			}
		}
	}

	void controll::Diag_Wall_Ctrl::Polling_BW()
	{
		BW_Status=diag_bw->RetData();
		if(pre_BW_Status==0 && BW_Status==1)
		{
			BW_Ctrl_Status=1;
			sum_x=0;
		}
		else if(pre_BW_Status==0 && BW_Status==2)
		{
			BW_Ctrl_Status=2;
			sum_x=0;
		}
		pre_BW_Status=BW_Status;
	}

	float controll::Diag_Wall_Ctrl::RetError(float ref,float ad)
	{
		float error=ad-ref;
		//float error=ref-ad;
		return error;
	}

	void controll::Diag_Wall_Ctrl::DecideCtrlSensor(bool* ctrlflag,float* range_1,float* range_2)//1制御するセンサーを決定する関数
	{
		if((*(range_1)<sum_x && sum_x<*(range_1+1)) || (*(range_2)<sum_x && sum_x<*(range_2+1)))
		{
			*ctrlflag=true;
		}
		else
		{
			*ctrlflag=false;
		}
	}

	void controll::Diag_Wall_Ctrl::DecideALLCtrlSensor(bool bw_R)
	{
		if(bw_R)
		{
			DecideCtrlSensor(&isCtrlSideL,R_BW_SIDE_L_WallCtrl_Range_1,R_BW_SIDE_L_WallCtrl_Range_2);
			DecideCtrlSensor(&isCtrlDiagL,R_BW_DIAG_L_WallCtrl_Range_1,R_BW_DIAG_L_WallCtrl_Range_2);
			DecideCtrlSensor(&isCtrlDiagR,R_BW_DIAG_R_WallCtrl_Range_1,R_BW_DIAG_R_WallCtrl_Range_2);
			DecideCtrlSensor(&isCtrlSideR,R_BW_SIDE_R_WallCtrl_Range_1,R_BW_SIDE_R_WallCtrl_Range_2);
		}
		else
		{
			DecideCtrlSensor(&isCtrlSideL,L_BW_SIDE_L_WallCtrl_Range_1,L_BW_SIDE_L_WallCtrl_Range_2);
			DecideCtrlSensor(&isCtrlDiagL,L_BW_DIAG_L_WallCtrl_Range_1,L_BW_DIAG_L_WallCtrl_Range_2);
			DecideCtrlSensor(&isCtrlDiagR,L_BW_DIAG_R_WallCtrl_Range_1,L_BW_DIAG_R_WallCtrl_Range_2);
			DecideCtrlSensor(&isCtrlSideR,L_BW_SIDE_R_WallCtrl_Range_1,L_BW_SIDE_R_WallCtrl_Range_2);
		}

		isCtrlSideL=(my_input->g_sensor_now[0]<THRESHOLD_SIDE_L)?false:isCtrlSideL;
		isCtrlDiagL=(my_input->g_sensor_now[1]<THRESHOLD_DIAG_L)?false:isCtrlDiagL;
		isCtrlDiagR=(my_input->g_sensor_now[3]<THRESHOLD_DIAG_R)?false:isCtrlDiagR;
		isCtrlSideR=(my_input->g_sensor_now[4]<THRESHOLD_SIDE_R)?false:isCtrlSideR;
	}
}

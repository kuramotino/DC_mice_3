/*
 * Diag_Wall_Controll.h
 *
 *  Created on: 2023/09/03
 *      Author: Ryu
 */

#ifndef INC_DIAG_WALL_CONTROLL_H_
#define INC_DIAG_WALL_CONTROLL_H_

#include "BaseCtrl.h"

namespace controll
{
	class Diag_Wall_Ctrl : public BaseCtrl
	{
		float THRESHOLD_DIAG_R=50;//1右壁の閾値
		float THRESHOLD_DIAG_L=50;//2左壁の閾値
		float THRESHOLD_SIDE_R=60;//1右壁の閾値
		float THRESHOLD_SIDE_L=60;//2左壁の閾値

		float DIAG_R_SENSOR_GAIN=0.0;//1壁制御のゲイン
		float DIAG_L_SENSOR_GAIN=0.0;//1壁制御のゲイン
		float SIDE_R_SENSOR_GAIN=0.1;//1壁制御のゲイン/0.2
		float SIDE_L_SENSOR_GAIN=0.1;//1壁制御のゲイン

		float R_BW_Side_R_XtoAD[4]={148.52,10.12,-0.1122,0.0002};
		float R_BW_Diag_R_XtoAD[4]={343.69,-13.106,0.2066,-0.0009};
		float R_BW_Diag_L_XtoAD[4]={245.55,0.3857,0.0568,-0.0001};
		float R_BW_Side_L_XtoAD[4]={179.74,-1.778,0.0075,0.0001};

		float L_BW_Side_R_XtoAD[4]={176.38,-1.8602,0.0088,0.00005};
		float L_BW_Diag_R_XtoAD[4]={234.5,-0.4269,0.0528,-0.0002};
		float L_BW_Diag_L_XtoAD[4]={334.93,-13.043,0.2011,-0.0008};
		float L_BW_Side_L_XtoAD[5]={263.43,3.9654,0.3753,-0.0072,0.00003};

		float R_BW_SIDE_L_WallCtrl_Range_1[2]={0,45};//1右壁切れ後に制御する範囲1
		float R_BW_SIDE_L_WallCtrl_Range_2[2]={65,125};//2右壁切れ後に制御する範囲2

		float R_BW_DIAG_L_WallCtrl_Range_1[2]={0,125};//1左壁切れ後に制御する範囲1
		float R_BW_DIAG_L_WallCtrl_Range_2[2]={0,0};//2左壁切れ後に制御する範囲2

		float R_BW_DIAG_R_WallCtrl_Range_1[2]={0,125};//1右壁切れ後に制御する範囲1
		float R_BW_DIAG_R_WallCtrl_Range_2[2]={0,0};//2右壁切れ後に制御する範囲2

		float R_BW_SIDE_R_WallCtrl_Range_1[2]={0,45};//1左壁切れ後に制御する範囲1
		float R_BW_SIDE_R_WallCtrl_Range_2[2]={65,125};//2左壁切れ後に制御する範囲2

		float L_BW_SIDE_L_WallCtrl_Range_1[2]={0,45};//1右壁切れ後に制御する範囲1
		float L_BW_SIDE_L_WallCtrl_Range_2[2]={65,132};//2右壁切れ後に制御する範囲2

		float L_BW_DIAG_L_WallCtrl_Range_1[2]={0,132};//1左壁切れ後に制御する範囲1
		float L_BW_DIAG_L_WallCtrl_Range_2[2]={0,0};//2左壁切れ後に制御する範囲2

		float L_BW_DIAG_R_WallCtrl_Range_1[2]={0,132};//1右壁切れ後に制御する範囲1
		float L_BW_DIAG_R_WallCtrl_Range_2[2]={0,0};//2右壁切れ後に制御する範囲2

		float L_BW_SIDE_R_WallCtrl_Range_1[2]={0,45};//1左壁切れ後に制御する範囲1
		float L_BW_SIDE_R_WallCtrl_Range_2[2]={65,132};//2左壁切れ後に制御する範囲2

		float R_BW_SIDE_R_offset=15;
		float R_BW_SIDE_L_offset=30;
		float L_BW_SIDE_R_offset=15;
		float L_BW_SIDE_L_offset=30;

		float sum_x=0;
		int BW_Status=0;//1壁切れの状態,(0壁切れ無し,1右で壁切れ、2左で壁切れ)
		int pre_BW_Status=0;
		int BW_Ctrl_Status=0;//1現在行っている制御の状態,(0壁切れ無し,1右で壁切れ、2左で壁切れ)
		bool isCtrlSideR=false;
		bool isCtrlDiagR=false;
		bool isCtrlDiagL=false;
		bool isCtrlSideL=false;

		float PID_Wall=0;//pid_ctrlに送信する壁制御の制御量
		BaseCtrl* pid_ctrl;
		BaseCtrl* diag_bw;

	public:
		void updata(Command* cm);//overrideする
		void transmit_DiagWall_PID();//壁制御の制御量を求めpid_ctrlに送信する関数(TIM6割り込みで呼ばれる)
		void SetPIDCtrl(BaseCtrl* pid);
		void SetDiagBW(BaseCtrl* diag);
		float MetertoAD(float x,bool isR,bool isSide,bool bw_R);//距離からAD値に変換する関数
		void Polling_BW();//壁切れを監視する関数
		float RetError(float ref,float ad);//制御量を求める関数
		void DecideCtrlSensor(bool* ctrlflag,float* range_1,float* range_2);//1制御するセンサーを決定する関数
		void DecideALLCtrlSensor(bool bw_R);
	};
}

#endif /* INC_DIAG_WALL_CONTROLL_H_ */

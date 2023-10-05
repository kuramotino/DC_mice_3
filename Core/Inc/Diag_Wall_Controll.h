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

		float DIAG_R_SENSOR_GAIN=0.000;//1壁制御のゲイン
		float DIAG_L_SENSOR_GAIN=0.00035;//1壁制御のゲイン
		float SIDE_R_SENSOR_GAIN=0.00035;//1壁制御のゲイン/0.2
		float SIDE_L_SENSOR_GAIN=0.000;//1壁制御のゲイン

		float R_BW_Side_L_XtoAD[4]={149.35,-0.925,-0.0022,0.0001};
		float R_BW_Diag_L_XtoAD[4]={215.26,1.1594,0.0312,-0.000005};
		float R_BW_Diag_R_XtoAD[4]={6.6933,1.0622,-0.0066,0.00004};
		float R_BW_Side_R_XtoAD[4]={213.99,6.6007,-0.1072,0.0021};

		float L_BW_Side_L_XtoAD[5]={362.57,8.1066,0.2019,-0.0106,0.0002};
		float L_BW_Diag_L_XtoAD[4]={76.552,0.3659,0.0045,0.00005};
		float L_BW_Diag_R_XtoAD[4]={231.84,2.3401,-0.0033,0.0001};
		float L_BW_Side_R_XtoAD[4]={172.57,-1.2172,-0.0041,0.0001};

		float R_BW_SIDE_L_WallCtrl_Range_1[2]={0,130};//1右壁切れ後に制御する範囲1
		float R_BW_SIDE_L_WallCtrl_Range_2[2]={0,0};//2右壁切れ後に制御する範囲2

		float R_BW_DIAG_L_WallCtrl_Range_1[2]={0,110};//1左壁切れ後に制御する範囲1
		float R_BW_DIAG_L_WallCtrl_Range_2[2]={0,0};//2左壁切れ後に制御する範囲2

		float R_BW_DIAG_R_WallCtrl_Range_1[2]={0,133};//1右壁切れ後に制御する範囲1
		float R_BW_DIAG_R_WallCtrl_Range_2[2]={0,0};//2右壁切れ後に制御する範囲2

		float R_BW_SIDE_R_WallCtrl_Range_1[2]={0,50};//1左壁切れ後に制御する範囲1
		float R_BW_SIDE_R_WallCtrl_Range_2[2]={0,0};//2左壁切れ後に制御する範囲2

		float L_BW_SIDE_L_WallCtrl_Range_1[2]={0,30};//1右壁切れ後に制御する範囲1
		float L_BW_SIDE_L_WallCtrl_Range_2[2]={0,0};//2右壁切れ後に制御する範囲2

		float L_BW_DIAG_L_WallCtrl_Range_1[2]={0,120};//1左壁切れ後に制御する範囲1
		float L_BW_DIAG_L_WallCtrl_Range_2[2]={0,0};//2左壁切れ後に制御する範囲2

		float L_BW_DIAG_R_WallCtrl_Range_1[2]={0,100};//1右壁切れ後に制御する範囲1
		float L_BW_DIAG_R_WallCtrl_Range_2[2]={0,0};//2右壁切れ後に制御する範囲2

		float L_BW_SIDE_R_WallCtrl_Range_1[2]={0,45};//1左壁切れ後に制御する範囲1
		float L_BW_SIDE_R_WallCtrl_Range_2[2]={0,120};//2左壁切れ後に制御する範囲2

		float R_BW_SIDE_R_offset=30;
		float R_BW_Diag_L_offset=-30;
		float L_BW_SIDE_R_offset=30;
		float L_BW_Diag_L_offset=-30;

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

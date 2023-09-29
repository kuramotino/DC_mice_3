/*
 * Wall_Controll.h
 *
 *  Created on: 2023/05/03
 *      Author: Ryu
 */

#ifndef INC_WALL_CONTROLL_H_
#define INC_WALL_CONTROLL_H_
#include "BaseCtrl.h"
#define DIFF_QUEUE_SIZE 10

namespace controll
{
	class Wall_Ctrl : public BaseCtrl
	{
		int g_WallControllStatus;//壁の存在状態(2進数で1bit目が左、2bit目が右)
		int wall_status[2];
		float THRESHOLD_R=110;//1右壁の閾値110
		float THRESHOLD_DIFF_R=15;//1右壁の変化量の閾値20
		float THRESHOLD_L=150;//2左壁の閾値150
		float THRESHOLD_DIFF_L=30;//2左壁の変化量の閾値20
		float R_SENSOR_GAIN=1.8;//1壁制御のゲイン0.0033/2
		float L_SENSOR_GAIN=1.8;//1壁制御のゲイン0.0033/2
		float CENTER_R=177;//機体が中心にあるときの右AD値
		float CENTER_L=175;//機体が中心にあるときの左AD値255
		float ABS_CENTER_R=170;
		float ABS_CENTER_L=185;
		float Side_R_ADtoX[5]={219.14,-2.0648,0.0092,-0.00002,0.00000002};//R距離変換関数の係数
		float Side_L_ADtoX[5]={137.04,-0.9474,0.0032,-0.000005,0.000000003};//L距離変換関数の係数
		float PID_Wall=0;//pid_ctrlに送信する壁制御の制御量
		int wall_ctrl_counter[2]={0,0};
		int wall_ctrl_count[2]={10,10};//2,2
		float diff_queue_r[DIFF_QUEUE_SIZE];
		float diff_queue_l[DIFF_QUEUE_SIZE];
		int diff_count_r=0;
		int diff_count_l=0;
		BaseCtrl* pid_ctrl;

	public:
//		int wall_ctrl_log[1200];
//		int wall_r_diff[1200];
//		int wall_l_diff[1200];
//		float wall_r_meter[1200];
//		float wall_l_meter[1200];
		int wall_counter=0;
		bool wall_log_flag=false;

	public:
		void updata(Command* cm);//overrideする
		void transmit_Wall_PID();//壁制御の制御量を求めpid_ctrlに送信する関数(TIM6割り込みで呼ばれる)
		void SetPIDCtrl(BaseCtrl* pid);
		void transmit(float message);//PID_Ctrlに壁制御量を送信する
		void receive(float message);
		float ADtoMeter(float ad,bool isR);//AD値から距離に変換する関数
		void setDiffqueue(bool isR);//now_diffをqueueにセットする
		float getDiffqueue(bool isR);//now_diffの積分値を返す関数
	};
}

#endif /* INC_WALL_CONTROLL_H_ */

/*
 * Wall_Controll.h
 *
 *  Created on: 2023/05/03
 *      Author: Ryu
 */

#ifndef INC_WALL_CONTROLL_H_
#define INC_WALL_CONTROLL_H_
#include "BaseCtrl.h"

namespace controll
{
	class Wall_Ctrl : public BaseCtrl
	{
		int g_WallControllStatus;//壁の存在状態(2進数で1bit目が左、2bit目が右)
		float THRESHOLD_R=15;//1右壁の閾値
		float THRESHOLD_DIFF_R=30;//1右壁の変化量の閾値
		float THRESHOLD_L=15;//2左壁の閾値
		float THRESHOLD_DIFF_L=30;//2左壁の変化量の閾値
		float SENSOR_GAIN=0.0033;//1壁制御のゲイン
		float CENTER_R=102;//機体が中心にあるときの右AD値
		float CENTER_L=120;//機体が中心にあるときの左AD値
		float PID_Wall=0;//pwmに送信する壁制御の制御量
		int wall_ctrl_counter[2]={0,0};
		int wall_ctrl_count[2]={1,1};

	public:
		void updata(Command cm);//overrideする
		void transmit_Wall_PID();//壁制御の制御量を求めpwmに送信する関数(TIM6割り込みで呼ばれる)
	};
}

#endif /* INC_WALL_CONTROLL_H_ */

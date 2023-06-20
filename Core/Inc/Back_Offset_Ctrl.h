/*
 * Back_Offset_Ctrl.h
 *
 *  Created on: 2023/06/20
 *      Author: Ryu
 */

#ifndef INC_BACK_OFFSET_CTRL_H_
#define INC_BACK_OFFSET_CTRL_H_
#include "BaseCtrl.h"

namespace controll
{
	class Back_Offset_Ctrl : public BaseCtrl
	{
		float r_back_offset=30;
		float l_back_offset=30;
		float CENTER_R=155;//R機体が中心にあるときの右AD値
		float CENTER_L=255;//L機体が中心にあるときの左AD値
		float ABS_CENTER_R=155;
		float ABS_CENTER_L=255;
		float Side_R_ADtoX[5]={198.56,-1.8756,0.0085,-0.00002,0.00000002};//R距離変換関数の係数
		float Side_L_ADtoX[5]={136.58,-0.7365,0.0019,-0.000002,0.0000000009};//L距離変換関数の係数

	public:
		void updata(Command cm);//overrideする
		float Side_Wall_Offset();//横壁制御を行う関数
		void Transmit_Back_Offset(float bu_back_offset);//kasokuに後距離の制御量を送信する関数
	};
}

#endif /* INC_BACK_OFFSET_CTRL_H_ */
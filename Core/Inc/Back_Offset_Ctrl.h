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
		float r_back_offset=48;
		float l_back_offset=43;
		float CENTER_R=177;//R機体が中心にあるときの右AD値
		float CENTER_L=175;//L機体が中心にあるときの左AD値255
		float ABS_CENTER_R=170;
		float ABS_CENTER_L=185;
		float max_offset_ctrl=20;
		float Side_R_ADtoX[5]={219.14,-2.0648,0.0092,-0.00002,0.00000002};//R距離変換関数の係数
		float Side_L_ADtoX[5]={137.04,-0.9474,0.0032,-0.000005,0.000000003};//L距離変換関数の係数
		float sub_back_offset=0;//1横壁制御が使えないときに補正する量のキュー//index1を使う
		bool isR=false;//制御に使った壁が右か左か
		float uturn_gain=0;//1袋小路での位置補正のゲイン
		float max_back_offset=5;//0袋小路での位置補正の最大の補正量

	public:
		void updata(Command* cm);//overrideする
		float Side_Wall_Offset();//横壁制御を行う関数
		void Transmit_Back_Offset(float bu_back_offset);//kasokuに後距離の制御量を送信する関数
		void receive(float message);
		void Set_sbu_queue(float sub_offset);//キューにセットする関数
	};
}

#endif /* INC_BACK_OFFSET_CTRL_H_ */

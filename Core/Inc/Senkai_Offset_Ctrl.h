/*
 * Senkai_Offset_Ctrl.h
 *
 *  Created on: 2023/07/08
 *      Author: Ryu
 */

#ifndef INC_SENKAI_OFFSET_CTRL_H_
#define INC_SENKAI_OFFSET_CTRL_H_

#include "BaseCtrl.h"

namespace controll
{
	class Senkai_Offset_Ctrl : public BaseCtrl
	{
		uint16_t turn_start_ad=500;//1ターンを行うAD値
		float sub_back_offset_ctrl=0;//1前壁で補正できなかったときに補正する後距離
		float offset_x=40;//offsetで進む距離
		BaseCtrl* my_back;
	public:
		void updata(Command* cm);//overrideする
		void BreakFrontOffset();//前壁との距離より前オフセットを調整する関数
		void transmit(float message);//後距離の補正量をBack_Offset_Ctrlに送信する関数
		void SetBackOffset(BaseCtrl* back_obj);
	};
}

#endif /* INC_SENKAI_OFFSET_CTRL_H_ */

/*
 * Front_Offset_Ctrl.h
 *
 *  Created on: 2023/06/19
 *      Author: Ryu
 */

#ifndef INC_FRONT_OFFSET_CTRL_H_
#define INC_FRONT_OFFSET_CTRL_H_
#include "BaseCtrl.h"

namespace controll
{
	class Front_Offset_Ctrl : public BaseCtrl
	{
		uint16_t turn_start_ad=350;//ターンを行うAD値
	public:
		void updata(Command cm);//overrideする
		void BreakFrontOffset();//前壁との距離より前オフセットを調整する関数
	};
}


#endif /* INC_FRONT_OFFSET_CTRL_H_ */

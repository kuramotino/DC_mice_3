/*
 * Break_Wall_Ctrl.h
 *
 *  Created on: 2023/07/08
 *      Author: Ryu
 */

#ifndef INC_BREAK_WALL_CTRL_H_
#define INC_BREAK_WALL_CTRL_H_

#include "BaseCtrl.h"

namespace controll
{
	class Break_Wall_Ctrl : public BaseCtrl
	{
		float l_offset=112;//1左壁の切れ目から112mm進む
		float r_offset=95;//2右壁の切れ目から95mm進む
		bool isRWall=false;//右壁があるか
		bool isLWall=false;//左壁があるか

	public:
		void updata(Command cm);//overrideする
		void BreakWall();//壁切れを判定する関数
	};
}

#endif /* INC_BREAK_WALL_CTRL_H_ */

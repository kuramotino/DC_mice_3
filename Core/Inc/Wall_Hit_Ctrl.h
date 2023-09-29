/*
 * Wall_Hit_Ctrl.h
 *
 *  Created on: 2023/07/28
 *      Author: Ryu
 */

#ifndef INC_WALL_HIT_CTRL_H_
#define INC_WALL_HIT_CTRL_H_
#include "BaseCtrl.h"

namespace controll
{
	class Wall_Hit_Ctrl : public BaseCtrl
	{
	public:
		void updata(Command* cm);//overrideする
		void Set_Wall_Status();
	};
}


#endif /* INC_WALL_HIT_CTRL_H_ */

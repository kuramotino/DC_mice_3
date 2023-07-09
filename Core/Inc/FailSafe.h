/*
 * FailSafe.h
 *
 *  Created on: 2023/04/27
 *      Author: Ryu
 */

#ifndef INC_FAILSAFE_H_
#define INC_FAILSAFE_H_
#include "BaseCtrl.h"

namespace controll
{
	class FailSafe : public BaseCtrl
	{
		float threshold_v=1000;
		float threshold_omega=500;
		float threshold_accel_y=-5;

		bool v_logical;
		bool accel_logical_y;
	public:
		bool isFail=false;

	public:
		void FailStop();//速度、角速度を監視し、FailSafeをかける関数
	};

}


#endif /* INC_FAILSAFE_H_ */

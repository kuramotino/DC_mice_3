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
		float threshold_v=500;
		float threshold_omega=500;
		float threshold_accel_y=-5;//-5
		float threshold_enc=15000;
		float threshold_back_v=-120;
		int back_zeroenc_cnt=0;

		bool v_logical=false;
		bool accel_logical_y;
		bool enc_logical=false;
		bool who_logical;
		bool zero_gyro_logical;
		bool back_enc_logical;
	public:
		bool isFail=false;

	public:
		void FailStop();//速度、角速度を監視し、FailSafeをかける関数
	};

}


#endif /* INC_FAILSAFE_H_ */

/*
 * Pass_Generator.h
 *
 *  Created on: 2023/06/22
 *      Author: Ryu
 */

#ifndef INC_PASS_GENERATOR_H_
#define INC_PASS_GENERATOR_H_

#include "Planning.h"

namespace Algorizm
{
	class Pass_Generator
	{
		int pass[255];
		int passcount=0;
		Planning* my_plan;

		int OO90_R[3] = { 1,-3,1 };
		int OO90_L[3] = { 1,-2,1 };
		int OO180_R[4] = { 1,-3,-3,1 };
		int OO180_L[4] = { 1,-2,-2,1 };

		float OO_90_conect_v=1000;//0大回り90の接続速度
		float OO_180_conect_v=1000;//1大回り180の接続速度

	public:
		void SetPlan(Planning* bu_plan);
		void M_Pass(int goal_size, POS* goal_pos);//pass�𐶐�����
		int DecodePass();//pass���玟�̍s����Ԃ��֐�
		void InitPassCount();//pass������������֐�
		void Comp_Pass(int* tar_pass, int pass_size, int setpassnum);//pass�����k����֐�
		void St_Comp_Pass(void);//�����̈��k
		void Conect_v_cal(float turn_v,float* M_start_conect_v,float* M_end_conect_v);//���i�̐ڑ����x���v�Z
		int Ret_NextPass();
		void Show_Pass();
	};
}

#endif /* INC_PASS_GENERATOR_H_ */

/*
 * Pass_Generator.h
 *
 *  Created on: 2023/06/22
 *      Author: Ryu
 */

#ifndef INC_PASS_GENERATOR_H_
#define INC_PASS_GENERATOR_H_

#include "Planning.h"
#include "Shortest_PARAM.h"

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
		int Diag_in45_R[2] = { 1,-3 };
		int Diag_in45_L[2] = { 1,-2 };
		int Diag_out45_R[2] = { -3,1 };
		int Diag_out45_L[2] = { -2,1 };
		int Diag_in135_R[3] = { 1,-3,-3 };
		int Diag_in135_L[3] = { 1,-2,-2 };
		int Diag_out135_R[3] = { -3,-3,1 };
		int Diag_out135_L[3] = { -2,-2,1 };
		int Diag_V90_R[2] = { -3,-3 };
		int Diag_V90_L[2] = { -2,-2 };
		int Diag_Stra_R[1] = { -3 };
		int Diag_Stra_L[1] = { -2 };

		bool isOO_Zip=true;//2大回りのパス圧縮をするかどうか

	public:
		void SetPlan(Planning* bu_plan);
		void M_Pass(int goal_size, POS* goal_pos);//pass�𐶐�����
		int DecodePass();//pass���玟�̍s����Ԃ��֐�
		void InitPassCount();//pass������������֐�
		void Comp_Pass(int* tar_pass, int pass_size, int setpassnum);//pass�����k����֐�
		void St_Comp_Pass(void);//�����̈��k
		void Diag_Comp_Pass(void);
		void Conect_v_cal(Shortest_PARAM* s_param,float* M_start_conect_v,float* M_end_conect_v);//���i�̐ڑ����x���v�Z
		int Ret_NextPass();
		void Show_Pass();
		void PassZipSetting(bool iszip);//pass圧縮に関する設定を行う関数
	};
}

#endif /* INC_PASS_GENERATOR_H_ */

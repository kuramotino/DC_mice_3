/*
 * Pass_Generator.cpp
 *
 *  Created on: 2023/06/22
 *      Author: Ryu
 */
#include "Pass_Generator.h"
#include "motor_drive.h"

namespace Algorizm
{
	void Pass_Generator::SetPlan(Planning* bu_plan)
	{
		my_plan = bu_plan;
	}

	void Pass_Generator::M_Pass(int goal_size, POS* goal_pos)
	{
		my_plan->BlockWall();//���T���̕ǂ��ӂ���
		my_plan->MiceInit();//�}�E�X�̏�Ԃ�������

		bool isGoal = false;
		int n = 0;

		for (int i = 0; i < 255; i++)//pass��������
		{
			pass[i] = 0;
		}
		//pass[0] = 2;
		pass[0]=1;
		n++;

		while (1)
		{
			int bu_pass = my_plan->saitan_dijkstra(goal_size, goal_pos);//���̍s���𓾂�
			if (bu_pass > 1)
			{
				for (int i = 0; i < bu_pass; i++)
				{
					pass[n] = 1;
					n++;
				}
			}
			else
			{
				pass[n] = bu_pass;
				n++;
			}

			isGoal = my_plan->RetIsSimEnd();
			if (isGoal || n == 253)
			{
				pass[n] = 1;//180mm���i
				n++;
				pass[n] = 1;
				break;
			}
		}

		//Comp_Pass(OO90_R, 3, -7);
		//Comp_Pass(OO90_L, 3, -5);
		//Comp_Pass(OO180_R, 4, -6);
		//Comp_Pass(OO180_L, 4, -4);
		St_Comp_Pass();
	}

	int Pass_Generator::DecodePass()
	{
		int ret = pass[passcount];
		if (ret != 0 && passcount != 254)
		{
			passcount++;
		}
		return ret;
	}

	void Pass_Generator::InitPassCount()
	{
		passcount = 0;
	}

	void Pass_Generator::Comp_Pass(int* tar_pass, int pass_size, int setpassnum)//pass�����k����֐�
	{
		int size = pass_size;
		for (int i = 0; i <= 255 - size; i++)//1pass�z���S����
		{
			int isEq = 1;
			for (int j = 0; j < size; j++)//2pass�z���tar�z����r
			{
				if (pass[i + j] != *(tar_pass + j))
				{
					isEq = 0;
				}
			}

			if (isEq == 1)
			{
				pass[i] = setpassnum;
				for (int k = i + 1; k <= 255 - size; k++)//3pass�z������k
				{
					pass[k] = pass[size + k - 1];
				}
			}
		}
	}

	void Pass_Generator::St_Comp_Pass()
	{
		int bu_pass[100];
		int n = 0;
		int count = 0;
		bool isSt = false;

		while (1)
		{
			if (pass[count] <= 0)
			{
				n = (isSt) ? n + 1 : n;
				isSt = false;
				bu_pass[n] = pass[count];
				n++;
			}
			else if (pass[count] > 0)
			{
				if (isSt == false)
				{
					isSt = true;
					bu_pass[n] = 1;
				}
				else
				{
					bu_pass[n] += 1;
				}
			}
			count++;

			if (n == 100)
			{
				break;
			}
		}

		for (int i = 0; i < 255; i++)
		{
			pass[i] = 0;
		}
		for (int i = 0; i < 100; i++)
		{
			pass[i] = bu_pass[i];
		}
	}

	int Pass_Generator::Ret_NextPass()
	{
		int ret=0;
		if(passcount!=254)
		{
			ret = pass[passcount + 1];
		}
		return ret;
	}

	void Pass_Generator::Show_Pass()
	{
		for(int i=0;i<255;i++)
		{
			printf("pass[%d]=%d\n\r",i,pass[i]);
		}
	}
}


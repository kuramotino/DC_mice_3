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
		pass[1]=1;
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
				pass[n] = 0;
				break;
			}
		}

		if(isOO_Zip)
		{
			Comp_Pass(OO90_R, 3, -7);
			Comp_Pass(OO90_L, 3, -5);
			Comp_Pass(OO180_R, 4, -6);
			Comp_Pass(OO180_L, 4, -4);

			Comp_Pass(Diag_in135_R, 3, -11);
			Comp_Pass(Diag_in135_L, 3, -10);
			Comp_Pass(Diag_in45_R, 2, -9);
			Comp_Pass(Diag_in45_L, 2, -8);
			Comp_Pass(Diag_out135_R, 3, -15);
			Comp_Pass(Diag_out135_L, 3, -14);
			Comp_Pass(Diag_out45_R, 2, -13);
			Comp_Pass(Diag_out45_L, 2, -12);
			Comp_Pass(Diag_V90_R, 2, -17);
			Comp_Pass(Diag_V90_L, 2, -16);
			Comp_Pass(Diag_Stra_R, 1, -100);
			Comp_Pass(Diag_Stra_L, 1, -100);
			Diag_Comp_Pass();
		}
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
			if(i==0)
			{
				continue;
			}

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

	void Pass_Generator::Diag_Comp_Pass()
	{
		int bu_pass[100];
		int n = 0;
		int count = 0;
		bool isSt = false;

		while (1)
		{
			if (pass[count] > -100)
			{
				n = (isSt) ? n + 1 : n;
				isSt = false;
				bu_pass[n] = pass[count];
				n++;
			}
			else if (pass[count] <= -100)
			{
				if (isSt == false)
				{
					isSt = true;
					bu_pass[n] = -100;
				}
				else
				{
					bu_pass[n] += -100;
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

	void Pass_Generator::Conect_v_cal(Shortest_PARAM* s_param,float* M_start_conect_v,float* M_end_conect_v)//直進の接続速度を計算
	{
		if(passcount!=254)
		{
			if((pass[passcount+1]==-2 || pass[passcount+1]==-3))//1現在が直進、次がスラローム
			{
				*M_end_conect_v=s_param->TURN_V;
			}
			else if((pass[passcount+1]==-6 || pass[passcount+1]==-4))//1現在が直進、次が大回り
			{
				*M_end_conect_v=s_param->OO180_V;
			}
			else if((pass[passcount+1]==-7 || pass[passcount+1]==-5))//2現在が直進、次が小回り
			{
				*M_end_conect_v=s_param->OO90_V;
			}
			else if((pass[passcount+1]==-8 || pass[passcount+1]==-9))//2現在が直進、次がin45
			{
				*M_end_conect_v=s_param->Diag_in45_V;
			}
			else if((pass[passcount+1]==-10 || pass[passcount+1]==-11))//2現在が直進、次がin135
			{
				*M_end_conect_v=s_param->Diag_in135_V;
			}
			else if((pass[passcount+1]==-12 || pass[passcount+1]==-13))//2現在が斜め直進、次がout45
			{
				*M_end_conect_v=s_param->Diag_out45_V;
			}
			else if((pass[passcount+1]==-14 || pass[passcount+1]==-15))//2現在が斜め直進、次がout135
			{
				*M_end_conect_v=s_param->Diag_out135_V;
			}
			else if((pass[passcount+1]==-16 || pass[passcount+1]==-17))//2現在が斜め直進、次がV90
			{
				*M_end_conect_v=s_param->Diag_V90_V;
			}
		}

		if(passcount!=0)
		{
			if((pass[passcount+1]==-2 || pass[passcount+1]==-3))//1現在が直進、一個前がスラローム
			{
				*M_start_conect_v=s_param->TURN_V;
			}
			else if((pass[passcount-1]==-6 || pass[passcount-1]==-4))//1現在が直進、一個前が大回り
			{
				*M_start_conect_v=s_param->OO180_V;
			}
			else if((pass[passcount-1]==-7 || pass[passcount-1]==-5))//2現在が直進、一個前が小回り
			{
				*M_start_conect_v=s_param->OO90_V;
			}
			else if((pass[passcount-1]==-12 || pass[passcount-1]==-13))//2現在が直進、一個前がout45
			{
				*M_start_conect_v=s_param->Diag_out45_V;
			}
			else if((pass[passcount-1]==-14 || pass[passcount-1]==-15))//2現在が直進、一個前がout135
			{
				*M_start_conect_v=s_param->Diag_out135_V;
			}
			else if((pass[passcount-1]==-8 || pass[passcount-1]==-9))//2現在が斜め直進、一個前がin45
			{
				*M_start_conect_v=s_param->Diag_out45_V;
			}
			else if((pass[passcount-1]==-10 || pass[passcount-1]==-11))//2現在が斜め直進、一個前がin135
			{
				*M_start_conect_v=s_param->Diag_out135_V;
			}
			else if((pass[passcount-1]==-16 || pass[passcount-1]==-17))//2現在が斜め直進一個前がV90
			{
				*M_start_conect_v=s_param->Diag_V90_V;
			}
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

	void Pass_Generator::PassZipSetting(bool iszip)
	{
		isOO_Zip=iszip;
	}
}


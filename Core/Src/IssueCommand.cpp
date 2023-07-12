/*
 * IssueCommand.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "IssueCommand.h"
#include "Act_Pat.h"
#include "motor_drive.h"
using namespace controll;

namespace Algorizm
{
	void IssueCommand::Init()
	{
		isStart = false;
		isStop = false;
		isM_Start=false;
		isM_Stop=false;
		isPass=false;
		my_plan->SetReturn(false);
		my_plan->SetTansakuEnd(false);
		fail_obj.isFail=false;
	}

	void IssueCommand::Tansaku()
	{
		if (!isStart)
		{
			application::App_Set_Command(first_Stra);
			isStart = true;
		}
		if (!isStop && isStart && !fail_obj.isFail)
		{
			application::App_Command(Front_offset);
			//int bu_next_vec = (!my_plan->RetReturn()) ? my_plan->Adati(4, goal_pos,false) : my_plan->Adati(1, start_pos,false);
			int bu_next_vec = (!my_plan->RetReturn()) ? my_plan->Adati(4, goal_pos,false) : my_plan->s_dijkstra(1, start_pos,false);
			//int bu_next_vec = (!my_plan->RetReturn()) ? my_plan->Adati(4, goal_pos,false) : my_plan->z_dijkstra();
			nextVec = (bu_next_vec > 0) ? Front : ((bu_next_vec == -3) ? Right : ((bu_next_vec == -2) ? Left : Back));
			application::App_Wait();

			switch (nextVec)
			{
			case Left:
				application::App_Set_Command(Left_f_off);
				application::App_Set_Command(Left_sla);
				application::App_Set_Command(Left_b_off);
				//application::App_Set_Command(Stra_Senkai_de_73);
				//application::App_Set_Command(Left_sen);
				//application::App_Set_Command(Stra_Senkai_ac_77);
				break;

			case Front:
				if(bu_next_vec<=1)
				{
					application::App_Set_Command(Mid_Stra);
					application::App_Set_Command(Stra_Wall_Break);
				}
				else
				{
					application::App_Set_Command(Mid_Stra_180,bu_next_vec,TURN_V,Know_MAX_V,TURN_V);
				}
				break;

			case Right:
				application::App_Set_Command(Right_f_off);
				application::App_Set_Command(Right_sla);
				application::App_Set_Command(Right_b_off);
				//application::App_Set_Command(Stra_Senkai_de_73);
				//application::App_Set_Command(Right_sen);
				//application::App_Set_Command(Stra_Senkai_ac_77);
				break;

			case Back:
				//application::App_Set_Command(Stra_de_70);
				//application::App_Set_Command(Right_sen);
				//application::App_Set_Command(Stra_ac_90);
				//application::App_Set_Command(Stra_Senkai_de_83);
				application::App_Set_Command(Senkai_Offset_40);//0横壁との距離を測る
				application::App_Set_Command(Stra_Senkai_de_40);
				if(offset==0)
				{
					application::App_Set_Command(Right_sen);
					application::App_Set_Command(Right_sen);
				}
				else if(offset>0)//1右に寄っているとき
				{
					application::App_Set_Command(Left_sen);
					application::App_Set_Command(UturnOffset, offset);
					application::App_Set_Command(Left_sen);
				}
				else if(offset<0)//2左に寄っているとき
				{
					application::App_Set_Command(Right_sen);
					application::App_Set_Command(UturnOffset, -1.0*offset);
					application::App_Set_Command(Right_sen);
				}
				application::App_Set_Command(Stra_Senkai_ac_90);
				break;
			}
			isStop = my_plan->RetTansakuEnd();
			if(isStop)
			{
				application::App_Set_Command(Stra_Stop);
				application::App_Set_Command(Right_sen);
				application::App_Set_Command(Right_sen);
				//application::App_Command(Stop_Cm);
			}
		}
		else if(fail_obj.isFail)
		{
			isStop=true;
		}
	}

	void IssueCommand::Saitan()
	{
		//test_sound(1.25,100);
		if (!isM_Start)
		{
			my_pass->M_Pass(4, goal_pos);//pass�̐���
			my_plan->MiceInit();
			my_pass->InitPassCount();
			isM_Start = true;
		}
		if (!isM_Stop && isM_Start)
		{
			int nextpass = 0;
			float add_conect_v_start=0;//0直進の接続速度
			float add_conect_v_end=0;//0直進の接続速度
			my_pass->Conect_v_cal(TURN_V, &add_conect_v_start, &add_conect_v_end);//接続速度の計算
			nextpass = my_pass->DecodePass();
			if (nextpass != 0)
			{
				if (nextpass > 0)
				{
					if(!isPass)
					{
						application::App_Set_Command(Saitan_Stra,nextpass,0,MAX_V,TURN_V+add_conect_v_end);
					}
					else if(my_pass->Ret_NextPass()==0)
					{
						application::App_Set_Command(Saitan_Stra,nextpass,TURN_V+add_conect_v_start,MAX_V,0);
					}
					else
					{
						application::App_Set_Command(Saitan_Stra,nextpass,TURN_V+add_conect_v_start,MAX_V,TURN_V+add_conect_v_end);
					}
				}
				else if (nextpass == -2)
				{
//					application::App_Set_Command(Saitan_Left_f_off);
//					application::App_Set_Command(Left_sla);
//					application::App_Set_Command(Left_b_off);
					application::App_Set_Command(Saitan_KO_90_foff);
					application::App_Set_Command(Saitan_KO_90_L);
					application::App_Set_Command(Saitan_KO_90_boff);
				}
				else if (nextpass == -3)
				{
//					application::App_Set_Command(Saitan_Right_f_off);
//					application::App_Set_Command(Right_sla);
//					application::App_Set_Command(Right_b_off);
					application::App_Set_Command(Saitan_KO_90_foff);
					application::App_Set_Command(Saitan_KO_90_R);
					application::App_Set_Command(Saitan_KO_90_boff);
				}
				else if (nextpass == -4)
				{
					//my_micemgr->SetAct(Left_OO180);
					application::App_Set_Command(Saitan_OO_180_foff_L);
					application::App_Set_Command(Saitan_OO_180_L);
					application::App_Set_Command(Saitan_OO_180_boff_L);
				}
				else if (nextpass == -6)
				{
					//my_micemgr->SetAct(Right_OO180);
					application::App_Set_Command(Saitan_OO_180_foff_R);
					application::App_Set_Command(Saitan_OO_180_R);
					application::App_Set_Command(Saitan_OO_180_boff_R);
				}
				else if (nextpass == -5)
				{
					//my_micemgr->SetAct(Left_OO90);
					application::App_Set_Command(Saitan_OO_90_foff);
					application::App_Set_Command(Saitan_OO_90_L);
					application::App_Set_Command(Saitan_OO_90_boff);
				}
				else if (nextpass == -7)
				{
					//my_micemgr->SetAct(Right_OO90);
					application::App_Set_Command(Saitan_OO_90_foff);
					application::App_Set_Command(Saitan_OO_90_R);
					application::App_Set_Command(Saitan_OO_90_boff);
				}
			}
			if(nextpass==0)
			{
				isM_Stop=true;
			}
			isPass=true;
		}
		else if(fail_obj.isFail)
		{
			isM_Stop=true;
		}
	}

	void IssueCommand::SetPlan(Planning* plan)
	{
		my_plan = plan;
	}

	void IssueCommand::SetPassGene(Pass_Generator* bu_pass)
	{
		my_pass = bu_pass;
	}
}

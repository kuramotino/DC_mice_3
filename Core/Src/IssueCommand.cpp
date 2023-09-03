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
		my_plan->MiceInit();
	}

	void IssueCommand::Tansaku()
	{
		if (!isStart)
		{
			application::App_Set_Command(Stra_ac_142);
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
				application::App_Set_Command(Senkai_Offset_40);//0横壁との距離を測る、壁当てできるか判定する
				application::App_Set_Command(Stra_Senkai_de_40);
				if(lfr_wall_status!=0)//1壁当てできるとき
				{
					if(lfr_wall_status==1)//1前壁のみ
					{
						application::App_Set_Command(Right_sen);
						application::App_Set_Command(Right_sen);
						application::App_Set_Command(Stra_Back);
						//HAL_Delay(1000);
						application::App_Set_Command(Stra_ac_142);
					}
					else if(lfr_wall_status==2)//2前壁+左壁
					{
						application::App_Set_Command(Right_sen);
						application::App_Set_Command(Stra_Back);
						application::App_Set_Command(Stra_Wall_Hit);
						application::App_Set_Command(Right_sen);
						application::App_Set_Command(Stra_Back);
						//HAL_Delay(1000);
						application::App_Set_Command(Stra_ac_142);
					}
					else if(lfr_wall_status==3)//3前壁+右壁
					{
						application::App_Set_Command(Left_sen);
						application::App_Set_Command(Stra_Back);
						application::App_Set_Command(Stra_Wall_Hit);
						application::App_Set_Command(Left_sen);
						application::App_Set_Command(Stra_Back);
						//HAL_Delay(1000);
						application::App_Set_Command(Stra_ac_142);
					}
				}
				else//壁当てできないとき
				{
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
				}
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

	void IssueCommand::Saitan(int index)
	{
		//test_sound(1.25,100);
		if (!isM_Start)
		{
			my_pass->M_Pass(4, goal_pos);//pass�̐���
			my_plan->MiceInit();
			my_pass->InitPassCount();
			isM_Start = true;
			Shortest_PARAM bu_param(index);
			s_param=bu_param;
		}
		if (!isM_Stop && isM_Start)
		{
			int nextpass = 0;
			float conect_v_start=0;//0直進またはオフセットの接続速度
			float conect_v_end=0;//0直進またはオフセットの接続速度
			my_pass->Conect_v_cal(&s_param, &conect_v_start, &conect_v_end);//接続速度の計算
			nextpass = my_pass->DecodePass();
			if (nextpass != 0)
			{
				if (nextpass > 0)
				{
					isContinueStra=true;
					if(!isPass)
					{
						application::App_Set_Command(s_param.F_Stra,1,0,conect_v_end,conect_v_end);
						while(1)
						{
							application::App_Set_Command(s_param.S_Stra,nextpass-1,conect_v_end,s_param.MAX_V,conect_v_end);
							if(!isContinueStra)
							{
								break;
							}
						}
					}
					else if(my_pass->Ret_NextPass()==0)
					{
						application::App_Set_Command(s_param.L_Stra,nextpass,conect_v_start,s_param.MAX_LAST_V,0);
					}
					else
					{
						while(1)
						{
							application::App_Set_Command(s_param.S_Stra,nextpass,conect_v_start,s_param.MAX_V,conect_v_end);
							if(!isContinueStra)
							{
								break;
							}
						}
					}
				}
				else if (nextpass <= -100)
				{
					isContinueStra=true;
					while(1)
					{
						application::App_Set_Command(s_param.Diag_Stra,nextpass/(-100),conect_v_start,s_param.MAX_DIAG_V,conect_v_end);
						if(!isContinueStra)
						{
							break;
						}
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
					conect_v_start = (conect_v_start==0) ? s_param.OO180_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.OO180_V : conect_v_end;
					application::App_Set_Command(s_param.OO_180_L_foff,1,conect_v_start,s_param.OO180_V,s_param.OO180_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO180_V,s_param.OO180_V,s_param.OO180_V);
					application::App_Set_Command(s_param.OO_180_L);
					application::App_Set_Command(s_param.OO_180_L_boff,1,s_param.OO180_V,s_param.OO180_V,conect_v_end);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO180_V,s_param.OO180_V,conect_v_end);
				}
				else if (nextpass == -6)
				{
					//my_micemgr->SetAct(Right_OO180);
					conect_v_start = (conect_v_start==0) ? s_param.OO180_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.OO180_V : conect_v_end;
					application::App_Set_Command(s_param.OO_180_R_foff,1,conect_v_start,s_param.OO180_V,s_param.OO180_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO180_V,s_param.OO180_V,s_param.OO180_V);
					application::App_Set_Command(s_param.OO_180_R);
					application::App_Set_Command(s_param.OO_180_R_boff,1,s_param.OO180_V,s_param.OO180_V,conect_v_end);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO180_V,s_param.OO180_V,conect_v_end);
				}
				else if (nextpass == -5)
				{
					//my_micemgr->SetAct(Left_OO90);
					conect_v_start = (conect_v_start==0) ? s_param.OO90_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.OO90_V : conect_v_end;
					application::App_Set_Command(s_param.OO_90_L_foff,1,conect_v_start,s_param.OO90_V,s_param.OO90_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO90_V,s_param.OO90_V,s_param.OO90_V);
					application::App_Set_Command(s_param.OO_90_L);
					application::App_Set_Command(s_param.OO_90_L_boff,1,s_param.OO90_V,s_param.OO90_V,conect_v_end);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO90_V,s_param.OO90_V,conect_v_end);
				}
				else if (nextpass == -7)
				{
					//my_micemgr->SetAct(Right_OO90);
					conect_v_start = (conect_v_start==0) ? s_param.OO90_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.OO90_V : conect_v_end;
					application::App_Set_Command(s_param.OO_90_R_foff,1,conect_v_start,s_param.OO90_V,s_param.OO90_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO90_V,s_param.OO90_V,s_param.OO90_V);
					application::App_Set_Command(s_param.OO_90_R);
					application::App_Set_Command(s_param.OO_90_R_boff,1,s_param.OO90_V,s_param.OO90_V,conect_v_end);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.OO90_V,s_param.OO90_V,conect_v_end);
				}
				else if (nextpass == -8)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_in45_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_in45_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_in45_L_foff,1,conect_v_start,s_param.Diag_in45_V,s_param.Diag_in45_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.Diag_in45_V,s_param.Diag_in45_V,s_param.Diag_in45_V);
					application::App_Set_Command(s_param.Diag_in45_L);
					application::App_Set_Command(s_param.Diag_in45_L_boff,1,s_param.Diag_in45_V,s_param.Diag_in45_V,conect_v_end);
				}
				else if (nextpass == -9)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_in45_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_in45_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_in45_R_foff,1,conect_v_start,s_param.Diag_in45_V,s_param.Diag_in45_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.Diag_in45_V,s_param.Diag_in45_V,s_param.Diag_in45_V);
					application::App_Set_Command(s_param.Diag_in45_R);
					application::App_Set_Command(s_param.Diag_in45_R_boff,1,s_param.Diag_in45_V,s_param.Diag_in45_V,conect_v_end);
				}
				else if (nextpass == -10)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_in135_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_in135_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_in135_L_foff,1,conect_v_start,s_param.Diag_in135_V,s_param.Diag_in135_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.Diag_in135_V,s_param.Diag_in135_V,s_param.Diag_in135_V);
					application::App_Set_Command(s_param.Diag_in135_L);
					application::App_Set_Command(s_param.Diag_in135_L_boff,1,s_param.Diag_in135_V,s_param.Diag_in135_V,conect_v_end);
				}
				else if (nextpass == -11)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_in135_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_in135_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_in135_R_foff,1,conect_v_start,s_param.Diag_in135_V,s_param.Diag_in135_V);
					application::App_Set_Command(s_param.S_WBreak,1,s_param.Diag_in135_V,s_param.Diag_in135_V,s_param.Diag_in135_V);
					application::App_Set_Command(s_param.Diag_in135_R);
					application::App_Set_Command(s_param.Diag_in135_R_boff,1,s_param.Diag_in135_V,s_param.Diag_in135_V,conect_v_end);
				}
				else if (nextpass == -12)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_out45_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_out45_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_out45_L_foff,1,conect_v_start,s_param.Diag_out45_V,s_param.Diag_out45_V);
					application::App_Set_Command(s_param.Diag_out45_L);
					application::App_Set_Command(s_param.Diag_out45_L_boff,1,s_param.Diag_out45_V,s_param.Diag_out45_V,conect_v_end);
				}
				else if (nextpass == -13)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_out45_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_out45_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_out45_R_foff,1,conect_v_start,s_param.Diag_out45_V,s_param.Diag_out45_V);
					application::App_Set_Command(s_param.Diag_out45_R);
					application::App_Set_Command(s_param.Diag_out45_R_boff,1,s_param.Diag_out45_V,s_param.Diag_out45_V,conect_v_end);
				}
				else if (nextpass == -14)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_out135_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_out135_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_out135_L_foff,1,conect_v_start,s_param.Diag_out135_V,s_param.Diag_out135_V);
					application::App_Set_Command(s_param.Diag_out135_L);
					application::App_Set_Command(s_param.Diag_out135_L_boff,1,s_param.Diag_out135_V,s_param.Diag_out135_V,conect_v_end);
				}
				else if (nextpass == -15)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_out135_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_out135_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_out135_R_foff,1,conect_v_start,s_param.Diag_out135_V,s_param.Diag_out135_V);
					application::App_Set_Command(s_param.Diag_out135_R);
					application::App_Set_Command(s_param.Diag_out135_R_boff,1,s_param.Diag_out135_V,s_param.Diag_out135_V,conect_v_end);
				}
				else if (nextpass == -16)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_V90_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_V90_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_V90_L_foff,1,conect_v_start,s_param.Diag_V90_V,s_param.Diag_V90_V);
					application::App_Set_Command(s_param.Diag_V90_L);
					application::App_Set_Command(s_param.Diag_V90_L_boff,1,s_param.Diag_V90_V,s_param.Diag_V90_V,conect_v_end);
				}
				else if (nextpass == -17)
				{
					conect_v_start = (conect_v_start==0) ? s_param.Diag_V90_V : conect_v_start;
					conect_v_end = (conect_v_end==0) ? s_param.Diag_V90_V : conect_v_end;
					application::App_Set_Command(s_param.Diag_V90_R_foff,1,conect_v_start,s_param.Diag_V90_V,s_param.Diag_V90_V);
					application::App_Set_Command(s_param.Diag_V90_R);
					application::App_Set_Command(s_param.Diag_V90_R_boff,1,s_param.Diag_V90_V,s_param.Diag_V90_V,conect_v_end);
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

	void IssueCommand::DebugWallBreak()
	{
		isContinueStra=true;
		while(1)
		{
			application::App_Set_Command(FF_Test_Stra_1,2,1000,1000,1000);//30
			if(!isContinueStra)
			{
				break;
			}
		}
	}

	void IssueCommand::DebugDiagBW()
	{
		isContinueStra=true;
		while(1)
		{
			application::App_Set_Command(S_Diag_Stra,4,0,500,0);
			if(!isContinueStra)
			{
				break;
			}
		}
	}
}

/*
 * IssueCommand.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "IssueCommand.h"
#include "Act_Pat.h"
using namespace controll;

namespace Algorizm
{
	void IssueCommand::Init()
	{
		isStart = false;
		isStop = false;
		my_plan->SetReturn(false);
		my_plan->SetTansakuEnd(false);
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
			nextVec = (!my_plan->RetReturn()) ? my_plan->Adati(4, goal_pos) : my_plan->Adati(1, start_pos);
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
				application::App_Set_Command(Mid_Stra);
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
				application::App_Set_Command(Stra_Senkai_de_83);
				application::App_Set_Command(Right_sen);
				application::App_Set_Command(Right_sen);
				application::App_Set_Command(Stra_Senkai_ac_90);
				break;
			}
			isStop = my_plan->RetTansakuEnd();
			if(isStop)
			{
				application::App_Set_Command(Stra_Stop);
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

	}

	void IssueCommand::SetPlan(Planning* plan)
	{
		my_plan = plan;
	}
}

/*
 * CommandExecuter.cpp
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */
#include <iostream>
#include <string>
#include <list>
#include "CommandExecuter.h"
#include "BaseCtrl.h"
#include "BaseCommand.h"
#include "kasoku.h"
#include "PWM_Output.h"
#include "CommandStatus.h"
#include "gpio.h"
using namespace std;

namespace controll
{
	void controll::CommandExecuter::addCtrl(BaseCtrl* ctrl)
	{
		CtrlList.push_back(ctrl);
	}

	void controll::CommandExecuter::add_kasoku_PWM(kasoku* ka,PWM_Out* pwm)
	{
		kasoku_listenar=ka;
		pwm_listenar=pwm;
	}

	void controll::CommandExecuter::notify_Ctrl(Command cm)
	{
		std::list<controll::BaseCtrl*>::iterator i;
		for(i=CtrlList.begin();i!=CtrlList.end();i++)
		{
			(*i)->updata(cm);
		}
	}

	void controll::CommandExecuter::notify_kasoku_PWM(Command cm)
	{
		kasoku_listenar->updata(cm);
		pwm_listenar->updata(cm);
	}

	void controll::CommandExecuter::set_cs(CommandStatus* cs)
	{
		my_cs=cs;
	}

	void controll::CommandExecuter::polling_cs()//TIM6割り込みでCommandStatusを監視し、offなら制御器をstopさせる
	{
		if((my_cs->show_status())==Normal_End || (my_cs->show_status())==Forced_End)
		{
			if(stop_cm.isStop==false)
			{
				Command bu_stop_cm(Stop);
				stop_cm=bu_stop_cm;
				//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
			}
			//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
			notify_Ctrl(stop_cm);
			notify_kasoku_PWM(stop_cm);
		}
		else if(my_cs->show_status()==Break_End)
		{
			if(break_cm.isBreakStop==false)
			{
				Command bu_break_cm(Break_Stop);
				break_cm=bu_break_cm;
			}
			notify_Ctrl(break_cm);
			notify_kasoku_PWM(break_cm);
		}
		else if((my_cs->show_status())==Abnormal_End)
		{
			if(fail_cm.isFailStop==false)
			{
				Command bu_fail_cm(Fail_Stop);
				fail_cm=bu_fail_cm;
			}
			notify_Ctrl(fail_cm);
			notify_kasoku_PWM(fail_cm);
		}
	}

	enum status controll::CommandExecuter::return_now_status()//現在のコマンドの実行状態を返す関数(Application層に呼ばれる)
	{
		return my_cs->show_status();
	}

	void controll::CommandExecuter::wake_CtrlSystem(Command cm)//制御システムを起動させる(Application層に呼ばれる)
	{
		my_cs->on_command(Run);
		notify_Ctrl(cm);
		notify_kasoku_PWM(cm);
		my_cs->on_command(Run);
	}
}


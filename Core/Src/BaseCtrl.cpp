/*
 * BaseCtrl.cpp
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */
#include "BaseCtrl.h"
#include "BaseCommand.h"
#include "CommandStatus.h"
#include "kasoku.h"
#include "PWM_Output.h"
#include "InputData.h"

namespace controll
{
	void controll::BaseCtrl::updata(Command* cm)
	{
		now_cm=cm;
		isStop=now_cm->isStop;
	}

	void controll::BaseCtrl::add_obj(kasoku* ka,PWM_Out* pwm,InputData* input,CommandStatus* cs)
	{
		my_kasoku=ka;
		my_pwm=pwm;
		my_input=input;
		my_cs=cs;
	}

	void controll::BaseCtrl::add_obj(kasoku* ka,PWM_Out* pwm,InputData* input,CommandStatus* cs,CtrlWindow* window)
	{
		my_kasoku=ka;
		my_pwm=pwm;
		my_input=input;
		my_cs=cs;
		my_ctrlwin=window;
	}

	void controll::BaseCtrl::status_off(enum status st)//CommandStatusをoffにする
	{
		my_cs->off_command(st);//-1:強制終了
	}

	void controll::BaseCtrl::transmit(float message)
	{

	}

	void controll::BaseCtrl::receive(float message)
	{

	}

	int controll::BaseCtrl::RetData()
	{

	}
}

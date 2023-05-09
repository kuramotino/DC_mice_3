/*
 * BaseCtrl.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */

#ifndef INC_BASECTRL_H_
#define INC_BASECTRL_H_
#include "BaseCommand.h"
#include "CommandStatus.h"
#include "kasoku.h"
#include "PWM_Output.h"
#include "InputData.h"

namespace controll
{
	class BaseCtrl
	{
	protected:
		Command now_cm;
		kasoku* my_kasoku;
		PWM_Out* my_pwm;
		InputData* my_input;
		CommandStatus* my_cs;

	protected:
		bool isStop=true;//現在動作がstopしているかどうか

	public:
		virtual void updata(Command cm);
		void add_obj(kasoku* ka,PWM_Out* pwm,InputData* input,CommandStatus* cs);
		void status_off(enum status st);
	};
}


#endif /* INC_BASECTRL_H_ */

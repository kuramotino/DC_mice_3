/*
 * CommandExecuter.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */

#ifndef INC_COMMANDEXECUTER_H_
#define INC_COMMANDEXECUTER_H_
#include "kasoku.h"
#include "PWM_Output.h"
#include "BaseCtrl.h"
#include "BaseCommand.h"
#include "CommandStatus.h"
#include <iostream>
#include <string>
#include <list>

namespace controll
{

	class CommandExecuter
	{
		std::list<controll::BaseCtrl*> CtrlList;
		kasoku* kasoku_listenar;
		PWM_Out* pwm_listenar;
		Command stop_cm;
		Command fail_cm;
		Command break_cm;
		CommandStatus* my_cs;

	public:
		void addCtrl(BaseCtrl* ctrl);//BaseCtrlを継承したオブジェクトを通知リストに登録する
		void add_kasoku_PWM(kasoku* ka,PWM_Out* pwm);//kasoku、pwmオブジェクトを通知リストに登録する
		void notify_Ctrl(Command cm);//BaseCtrlを継承したオブジェクトにCommandを通知する
		void notify_kasoku_PWM(Command cm);//kasoku、pwmオブジェクトにCommandを通知する
		void set_cs(CommandStatus* cs);//CommandStatusオブジェクトをセットする
		void polling_cs();//TIM6割り込みでCommandStatusオブジェクトを監視し、変化があれば通知リストに通知する
		enum status return_now_status();//現在のコマンドの実行状態を返す関数(Application層に呼ばれる)
		void wake_CtrlSystem(Command cm);//制御システムを起動させる(Application層に呼ばれる)

	};
}


#endif /* INC_COMMANDEXECUTER_H_ */

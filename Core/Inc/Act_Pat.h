/*
 * Act_Pat.h
 *
 *  Created on: 2023/04/16
 *      Author: Ryu
 */

#ifndef INC_ACT_PAT_H_
#define INC_ACT_PAT_H_
#include "BaseCommand.h"
#include "Init_Controll_Objs.h"

namespace application
{
	using namespace controll;
	void App_Set_Command(enum command_type c_type);//制御部にコマンドを発行し、動作が終わるまで待つ関数
	void App_Set_Command(enum command_type c_type,int st_num,float start_speed,float max_speed,float end_speed);
	void App_Set_Command(enum command_type c_type,float x);
	void App_Command(enum command_type c_type);//コマンドの発行のみを行う関数
	void App_Wait();//コマンドが実行されるまで待つ関数
}


#endif /* INC_ACT_PAT_H_ */

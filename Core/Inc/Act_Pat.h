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
	void App_Set_Command(enum command_type c_type);
}


#endif /* INC_ACT_PAT_H_ */

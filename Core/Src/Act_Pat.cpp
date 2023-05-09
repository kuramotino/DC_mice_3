/*
 * Act_Pat.cpp
 *
 *  Created on: 2023/04/16
 *      Author: Ryu
 */
#include "Act_Pat.h"
#include "BaseCommand.h"
#include "Init_Controll_Objs.h"
#include "gpio.h"
using namespace controll;
namespace application
{
	void App_Set_Command(enum command_type c_type)
	{
		Command bu_cm(c_type);
		cx_obj.wake_CtrlSystem(bu_cm);
		//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		while(cx_obj.return_now_status()==Run)
		{
			HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		}
	}
}


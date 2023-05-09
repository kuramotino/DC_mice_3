/*
 * CommandStatus.cpp
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */
#include "CommandStatus.h"
#include "gpio.h"

namespace controll
{
	void controll::CommandStatus::off_command(enum status cs)
	{
		if(cs!=Run)
		{
			command_status=cs;
			HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		}
	}

	void controll::CommandStatus::on_command(enum status cs)
	{
		if(cs==Run)
		{
			command_status=cs;
			HAL_GPIO_WritePin(ILED10_GPIO_Port,ILED10_Pin,GPIO_PIN_SET);
		}
	}

	enum status controll::CommandStatus::show_status()
	{
		//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		return command_status;
	}
}

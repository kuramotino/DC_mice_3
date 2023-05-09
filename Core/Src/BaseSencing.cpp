/*
 * BaseSencing.cpp
 *
 *  Created on: Apr 15, 2023
 *      Author: Ryu
 */
#include "BaseSencing.h"
#include "InputData.h"

namespace module
{
	void module::BaseSencing::add_input(controll::InputData* input)//InputDataObjをセットする関数
	{
		my_input=input;
	}

	void module::BaseSencing::sensor_input()//センサー値をInputDataに入力する関数(encoderやgyroにオーバーライドされる)
	{

	}
}


/*
 * BaseSencing.h
 *
 *  Created on: Apr 15, 2023
 *      Author: Ryu
 */

#ifndef INC_BASESENCING_H_
#define INC_BASESENCING_H_
#include "InputData.h"

namespace module
{
	class BaseSencing
	{
	protected:
		controll::InputData* my_input;

	public:
		void add_input(controll::InputData* input);
		virtual void sensor_input();
	};
}


#endif /* INC_BASESENCING_H_ */

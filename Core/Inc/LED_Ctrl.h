/*
 * LED_Ctrl.h
 *
 *  Created on: 2023/06/13
 *      Author: Ryu
 */

#ifndef INC_LED_CTRL_H_
#define INC_LED_CTRL_H_

#include "gpio.h"

namespace module
{
	class LED_Ctrl
	{
		int led_controll_status;
		int gpio_pin_set[8];
	public:
		void set_all_led(int controll_status);
	};
}

#endif /* INC_LED_CTRL_H_ */

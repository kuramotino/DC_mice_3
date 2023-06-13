/*
 * LED_Ctrl.cpp
 *
 *  Created on: 2023/06/13
 *      Author: Ryu
 */
#include "LED_Ctrl.h"
namespace module
{
	void module::LED_Ctrl::set_all_led(int controll_status)
	{
		led_controll_status=controll_status;
		for(int i=0;i<8;i++)
		{
			gpio_pin_set[i]=((controll_status & (1<<i))==(1<<i)) ? 1 : 0;
		}
		HAL_GPIO_WritePin(ILED1_GPIO_Port,ILED1_Pin,(GPIO_PinState)gpio_pin_set[0]);
		HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,(GPIO_PinState)gpio_pin_set[1]);
		HAL_GPIO_WritePin(ILED5_GPIO_Port,ILED5_Pin,(GPIO_PinState)gpio_pin_set[2]);
		HAL_GPIO_WritePin(ILED6_GPIO_Port,ILED6_Pin,(GPIO_PinState)gpio_pin_set[3]);
		HAL_GPIO_WritePin(ILED7_GPIO_Port,ILED7_Pin,(GPIO_PinState)gpio_pin_set[4]);
		HAL_GPIO_WritePin(ILED8_GPIO_Port,ILED8_Pin,(GPIO_PinState)gpio_pin_set[5]);
		HAL_GPIO_WritePin(ILED9_GPIO_Port,ILED9_Pin,(GPIO_PinState)gpio_pin_set[6]);
		HAL_GPIO_WritePin(ILED10_GPIO_Port,ILED10_Pin,(GPIO_PinState)gpio_pin_set[7]);
	}
}

/*
 * test_1.cpp
 *
 *  Created on: 2023/03/12
 *      Author: Ryu
 */
#include <test_1.h>
#include "stm32f4xx_hal.h"
#include "gpio.h"

void LedBlink::toggle() {
    HAL_GPIO_TogglePin(ILED8_GPIO_Port,ILED8_Pin);
    //HAL_Delay(100);
}


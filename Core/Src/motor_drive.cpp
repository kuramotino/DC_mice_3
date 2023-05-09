/*
 * motor_drive.c
 *
 *  Created on: Mar 26, 2023
 *      Author: Ryu
 */
#include <main.h>
#include "motor_drive.h"
#include "tim.h"


void R_test_drive(void)
{
	/*init channel 1,2 motor*/
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);

	    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	    HAL_Delay(100);

	    int duty = (int)(280 - (140));  //50%
	    /* setting do pwm*/
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, duty);

	    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
	    HAL_Delay(100);

	    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
	    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
}

void L_test_drive(void)
{
	/*init channel 1,2 motor*/
	    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);
	    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 0);

	    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	    HAL_Delay(100);

	    int duty = (int)(280 - (140));  //50%
	    /* setting do pwm*/
	    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, duty);
	    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, duty);

	    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	    HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
	    HAL_Delay(100);

	    HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
	    HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
}

void R_L_test_drive(void)
{
	/*init channel 1,2 motor*/
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
		    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
		    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);
		    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 0);

		    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
		    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
		    HAL_Delay(100);

		    int duty = (int)(5000);  //50%
		    /* setting do pwm*/
		    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
		    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, duty);
		    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, duty);
		    __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, duty);

		    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
		    HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		    HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
		    HAL_Delay(100);

		    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
		    HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);
		    HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
}

void test_sound(void)
{
	int duty=(int)(270000-(200000));
	__HAL_TIM_SET_AUTORELOAD(&htim2, 270000);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty);


	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_Delay(1000);

	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
}

int PressButton()
{
	//1ボタンが押されたか
	if(HAL_GPIO_ReadPin(SWITCH_GPIO_Port,SWITCH_Pin)==0)
	{
		return 1;
	}
	return 0;
}

void test_suction(void)
{
	/*init channel 1,2 motor*/
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	HAL_Delay(100);
	int duty = (int)(300 - (140));  //50%
	__HAL_TIM_SET_AUTORELOAD(&htim2, 300);
	/* setting do pwm*/
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, duty);
	HAL_Delay(1000);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
}



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
		cx_obj.cx_cm=bu_cm;
		cx_obj.wake_CtrlSystem(&(cx_obj.cx_cm));
		//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		while(cx_obj.return_now_status()==Run)
		{
			//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		}
	}

	void App_Set_Command(enum command_type c_type,int st_num,float v_start,float v_max,float v_end)
	{
		Command bu_cm(c_type);
		bu_cm.bu_tar_x*=st_num;
		bu_cm.bu_tar_x-=(c_type==Mid_Stra_180)?10:0;//0既知加速の直線なら
		bu_cm.bu_tar_v_start=v_start;
		bu_cm.bu_tar_v_max=v_max;
		bu_cm.bu_tar_v_end=v_end;
		cx_obj.cx_cm=bu_cm;
		cx_obj.wake_CtrlSystem(&(cx_obj.cx_cm));
		//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		while(cx_obj.return_now_status()==Run)
		{
			//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		}
	}

	void App_Set_Command(enum command_type c_type,float x)
	{
		Command bu_cm(c_type);
		bu_cm.bu_tar_x=x;
		cx_obj.cx_cm=bu_cm;
		cx_obj.wake_CtrlSystem(&(cx_obj.cx_cm));
		//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		while(cx_obj.return_now_status()==Run)
		{
			//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		}
	}

	void App_Command(enum command_type c_type)
	{
		Command bu_cm(c_type);
		cx_obj.cx_cm=bu_cm;
		cx_obj.wake_CtrlSystem(&(cx_obj.cx_cm));
	}

	void App_Wait()
	{
		while(cx_obj.return_now_status()==Run)
		{
			//HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
		}
	}
}


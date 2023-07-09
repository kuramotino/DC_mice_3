/*
 * Init_Controll_Objs.h
 *
 *  Created on: Apr 15, 2023
 *      Author: Ryu
 */

#ifndef INC_INIT_CONTROLL_OBJS_H_
#define INC_INIT_CONTROLL_OBJS_H_
#include "PL_sensor.h"
#include "CommandExecuter.h"
#include "kasoku.h"
#include "PWM_Output.h"
#include "CommandStatus.h"
#include "InputData.h"
#include "spi_com.h"
#include "encoder.h"
#include "PID_Ctrl.h"
#include "Wall_Controll.h"
#include "PL_sensor.h"
#include "FailSafe.h"
#include "LED_Ctrl.h"
#include "Front_Offset_Ctrl.h"
#include "Back_Offset_Ctrl.h"
#include "Senkai_Offset_Ctrl.h"
#include "Break_Wall_Ctrl.h"

extern controll::CommandExecuter cx_obj;
extern controll::kasoku ksk_obj;
extern controll::PWM_Out pwm_obj;
extern controll::CommandStatus cs_obj;
extern controll::Command com_obj;
extern controll::InputData input_obj;
extern module::Enc enc_obj;
extern module::Gyro gyro_obj;
extern module::PL_sensor pl_obj;
extern controll::PID_Ctrl pid_obj;
extern controll::FailSafe fail_obj;
extern controll::Wall_Ctrl wall_obj;
extern bool init_flag;
extern module::LED_Ctrl led_obj;
extern controll::Front_Offset_Ctrl front_offset_obj;
extern controll::Back_Offset_Ctrl back_offset_obj;
extern controll::Senkai_Offset_Ctrl senkai_offset_obj;
extern controll::Break_Wall_Ctrl break_wall_obj;

void Init_Controll();
void Sync_Module();
void Sync_Mo_R();//右モータの割り込み処理
void Sync_Mo_L();//左モータの割り込み処理


#endif /* INC_INIT_CONTROLL_OBJS_H_ */

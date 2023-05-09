/*
 * PWM_Output.cpp
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */
#include "PWM_Output.h"
#include "BaseCommand.h"
#include "CommandStatus.h"
#include "math.h"
#include "gpio.h"

namespace controll
{
	controll::PWM_Out::PWM_Out(void)//pwm_outのコンストラクタ
	{
		isDutyEnd=true;
	}

	void controll::PWM_Out::set_cs(CommandStatus* cs)
	{
		my_cs=cs;
	}

	void controll::PWM_Out::updata(Command cm)//現在のコマンドを更新(CommandExecuterに呼ばれる)
	{
		now_cm=cm;
		isDutyEnd=now_cm.isStop;
		duty_FF_stra=0;
		duty_FF_turn=0;
		duty_FB_stra=0;
		duty_FB_turn=0;
		if(isDutyEnd==false)
		{
			set_pwm();
		}
	}

	void controll::PWM_Out::updata_x_v(float x,float v,bool isKasokuEnd,bool isBreak)//kasokuから現在のxとvとフラグを取得(kasokuから呼ばれる)
	{
		now_x=x;
		now_v=v;
		bool bu_isKasokuEnd=isKasokuEnd;
		bu_isBreak=isBreak;
		if(bu_isKasokuEnd==true && isDutyEnd==false)
		{
			status_off();
			HAL_GPIO_WritePin(ILED2_GPIO_Port,ILED2_Pin,GPIO_PIN_SET);
			isDutyEnd=isKasokuEnd;
		}
	}

	void controll::PWM_Out::updata_PID(float fb_stra,float fb_turn)//PIDから現在のPID値を取得(PID_Ctrlから呼ばれる)
	{
		duty_FB_stra=fb_stra;
		duty_FB_turn=fb_turn;
	}

	void controll::PWM_Out::updata_Wall_PID(float wall_pid)//Wall_Ctrlから現在の壁制御量を取得(Wall_Ctrlから呼ばれる)
	{
		duty_Wall_PID=wall_pid;
	}

	void controll::PWM_Out::set_pwm()//duty変換を開始する関数
	{
		target_a=now_cm.bu_tar_a;
	}

	void controll::PWM_Out::pwm()//duty変換を行う関数
	{
		if(isDutyEnd==false)
		{
			if(now_cm.isTurn==true)
			{
				duty_FF_stra=1/V_bat*(R/kt*(m*now_cm.ga/(2*10*10*10))*taiya_dirmeter/n+ke*(60*n*now_cm.gv/2/3.14/taiya_dirmeter));
				duty_FF_turn=1/V_bat*((turn_A*R*10*10*10)/kt*(I*target_a*(3.14/180)/L)*taiya_dirmeter/n+ke*(turn_B*60*n*L*now_v*(3.14/180)/4/3.14/taiya_dirmeter));
				/*if(now_cm.MoveVec==true)
				{
					cw=Left;
				}
				else
				{
					cw=Right;
				}*/
			}
			else
			{
				duty_FF_stra=1/V_bat*(R/kt*(m*target_a/(2*10*10*10))*taiya_dirmeter/n+ke*(60*n*now_v/2/3.14/taiya_dirmeter));
				duty_FF_turn=0;
				if(now_cm.MoveVec==true)
				{
					cw_R=Front;
					cw_L=Front;
				}
				else
				{
					cw_R=Back;
					cw_L=Back;
				}
			}

			if(now_cm.isTurn==true)
			{
				float cwvec;
				if(now_cm.MoveVec==true)//左回転
				{
					cwvec=1;
				}
				else//右回転
				{
					cwvec=-1;
				}

				/*if((duty_FB_stra+duty_FF_stra)<0)
				{
					duty_FB_stra=-duty_FF_stra;
				}*/


				duty_R=duty_FF_stra+cwvec*duty_FF_turn+duty_FB_stra+cwvec*duty_FB_turn;
				duty_L=duty_FF_stra-1*cwvec*duty_FF_turn+duty_FB_stra-1*cwvec*duty_FB_turn;

				/*if((duty_FB_stra+duty_FF_stra)<0)
				{
					duty_FB_stra=-duty_FF_stra;
				}*/

				if(duty_R<0)
				{
					cw_R=Back;
				}
				else
				{
					cw_R=Front;
				}

				if(duty_L<0)
				{
					cw_L=Back;
				}
				else
				{
					cw_L=Front;
				}

				duty_R=fabs(duty_R);
				duty_L=fabs(duty_L);
			}
			else
			{
				duty_R=duty_FF_stra+duty_FF_turn+duty_FB_stra+duty_FB_turn+duty_Wall_PID;
				duty_L=duty_FF_stra-duty_FF_turn+duty_FB_stra-duty_FB_turn-duty_Wall_PID;
			}

			if(duty_R>1)
			{
				duty_R=1;
			}
			if(duty_L>1)
			{
				duty_L=1;
			}
			if(duty_R<0)
			{
				duty_R=0;
			}
			if(duty_L<0)
			{
				duty_L=0;
			}

			if(log_count!=1200)
			{
				now_R_log[log_count]=duty_R;
				now_L_log[log_count]=duty_L;
				log_count++;
			}
		}
	}

	void controll::PWM_Out::out_duty(float* dutyR,float* dutyL,enum turn* bu_cw_R,enum turn* bu_cw_L)
	{
		*dutyR=duty_R;
		*dutyL=duty_L;
		*bu_cw_R=cw_R;
		*bu_cw_L=cw_L;
		if(now_cm.isFailStop==true || now_cm.isBreakStop==true)
		{
			*dutyR=0;
			*dutyL=0;
			*bu_cw_R=cw_R;
			*bu_cw_L=cw_L;
		}
	}

	void controll::PWM_Out::status_off()
	{
		if(bu_isBreak==false)
		{
			my_cs->off_command(Normal_End);//1:通常終了
		}
		else
		{
			my_cs->off_command(Break_End);//2:Break終了
		}
	}
}

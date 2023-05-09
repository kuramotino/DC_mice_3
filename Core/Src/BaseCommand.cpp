/*
 * BaseCommand.cpp
 *
 *  Created on: Apr 13, 2023
 *      Author: Ryu
 */
#include "BaseCommand.h"
namespace controll
{
	controll::Command::Command()
	{
		bu_tar_a=3000;//1目標加速度
						bu_tar_v_start=100;//2目標初速度
						bu_tar_v_max=500;//3目標最高速度
						bu_tar_v_end=100;//4目標終端速度
						bu_tar_x=360;//5目標距離
						gv=800;//6重心速度
						isStop=false;//stopさせるかどうか
						isFailStop=false;//FailSafeでstopさせるか
						isPID_Stop=false;//PIDをstopさせるか
						isTurn=false;//turnかどうか
	}

	controll::Command::Command(enum command_type type)
	{
		switch (type)
		{
			case Stra:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=630;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;//壁制御のPIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case Left_sla:
				bu_tar_a=5730;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=286;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=90;//5目標距離
				gv=500;//6重心速度
				ga=3000;//7重心加速度
				MoveVec=true;//左回転
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
				isTurn=true;//turnかどうか
				break;

			case Right_sla:
				bu_tar_a=5730;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=286;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=90;//5目標距離
				gv=500;//6重心速度
				ga=3000;//7重心加速度
				MoveVec=false;//右回転
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
				isTurn=true;//turnかどうか
				break;

			case Left_sen:
				bu_tar_a=5730;//1目標加速度
								bu_tar_v_start=0;//2目標初速度
								bu_tar_v_max=286;//3目標最高速度
								bu_tar_v_end=0;//4目標終端速度
								bu_tar_x=180;//5目標距離
								gv=0;//6重心速度
								ga=0;//7重心加速度
								MoveVec=true;//左回転
								isStop=false;//stopさせるかどうか
								isFailStop=false;//FailSafeでstopさせるか
								isPID_Stop=false;//PIDをstopさせるか
								isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
								isTurn=true;//turnかどうか
								isSenkai=true;//旋回
				break;

			case Right_sen:
				bu_tar_a=5730;//1目標加速度
								bu_tar_v_start=0;//2目標初速度
								bu_tar_v_max=286;//3目標最高速度
								bu_tar_v_end=0;//4目標終端速度
								bu_tar_x=360;//5目標距離
								gv=0;//6重心速度
								ga=0;//7重心加速度
								MoveVec=false;//右回転
								isStop=false;//stopさせるかどうか
								isFailStop=false;//FailSafeでstopさせるか
								isPID_Stop=false;//PIDをstopさせるか
								isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
								isTurn=true;//turnかどうか
								isSenkai=true;//旋回
				break;

			case Stra_Back:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=100;//5目標距離
				gv=500;//6重心速度
				MoveVec=false;//後進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case Left_f_off:
				bu_tar_a=3000;//1目標加速度
								bu_tar_v_start=0;//2目標初速度
								bu_tar_v_max=500;//3目標最高速度
								bu_tar_v_end=500;//4目標終端速度
								bu_tar_x=100;//5目標距離
								gv=500;//6重心速度
								MoveVec=true;//前進
								isStop=false;//stopさせるかどうか
								isFailStop=false;//FailSafeでstopさせるか
								isPID_Stop=false;//PIDをstopさせるか
								isTurn=false;//turnかどうか
				break;

			case Left_b_off:
				bu_tar_a=3000;//1目標加速度
								bu_tar_v_start=500;//2目標初速度
								bu_tar_v_max=500;//3目標最高速度
								bu_tar_v_end=0;//4目標終端速度
								bu_tar_x=100;//5目標距離
								gv=500;//6重心速度
								MoveVec=true;//前進
								isStop=false;//stopさせるかどうか
								isFailStop=false;//FailSafeでstopさせるか
								isPID_Stop=false;//PIDをstopさせるか
								isWall_PID_Stop=true;
								isTurn=false;//turnかどうか
				break;

			case Mid_Stra:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=100;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case Stop:
				isStop=true;
				break;

			case Fail_Stop:
				isStop=true;
				isFailStop=true;
				break;

			case Break_Stop:
				isStop=true;
				isBreakStop=true;
				break;
		}
	}
}


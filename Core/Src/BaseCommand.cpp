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
				bu_tar_x=180;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case first_Stra:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=90;//5目標距離132.5
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;//壁制御のPIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case Left_sla:
				bu_tar_a=12000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=480;//3目標最高速度
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
				bu_tar_a=12000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=480;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=90.0;//5目標距離
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
				bu_tar_x=91;//5目標距離
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
				bu_tar_x=91;//5目標距離
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
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=100;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isFrontOffset=true;//前壁制御をおこなうかどうか
				offset_x=10;
				break;

			case Left_b_off:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=30;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isSetBackOffset=true;//back_offsetの補正量をセットする
				break;

			case Right_f_off:
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
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isFrontOffset=true;//前壁制御をおこなうかどうか
				offset_x=10;
				break;

			case Right_b_off:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=30;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isSetBackOffset=true;//back_offsetの補正量をセットする
				break;

			case Front_offset:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=10;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isCalBackOffset=true;//back_offsetの補正量を計算させる
				break;

			case Mid_Stra:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=170;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				isBreakWall=true;//壁切れを見る
				break;

			case Stra_Stop:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=90;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stop_Cm:
				isStop=true;
				isFailStop=true;
				break;

			case Fail_Stop:
				isStop=true;
				isFailStop=true;
				break;

			case Break_Stop:
				isStop=true;
				isBreakStop=true;
				break;

			case Stra_de_70:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=160;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stra_ac_90:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=160;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stra_ac_180:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=190;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				break;

			case Stra_de_180:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=180;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				break;

			case Stra_Senkai_ac_77:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=77;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stra_Senkai_de_73:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=75;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stra_Senkai_ac_90:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=80;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stra_Senkai_de_83:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=83;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Saitan_Stra:
				bu_tar_a=12000;//1目標加速度
				bu_tar_v_start=1500;//2目標初速度
				bu_tar_v_max=1500;//3目標最高速度
				bu_tar_v_end=1500;//4目標終端速度
				bu_tar_x=90;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;//壁制御のPIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case FF_Test_Stra_1:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=250;//3目標最高速度
				bu_tar_v_end=250;//4目標終端速度
				bu_tar_x=10;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case FF_Test_Stra_2:
				bu_tar_a=7000;//1目標加速度
				bu_tar_v_start=250;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=170;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;//壁制御のPIDをstopさせるか
				isTurn=false;//turnかどうか
				break;

			case FF_Test_Senkai_1:
				bu_tar_a=3900;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=286;//3目標最高速度
				bu_tar_v_end=286;//4目標終端速度
				bu_tar_x=10;//5目標距離
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

			case FF_Test_Senkai_2:
				bu_tar_a=12000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=90;//5目標距離
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

			case Senkai_Offset_40:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=80;//5目標距離,本来は40
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				//isCalBackOffset=true;//横壁制御量を計算する
				isSenkaiOffset=true;//Uターンの前にオフセット調整する
				isCalSideWall=true;//横壁との距離をissueCommandに渡す
				break;

			case Stra_Senkai_de_40:
				bu_tar_a=6000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=40;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				break;

			case Stra_Wall_Break:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=0;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				isBreakWallStra=true;//壁切れ後の直進
				break;

			case UturnOffset:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=0;//2目標初速度
				bu_tar_v_max=300;//3目標最高速度
				bu_tar_v_end=0;//4目標終端速度
				bu_tar_x=10;//5目標距離
				gv=300;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;//壁制御を止める
				isTurn=false;//turnかどうか
				break;

			case Saitan_Right_f_off:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=20;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isFrontOffset=true;//前壁制御をおこなうかどうか
				offset_x=20;
				break;

			case Saitan_Left_f_off:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=20;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=true;
				isTurn=false;//turnかどうか
				isFrontOffset=true;//前壁制御をおこなうかどうか
				offset_x=20;
				break;

			case Mid_Stra_180:
				bu_tar_a=3000;//1目標加速度
				bu_tar_v_start=500;//2目標初速度
				bu_tar_v_max=500;//3目標最高速度
				bu_tar_v_end=500;//4目標終端速度
				bu_tar_x=180;//5目標距離
				gv=500;//6重心速度
				MoveVec=true;//前進
				isStop=false;//stopさせるかどうか
				isFailStop=false;//FailSafeでstopさせるか
				isPID_Stop=false;//PIDをstopさせるか
				isWall_PID_Stop=false;
				isTurn=false;//turnかどうか
				isBreakWall=false;//壁切れを見る
				break;
		}
	}
}


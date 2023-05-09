/*
 * BaseCommand.h
 *
 *  Created on: Apr 13, 2023
 *      Author: Ryu
 */

#ifndef INC_BASECOMMAND_H_
#define INC_BASECOMMAND_H_

namespace controll
{
	enum command_type{Stra,Left_sla,Right_sla,Left_sen,Right_sen,Stra_Back,Left_f_off,Left_b_off,Mid_Stra,Stop,Fail_Stop,Break_Stop};
	class Command
	{
	public:
		float bu_tar_a=1000;//1目標加速度
		float bu_tar_v_start=0;//2目標初速度
		float bu_tar_v_max=500;//3目標最高速度
		float bu_tar_v_end=0;//4目標終端速度
		float bu_tar_x=500;//5目標距離
		float gv=500;//6重心速度
		float ga=3000;//7重心加速度
		bool MoveVec=true;//運動の向き(前進、左回転が正の向きでtrue、後進、右回転が負の向きでfalse)
		bool isStop=false;//stopさせるかどうか
		bool isFailStop=false;//FailSafeでstopさせるか
		bool isBreakStop=false;//Breakをかけるか
		bool isPID_Stop=false;//PIDをstopさせるか
		bool isWall_PID_Stop=false;//壁制御のPIDをstopさせるか
		bool isTurn=false;//turnかどうか
		bool isSenkai=false;//旋回かどうか

	public:
		Command();
		Command(enum command_type type);//Commandのコンストラクタ*/

	};
}


#endif /* INC_BASECOMMAND_H_ */

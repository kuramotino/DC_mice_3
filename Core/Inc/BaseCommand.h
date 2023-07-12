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
	enum command_type{Stra,first_Stra,Left_sla,Right_sla,Left_sen,Right_sen,Stra_Back,Left_f_off,Left_b_off,Right_f_off,Right_b_off,Mid_Stra,Stop_Cm,Stra_Stop,Fail_Stop,Break_Stop,Front_offset,Stra_de_70,Stra_ac_90,Stra_ac_180,Stra_de_180,Stra_Senkai_ac_77,Stra_Senkai_de_73,Stra_Senkai_de_83,Stra_Senkai_ac_90
	,Saitan_Stra,FF_Test_Stra_1,FF_Test_Stra_2,FF_Test_Senkai_1,FF_Test_Senkai_2,Senkai_Offset_40,Stra_Senkai_de_40,Stra_Wall_Break
	,UturnOffset,Saitan_Right_f_off,Saitan_Left_f_off,Mid_Stra_180,Saitan_KO_90_foff,Saitan_KO_90_R,Saitan_KO_90_L,Saitan_KO_90_boff
	,Saitan_OO_90_foff,Saitan_OO_90_R,Saitan_OO_90_L,Saitan_OO_90_boff
	,Saitan_OO_180_foff_R,Saitan_OO_180_foff_L,Saitan_OO_180_R,Saitan_OO_180_L,Saitan_OO_180_boff_R,Saitan_OO_180_boff_L};
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
		float offset_x=0;//8前壁制御で進むオフセット量
		float turn_start_ad=0;//9前壁制御でターンを始めるAD値
		bool MoveVec=true;//運動の向き(前進、左回転が正の向きでtrue、後進、右回転が負の向きでfalse)
		bool isStop=false;//stopさせるかどうか
		bool isFailStop=false;//FailSafeでstopさせるか
		bool isBreakStop=false;//Breakをかけるか
		bool isPID_Stop=false;//PIDをstopさせるか
		bool isWall_PID_Stop=false;//壁制御のPIDをstopさせるか
		bool isTurn=false;//turnかどうか
		bool isSenkai=false;//旋回かどうか
		bool isFrontOffset=false;//前壁制御をおこなうかどうか
		bool isCalBackOffset=false;//横壁制御量を計算するかどうか
		bool isSetBackOffset=false;//横壁制御量をセットするかどうか
		bool isSenkaiOffset=false;//Uターンのときにオフセットを調整するか
		bool isBreakWall=false;//壁切れを見るか
		bool isBreakWallStra=false;//壁切れ後の直進かどうか
		bool isCalSideWall=false;//袋小路での位置補正を行うかどうか

	public:
		Command();
		Command(enum command_type type);//Commandのコンストラクタ*/

	};
}


#endif /* INC_BASECOMMAND_H_ */

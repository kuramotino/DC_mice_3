/*
 * Break_Wall_Ctrl.h
 *
 *  Created on: 2023/07/08
 *      Author: Ryu
 */

#ifndef INC_BREAK_WALL_CTRL_H_
#define INC_BREAK_WALL_CTRL_H_

#include "BaseCtrl.h"

namespace controll
{
	class Break_Wall_Ctrl : public BaseCtrl
	{
		float l_offset=68;//1左壁の切れ目から112mm進む(sensor1で左の壁切れを見たとき、中心線から68mm進んだ位置にいる)
		float r_offset=85;//2右壁の切れ目から95mm進む(sensor3で右の壁切れを見たとき、中心線から85mm進んだ位置にいる)
		float l_side_offset=150;//1左壁の切れ目から30mm進む(sensor1で左の壁切れを見たとき、中心線から150mm進んだ位置にいる)
		float r_side_offset=152;//2右壁の切れ目から28mm進む(sensor3で右の壁切れを見たとき、中心線から152mm進んだ位置にいる)
		float end_pos=0;//3中心線を基準とした到達位置
		float sum_x=0;
		int blocknum=0;
		bool isRWall=false;//右壁があるか
		bool isLWall=false;//左壁があるか
		bool isRSIDE=false;//側面センサーから見て右壁があるか
		bool isLSIDE=false;//側面センサーから見て左壁があるか
		bool isRecursive=false;//再帰的に壁切れを見るか
		bool preRecursive=false;

	public:
		void updata(Command cm);//overrideする
		void BreakWall();//壁切れを判定する関数
	};
}

#endif /* INC_BREAK_WALL_CTRL_H_ */

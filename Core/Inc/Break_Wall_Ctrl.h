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
		float l_side_offset=153;//1左壁の切れ目から27mm進む(sensor0で左の壁切れを見たとき、中心線から153mm進んだ位置にいる)
		float r_side_offset=160;//2右壁の切れ目から20mm進む(sensor4で右の壁切れを見たとき、中心線から160mm進んだ位置にいる)
		float l_diag_offset=76;//1左壁の切れ目から109mm進む(sensor1で左の壁切れを見たとき、中心線から71mm進んだ位置にいる)
		float r_diag_offset=76;//2右壁の切れ目から104mm進む(sensor3で右の壁切れを見たとき、中心線から76mm進んだ位置にいる)
		float end_pos=0;//3中心線を基準とした到達位置
		float sum_x=0;
		int blocknum=0;
		float polldetecttimer=0.0;
		bool OKPollDetect=true;
		float threshold_sum_x=90;//4壁切れを行わない残り距離の閾値
		bool isdxBreak=false;//4壁切れできる残り距離かどうか
		bool isExistWall_R=false;//5右壁があるかどうか
		bool isExistWall_L=false;//5左壁があるかどうか
		bool isWallBreaked=false;
		bool isRecursive=false;//再帰的に壁切れを見るか
		bool preRecursive=false;
		float diag_breakwall_offset=0;//6残り90での壁切れ時にどれだけ直進を追加するか

	public:
		void updata(Command* cm);//overrideする
		void BreakWall();//壁切れを判定する関数
	};
}

#endif /* INC_BREAK_WALL_CTRL_H_ */

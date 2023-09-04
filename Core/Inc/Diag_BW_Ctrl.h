/*
 * Diag_BW_Ctrl.h
 *
 *  Created on: 2023/09/01
 *      Author: Ryu
 */

#ifndef INC_DIAG_BW_CTRL_H_
#define INC_DIAG_BW_CTRL_H_

#include "BaseCtrl.h"

namespace controll
{
class Diag_BW_Ctrl : public BaseCtrl
	{
		float l_side_offset=35;//1左壁の切れ目から27mm進む(sensor0で左の壁切れを見たとき、中心線から153mm進んだ位置にいる)
		float r_side_offset=38;//2右壁の切れ目から20mm進む(sensor4で右の壁切れを見たとき、中心線から160mm進んだ位置にいる)
		float l_diag_offset=106;//1左壁の切れ目から109mm進む(sensor1で左の壁切れを見たとき、中心線から71mm進んだ位置にいる)
		float r_diag_offset=110;//2右壁の切れ目から104mm進む(sensor3で右の壁切れを見たとき、中心線から76mm進んだ位置にいる)
		float end_pos=0;//3中心線を基準とした到達位置
		float sum_x=0;
		int blocknum=0;
		float polldetecttimer=0.0;
		bool OKPollDetect=true;
		float threshold_sum_x=0;//4壁切れを行わない残り距離の閾値
		bool isdxBreak=false;//4壁切れできる残り距離かどうか
		bool isWallBreaked=false;
		bool isRecursive=false;//再帰的に壁切れを見るか
		bool preRecursive=false;
		float diag_bw_th_x=60;//5sum_xがこの値以下なら壁切れしない
		int BW_Status=0;//1壁切れの状態,(0壁切れ無し,1右で壁切れ、2左で壁切れ)

	public:
		void updata(Command cm);//overrideする
		void DiagBreakWall();//壁切れを判定する関数
		int RetData();
	};
}

#endif /* INC_DIAG_BW_CTRL_H_ */

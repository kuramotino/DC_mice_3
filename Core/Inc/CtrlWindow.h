/*
 * CtrlWindow.h
 *
 *  Created on: 2023/07/09
 *      Author: Ryu
 */

#ifndef INC_CTRLWINDOW_H_
#define INC_CTRLWINDOW_H_

namespace controll
{
	class CtrlWindow
	{
	protected:
		float offset=0;
		int lfr_wall_status=0;//1壁当て時の周囲の壁の状態(0:壁あてなし、1:前ののみ、2前+左、3:前+右)

	public:
		void Set_Offset(float buoffset);//オフセットをセットする関数
		void Set_HitStatus(int bustatus);//1壁当ての周囲の壁の状態をセットする関数
	};
}

#endif /* INC_CTRLWINDOW_H_ */

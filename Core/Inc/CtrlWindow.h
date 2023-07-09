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

	public:
		void Set_Offset(float buoffset);//オフセットをセットする関数
	};
}

#endif /* INC_CTRLWINDOW_H_ */

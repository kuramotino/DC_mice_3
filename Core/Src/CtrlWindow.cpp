/*
 * CtrlWindow.cpp
 *
 *  Created on: 2023/07/09
 *      Author: Ryu
 */
#include "CtrlWindow.h"

namespace controll
{
	void controll::CtrlWindow::Set_Offset(float buoffset)
	{
		offset=buoffset;
	}

	void controll::CtrlWindow::Set_HitStatus(int bustatus)
	{
		lfr_wall_status=bustatus;
	}
}


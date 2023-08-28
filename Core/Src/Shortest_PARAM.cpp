/*
 * Shortest_PARAM.cpp
 *
 *  Created on: 2023/07/29
 *      Author: Ryu
 */
#include "Shortest_PARAM.h"
#include "BaseCommand.h"
using namespace controll;

namespace Algorizm
{
	Algorizm::Shortest_PARAM::Shortest_PARAM()
	{

	}

	Algorizm::Shortest_PARAM::Shortest_PARAM(int index)
	{
		switch(index)
		{
		case 0:
			OO_90_L_foff=Saitan_OO_90_foff_L;
			OO_90_R_foff=Saitan_OO_90_foff_R;
			OO_90_L=Saitan_OO_90_L;
			OO_90_R=Saitan_OO_90_R;
			OO_90_L_boff=Saitan_OO_90_boff_L;
			OO_90_R_boff=Saitan_OO_90_boff_R;
			OO_180_L_foff=Saitan_OO_180_foff_L;
			OO_180_R_foff=Saitan_OO_180_foff_R;
			OO_180_L=Saitan_OO_180_L;
			OO_180_R=Saitan_OO_180_R;
			OO_180_L_boff=Saitan_OO_180_boff_L;
			OO_180_R_boff=Saitan_OO_180_boff_R;
			Diag_in45_L_foff=S_Diag_in45_L_foff;
			Diag_in45_R_foff=S_Diag_in45_R_foff;
			Diag_in45_L=S_Diag_in45_L;
			Diag_in45_R=S_Diag_in45_R;
			Diag_in45_L_boff=S_Diag_in45_L_boff;
			Diag_in45_R_boff=S_Diag_in45_R_boff;
			Diag_out45_L_foff=S_Diag_out45_L_foff;
			Diag_out45_R_foff=S_Diag_out45_R_foff;
			Diag_out45_L=S_Diag_out45_L;
			Diag_out45_R=S_Diag_out45_R;
			Diag_out45_L_boff=S_Diag_out45_L_boff;
			Diag_out45_R_boff=S_Diag_out45_R_boff;
			Diag_in135_L_foff=S_Diag_in135_L_foff;
			Diag_in135_R_foff=S_Diag_in135_R_foff;
			Diag_in135_L=S_Diag_in135_L;
			Diag_in135_R=S_Diag_in135_R;
			Diag_in135_L_boff=S_Diag_in135_L_boff;
			Diag_in135_R_boff=S_Diag_in135_R_boff;
			Diag_out135_L_foff=S_Diag_out135_L_foff;
			Diag_out135_R_foff=S_Diag_out135_R_foff;
			Diag_out135_L=S_Diag_out135_L;
			Diag_out135_R=S_Diag_out135_R;
			Diag_out135_L_boff=S_Diag_out135_L_boff;
			Diag_out135_R_boff=S_Diag_out135_R_boff;
			Diag_V90_L_foff=S_Diag_V90_L_foff;
			Diag_V90_R_foff=S_Diag_V90_R_foff;
			Diag_V90_L=S_Diag_V90_L;
			Diag_V90_R=S_Diag_V90_R;
			Diag_V90_L_boff=S_Diag_V90_L_boff;
			Diag_V90_R_boff=S_Diag_V90_R_boff;
			S_Stra=Saitan_Stra;
			L_Stra=Last_Stra;
			Diag_Stra=S_Diag_Stra;
			F_Stra=first_Stra;
			S_WBreak=S_Wall_Break;
			TURN_V=1000;
			OO90_V=1000;
			OO180_V=1000;
			Diag_in45_V=1000;
			Diag_out45_V=1000;
			Diag_in135_V=1000;
			Diag_out135_V=1000;
			Diag_V90_V=1000;
			MAX_V=1000;
			MAX_DIAG_V=1000;
			MAX_LAST_V=1000;
			break;

		case 1:
			break;

		case 2:
			break;
		}
	}
}


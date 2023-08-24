/*
 * Shortest_PARAM.h
 *
 *  Created on: 2023/07/29
 *      Author: Ryu
 */

#ifndef INC_SHORTEST_PARAM_H_
#define INC_SHORTEST_PARAM_H_
#include "BaseCommand.h"

namespace Algorizm
{
	using namespace controll;
	class Shortest_PARAM
	{
	public:
		enum command_type OO_90_L_foff;
		enum command_type OO_90_R_foff;
		enum command_type OO_90_L;
		enum command_type OO_90_R;
		enum command_type OO_90_L_boff;
		enum command_type OO_90_R_boff;
		enum command_type OO_180_L_foff;
		enum command_type OO_180_R_foff;
		enum command_type OO_180_L;
		enum command_type OO_180_R;
		enum command_type OO_180_L_boff;
		enum command_type OO_180_R_boff;
		enum command_type Diag_in45_L_foff;
		enum command_type Diag_in45_R_foff;
		enum command_type Diag_in45_L;
		enum command_type Diag_in45_R;
		enum command_type Diag_in45_L_boff;
		enum command_type Diag_in45_R_boff;
		enum command_type Diag_out45_L_foff;
		enum command_type Diag_out45_R_foff;
		enum command_type Diag_out45_L;
		enum command_type Diag_out45_R;
		enum command_type Diag_out45_L_boff;
		enum command_type Diag_out45_R_boff;
		enum command_type Diag_in135_L_foff;
		enum command_type Diag_in135_R_foff;
		enum command_type Diag_in135_L;
		enum command_type Diag_in135_R;
		enum command_type Diag_in135_L_boff;
		enum command_type Diag_in135_R_boff;
		enum command_type Diag_out135_L_foff;
		enum command_type Diag_out135_R_foff;
		enum command_type Diag_out135_L;
		enum command_type Diag_out135_R;
		enum command_type Diag_out135_L_boff;
		enum command_type Diag_out135_R_boff;
		enum command_type Diag_V90_L_foff;
		enum command_type Diag_V90_R_foff;
		enum command_type Diag_V90_L;
		enum command_type Diag_V90_R;
		enum command_type Diag_V90_L_boff;
		enum command_type Diag_V90_R_boff;
		enum command_type S_Stra;
		enum command_type Diag_Stra;
		enum command_type F_Stra;
		enum command_type S_WBreak;
		float TURN_V;
		float OO90_V;
		float OO180_V;
		float Diag_in45_V;
		float Diag_out45_V;
		float Diag_in135_V;
		float Diag_out135_V;
		float Diag_V90_V;
		float MAX_V;
		float MAX_DIAG_V;

	public:
		Shortest_PARAM();
		Shortest_PARAM(int param_num);
	};
}

#endif /* INC_SHORTEST_PARAM_H_ */

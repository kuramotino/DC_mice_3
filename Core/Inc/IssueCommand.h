/*
 * IssueCommand.h
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#ifndef INC_ISSUECOMMAND_H_
#define INC_ISSUECOMMAND_H_

#include "Planning.h"
#include "Pass_Generator.h"
#include "CtrlWindow.h"
using namespace controll;

namespace Algorizm
{
	class IssueCommand : public CtrlWindow
	{
		Planning* my_plan;
		Pass_Generator* my_pass;
		POS goal_pos[4] = { {7,7},{7,8},{8,7},{8,8} };//{ {1,0},{1,1},{2,0},{2,1} }
		POS start_pos[1] = { {0,0} };
		enum Vec nextVec;

		float TURN_V=700;
		float MAX_V=2500;
		float Know_MAX_V=1000;

	public:
		bool isStart = false;
		bool isStop = false;
		bool isM_Start=false;
		bool isM_Stop=false;
		bool isPass=false;

	public:
		void Init();//��Ԃ�����������֐�
		void Tansaku();//�T�����s���֐�
		void Saitan();//�ŒZ���s���֐�
		void SetPlan(Planning* plan);
		void SetPassGene(Pass_Generator* bu_pass);
	};
}


#endif /* INC_ISSUECOMMAND_H_ */

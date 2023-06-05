/*
 * IssueCommand.h
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#ifndef INC_ISSUECOMMAND_H_
#define INC_ISSUECOMMAND_H_

#include "Planning.h"

namespace Algorizm
{
	class IssueCommand
	{
		Planning* my_plan;
		POS goal_pos[4] = { {1,0},{1,1},{2,0},{2,1} };
		POS start_pos[1] = { {0,0} };
		enum Vec nextVec;

	public:
		bool isStart = false;
		bool isStop = false;

	public:
		void Init();//��Ԃ�����������֐�
		void Tansaku();//�T�����s���֐�
		void Saitan();//�ŒZ���s���֐�
		void SetPlan(Planning* plan);
	};
}


#endif /* INC_ISSUECOMMAND_H_ */

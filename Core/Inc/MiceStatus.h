/*
 * MiceStatus.h
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#ifndef INC_MICESTATUS_H_
#define INC_MICESTATUS_H_

namespace Algorizm
{
	enum Dir {North,East,South,West};
	class MiceStatus
	{
		int PosX = 0;
		int PosY = 1;
		int SimPosX=0;
		int SimPosY=1;
		int PreSimPosX=0;
		int PreSimPosY=1;
		enum Dir MiceVec=North;//�@�̂̌���(0����A1���E�A2�����A3����)
		enum Dir PreMiceVec=North;//�O��̋@�̂̌���
		enum Dir SimMiceVec=North;
		enum Dir PreSimMiceVec=North;

	public:
		void InitStatus();//�}�E�X�̏�Ԃ�����������֐�
		void VecDecide(bool isRight);//�������ߊ֐�
		void PosDecide(void);//�ʒu���ߊ֐�
		void CopyFromSimtoPosVec(void);
		bool GoalCheck(int goal_size, int x, int y);//�S�[���������ǂ����𔻒肷��֐�
		bool SimGoalCheck(int goal_size,int x,int y);
		void RetPos(int* x, int* y, enum Dir* dir);
		void SetSimPosVec();
		void SimVecDecide(bool isRight);
		void SimPosDecide(void);
		void RetSimPos(int* x,int* y,enum Dir* dir);
		void UndoSim();
		void UpDataPreSim();
	};
}

#endif /* INC_MICESTATUS_H_ */

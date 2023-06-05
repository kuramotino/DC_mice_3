/*
 * MiceStatus.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "MiceStatus.h"
#include "MakePotential.h"

namespace Algorizm
{
	void MiceStatus::InitStatus()//�}�E�X�̏�Ԃ�����������֐�
	{
		PosX = 0;
		PosY = 1;
		MiceVec = North;
		PreMiceVec = North;
	}

	void MiceStatus::VecDecide(bool isRight)//�������ߊ֐�(1���͂ŉE��]�A2���͂ō���])
	{
		switch (MiceVec)
		{
		case North:
			MiceVec = (isRight) ? East : West;
			break;
		case East:
			MiceVec = (isRight) ? South : North;
			break;
		case South:
			MiceVec = (isRight) ? West : East;
			break;
		case West:
			MiceVec = (isRight) ? North : South;
			break;
		}
	}

	void MiceStatus::PosDecide(void)//�ʒu���ߊ֐�
	{
		switch (MiceVec)
		{
		case North:
			PosY++;
			PreMiceVec = MiceVec;
			break;

		case East:
			PosX++;
			PreMiceVec = MiceVec;
			break;

		case South:
			PosY--;
			PreMiceVec = MiceVec;
			break;

		case West:
			PosX--;
			PreMiceVec = MiceVec;
			break;
		}
	}

	bool MiceStatus::GoalCheck(int goal_size, int x, int y)//�S�[���������ǂ����𔻒肷��֐�
	{
		for (int i = 0; i < goal_size; i++)
		{
			if (PosX == x && PosY == y)
			{
				return true;
			}
		}
		return false;
	}

	void MiceStatus::RetPos(int* x, int* y, enum Dir* dir)
	{
		*x = PosX;
		*y = PosY;
		*dir = MiceVec;
	}
}

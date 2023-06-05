/*
 * Planning.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "Planning.h"
#include "MiceStatus.h"

namespace Algorizm
{
	enum Vec Planning::Adati(int goal_size,POS* goal_pos)
	{
		my_potential->DecideDist(goal_size, goal_pos);
		my_status->RetPos(&x, &y, &MiceVec);

		front_dist = 255;
		back_dist = 255;
		left_dist = 255;
		right_dist = 255;

		//1����ʒu(x,y)�ɂ���Ƃ��̑O�㍶�E�̕������擾
		if (MiceVec == North)
		{
			if (y != 15)
			{
				front_dist = my_potential->RetDist(x, y + 1);
			}
			if (y != 0)
			{
				back_dist = my_potential->RetDist(x, y - 1);
			}
			if (x != 15)
			{
				right_dist = my_potential->RetDist(x + 1, y);
			}
			if (x != 0)
			{
				left_dist = my_potential->RetDist(x - 1, y);
			}
		}
		else if (MiceVec == East)
		{
			if (x != 15)
			{
				front_dist = my_potential->RetDist(x + 1, y);
			}
			if (x != 0)
			{
				back_dist = my_potential->RetDist(x - 1, y);
			}
			if (y != 0)
			{
				right_dist = my_potential->RetDist(x, y - 1);
			}
			if (y != 15)
			{
				left_dist = my_potential->RetDist(x, y + 1);
			}
		}
		else if (MiceVec == South)
		{
			if (y != 0)
			{
				front_dist = my_potential->RetDist(x, y - 1);
			}
			if (y != 15)
			{
				back_dist = my_potential->RetDist(x, y + 1);
			}
			if (x != 0)
			{
				right_dist = my_potential->RetDist(x - 1, y);
			}
			if (x != 15)
			{
				left_dist = my_potential->RetDist(x + 1, y);
			}
		}
		else if (MiceVec == West)
		{
			if (x != 0)
			{
				front_dist = my_potential->RetDist(x - 1, y);
			}
			if (x != 15)
			{
				back_dist = my_potential->RetDist(x + 1, y);
			}
			if (y != 15)
			{
				right_dist = my_potential->RetDist(x, y + 1);
			}
			if (y != 0)
			{
				left_dist = my_potential->RetDist(x, y - 1);
			}
		}

		//2�ŏ��̕���������

		//3�O���E��������
		int sort[4];
		sort[0] = front_dist;
		sort[1] = right_dist;
		sort[2] = left_dist;
		sort[3] = back_dist;

		my_map->isLFRKnowWall(&isLWall, &isFWall, &isRWall, x, y, MiceVec);

		//4�ǂɑj�܂ꂽ���������O
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				if (isFWall != 0)
				{
					sort[i] = 255;
				}
				break;

			case 1:
				if (isRWall != 0)
				{
					sort[i] = 255;
				}
				break;

			case 2:
				if (isLWall != 0)
				{
					sort[i] = 255;
				}
				break;

			case 3:

				break;
			}
		}

		//5�ŏ��l������
		num = 0;
		min = 255;
		for (int i = 0; i < 4; i++)
		{
			if (sort[i] < min)
			{
				min = sort[i];
				num = i;
			}
		}

		//6setnum�ɕύX
		ret = (num == 0) ? Front : ((num == 1) ? Right : ((num == 2) ? Left : Back));

		UpDataVecPos(ret);
		for (int i = 0; i < goal_size; i++)
		{
			if (isReturn)
			{
				isTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
				if (isTansakuEnd)
				{
					break;
				}
			}
			else
			{
				isReturn = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
				if (isReturn)
				{
					break;
				}
			}
		}
		return ret;
	}

	void Algorizm::Planning::SetObj(MiceStatus* status, MakePotential* potential, Map* map)//�K�v�ȃI�u�W�F�N�g���Z�b�g����֐�
	{
		my_status = status;
		my_potential = potential;
		my_map = map;
	}

	void Algorizm::Planning::UpDataVecPos(enum Vec vec)//���ɐi�ތ���(���C�E�C�O�C��)����C���̈ʒu�C�������X�V����֐�
	{
		switch (vec)
		{
		case Left:
			my_status->VecDecide(false);
			my_status->PosDecide();
			break;

		case Front:
			my_status->PosDecide();
			break;

		case Right:
			my_status->VecDecide(true);
			my_status->PosDecide();
			break;

		case Back:
			my_status->VecDecide(false);
			my_status->VecDecide(false);
			my_status->PosDecide();
			break;
		}
	}

	void Algorizm::Planning::SetReturn(bool isreturn)//�߂�T���t���O���Z�b�g����֐�
	{
		isReturn = isreturn;
	}

	bool Algorizm::Planning::RetReturn()//�߂�T���t���O��Ԃ��֐�
	{
		return isReturn;
	}

	void Algorizm::Planning::SetTansakuEnd(bool istansakuend)
	{
		isTansakuEnd = istansakuend;
	}

	bool Algorizm::Planning::RetTansakuEnd()//�T���I���t���O��Ԃ��֐�
	{
		return isTansakuEnd;
	}
}

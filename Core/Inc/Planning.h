/*
 * Planning.h
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#ifndef INC_PLANNING_H_
#define INC_PLANNING_H_

#include "MakePotential.h"
#include "Map.h"
#include "MiceStatus.h"

namespace Algorizm
{
	class Planning
	{
		int num;
		enum Vec ret;
		int x = 0;
		int y = 1;
		enum Dir MiceVec;
		int front_dist = 255;
		int back_dist = 255;
		int right_dist = 255;
		int left_dist = 255;
		int isLWall = 0;
		int isFWall = 0;
		int isRWall = 0;
		int min = 255;//0�ŏ��l
		bool isReturn = false;//�߂�T�����ǂ���
		bool isTansakuEnd = false;//�T�����I�����Ă��邩
		MiceStatus* my_status;
		MakePotential* my_potential;
		Map* my_map;

	public:
		enum Vec Adati(int goal_size, POS* goal_pos);//�����@�ɑ����Ď��̍s����Ԃ��֐�
		void SetObj(MiceStatus* status, MakePotential* potential, Map* map);//�K�v�ȃI�u�W�F�N�g���Z�b�g����֐�
		void UpDataVecPos(enum Vec vec);//���ɐi�ތ���(���C�E�C�O�C��)����C���̈ʒu�C�������X�V����֐�
		void SetReturn(bool isreturn);//�߂�T���t���O���Z�b�g����֐�
		bool RetReturn();//�߂�T���t���O��Ԃ��֐�
		void SetTansakuEnd(bool istansakuend);//�T���I���t���O���Z�b�g����֐�
		bool RetTansakuEnd();//�T���I���t���O��Ԃ��֐�
	};
}

#endif /* INC_PLANNING_H_ */

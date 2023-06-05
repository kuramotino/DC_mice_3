/*
 * MakePotential.h
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#ifndef INC_MAKEPOTENTIAL_H_
#define INC_MAKEPOTENTIAL_H_

#define MAX_QUEUE_NUM 50
#include "Map.h"

namespace Algorizm
{
	//pos_queue�\����
	typedef struct POS_QUEUE
	{
		int x;
		int y;
	}POS;

	//queue�\����
	typedef struct QUEUE
	{
		int head;//�f�[�^�̍őO��
		int tail;//�f�[�^�̍Ō��
		POS pos[MAX_QUEUE_NUM];//push����Ă���f�[�^
	}QUEUE_T;

	class MakePotential
	{
		int DistMap[16][16] = {255};
		Map* map;

	public:
		void initQueue(QUEUE_T* queue);//queue�̏�����
		void pushQueue_walk(QUEUE_T* queue, POS input);//queue��push
		POS popQueue_walk(QUEUE_T* queue);//queue��pop
		void Init_Dist(void);//�����}�b�v�̏��������s���֐�
		void DecideDist(int goal_size,POS* goal_pos);//�����}�b�v�̍X�V���s���֐�
		int RetDist(int x, int y);//�����}�b�v�̒l��Ԃ��֐�
		void SetMap(Map* bu_map);//�}�b�v�̃Z�b�g���s���֐�
	};
}


#endif /* INC_MAKEPOTENTIAL_H_ */

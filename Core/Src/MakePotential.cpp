/*
 * MakePotential.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "MakePotential.h"

namespace Algorizm
{
	void Algorizm::MakePotential::initQueue(QUEUE_T* queue)//queue�̏�����
	{
		queue->head = 0;
		queue->tail = 0;
	}

	void Algorizm::MakePotential::pushQueue_walk(QUEUE_T* queue, POS input)//queue��push
	{
		//1�f�[�^���f�[�^�̍Ō���̈���Ɋi�[
		queue->pos[queue->tail] = input;
		//2�f�[�^�̍Ō��������Ɉړ�
		queue->tail = queue->tail + 1;
		//3����V�t�g
		if (queue->tail == MAX_QUEUE_NUM)
		{
			queue->tail = 0;
		}
		//4�L���[�����t�Ȃ牽�������Ɋ֐��I��
		if (queue->tail == queue->head)
		{
			return;
		}
	}

	POS Algorizm::MakePotential::popQueue_walk(QUEUE_T* queue)//queue��pop
	{
		POS ret = { 0,0 };

		//1�L���[����Ȃ牽�������ɏI��
		if (queue->tail == queue->head)
		{
			ret.x = 65535;
			return ret;
		}
		//2�f�[�^�̍őO�񂩂�f�[�^���擾
		ret = queue->pos[queue->head];
		//3�f�[�^�̍őO�����O�ɂ��炷
		queue->head = queue->head + 1;
		//4����V�t�g
		if (queue->head == MAX_QUEUE_NUM)
		{
			queue->head = 0;
		}
		//5�擾�����f�[�^��ԋp
		return ret;
	}

	void Algorizm::MakePotential::Init_Dist(void)//�����}�b�v�̏��������s���֐�
	{
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				DistMap[x][y] = 255;
			}
		}
	}

	void Algorizm::MakePotential::DecideDist(int goal_size, POS* goal_pos)//�C�ӂ̃S�[�����W�ɑ΂��ĕ����}�b�v�X�V���s���֐�
	{
		map->MapDecide();//�Ǐ��̍X�V
		Init_Dist();//�����}�b�v�̏�����

		QUEUE_T queue;
		POS bupos;
		initQueue(&queue);//1�L���[��������

		for (int i = 0; i < goal_size; i++)
		{
			DistMap[(goal_pos+i)->x][(goal_pos+i)->y] = 0;//goal���W��0�ɂ���
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			pushQueue_walk(&queue, bupos);//goal���W���X�^�b�N��push����
		}

		int currnet_step = 0;

		while (1)
		{
			bupos = popQueue_walk(&queue);//�L���[������W��pop����
			int x = bupos.x;
			int y = bupos.y;

			if (x == 65535)//�L���[����Ȃ̂Ɏ��o�����Ƃ�����break;
			{
				break;
			}
			if (DistMap[x][y] == currnet_step + 1)//pop�������W�̕���������count�Ȃ猻�݂̃J�E���g��++
			{
				currnet_step++;
			}
			if (currnet_step == 254)
			{
				break;
			}

			//Pop���ꂽ���W�̎��ӏ󋵂̊m�F
			if (DistMap[x][y] == currnet_step)
			{
				if (x != 15 && DistMap[x + 1][y] == 255 && map->isKnowWall(x,y,East) == 0)//1�E�[�łȂ��A�T���ς݂łȂ��A�E�ǂȂ��̂Ƃ�
				{
					DistMap[x + 1][y] = currnet_step + 1;
					bupos.x = x + 1;
					bupos.y = y;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
				if (x != 0 && DistMap[x - 1][y] == 255 && map->isKnowWall(x, y, West) == 0)//2���[�łȂ��A�T���ς݂łȂ��A���ǂȂ��̂Ƃ�
				{
					DistMap[x - 1][y] = currnet_step + 1;
					bupos.x = x - 1;
					bupos.y = y;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
				if (y != 15 && DistMap[x][y + 1] == 255 && map->isKnowWall(x, y, North) == 0)//3��[�łȂ��A�T���ς݂łȂ��A��ǂȂ��̂Ƃ�
				{
					DistMap[x][y + 1] = currnet_step + 1;
					bupos.x = x;
					bupos.y = y + 1;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
				if (y != 0 && DistMap[x][y - 1] == 255 && map->isKnowWall(x, y, South) == 0)//3���[�łȂ��A�T���ς݂łȂ��A���ǂȂ��̂Ƃ�
				{
					DistMap[x][y - 1] = currnet_step + 1;
					bupos.x = x;
					bupos.y = y - 1;
					pushQueue_walk(&queue, bupos);//����������W���L���[��push����
				}
			}
		}
	}

	int Algorizm::MakePotential::RetDist(int x, int y)
	{
		return DistMap[x][y];
	}

	void Algorizm::MakePotential::SetMap(Map* bu_map)//�}�b�v�̃Z�b�g���s���֐�
	{
		map = bu_map;
	}
}

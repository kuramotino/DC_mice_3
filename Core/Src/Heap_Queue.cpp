/*
 * Heap_Queue.cpp
 *
 *  Created on: 2023/06/22
 *      Author: Ryu
 */
#include "HeapQueue.h"

namespace Algorizm
{
	void Algorizm::HeapQueue::init_heap()
	{
		now_node_num = 0;
	}

	void Algorizm::HeapQueue::up_heap(int root, int tail)//�������������𖞂����Ȃ��q�[�v���č\�z����֐�
	{
		int next_swap_point = 2 * root;
		NODE root_node = DAT[root];

		if (DAT[next_swap_point + 1].cost < DAT[next_swap_point].cost && next_swap_point + 1 <= tail)
		{
			next_swap_point++;
		}

		while (next_swap_point <= tail && root_node.cost > DAT[next_swap_point].cost)
		{
			DAT[root] = DAT[next_swap_point];
			root = next_swap_point;
			next_swap_point = 2 * root;
			if (DAT[next_swap_point + 1].cost < DAT[next_swap_point].cost && next_swap_point + 1 <= tail)
			{
				next_swap_point++;
			}
		}
		DAT[root] = root_node;
	}

	void Algorizm::HeapQueue::construction_heap()//�q�[�v���č\�z����֐�
	{
		for (int i = now_node_num / 2; i > 0; i--)
		{
			up_heap(i, now_node_num);
		}
	}

	void Algorizm::HeapQueue::push_heap(NODE node)//�q�[�v�Ƀv�b�V������֐�
	{
		if (now_node_num == MAX_HEAP_NUM - 1)
		{
			return;
		}
		now_node_num++;
		DAT[now_node_num] = node;
		construction_heap();
	}

	NODE Algorizm::HeapQueue::pop_heap()//�q�[�v����|�b�v����֐�
	{
		NODE ret = { 0,false,0,0};
		if (now_node_num == 0)
		{
			return ret;
		}
		ret = DAT[1];
		DAT[1] = DAT[now_node_num];
		now_node_num--;
		up_heap(1, now_node_num);
		return ret;
	}

	int Algorizm::HeapQueue::ret_node_num()
	{
		return now_node_num;
	}
}


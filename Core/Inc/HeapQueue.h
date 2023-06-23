/*
 * HeapQueue.h
 *
 *  Created on: 2023/06/22
 *      Author: Ryu
 */

#ifndef INC_HEAPQUEUE_H_
#define INC_HEAPQUEUE_H_

#define MAX_HEAP_NUM 255

namespace Algorizm
{
	enum saitan_node_dir { NN, NE, EE, SE, SS, SW, WW, NW };

	typedef struct Search_Node
	{
		int cost;
		bool isConfirm;
		int pos_x;
		int pos_y;
		Search_Node* pre_node;
		saitan_node_dir node_dir;
		bool isNoWall;
		bool isRow;
	}NODE;

	class HeapQueue
	{
		NODE DAT[MAX_HEAP_NUM];//�m�[�h�z��,1����g�p����
		int now_node_num = 0;//���݃L���[�ɓ����Ă���m�[�h��

	public:
		void init_heap();//�q�[�v������������֐�
		void up_heap(int root, int tail);//�������������𖞂����Ȃ��q�[�v���č\�z����֐�
		void construction_heap();//�q�[�v���č\�z����֐�
		void push_heap(NODE node);//�q�[�v�Ƀv�b�V������֐�
		NODE pop_heap();//�q�[�v����|�b�v����֐�
		int ret_node_num();//���݃L���[�ɓ����Ă���m�[�h����Ԃ��֐�
	};
}


#endif /* INC_HEAPQUEUE_H_ */

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
#include "HeapQueue.h"

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
		int isKnowMap[16] = {0};//�����悪���m���ǂ����C(0�̂Ƃ����m�C1�̂Ƃ����m)
		NODE search_node[16][16];//�T���p�̃m�[�h
		HeapQueue heap;//�T���p�̃q�[�v
		int search_edge_miti = 1;//���m��Ԃ̃G�b�W�̏d��
		int search_edge_kiti = 5;//���m��Ԃ̃G�b�W�̏d��
		NODE saitan_node_column[15][16];//�ŒZ�p�̃m�[�h
		NODE saitan_node_row[15][16];//�ŒZ�p�̃m�[�h
		NODE no_conect_node;//�q����Ȃ��m�[�h
		int strate_edge_cost = 7;
		int diagonal_edge_cost = 5;
		int continue_st_edge_cost = 3;
		int continue_dag_edge_cost = 3;
		Map* map;

	public:
		void initQueue(QUEUE_T* queue);//queue�̏�����
		void pushQueue_walk(QUEUE_T* queue, POS input);//queue��push
		POS popQueue_walk(QUEUE_T* queue);//queue��pop
		void Init_Dist(void);//�����}�b�v�̏��������s���֐�
		void DecideDist(int goal_size,POS* goal_pos);//�����}�b�v�̍X�V���s���֐�
		void search_dijkstra(int goal_size, POS* goal_pos);//�T���_�C�N�X�g���@�̕����}�b�v�X�V���s���֐�
		int RetDist(int x, int y);//�����}�b�v�̒l��Ԃ��֐�
		void SetMap(Map* bu_map);//�}�b�v�̃Z�b�g���s���֐�
		void updata_knowmap(int x, int y);
		void init_knowmap();
		void init_search_node();
		NODE ret_search_node(int x, int y);//����ʒux,y�ɂ�����m�[�h��Ԃ��֐�
		void init_saitan_node();
		void saitan_dijkstra(int goal_size, POS* goal_pos);//�ŒZ�_�C�N�X�g���@�̕����}�b�v�X�V���s���֐�
		NODE* RetSaitanNode(int x, int y, bool isRow);//����x,y,row��column���w�肵���Ƃ��̃m�[�h��Ԃ��֐�
		int CalEdgeCost(NODE* prenode,NODE* nownode);//����m�[�h�ɐڑ����ꂽ�G�b�W�̃R�X�g���v�Z����֐�
		void SaitanPushNode(NODE* node, NODE* new_node, int edge_cost, saitan_node_dir dir);//����m�[�h���v�b�V������֐�
		void BlockKnowWall();//���m��Ԃ̕ǂ��ӂ����֐�
	};
}



#endif /* INC_MAKEPOTENTIAL_H_ */

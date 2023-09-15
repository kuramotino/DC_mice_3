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
#include "MazeInfKeeper.h"

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
		bool isSimEnd = false;//�o�H���o���I�����Ă��邩
		bool isTentativeTansakuEnd=true;//仮のゴールに着いたかどうか
		POS Tentative_goal_pos={0,0};//一時的なゴール座標
		MiceStatus* my_status;
		MakePotential* my_potential;
		Map* my_map;
		MazeInfKeeper mazekeeper;

	public:
		int Adati(int goal_size, POS* goal_pos,bool isKitikasoku);//�����@�ɑ����Ď��̍s����Ԃ��֐�
		int s_dijkstra(int goal_size, POS* goal_pos,bool isKitikasoku);//�_�C�N�X�g���@�ɑ����Ď��̍s����Ԃ��֐�
		int z_dijkstra(bool isKitikasoku);//全面探索を行う関数
		void set_goal_pos();//goalを設定する関数
		void BlockIsopos();//孤立区画をつぶす関数
		int saitan_dijkstra(int goal_size, POS* goal_pos);//�΂߂̃_�C�N�X�g���@�ɑ����Ď��̍s����Ԃ��֐�
		void SetObj(MiceStatus* status, MakePotential* potential, Map* map);//�K�v�ȃI�u�W�F�N�g���Z�b�g����֐�
		void UpDataVecPos(enum Vec vec);//���ɐi�ތ���(���C�E�C�O�C��)����C���̈ʒu�C�������X�V����֐�
		void UpDataSimVecPos(enum Vec vec);
		void SetReturn(bool isreturn);//�߂�T���t���O���Z�b�g����֐�
		bool RetReturn();//�߂�T���t���O��Ԃ��֐�
		void SetTansakuEnd(bool istansakuend);//�T���I���t���O���Z�b�g����֐�
		bool RetTansakuEnd();//�T���I���t���O��Ԃ��֐�
		void BlockWall();//�ǂ��ӂ����֐�
		void MiceInit();//�@�̂̈ʒu����������������
		bool RetIsSimEnd();//�o�H���o���I�����Ă��邩�ǂ����̃t���O��Ԃ��֐�
		void UndoMazeData();
	};
}
#endif /* INC_PLANNING_H_ */

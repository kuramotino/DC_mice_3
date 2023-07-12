#include "Planning.h"
#include "MiceStatus.h"

namespace Algorizm
{
	int Planning::Adati(int goal_size,POS* goal_pos,bool isKitikasoku)
	{
		if(!isKitikasoku)
		{
			my_potential->DecideDist(goal_size, goal_pos);
			my_status->RetPos(&x, &y, &MiceVec);
		}
		else
		{
			my_status->RetSimPos(&x, &y, &MiceVec);
		}

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
		int ret_num = (ret==Front) ? 1 : ((ret==Left) ? -2 : ((ret==Right) ? -3 : -4));

		if(isKitikasoku)
		{
			UpDataSimVecPos(ret);
		}
		else
		{
			UpDataVecPos(ret);
			my_status->SetSimPosVec();
		}


		bool isSimGoal=false;
		for (int i = 0; i < goal_size; i++)
		{
			if(!isKitikasoku)
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
			else
			{
				isSimGoal = my_status->SimGoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			}
		}


		//1次の座標が既知で、次の行動が直進ならば
		int next_x=0;
		int next_y=0;
		enum Dir next_dir;
		my_status->RetSimPos(&next_x, &next_y, &next_dir);
		int isKnow=(my_potential->RetKnowMap(next_x, next_y));

		if(isKnow==1 && ret==Front && !isSimGoal)//次の座標が既知で、次の行動が直進で、次の座標がゴールではないとき
		{
			my_status->UpDataPreSim();
			int bu_comp=1;
			bu_comp+=Adati(goal_size,goal_pos,true);//既知加速onにして再帰呼び出し/onのときは歩数マップ、壁情報の更新をせず、仮想的に位置を更新する
			return bu_comp;
		}
		else if(isKitikasoku)
		{
			my_status->UndoSim();
			my_status->CopyFromSimtoPosVec();//PosとVecをSimPos,SimVecで上書きする
			return 0;
		}

		return ret_num;
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

	void Algorizm::Planning::UpDataSimVecPos(enum Vec vec)//���ɐi�ތ���(���C�E�C�O�C��)����C���̈ʒu�C�������X�V����֐�
		{
			switch (vec)
			{
			case Left:
				my_status->SimVecDecide(false);
				my_status->SimPosDecide();
				break;

			case Front:
				my_status->SimPosDecide();
				break;

			case Right:
				my_status->SimVecDecide(true);
				my_status->SimPosDecide();
				break;

			case Back:
				my_status->SimVecDecide(false);
				my_status->SimVecDecide(false);
				my_status->SimPosDecide();
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

	int Algorizm::Planning::s_dijkstra(int goal_size, POS* goal_pos,bool isKitikasoku)
	{
		NODE node;
		NODE pre_node;
		int pre_x, pre_y;
		if(!isKitikasoku)
		{
			my_potential->search_dijkstra(goal_size, goal_pos);//���݂̃m�[�h���X�V����
			my_status->RetPos(&x, &y, &MiceVec);
		}
		else
		{
			my_status->RetSimPos(&x, &y, &MiceVec);
		}
		node = my_potential->ret_search_node(x, y);
		pre_node = *(node.pre_node);
		pre_x = pre_node.pos_x;
		pre_y = pre_node.pos_y;


		//1����ʒu(x,y)�ɂȂ����Ă���m�[�h�̍��W���玟�ɐi�ތ���������
		if (MiceVec == North)
		{
			ret = (y + 1 == pre_y) ? Front : ((x + 1 == pre_x) ? Right : ((x - 1 == pre_x) ? Left : Back));
		}
		else if (MiceVec == East)
		{
			ret = (x + 1 == pre_x) ? Front : ((y - 1 == pre_y) ? Right : ((y + 1 == pre_y) ? Left : Back));
		}
		else if (MiceVec == South)
		{
			ret = (y - 1 == pre_y) ? Front : ((x - 1 == pre_x) ? Right : ((x + 1 == pre_x) ? Left : Back));
		}
		else if (MiceVec == West)
		{
			ret = (x - 1 == pre_x) ? Front : ((y + 1 == pre_y) ? Right : ((y - 1 == pre_y) ? Left : Back));
		}

		int ret_num = (ret==Front) ? 1 : ((ret==Left) ? -2 : ((ret==Right) ? -3 : -4));
		ret_num=(node.cost==999)?-4:ret_num;
		ret=(node.cost==999)?Back:ret;

		if(isKitikasoku)
		{
			UpDataSimVecPos(ret);
		}
		else
		{
			UpDataVecPos(ret);//���ɐi�ތ�������ʒu�ƌ������X�V
			my_status->SetSimPosVec();
		}

		bool isSimGoal=false;
		for (int i = 0; i < goal_size; i++)//�S�[�����W�ɓ��B���Ă�����T���I��
		{
			if(!isKitikasoku)
			{
				isTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
				//			isTentativeTansakuEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			}
			else
			{
				isSimGoal = my_status->SimGoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			}
//
//			if(isTentativeTansakuEnd && (goal_pos+i)->x==0 && (goal_pos+i)->y==0)
//			{
//				isTansakuEnd=true;
//			}

//			if (isTansakuEnd || isTentativeTansakuEnd)
//			{
//				break;
//			}
			if (isTansakuEnd)
			{
					break;
			}
		}

		//1次の座標が既知で、次の行動が直進ならば
		int next_x=0;
		int next_y=0;
		enum Dir next_dir;
		my_status->RetSimPos(&next_x, &next_y, &next_dir);
		int isKnow=(my_potential->RetKnowMap(next_x, next_y));

		if(isKnow==1 && ret==Front && !isSimGoal)//次の座標が既知で、次の行動が直進で、次の座標がゴールでないとき
		{
			my_status->UpDataPreSim();
			int bu_comp=1;
			bu_comp+=s_dijkstra(goal_size,goal_pos,true);//既知加速onにして再帰呼び出し/onのときは歩数マップ、壁情報の更新をせず、仮想的に位置を更新する
			return bu_comp;
		}
		else if(isKitikasoku)
		{
			my_status->UndoSim();
			my_status->CopyFromSimtoPosVec();//PosとVecをSimPos,SimVecで上書きする
			return 0;
		}

		return ret_num;
	}

	int Algorizm::Planning::z_dijkstra()//全面探索を行う関数
	{
		if(isTentativeTansakuEnd && !isTansakuEnd)
		{
			//goal座標を設定する
			set_goal_pos();
			isTentativeTansakuEnd=false;
		}

		int t_x;
		int t_y;
		enum Dir t_vec;
		my_status->RetPos(&t_x, &t_y, &t_vec);
		int t_dist=my_potential->RetDist(t_x, t_y);

		if(t_dist>=255)//goalが塞がれていたらgoalを変更する
		{
			set_goal_pos();
		}

		int ret_num=s_dijkstra(1, &Tentative_goal_pos,false);
		return ret_num;
	}

	void Algorizm::Planning::set_goal_pos()//現在の座標から最も近い未知区画をgoalに設定する関数
	{
		POS bu_pos={255,255};
		int goal_len=0;//0ゴールへの距離
		int pre_goal_len=512;
		int n_x;
		int n_y;
		enum Dir n_vec;
		my_status->RetPos(&n_x, &n_y, &n_vec);

		for(int i=0;i<16;i++)
		{
			for(int j=0;j<16;j++)
			{
				if(my_potential->RetDist(i, j)<255 && my_potential->RetKnowMap(i, j)==0)//0その区画が塞がれておらず、未知区間なら
				{
					goal_len=(n_x-i)*(n_x-i)+(n_y-j)*(n_y-j);
					if(goal_len<pre_goal_len)
					{
						pre_goal_len=goal_len;
						bu_pos.x=i;
						bu_pos.y=j;
					}
				}
			}
		}
		Tentative_goal_pos=bu_pos;

		if(bu_pos.x==255 || bu_pos.y==255)//1仮のゴールが見つからないならスタート地点をゴールにする
		{
			Tentative_goal_pos={0,0};
		}
	}

	int Algorizm::Planning::saitan_dijkstra(int goal_size, POS* goal_pos)
	{
		NODE node;
		NODE pre_node;
		int pre_x, pre_y;
		my_potential->saitan_dijkstra(goal_size, goal_pos);//���݂̃m�[�h���X�V����
		my_status->RetPos(&x, &y, &MiceVec);

		if (MiceVec == North)
		{
			node = *(my_potential->RetSaitanNode(y - 1, x, true));
		}
		else if (MiceVec == East)
		{
			node = *(my_potential->RetSaitanNode(x - 1, y, false));
		}
		else if (MiceVec == South)
		{
			node = *(my_potential->RetSaitanNode(y, x, true));
		}
		else if (MiceVec == West)
		{
			node = *(my_potential->RetSaitanNode(x, y, false));
		}


		//pre_node = *(node.pre_node);
		//pre_x = pre_node.pos_x;
		//pre_y = pre_node.pos_y;


		//1����ʒu(x,y)�ɂȂ����Ă���m�[�h�̍��W���玟�ɐi�ތ���������
		if (MiceVec == North)
		{
			ret = (node.node_dir == NW) ? Left : ((node.node_dir == NE) ? Right : Front);
		}
		else if (MiceVec == East)
		{
			ret = (node.node_dir == NE) ? Left : ((node.node_dir == SE) ? Right : Front);
		}
		else if (MiceVec == South)
		{
			ret = (node.node_dir == SE) ? Left : ((node.node_dir == SW) ? Right : Front);
		}
		else if (MiceVec == West)
		{
			ret = (node.node_dir == SW) ? Left : ((node.node_dir == NW) ? Right : Front);
		}

		UpDataVecPos(ret);//���ɐi�ތ�������ʒu�ƌ������X�V

		for (int i = 0; i < goal_size; i++)//�S�[�����W�ɓ��B���Ă�����T���I��
		{
			isSimEnd = my_status->GoalCheck(goal_size, (goal_pos + i)->x, (goal_pos + i)->y);
			if (isSimEnd)
			{
				break;
			}
		}
		int nextpass = (ret == Left) ? -2 : ((ret == Right) ? -3 : 2);
		return nextpass;
	}

	void Algorizm::Planning::BlockWall()
	{
		my_potential->BlockKnowWall();
	}

	void Algorizm::Planning::MiceInit()//�@�̂̈ʒu����������������
	{
		my_status->InitStatus();
	}

	bool Algorizm::Planning::RetIsSimEnd()
	{
		return isSimEnd;
	}

}

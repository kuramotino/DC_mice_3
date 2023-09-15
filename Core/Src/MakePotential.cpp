#include "MakePotential.h"
#include "HeapQueue.h"

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
		int now_x;
		int now_y;
		map->RetPos(&now_x, &now_y);
		updata_knowmap(now_x, now_y);//���m��Ԃ̍X�V
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

	void Algorizm::MakePotential::updata_knowmap(int x, int y)//既知区間の更新，壁情報取得後に呼ばれる
	{
		isKnowMap[x] = isKnowMap[x] | (1 << y);
		if (x != 0)
		{
			int sum_west = 0;
			int sum_M_west=4;
			for (int i = 0; i < 4; i++)
			{
				sum_west += map->isKnowWall(x - 1, y, (Dir)i);
				sum_M_west -= map->isMKnowWall(x - 1, y, (Dir)i);
			}
			isKnowMap[x - 1] = (sum_west >= 3 || sum_M_west==4 || (sum_west+sum_M_west)==4) ? isKnowMap[x - 1] | (1 << y) : isKnowMap[x - 1];
		}
		if (x != 15)
		{
			int sum_east = 0;
			int sum_M_east=4;
			for (int i = 0; i < 4; i++)
			{
				sum_east+=map->isKnowWall(x + 1, y, (Dir)i);
				sum_M_east -= map->isMKnowWall(x + 1, y, (Dir)i);
			}
			isKnowMap[x + 1] = (sum_east >= 3 || sum_M_east==4 || (sum_east+sum_M_east)==4) ? isKnowMap[x + 1] | (1 << y) : isKnowMap[x + 1];
		}
		if (y != 0)
		{
			int sum_south = 0;
			int sum_M_south=4;
			for (int i = 0; i < 4; i++)
			{
				sum_south+=map->isKnowWall(x, y - 1, (Dir)i);
				sum_M_south -= map->isMKnowWall(x, y - 1, (Dir)i);
			}
			isKnowMap[x] = (sum_south >= 3 || sum_M_south==4 || (sum_south+sum_M_south)==4) ? isKnowMap[x] | (1 << (y - 1)) : isKnowMap[x];
		}
		if (y != 15)
		{
			int sum_north = 0;
			int sum_M_north=4;
			for (int i = 0; i < 4; i++)
			{
				sum_north+=map->isKnowWall(x, y + 1, (Dir)i);
				sum_M_north -= map->isMKnowWall(x, y + 1, (Dir)i);
			}
			isKnowMap[x] = (sum_north >= 3 || sum_M_north==4 || (sum_north+sum_M_north)==4) ? isKnowMap[x] | (1 << (y + 1)) : isKnowMap[x];
		}
	}

	void Algorizm::MakePotential::init_knowmap()
	{
		for (int i = 0; i < 16; i++)
		{
			isKnowMap[i] = 0;
		}
	}

	void Algorizm::MakePotential::InitSerch_Dist(void)//歩数マップの初期化を行う関数
	{
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				DistMap[x][y] = 999;
			}
		}
	}

	void Algorizm::MakePotential::search_dijkstra(int goal_size,POS* goal_pos)
	{
		map->MapDecide();//�Ǐ��̍X�V
		int now_x;
		int now_y;
		map->RetPos(&now_x, &now_y);
		updata_knowmap(now_x, now_y);//���m��Ԃ̍X�V
		//Init_Dist();//�����}�b�v�̏�����
		InitSerch_Dist();
		init_search_node();//�m�[�h�̏�����

		POS bupos = { 0,0 };//�V���Ɋm�肵���m�[�h�̍��W
		NODE new_confirm_node;//�V���Ɋm�肵���m�[�h

		heap.init_heap();//1�L���[��������

		for (int i = 0; i < goal_size; i++)
		{
			DistMap[(goal_pos + i)->x][(goal_pos + i)->y] = 0;//goal���W��0�ɂ���
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			search_node[bupos.x][bupos.y].cost = 0;//�X�^�[�g�m�[�h�̃R�X�g��0�ɂ���
			heap.push_heap(search_node[bupos.x][bupos.y]);//�X�^�[�g�m�[�h���L���[�Ƀv�b�V������
		}
		int x = bupos.x;
		int y = bupos.y;

		while (heap.ret_node_num() != 0)
		{
			if (heap.ret_node_num() != 0)
			{
				new_confirm_node = heap.pop_heap();//�D��x�t���L���[����ŏ��̃R�X�g�����m�[�h�����o��
				bupos.x = new_confirm_node.pos_x;//�m�肵���m�[�h�̍��W���i�[����
				bupos.y = new_confirm_node.pos_y;//�m�肵���m�[�h�̍��W���i�[����
				x = bupos.x;
				y = bupos.y;
				if (!search_node[x][y].isConfirm)
				{
					new_confirm_node.isConfirm = true;//�m�[�h���m�肳����
					search_node[bupos.x][bupos.y] = new_confirm_node;
					DistMap[x][y] = new_confirm_node.cost;
				}
				else
				{
					continue;
				}
			}


			int edge_cost = ((isKnowMap[x] & (1 << y)) == (1 << y)) ? search_edge_kiti : search_edge_miti;
			//Pop���ꂽ���W�̎��ӏ󋵂̊m�F
			if (x != 15 && map->isKnowWall(x, y, East) == 0)//1�E�[�łȂ��A�E�ǂȂ��̂Ƃ�
			{
				if (search_node[x + 1][y].cost > search_node[x][y].cost + edge_cost && !search_node[x + 1][y].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x + 1][y].cost = search_node[x][y].cost + edge_cost;
					search_node[x + 1][y].pre_node = &search_node[x][y];
					DistMap[x + 1][y] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x + 1][y].isConfirm)
				{
					heap.push_heap(search_node[x + 1][y]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x + 1][y] = search_node[x + 1][y].cost;
				}
			}
			if (x != 0 && map->isKnowWall(x, y, West) == 0)//2���[�łȂ��A���ǂȂ��̂Ƃ�
			{
				if (search_node[x - 1][y].cost > search_node[x][y].cost + edge_cost && !search_node[x - 1][y].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x - 1][y].cost = search_node[x][y].cost + edge_cost;
					search_node[x - 1][y].pre_node = &search_node[x][y];
					DistMap[x - 1][y] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x - 1][y].isConfirm)
				{
					heap.push_heap(search_node[x - 1][y]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x - 1][y] = search_node[x - 1][y].cost;
				}
			}
			if (y != 15 && map->isKnowWall(x, y, North) == 0)//3��[�łȂ��A��ǂȂ��̂Ƃ�
			{
				if (search_node[x][y + 1].cost > search_node[x][y].cost + edge_cost && !search_node[x][y + 1].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x][y + 1].cost = search_node[x][y].cost + edge_cost;
					search_node[x][y + 1].pre_node = &search_node[x][y];
					DistMap[x][y + 1] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x][y + 1].isConfirm)
				{
					heap.push_heap(search_node[x][y + 1]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x][y + 1] = search_node[x][y + 1].cost;
				}
			}
			if (y != 0 && map->isKnowWall(x, y, South) == 0)//3���[�łȂ��A���ǂȂ��̂Ƃ�
			{
				if (search_node[x][y - 1].cost > search_node[x][y].cost + edge_cost && !search_node[x][y - 1].isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
				{
					search_node[x][y - 1].cost = search_node[x][y].cost + edge_cost;
					search_node[x][y - 1].pre_node = &search_node[x][y];
					DistMap[x][y - 1] = search_node[x][y].cost + edge_cost;
				}
				if (!search_node[x][y - 1].isConfirm)
				{
					heap.push_heap(search_node[x][y - 1]);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
					DistMap[x][y - 1] = search_node[x][y - 1].cost;
				}
			}
		}
	}

	void Algorizm::MakePotential::init_search_node()
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				search_node[i][j].cost = 999;
				search_node[i][j].isConfirm = false;
				search_node[i][j].pos_x = i;
				search_node[i][j].pos_y = j;
				search_node[i][j].pre_node = &search_node[i][j];
			}
		}
	}

	NODE Algorizm::MakePotential::ret_search_node(int x, int y)//����ʒux,y�ɂ�����m�[�h��Ԃ��֐�
	{
		return search_node[x][y];
	}

	void Algorizm::MakePotential::init_saitan_node()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				saitan_node_row[i][j].cost = 999;
				saitan_node_row[i][j].isConfirm = false;
				saitan_node_row[i][j].pos_x = i;
				saitan_node_row[i][j].pos_y = j;
				saitan_node_row[i][j].pre_node = &search_node[i][j];
				saitan_node_row[i][j].isNoWall = !(map->isExistRowColumn(i, j, true));
				saitan_node_row[i][j].isRow = true;
				saitan_node_row[i][j].node_dir = NN;

				saitan_node_column[i][j].cost = 999;
				saitan_node_column[i][j].isConfirm = false;
				saitan_node_column[i][j].pos_x = i;
				saitan_node_column[i][j].pos_y = j;
				saitan_node_column[i][j].pre_node = &search_node[i][j];
				saitan_node_column[i][j].isNoWall = !(map->isExistRowColumn(i, j, false));
				saitan_node_column[i][j].isRow = false;
				saitan_node_column[i][j].node_dir = NN;
			}
		}
	}

	void Algorizm::MakePotential::saitan_dijkstra(int goal_size, POS* goal_pos)//�ŒZ�p�̃_�C�N�X�g���@
	{
		//map->MapDecide();//�Ǐ��̍X�V
		//int now_x;
		//int now_y;
		//map->RetPos(&now_x, &now_y);
		//updata_knowmap(now_x, now_y);//���m��Ԃ̍X�V
		init_saitan_node();//�m�[�h�̏�����

		POS bupos = { 0,0 };//�V���Ɋm�肵���m�[�h�̍��W
		NODE new_confirm_node;//�V���Ɋm�肵���m�[�h

		heap.init_heap();//1�L���[��������

		for (int i = 0; i < goal_size; i++)
		{
			bupos.x = (goal_pos + i)->x;
			bupos.y = (goal_pos + i)->y;
			saitan_node_column[bupos.x][bupos.y].cost = 0;//�X�^�[�g�m�[�h�̃R�X�g��0�ɂ���
			if (saitan_node_column[bupos.x][bupos.y].isNoWall)
			{
				heap.push_heap(saitan_node_column[bupos.x][bupos.y]);//�X�^�[�g�m�[�h���L���[�Ƀv�b�V������
			}

			saitan_node_row[bupos.y][bupos.x].cost = 0;//�X�^�[�g�m�[�h�̃R�X�g��0�ɂ���
			if (saitan_node_row[bupos.y][bupos.x].isNoWall)
			{
				heap.push_heap(saitan_node_row[bupos.y][bupos.x]);//�X�^�[�g�m�[�h���L���[�Ƀv�b�V������
			}

			saitan_node_column[bupos.x - 1][bupos.y].cost = 0;//�X�^�[�g�m�[�h�̃R�X�g��0�ɂ���
			if (saitan_node_column[bupos.x - 1][bupos.y].isNoWall)
			{
				heap.push_heap(saitan_node_column[bupos.x - 1][bupos.y]);//�X�^�[�g�m�[�h���L���[�Ƀv�b�V������
			}

			saitan_node_row[bupos.y - 1][bupos.x].cost = 0;//�X�^�[�g�m�[�h�̃R�X�g��0�ɂ���
			if (saitan_node_row[bupos.y - 1][bupos.x].isNoWall)
			{
				heap.push_heap(saitan_node_row[bupos.y - 1][bupos.x]);//�X�^�[�g�m�[�h���L���[�Ƀv�b�V������
			}
		}
		bool isRow = false;
		int x = bupos.x;
		int y = bupos.y;

		while (heap.ret_node_num() != 0)
		{
			if (heap.ret_node_num() != 0)
			{
				new_confirm_node = heap.pop_heap();//�D��x�t���L���[����ŏ��̃R�X�g�����m�[�h�����o��
				bupos.x = new_confirm_node.pos_x;//�m�肵���m�[�h�̍��W���i�[����
				bupos.y = new_confirm_node.pos_y;//�m�肵���m�[�h�̍��W���i�[����
				x = bupos.x;
				y = bupos.y;
				isRow = new_confirm_node.isRow;
				if (!((RetSaitanNode(x, y, isRow)->isConfirm)))
				{
					new_confirm_node.isConfirm = true;//�m�[�h���m�肳����
					*RetSaitanNode(x, y, isRow) = new_confirm_node;
				}
				else
				{
					continue;
				}
			}

			int edge_cost;
			saitan_node_dir pre_dir;
			//Pop���ꂽ���W�̎��ӏ󋵂̊m�F
			if (RetSaitanNode(x, y, isRow)->isRow)//�L���[������o���ꂽ�m�[�h��Row�̂Ƃ�
			{
				if (RetSaitanNode(x + 1, y, true)->isNoWall)//�k�����̂Ƃ�
				{
					pre_dir = RetSaitanNode(x + 1, y, true)->node_dir;
					RetSaitanNode(x + 1, y, true)->node_dir = SS;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x + 1, y, true));
					SaitanPushNode(RetSaitanNode(x + 1, y, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y, x + 1, false)->isNoWall)//�k���̂Ƃ�
				{
					pre_dir = RetSaitanNode(y, x + 1, false)->node_dir;
					RetSaitanNode(y, x + 1, false)->node_dir = SW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x + 1, false));
					SaitanPushNode(RetSaitanNode(y, x + 1, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y, x, false)->isNoWall)//�쓌�̂Ƃ�
				{
					pre_dir = RetSaitanNode(y, x, false)->node_dir;
					RetSaitanNode(y, x, false)->node_dir = NW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x, false));
					SaitanPushNode(RetSaitanNode(y, x, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(x - 1, y, true)->isNoWall)//��̂Ƃ�
				{
					pre_dir = RetSaitanNode(x - 1, y, true)->node_dir;
					RetSaitanNode(x - 1, y, true)->node_dir = NN;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x - 1, y, true));
					SaitanPushNode(RetSaitanNode(x - 1, y, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x, false)->isNoWall)//�쐼�̂Ƃ�
				{
					pre_dir = RetSaitanNode(y - 1, x, false)->node_dir;
					RetSaitanNode(y - 1, x, false)->node_dir = NE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x, false));
					SaitanPushNode(RetSaitanNode(y - 1, x, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x + 1, false)->isNoWall)//�k���̂Ƃ�
				{
					pre_dir = RetSaitanNode(y - 1, x + 1, false)->node_dir;
					RetSaitanNode(y - 1, x + 1, false)->node_dir = SE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x + 1, false));
					SaitanPushNode(RetSaitanNode(y - 1, x + 1, false), &new_confirm_node, edge_cost, pre_dir);
				}
			}
			else//�L���[������o���ꂽ�m�[�h��Column�̂Ƃ�
			{
				if (RetSaitanNode(y, x + 1, true)->isNoWall)//�k���̂Ƃ�
				{
					pre_dir = RetSaitanNode(y, x + 1, true)->node_dir;
					RetSaitanNode(y, x + 1, true)->node_dir = SW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x + 1, true));
					SaitanPushNode(RetSaitanNode(y, x + 1, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(x + 1, y, false)->isNoWall)//���̂Ƃ�
				{
					pre_dir = RetSaitanNode(x + 1, y, false)->node_dir;
					RetSaitanNode(x + 1, y, false)->node_dir = WW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x + 1, y, false));
					SaitanPushNode(RetSaitanNode(x + 1, y, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x + 1, true)->isNoWall)//�쓌�̂Ƃ�
				{
					pre_dir = RetSaitanNode(y - 1, x + 1, true)->node_dir;
					RetSaitanNode(y - 1, x + 1, true)->node_dir = NW;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x + 1, true));
					SaitanPushNode(RetSaitanNode(y - 1, x + 1, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y - 1, x, true)->isNoWall)//�쐼�̂Ƃ�
				{
					pre_dir = RetSaitanNode(y - 1, x, true)->node_dir;
					RetSaitanNode(y - 1, x, true)->node_dir = NE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y - 1, x, true));
					SaitanPushNode(RetSaitanNode(y - 1, x, true), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(x - 1, y, false)->isNoWall)//���̂Ƃ�
				{
					pre_dir = RetSaitanNode(x - 1, y, false)->node_dir;
					RetSaitanNode(x - 1, y, false)->node_dir = EE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(x - 1, y, false));
					SaitanPushNode(RetSaitanNode(x - 1, y, false), &new_confirm_node, edge_cost, pre_dir);
				}
				if (RetSaitanNode(y, x, true)->isNoWall)//�k���̂Ƃ�
				{
					pre_dir = RetSaitanNode(y, x, true)->node_dir;
					RetSaitanNode(y, x, true)->node_dir = SE;
					edge_cost = CalEdgeCost(RetSaitanNode(x, y, isRow), RetSaitanNode(y, x, true));
					SaitanPushNode(RetSaitanNode(y, x, true), &new_confirm_node, edge_cost, pre_dir);
				}
			}
		}
	}

	NODE* Algorizm::MakePotential::RetSaitanNode(int x, int y, bool isRow)//����x,y,row��column���w�肵���Ƃ��̃m�[�h��Ԃ��֐�
	{
		no_conect_node.isNoWall = false;

		if (isRow)
		{
			if (x < 0 || x > 14 || y < 0 || y > 15)
			{
				return &(no_conect_node);//�m�[�h�����̈ʒu�ɑ��݂��Ȃ��ꍇ
			}
			return &(saitan_node_row[x][y]);
		}
		else
		{
			if (x < 0 || x > 14 || y < 0 || y > 15)
			{
				return &(no_conect_node);//�m�[�h�����̈ʒu�ɑ��݂��Ȃ��ꍇ
			}
			return &(saitan_node_column[x][y]);
		}
	}

	int Algorizm::MakePotential::CalEdgeCost(NODE* prenode, NODE* nownode)//����m�[�h�ɐڑ����ꂽ�G�b�W�̃R�X�g���v�Z����֐�
	{
		int ret;
		saitan_node_dir pre_dir = prenode->node_dir;
		saitan_node_dir now_dir = nownode->node_dir;
		if (now_dir == NN || now_dir == EE || now_dir == SS || now_dir == WW)
		{
			ret = (now_dir == pre_dir) ? continue_st_edge_cost : strate_edge_cost;
		}
		else
		{
			ret = (now_dir == pre_dir) ? continue_dag_edge_cost : diagonal_edge_cost;
		}
		return ret;
	}

	void Algorizm::MakePotential::SaitanPushNode(NODE* node, NODE* new_node, int edge_cost, saitan_node_dir predir)//����m�[�h���v�b�V������֐�
	{
		if (node->cost > new_node->cost + edge_cost && !node->isConfirm)//�m�肵���m�[�h�ɂȂ����Ă���m�[�h�̃R�X�g�̍X�V
		{
			node->cost = new_node->cost + edge_cost;
			node->pre_node = new_node;
			heap.push_heap(*node);//�m�肵���m�[�h�ɂȂ����Ă���m�[�h���L���[�Ƀv�b�V������
		}
		else
		{
			node->node_dir = predir;
		}
	}

	void Algorizm::MakePotential::BlockKnowWall()//���m��Ԃ̕ǂ��ӂ����֐�
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if ((isKnowMap[i] & (1<<j)) != (1<<j))
				{
					map->BlockWall(i, j);
				}
			}
		}
	}

	int Algorizm::MakePotential::RetKnowMap(int x,int y)//ある位置x,yが既知かどうかを返す関数
	{
		return ((isKnowMap[x] & (1<<y))>>y);
	}

	int* Algorizm::MakePotential::RetKnowArray()
	{
		return isKnowMap;
	}

	void Algorizm::MakePotential::SetKnowMap(int x, int y)//ある位置x,yの既知区画を変更する関数
	{
		isKnowMap[x] = (isKnowMap[x] | (1 << y));
	}
}

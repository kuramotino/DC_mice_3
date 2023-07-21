/*
 * Map.cpp
 *
 *  Created on: 2023/06/03
 *      Author: Ryu
 */

#include "Map.h"
#include "InitAlgo.h"

namespace Algorizm
{
	void Algorizm::Map::Init_Row_Column()
	{
		for (int i = 0; i < 15; i++)
		{
			Row[i] = 0;
			Column[i] = 0;
			M_Row[i] = 0b1111111111111111;
			M_Column[i] = 0b1111111111111111;
		}
		Column[0] = 0b0000000000000001;
	}

	void Algorizm::Map::Updata_current()
	{
		my_status->RetPos(&current_x, &current_y, &current_vec);
		int pre_wall[3];
		isLFRKnowWall(&pre_wall[0],&pre_wall[1],&pre_wall[2],current_x,current_y,current_vec);
		currentWall[Left] = (my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD) ? 1:0;
		currentWall[Front] = (my_input->g_sensor_now[2]>my_input->FRONT_SLESHOLD) ? 1:0;
		currentWall[Right] = (my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD) ? 1:0;
		for(int i=0;i<3;i++)
		{
			if(pre_wall[i]==1 && currentWall[i]==0)
			{
				currentWall[i]=1;
			}
		}

	}

	void Algorizm::Map::MapDecide()
	{
		Updata_current();
		switch (current_vec)
		{
		case North:
			if (current_x != 0)
			{
				if (currentWall[Left] == 1)
				{
					Column[current_x - 1] = Column[current_x - 1] | (1 << current_y);
				}
				else
				{
					Column[current_x - 1] = Column[current_x - 1] & ~(1 << current_y);
				}
			}

			if (current_x != 15)
			{
				if (currentWall[Right] == 1)
				{
					Column[current_x] = Column[current_x] | (1 << current_y);
				}
				else
				{
					Column[current_x] = Column[current_x] & ~(1 << current_y);
				}
			}

			if (current_y != 15)
			{
				if (currentWall[Front] == 1)
				{
					Row[current_y] = Row[current_y] | (1 << current_x);
				}
				else
				{
					Row[current_y] = Row[current_y] & ~(1 << current_x);
				}
			}
			break;

		case East:
			if (current_x != 15)
			{
				if (currentWall[Front] == 1)
				{
					Column[current_x] = Column[current_x] | (1 << current_y);
				}
				else
				{
					Column[current_x] = Column[current_x] & ~(1 << current_y);
				}
			}

			if (current_y != 0)
			{
				if (currentWall[Right] == 1)
				{
					Row[current_y - 1] = Row[current_y - 1] | (1 << current_x);
				}
				else
				{
					Row[current_y - 1] = Row[current_y - 1] & ~(1 << current_x);
				}
			}

			if (current_y != 15)
			{
				if (currentWall[Left] == 1)
				{
					Row[current_y] = Row[current_y] | (1 << current_x);
				}
				else
				{
					Row[current_y] = Row[current_y] & ~(1 << current_x);
				}
			}
			break;

		case South:
			if (current_x != 0)
			{
				if (currentWall[Right] == 1)
				{
					Column[current_x - 1] = Column[current_x - 1] | (1 << current_y);
				}
				else
				{
					Column[current_x - 1] = Column[current_x - 1] & ~(1 << current_y);
				}
			}

			if (current_x != 15)
			{
				if (currentWall[Left] == 1)
				{
					Column[current_x] = Column[current_x] | (1 << current_y);
				}
				else
				{
					Column[current_x] = Column[current_x] & ~(1 << current_y);
				}
			}

			if (current_y != 0)
			{
				if (currentWall[Front] == 1)
				{
					Row[current_y - 1] = Row[current_y - 1] | (1 << current_x);
				}
				else
				{
					Row[current_y - 1] = Row[current_y - 1] & ~(1 << current_x);
				}
			}
			break;

		case West:
			if (current_x != 0)
			{
				if (currentWall[Front] == 1)
				{
					Column[current_x - 1] = Column[current_x - 1] | (1 << current_y);
				}
				else
				{
					Column[current_x - 1] = Column[current_x - 1] & ~(1 << current_y);
				}
			}

			if (current_y != 0)
			{
				if (currentWall[Left] == 1)
				{
					Row[current_y - 1] = Row[current_y - 1] | (1 << current_x);
				}
				else
				{
					Row[current_y - 1] = Row[current_y - 1] & ~(1 << current_x);
				}
			}

			if (current_y != 15)
			{
				if (currentWall[Right] == 1)
				{
					Row[current_y] = Row[current_y] | (1 << current_x);
				}
				else
				{
					Row[current_y] = Row[current_y] & ~(1 << current_x);
				}
			}
			break;
		}
	}

	int Algorizm::Map::isKnowWall(int x, int y,enum Dir wall_dir)
	{
		switch (wall_dir)
		{
		case North:

			return (y != 15) ? (Row[y] & (1 << x)) >> x : 1;

			break;

		case East:

			return (x != 15) ? (Column[x] & (1 << y)) >> y : 1;

			break;

		case South:

			return (y != 0) ? (Row[y - 1] & (1 << x)) >> x : 1;

			break;

		case West:

			return (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;

			break;
		}
	}

	void Algorizm::Map::isLFRKnowWall(int* l, int* f, int* r, int x, int y, enum Dir dir)
	{
		switch (dir)
		{
		case North:
			*l = (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			*f = (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			*r = (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			break;

		case East:
			*l = (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			*f = (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			*r = (y != 0) ? (Row[y-1] & (1 << x)) >> x : 1;
			break;

		case South:
			*l = (x != 15) ? (Column[x] & (1 << y)) >> y : 1;
			*f = (y != 0) ? (Row[y - 1] & (1 << x)) >> x : 1;
			*r = (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			break;

		case West:
			*l = (y != 0) ? (Row[y - 1] & (1 << x)) >> x : 1;
			*f = (x != 0) ? (Column[x - 1] & (1 << y)) >> y : 1;
			*r = (y != 15) ? (Row[y] & (1 << x)) >> x : 1;
			break;
		}
	}

	void Algorizm::Map::SetInputStatus(controll::InputData* input, MiceStatus* status)//Input��MiceStatus�̃I�u�W�F�N�g���Z�b�g����
	{
		my_input = input;
		my_status = status;
	}

	void Algorizm::Map::ShowMap(void)//マップを表示する関数
	{
		int MapSize=16;
		printf("\n\r");

				int i,j;
				for(i=2*MapSize+1;i>0;i--)
				{
					if(i==2*MapSize+1 || i==1)
					{
						for(int f=0;f<MapSize-1;f++)
						{
							printf("+---");
						}
						printf("+---+\n\r");
					}
					else if(i%2==0)
					{
						//columnの出力
						printf("|%3d",potential_obj.RetDist(0, i/2-1));
						for(j=0;j<MapSize-1;j++)
						{
							if((Column[j] & (1<<(i/2-1))) == (1<<(i/2-1)))
							{
								if(j==0)
								{
									printf("|");
								}
								else
								{
									printf("%3d|",potential_obj.RetDist(j,i/2-1));
								}

							}
							else
							{
								if(j==0)
								{
									printf(" ");
								}
								else
								{
									printf("%3d ",potential_obj.RetDist(j,i/2-1));
								}

							}
						}
						if((Column[MapSize-1] & (1<<(i/2-1)))== (1<<(i/2-1)))
						{
							printf("%3d|\n\r",potential_obj.RetDist(MapSize-1,i/2-1));
						}
						else
						{
							printf("%3d|\n\r",potential_obj.RetDist(MapSize-1,i/2-1));
						}
					}
					else
					{
						//Rowの出力
						printf("+");
						for(j=0;j<MapSize;j++)
						{
							if((Row[(i-1)/2-1] & (1<<j))== (1<<j))
							{
								printf("---+");
							}
							else
							{
								printf("   +");
							}
						}
						printf("   +\n\r");
					}
				}
	}

	void Algorizm::Map::ShowKnowMap(void)//マップを表示する関数
	{
		int MapSize=16;
		printf("\n\r");

		int i,j;
		for(i=2*MapSize+1;i>0;i--)
		{
			if(i==2*MapSize+1 || i==1)
			{
				for(int f=0;f<MapSize-1;f++)
				{
					printf("+---");
				}
				printf("+---+\n\r");
			}
			else if(i%2==0)
			{
				//columnの出力
				printf("|%3d",(potential_obj.RetKnowMap(0, i/2-1)));
				for(j=0;j<MapSize-1;j++)
				{
					if((Column[j] & (1<<(i/2-1))) == (1<<(i/2-1)))
					{
						if(j==0)
						{
							printf("|");
						}
						else
						{
							printf("%3d|",(potential_obj.RetKnowMap(j,i/2-1)));
						}

					}
					else
					{
						if(j==0)
						{
							printf(" ");
						}
						else
						{
							printf("%3d ",(potential_obj.RetKnowMap(j,i/2-1)));
						}

					}
				}
				if((Column[MapSize-1] & (1<<(i/2-1)))== (1<<(i/2-1)))
				{
					printf("%3d|\n\r",(potential_obj.RetKnowMap(MapSize-1,i/2-1)));
				}
				else
				{
					printf("%3d|\n\r",(potential_obj.RetKnowMap(MapSize-1,i/2-1)));
				}
			}
			else
			{
				//Rowの出力
				printf("+");
				for(j=0;j<MapSize;j++)
				{
					if((Row[(i-1)/2-1] & (1<<j))== (1<<j))
					{
						printf("---+");
					}
					else
					{
						printf("   +");
					}
				}
				printf("   +\n\r");
			}
		}
	}

	void Algorizm::Map::RetPos(int* x, int* y)
		{
			int bu_x;
			int bu_y;
			Dir bu_dir;
			my_status->RetPos(&bu_x, &bu_y, &bu_dir);
			*x = bu_x;
			*y = bu_y;
		}

		bool Algorizm::Map::isExistRowColumn(int x, int y, bool isRow)
		{
			bool Ret;
			if (isRow)
			{
				Ret = ((Row[x] & (1 << y)) == (1 << y)) ? true : false;
			}
			else
			{
				Ret = ((Column[x] & (1 << y)) == (1 << y)) ? true : false;
			}
			return Ret;
		}

		void Algorizm::Map::BlockWall(int x, int y)//����ʒux,y�̕ǂ����ׂĂӂ����֐�
		{
			//if(!(x==4&&y==6))
			//{
				if (y != 0)
				{
					Row[y - 1] = (Row[y - 1] | (1 << x));
				}
				if (y != 15)
				{
					Row[y] = (Row[y] | (1 << x));
				}
				if (x != 0)
				{
					Column[x - 1] = (Column[x - 1] | (1 << y));
				}
				if (x != 15)
				{
					Column[x] = (Column[x] | (1 << y));
				}
			//}
		}

		int* Algorizm::Map::RetRowArray()
		{
			return Row;
		}

		int* Algorizm::Map::RetColumnArray()
		{
			return Column;
		}
}

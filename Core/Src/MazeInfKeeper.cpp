/*
 * MazeInfKeeper.cpp
 *
 *  Created on: 2023/07/21
 *      Author: Ryu
 */
#include "MazeInfKeeper.h"

namespace Algorizm
{
	void Algorizm::MazeInfKeeper::SetMazeData(int* row,int* column,int* m_row,int* m_column,int* know)
	{
		MAZEINF bu_data;
		for(int i=0;i<MAZE_DATA_SIZE-1;i++)
		{
			maze_data[i]=maze_data[i+1];
		}
		for(int i=0;i<16;i++)
		{
			if(i<15)
			{
				bu_data.Maze_Row[i]=*(row+i);
				bu_data.Maze_Column[i]=*(column+i);
				bu_data.Maze_M_Row[i]=*(m_row+i);
				bu_data.Maze_M_Column[i]=*(m_column+i);
			}
			bu_data.Maze_KnowMap[i]=*(know+i);
		}
		maze_data[MAZE_DATA_SIZE-1]=bu_data;
	}

	void Algorizm::MazeInfKeeper::GetMazeData(int* row,int* column,int* m_row,int* m_column,int* know)
	{
		for(int i=0;i<MAZE_DATA_SIZE-1;i++)
		{
			maze_data[i]=maze_data[0];
		}
		for(int i=0;i<16;i++)
		{
			if(i<15)
			{
				*(row+i)=maze_data[0].Maze_Row[i];
				*(column+i)=maze_data[0].Maze_Column[i];
				*(m_row+i)=maze_data[0].Maze_M_Row[i];
				*(m_column+i)=maze_data[0].Maze_M_Column[i];
			}
			*(know+i)=maze_data[0].Maze_KnowMap[i];
		}
	}
}

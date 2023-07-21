/*
 * MazeInfKeeper.h
 *
 *  Created on: 2023/07/21
 *      Author: Ryu
 */

#ifndef INC_MAZEINFKEEPER_H_
#define INC_MAZEINFKEEPER_H_
#define MAZE_DATA_SIZE 5

namespace Algorizm
{
	typedef struct MAZE_INF
	{
		int Maze_Row[15];
		int Maze_Column[15];
		int Maze_KnowMap[16];
	}MAZEINF;

	class MazeInfKeeper
	{
		MAZEINF maze_data[MAZE_DATA_SIZE];//常に最後尾に最新のデータ、先頭に最も古いデータ

	public:
		void SetMazeData(int* row,int* column,int* know);//壁情報、既知区画更新後に呼ぶ、迷路情報をキューにプッシュする
		void GetMazeData(int* row,int* column,int* know);//壁情報、既知区画更新後に呼ぶ、迷路情報をキューからポップする
	};
}


#endif /* INC_MAZEINFKEEPER_H_ */

#include "MapCluster.h"

MapCluster::MapCluster()
{
	srand(time(0));
	memset(&maps, 0, 28 * 9 * 9 * sizeof(int));
	int index = 0, tm[] = { -1,1 };
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			MapConditionGenerate((int (*)[9])maps[index++], tm[i], tm[j]);
	int len = index;
	for (int i = 0; i < len; i++)
	{
		for (int  cnt = 0; cnt < 3; cnt++)
		{
			memcpy(&maps[index], &maps[i], 9 * 9 * sizeof(int));
			CopyRow(maps[index], 3 * cnt + 1, maps[i], 3 * cnt + 2);
			CopyRow(maps[index], 3 * cnt + 2, maps[i], 3 * cnt + 3);
			CopyRow(maps[index], 3 * cnt + 3, maps[i], 3 * cnt + 1);
			index++;
			memcpy(maps[index], maps[i], 9 * 9 * sizeof(int));
			CopyRow(maps[index], 3 * cnt + 1, maps[i], 3 * cnt + 3);
			CopyRow(maps[index], 3 * cnt + 2, maps[i], 3 * cnt + 1);
			CopyRow(maps[index], 3 * cnt + 3, maps[i], 3 * cnt + 2);
			index++;
		}
	}
	size = index;
}

void MapCluster::ParseMap(int map[9][9], int * param, int MapIndex)
{
	REPEAT(i,9)
		REPEAT(j,9)
			map[i][j] = param[maps[MapIndex][i][j] - 1];
}

void MapCluster::MapConditionGenerate(int map[9][9], int row, int col)
{
	int baseMap[][3] = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	int tmX[3] = { row,0,-row }, tmY[3] = { col,0,-col };
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			map[i][j] = baseMap[(3 + i + tmX[j / 3]) % 3][(3 + j + tmY[i / 3]) % 3];
		}
	}
}
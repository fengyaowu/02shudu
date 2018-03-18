#pragma once
#include<ctime>
#include<cstdlib>
#include<cstring>
#define REPEAT(i,n) for(int i=0;i<n;i++)
#define CopyRow(p1,row1,p2,row2) REPEAT(x,9){p1[row1-1][x] = p2[row2-1][x];}
#define CopyCol(p1,col1,p2,col2) REPEAT(x,9){p1[x][col1-1] = p2[x][col2-1];}

class MapCluster
{
public:
	MapCluster();
	~MapCluster() {};
	void ParseMap(int map[9][9], int *param, int MapIndex);
	int maps[28][9][9] = { 0 };
	int size = 0;
private:
	void MapConditionGenerate(int map[9][9], int row, int col);
};
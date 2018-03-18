#include "generator.h"
#define N 7

int InitMapIndex = 0, CurrMapIndex = 0;
int BaseMap[8] = { 0 };
int TmpMap[9] = { 0 };
int ArrSoduku[9][9] = { 0 };
MapCluster mc;

void newMapIndex()
{
	InitMapIndex = CurrMapIndex = rand() % mc.size;
}

int nextMap()
{
	return next_permutation(BaseMap, BaseMap + 8);
}

int* newTmpMap(int index)
{
	int * tmp = TmpMap;
	memset(tmp, 0, sizeof(int) * 9);
	tmp[index] = N;
	for (int i = 0, j = 0; i < 9; i++)
	{
		if (tmp[i])continue;
		tmp[i] = BaseMap[j++];
	}
	return tmp;
}

void InitGenerator() {
	// randomize the seed
	srand(time(0));
	// initialize the base permutation map
	REPEAT(i, 8) BaseMap[i] = i<N-1?i+1:i+2;
	newMapIndex();
}

int simple_check()
{
	REPEAT(i, 9) {
		int row_vis[9] = { 0 };
		int col_vis[9] = { 0 };
		int blk_vis[9] = { 0 };
		REPEAT(j, 9) {
			//row check
			if (row_vis[ArrSoduku[i][j] - 1])return false;
			row_vis[ArrSoduku[i][j] - 1] = 1;
			//col check
			if (col_vis[ArrSoduku[j][i] - 1])return false;
			col_vis[ArrSoduku[j][i] - 1] = 1;
			//block check
			if (blk_vis[ArrSoduku[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3] - 1])return false;
			blk_vis[ArrSoduku[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3] - 1] = 1;
		}
	}
	return true;
}

int* SudokuNext() {
	int*TmpMap = newTmpMap(mc.maps[CurrMapIndex][0][0] - 1);
	mc.ParseMap(ArrSoduku, TmpMap, CurrMapIndex++);
	CurrMapIndex %= mc.size;
	if (InitMapIndex == CurrMapIndex) {
		newMapIndex();
		nextMap();
	}
	//if (!simple_check()) {
	//	cout << "ERROR" << " MapIndex " << CurrMapIndex << ",TmpMap:";
	//	REPEAT(i, 9)cout << TmpMap[i]<<' ';
	//	cout << endl << "SUDOKU:" << endl;
	//	REPEAT(i, 9)REPEAT(j, 9) {
	//		cout << ArrSoduku[i][j] << ' ';
	//		if (j == 8)cout << endl;
	//	}
	//	getchar();
	//	exit(-1);
	//}

	return (int*)ArrSoduku;
}
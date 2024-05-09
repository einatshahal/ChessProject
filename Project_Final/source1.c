#include "general_functions.h"
#include "source1.h"

chessPosArray*** validKnightMoves()
{
	int r, c, i;
	int physicalSize = ROW;
	int logicalSize = 0;
	chessPosArray*** knightStr = (chessPosArray***)malloc(sizeof(chessPosArray***));
	*(knightStr) = (chessPosArray**)malloc(ROW * sizeof(chessPosArray*));
	check_allocation(*knightStr, "Memory Allocation failure\n");

	for (r = 0; r < ROW; r++)
	{
		**(knightStr) = (chessPosArray*)malloc(COL * sizeof(chessPosArray));
		check_allocation(**knightStr, "Memory Allocation failure\n");

		for (c = 0; c < COL; c++)
		{
			chessPos* arr;

			arr = knightOptions(physicalSize, &logicalSize, r, c);
			knightStr[r][c]->positions = arr;
			knightStr[r][c]->size = logicalSize;
		}

	}
	return knightStr;
}

chessPos* knightOptions(int physicalsize, int* logicalsize, int row, int col)
{
	int i = 0;

	chessPos* arr;
	arr = (chessPos*)malloc((physicalsize) * sizeof(*arr));
	check_allocation(arr, "Memory Allocation failure\n");
	if (row - 2 >= 0 && col - 1 >= 0 && row - 2 <= ROW - 1 && col - 1 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row - 2;
		(*(arr + i))[1] = '1' + col - 1;
		i++;
		(*logicalsize)++;
	}
	if (row - 2 >= 0 && col + 1 >= 0 && row - 2 <= ROW - 1 && col + 1 <= COL - 1)
	{

		(*(arr + i))[0] = 'A' + row - 2;
		(*(arr + i))[1] = '1' + col + 1;
		i++;
		(*logicalsize)++;
	}
	if (row + 2 >= 0 && col - 1 >= 0 && row + 2 <= ROW - 1 && col - 1 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row + 2;
		(*(arr + i))[1] = '1' + col - 1;
		i++;
		(*logicalsize)++;
	}
	if (row + 2 >= 0 && col + 1 >= 0 && row + 2 <= ROW - 1 && col + 1 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row + 2;
		(*(arr + i))[1] = '1' + col + 1;
		i++;
		(*logicalsize)++;
	}
	if (row - 1 >= 0 && col - 2 >= 0 && row - 1 <= ROW - 1 && col - 2 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row - 1;
		(*(arr + i))[1] = '1' + col - 2;
		i++;
		(*logicalsize)++;
	}
	if (row - 1 >= 0 && col + 2 >= 0 && row - 1 <= ROW - 1 && col + 2 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row - 1;
		(*(arr + i))[1] = '1' + col + 2;
		i++;
		(*logicalsize)++;
	}
	if (row + 1 >= 0 && col - 2 >= 0 && row + 1 <= ROW - 1 && col - 2 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row + 1;
		(*(arr + i))[1] = '1' + col - 2;
		i++;
		(*logicalsize)++;
	}
	if (row + 1 >= 0 && col + 2 >= 0 && row + 1 <= ROW - 1 && col + 2 <= COL - 1)
	{
		(*(arr + i))[0] = 'A' + row + 1;
		(*(arr + i))[1] = '1' + col + 2;
		i++;
		(*logicalsize)++;
	}
	if ((*logicalsize) != physicalsize)
	{
		arr = (chessPos*)realloc(arr, (*logicalsize) * sizeof(chessPos));
		check_allocation(arr, "Memory Allocation failure\n");
	}
	return arr;
}

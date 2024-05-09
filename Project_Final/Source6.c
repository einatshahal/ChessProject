#include "general_functions.h"
#include "source6.h"
#include "source2.h"

int checkAndDisplayPathFromFile(char* fileName)
{
	char board[ROW][COL];
	short int size;
	bool boardIsFull;
	chessPosList pos_list;
	FILE* file;
	file = fopen(fileName, "rb");

	if (!file)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	pos_list = getPositionsListFromBinaryFile(file);

	/*If: path is not good - return 1*/
	if (checkPosListFromBinaryFile(&pos_list) == false)
	{
		fclose(file);
		return 1;
	}
	/*If:path is good, check double location and delete them and print board*/
	else
	{
		display(&pos_list);/*(2)*/
		boardIsFull = CheckBoardifFull(board, &pos_list);
		if (boardIsFull == true)
		{
			fclose(file);
			return 2;
		}
	}

	fclose(file);
	return 3;
}

chessPosList getPositionsListFromBinaryFile(FILE* file)
{
	char MASK_ROW = 7 << 5; /* 1110 0000*/
	char MASK_COL = 7 << 2;  /* 0001 1100*/

	chessPosList lst;
	unsigned char currByte, prevByte, tempByte, resultRow, resultCol;
	int byteAmount, count = 1, i;
	short size;
	int b = 0; // helper for check if there is a remainder for byte amount

	makeEmptyList(&lst);
	fread(&size, sizeof(short), 1, file);

	if ((size * 6) % 8 != 0)
		b = 1;

	byteAmount = ((size * 6) / 8) + b;


	for (i = 1; i <= byteAmount; i++)
	{
		fread(&currByte, sizeof(char), 1, file);

		if (i % 3 == 1)
		{
			resultRow = currByte & MASK_ROW;
			resultRow = resultRow >> 5;
			resultCol = currByte & MASK_COL;
			resultCol = resultCol >> 2;
			insertCellToEndList(&lst, resultRow + 1, resultCol + 1);
			count++;
		}
		else if (i % 3 == 2)
		{
			tempByte = currByte;
			prevByte = prevByte << 6;
			tempByte = tempByte >> 2;
			tempByte = tempByte | prevByte;

			resultRow = tempByte & MASK_ROW;
			resultRow = resultRow >> 5;
			resultCol = tempByte & MASK_COL;
			resultCol = resultCol >> 2;

			insertCellToEndList(&lst, resultRow + 1, resultCol + 1);
			count++;

		}
		else if (i % 3 == 0)
		{
			tempByte = currByte;
			prevByte = prevByte << 4;
			tempByte = tempByte >> 4;
			tempByte = tempByte | prevByte;

			resultRow = tempByte & MASK_ROW;
			resultRow = resultRow >> 5;
			resultCol = tempByte & MASK_COL;
			resultCol = resultCol >> 2;

			insertCellToEndList(&lst, resultRow + 1, resultCol + 1);
			count++;

			if (count <= size)
			{
				tempByte = currByte;
				tempByte = tempByte << 2;

				resultRow = tempByte & MASK_ROW;
				resultRow = resultRow >> 5;
				resultCol = tempByte & MASK_COL;
				resultCol = resultCol >> 2;

				insertCellToEndList(&lst, resultRow + 1, resultCol + 1);
				count++;
			}
		}

		prevByte = currByte;
	}

	return lst;

}

bool checkPosListFromBinaryFile(chessPosList* lst)
{
	bool ifListIsGood = true;
	chessPosCell* cell = lst->head;
	while (cell != NULL)
	{
		cell->position[0] = cell->position[0] + '0';
		cell->position[1] = cell->position[1] + '0';
		if (cell->position[0] < '1' || cell->position[0]>'8')
			ifListIsGood = false;
		if (cell->position[1] < '1' || cell->position[1]>'8')
			ifListIsGood = false;

		cell = cell->next;
	}
	return ifListIsGood;
}

bool CheckBoardifFull(char Board[][COL], chessPosList* lst)
{
	fillEmptyBoard(Board);
	int row, col;
	int numOfPoss = 1; /*the num of the node in the lst*/ 
	chessPosCell* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		row = (curr->position[0] - 1) - '0';
		col = (curr->position[1] - 1) - '0';
		Board[row][col] = numOfPoss + '0';
		numOfPoss++;
		curr = curr->next;
	}
	return(checkBoard(Board));
}

bool checkBoard(char Board[][COL])
{
	bool IfBoardIsFull = true;
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (Board[i][j] == ' ')
				IfBoardIsFull = false;
		}
	}
	return IfBoardIsFull;
}
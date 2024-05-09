#include "general_functions.h"
#include "source2.h"

void display(chessPosList* lst)
{
	chessPosCell* node = lst->head; /*from where the list is beginng*/
	chessPosCell* nodeTemp;
	chessPosCell* nodeTempPrev = lst->head;
	chessPosCell* saveNext; /*the next of the node that we want to delete*/
	char Board[ROW][COL];

	while (node != NULL)
	{
		nodeTemp = node->next;
		while (nodeTemp != NULL)
		{
			if (nodeTemp->position[0] == node->position[0] && nodeTemp->position[1] == node->position[1])
			{
				if (nodeTemp->next == NULL) /* tail*/
				{
					nodeTempPrev->next = NULL;
					free(nodeTemp->position);
					free(nodeTemp);
					lst->tail = nodeTempPrev;

				}
				else
				{
					saveNext = nodeTemp->next;
					free(nodeTemp->position);
					free(nodeTemp);
					nodeTempPrev->next = saveNext;
					nodeTemp = nodeTempPrev;
				}
			}
			nodeTempPrev = nodeTemp;
			nodeTemp = nodeTemp->next;
		}

		node = node->next;
	}
	fillBoard(Board, lst);

	return;
}

void fillBoard(char Board[][COL], chessPosList* lst)
{
	fillEmptyBoard(Board);
	int row, col;
	int numOfPoss = 1; // the num of the node in the lst 
	chessPosCell* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		row = (curr->position[0] - 1) - '0';
		col = (curr->position[1] - 1) - '0';
		if (Board[row][col] == ' ')
		{
			Board[row][col] = numOfPoss + '0';
		}
		numOfPoss++;
		curr = curr->next;
	}

	printBoard(Board, ROW, COL);
}

void fillEmptyBoard(char Board[][COL])
{
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			Board[i][j] = ' ';
		}
	}
}

void printBoard(char Board[][COL], int row, int cols)
{
	int i, j;
	char letter = 'A';

	printf("    1   2   3   4   5   6   7   8   \n");
	printf("___________________________________\n");
	for (i = 0; i < row; i++)
	{
		printf("%c ", letter);
		for (j = 0; j < cols; j++)
		{
			if (Board[i][j] >= '1' && Board[i][j] <= '9')
			{
				printf("| %c  ", Board[i][j]);
			}
			else
			{
				printf("| %d ", Board[i][j] - '0');
			}
		}
		letter = letter + 1;
		printf("|\n");
	}
	printf("___________________________________\n");
}
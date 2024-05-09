#include "general_functions.h"
#include "source4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	int rowCurr, colCurr;
	int board[ROW][COL];
	chessPosList* lst;
	lst = (chessPosList*)malloc(sizeof(chessPosList));
	check_allocation(lst, "Memory Allocation failure\n");
	makeEmptyList(lst);
	/* Initialization of solution matrix */
	int row, col;
	for (row = 0; row < ROW; row++)
		for (col = 0; col < COL; col++)
			board[row][col] = 0;

	rowCurr = path_tree->root->position[0] - 'A';
	colCurr = path_tree->root->position[1] - '1';

	/*Since the Knight is initially at the first block*/
	board[rowCurr][colCurr] = 1;
	insertCellToEndList(lst, path_tree->root->position[0], path_tree->root->position[1]);

	/* Start from rowTemp, colTemp and explore all tours using helper() */
	if (helper(2, board, path_tree->root->next_possible_positions, lst) == false)
	{
		printf("Solution does not exist\n");
		return NULL;
	}
	return lst;
}

bool helper(int num, int* board[][COL], treeNodeListCell* cell, chessPosList* lst)
{
	int rowNext, colNext;

	if (cell == NULL)
		return false;
	//printf "recursive check cell"
	if (num == (ROW * COL))
	{
		insertCellToEndList(lst, cell->node->position[0], cell->node->position[1]);
		return true;
	}


	/* Try all next moves from the current coordinate*/
	while (cell != NULL)
	{
		//printf "while check cell"
		rowNext = cell->node->position[0] - 'A';
		colNext = cell->node->position[1] - '1';

		if (board[rowNext][colNext] == 0)
		{
			board[rowNext][colNext] = num;

			insertCellToEndList(lst, cell->node->position[0], cell->node->position[1]);
			if (helper(num + 1, board, cell->node->next_possible_positions, lst) == true)
			{
				return true;
			}
			board[rowNext][colNext] = 0;
			deleteEndOfList(lst);

		}
		/*the next cell*/
		cell = cell->next;


	}

	return false;

}

void deleteEndOfList(chessPosList* lst)
{
	chessPosCell* curr;
	curr = lst->head;

	if (curr == NULL)
		return;

	if (lst->head->next == NULL)
	{
		lst->head = NULL;
		return;
	}

	while (curr->next->next != NULL)
		curr = curr->next;

	curr->next = NULL;
	lst->tail = curr;
}


#include "general_functions.h"

char LetterToNumber(char row)
{
	if (row == 'A')
		row = '1';
	else if (row == 'B')
		row = '2';
	else if (row == 'C')
		row = '3';
	else if (row == 'D')
		row = '4';
	else if (row == 'E')
		row = '5';
	else if (row == 'F')
		row = '6';
	else if (row == 'G')
		row = '7';
	else if (row == 'H')
		row = '8';

	return row;
}

void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}

void insertCellToEndList(chessPosList* lst, char num1, char num2)
{
	chessPosCell* curr;
	curr = lst->head;

	chessPosCell* node;
	node = (chessPosCell*)malloc(sizeof(chessPosCell));
	check_allocation(node, "Memory Allocation failure\n");
	node->position[0] = num1;
	node->position[1] = num2;
	node->next = NULL;

	if (curr == NULL)
	{
		lst->head = lst->tail = node;
	}
	else
	{
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = node;
		lst->tail = node;
	}
}



void check_allocation(void* ptr, char* msg)
{
	if (!ptr)
	{
		fprintf(stderr, "Allocation failure:%s\n", msg);
		exit(MEMORY_ALLOCATION_ERROR);
	}
}

void freeCpList(chessPosList cpList)
{
	freeCpListHelper(cpList.head);
}

void freeCpListHelper(chessPosCell* cpCell)
{
	if (cpCell == NULL)
	{
		return;
	}
	freeCpListHelper(cpCell->next);
	free(cpCell);
}

void freeTree(treeNode* root)
{
	treeNodeListCell* currNode, * tempNode;

	if (root == NULL)
		return;

	currNode = root->next_possible_positions;

	while (currNode != NULL)
	{
		
		tempNode = currNode;
		freeTree(currNode->node);
		currNode = tempNode->next;
		free(tempNode);
	}
	free(root);
}
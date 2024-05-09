#include "general_functions.h"
#include "source1.h"
#include "source3.h"


pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree* tree;
	tree = (pathTree*)malloc(sizeof(pathTree));
	check_allocation(tree, "Memory Allocation failure\n");
	tree->root = NULL;

	chessPosList cpList;
	cpList.head = NULL;
	cpList.tail = NULL;
	tree->root = recursiveTree(startingPosition, cpList);
	return *tree;
}

treeNode* recursiveTree(chessPos* startingPosition, chessPosList cpList)
{
	int logicalSize = 0;
	int i;
	int j;
	bool wasThere = false; /* if the knight was already in this location */

	treeNode* root = makeANewRoot(startingPosition);
	chessPos* arRoot = makeANewArr(root, &logicalSize);
	chessPos tempPos;
	chessPosCell* cpCell;
	cpCell = makeANewCell(*startingPosition);
	if (cpList.head == NULL)
	{
		cpList.head = cpCell;
		cpList.tail = cpCell;
	}
	else
	{
		cpList.tail->next = cpCell;
		cpList.tail = cpCell;
	}
	if (logicalSize == 0)
	{
		freeCpList(cpList);
		return root;
	}
	else
	{
		/* temp list of the loctation that the knight was there */
		for (j = 0; j < logicalSize; j++)
		{
			chessPosCell* tem;
			tem = cpList.head;
			tempPos[0] = (*(arRoot + j))[0];
			tempPos[1] = (*(arRoot + j))[1];
			wasThere = false;
			while (tem != NULL)
			{
				if (tem->position[0] == tempPos[0] && tem->position[1] == tempPos[1])
				{
					wasThere = true;
					tem = NULL;
				}
				else
				{
					tem = tem->next;
				}
			}
			if (wasThere == false)
			{
				j = logicalSize;
			}
		}
		if (wasThere)
		{
			freeCpList(cpList);
			return root;
		}
	}
	treeNodeListCell* list;
	list = NULL;
	treeNodeListCell* res = NULL;
	chessPosCell* cpTemp;
	bool isFirst = true;
	for (i = 0; i < logicalSize; i++)
	{
		tempPos[0] = (*(arRoot + i))[0];
		tempPos[1] = (*(arRoot + i))[1];
		cpTemp = cpList.head;
		wasThere = false;
		while (cpTemp != NULL)
		{
			if (cpTemp->position[0] == tempPos[0] && cpTemp->position[1] == tempPos[1])
			{
				wasThere = true;
			}
			cpTemp = cpTemp->next;
		}
		if (!wasThere)
		{
			if (isFirst)
			{
				list = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
				check_allocation(list, "Memory Allocation failure\n");
				list->next = NULL;
				res = list;
			}
			else
			{
				list->next = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
				check_allocation(list->next, "Memory Allocation failure\n");
				list = list->next;
			}
			list->node = recursiveTree(&tempPos, copyList(cpList));
			isFirst = false;
		}
	}
	list->next = NULL;
	root->next_possible_positions = res;
	freeCpList(cpList);
	return root;
}

chessPosList copyList(chessPosList cpList)
{
	chessPosList res;
	res.head = NULL;
	res.tail = NULL;
	chessPosCell* temp = cpList.head;
	chessPosCell* cpCell;
	while (temp != NULL)
	{
		cpCell = makeANewCell(temp->position);
		if (res.head == NULL)
		{
			res.head = cpCell;
			res.tail = cpCell;
		}
		else
		{
			res.tail->next = cpCell;
			res.tail = cpCell;
		}
		temp = temp->next;
	}
	return res;
}

chessPosCell* makeANewCell(chessPos cp)
{
	chessPosCell* res = (chessPosCell*)malloc(sizeof(chessPosCell));
	check_allocation(res, "Memory Allocation failure\n");
	res->position[0] = cp[0];
	res->position[1] = cp[1];
	res->next = NULL;
	return res;
}

treeNode* makeANewRoot(chessPos* startingPosition)
{
	treeNode* root;
	root = (treeNode*)malloc(sizeof(treeNode));
	check_allocation(root, "Memory Allocation failure\n");

	root->position[0] = (*startingPosition)[0];
	root->position[1] = (*startingPosition)[1];
	root->next_possible_positions = NULL;
	return root;
}

chessPos* makeANewArr(treeNode* root, int* logicalSize)
{
	int physicalSize = 8;

	chessPos* arRoot;
	arRoot = knightOptions(physicalSize, logicalSize, (root->position[0] - 'A'), (root->position[1] - '1'));
	return arRoot;
}


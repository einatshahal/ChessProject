#pragma once
#ifndef _GENERAL_FUNCTIONS_
#define _GENERAL_FUNCTIONS_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 5
#define SIZE 100
#define SPACE ' '
#define MEMORY_ALLOCATION_ERROR -1


typedef char chessPos[2];

typedef struct chessPosArray
{
	unsigned int size;
	chessPos* positions;
}chessPosArray;

typedef struct chessPosList {
	struct chessPosCell* head;
	struct chessPosCell* tail;
}chessPosList;

typedef struct chessPosCell {
	chessPos position;
	struct chessPosCell* next;
}chessPosCell;

typedef struct treeNode
{
	chessPos position;
	struct treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct treeNodeListCell
{
	treeNode* node;
	struct treeNodeListCell* next;
}treeNodeListCell;

typedef struct pathTree
{
	treeNode* root;
}pathTree;


void check_allocation(void* ptr, char* msg); /* check the new alloction */
char LetterToNumber(char row);
void makeEmptyList(chessPosList* lst); //Make empty list
void insertCellToEndList(chessPosList* lst, char num1, char num2); //the function is insert cell to the end of the list
void freeCpList(chessPosList cpList);
void freeCpListHelper(chessPosCell* cpCell);
void freeTree(treeNode* root);

#endif
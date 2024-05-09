#pragma once
#ifndef _SOURCE4_
#define _SOURCE4_
#include "general_functions.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
bool helper(int num, int* board[][COL], treeNodeListCell* cell, chessPosList* lst);
void deleteEndOfList(chessPosList* lst);

#endif
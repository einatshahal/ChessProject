#pragma once
#ifndef _SOURCE3_
#define _SOURCE3_
#include "general_functions.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);/*the fun bulid tree of all the possibl knight path*/
treeNode* recursiveTree(chessPos* startingPosition, chessPosList cpList);/*build the tree in recursive*/
chessPosList copyList(chessPosList cpList);
chessPosCell* makeANewCell(chessPos cp);
treeNode* makeANewRoot(chessPos* startingPosition);
chessPos* makeANewArr(treeNode* root, int* logicalSize);

#endif
#pragma once
#ifndef _SOURCE6_
#define _SOURCE6_
#include "general_functions.h"

int checkAndDisplayPathFromFile(char* fileName);
chessPosList getPositionsListFromBinaryFile(FILE* file);
bool checkPosListFromBinaryFile(chessPosList* lst);
bool CheckBoardifFull(char Board[][COL], chessPosList* lst);
bool checkBoard(char Board[][COL]);

#endif
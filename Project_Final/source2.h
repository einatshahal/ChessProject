#pragma once
#ifndef _SOURCE2_
#define _SOURCE2_
#include "general_functions.h"

void display(chessPosList* lst);/*delete the nodes in the lst that found double,call to fillBoard*/
void fillBoard(char Board[][COL], chessPosList* lst);
void fillEmptyBoard(char Board[][COL]); // fill the borad in spaces
void printBoard(char Board[][COL], int row, int cols); // print the  bord of the chess

#endif

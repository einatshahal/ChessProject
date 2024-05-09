#pragma once
#ifndef _SOURCE1_
#define _SOURCE1_

#include "general_functions.h"

chessPosArray*** validKnightMoves(); /* bulid the bord of the chess and in every cell inculde list of the moves that the knight can move */
chessPos* knightOptions(int physicalsize, int* logicalsize, int row, int col); /* make a new list of all the moves of the knight */

#endif /* !_SOURCE1_*/
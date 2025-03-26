#pragma once
#include "const.h"

void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]);

void printChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]);

Position getPiceByUser();
//void userGetPice(setPiceByUser);
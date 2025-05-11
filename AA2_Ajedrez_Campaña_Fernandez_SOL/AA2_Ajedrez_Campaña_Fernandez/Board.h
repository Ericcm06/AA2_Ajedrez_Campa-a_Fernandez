#pragma once
#include "const.h"
#include "utils.h"

/// Inicializa el tablero con piezas en posición inicial
void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]);

/// Imprime el tablero con columnas 1–8 arriba y filas 8→1 a la izquierda
void printChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]);

#pragma once
#include "const.h"
#include "utils.h"
#include "Board.h"

/// Bucle principal: solicita movimientos, valida, alterna turnos,
/// ejecuta capturas, promoción y detecta final al capturar un rey.
void gameLoop(char chessBoard[BOARD_SIZE][BOARD_SIZE]);

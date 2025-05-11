#include "const.h"
#include "utils.h"
#include <iostream>

void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    // Primero fondo y peones
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (j == BOARD_SIZE - 2)
                chessBoard[j][i] = WHITE_PAWN;
            else if (j == 1)
                chessBoard[j][i] = BLACK_PAWN;
            else
                chessBoard[j][i] = CHAR_BG_BOARD;
        }
    }

    // Posiciones fijas de torres, caballos, alfiles, rey y dama
    const short R_L = 0;
    const short R_R = BOARD_SIZE - 1;
    const short N_L = 1;
    const short N_R = BOARD_SIZE - 2;
    const short B_L = 2;
    const short B_R = BOARD_SIZE - 3;
    const short K_X = 3;
    const short Q_X = BOARD_SIZE - 4;

    // Negras en fila 8 (índice 0)
    chessBoard[0][R_L] = BLACK_ROOK;
    chessBoard[0][R_R] = BLACK_ROOK;
    chessBoard[0][N_L] = BLACK_KNIGHT;
    chessBoard[0][N_R] = BLACK_KNIGHT;
    chessBoard[0][B_L] = BLACK_BISHOP;
    chessBoard[0][B_R] = BLACK_BISHOP;
    chessBoard[0][K_X] = BLACK_KING;
    chessBoard[0][Q_X] = BLACK_QUEEN;

    // Blancas en fila 1 (índice 7)
    chessBoard[BOARD_SIZE - 1][R_L] = WHITE_ROOK;
    chessBoard[BOARD_SIZE - 1][R_R] = WHITE_ROOK;
    chessBoard[BOARD_SIZE - 1][N_L] = WHITE_KNIGHT;
    chessBoard[BOARD_SIZE - 1][N_R] = WHITE_KNIGHT;
    chessBoard[BOARD_SIZE - 1][B_L] = WHITE_BISHOP;
    chessBoard[BOARD_SIZE - 1][B_R] = WHITE_BISHOP;
    chessBoard[BOARD_SIZE - 1][K_X] = WHITE_KING;
    chessBoard[BOARD_SIZE - 1][Q_X] = WHITE_QUEEN;
}

void printChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    // Cabecera de columnas
    std::cout << "  ";
    for (int c = 1; c <= BOARD_SIZE; ++c)
        std::cout << c << ' ';
    std::cout << "\n";

    // Filas 8?1
    for (int r = 0; r < BOARD_SIZE; ++r) {
        std::cout << (BOARD_SIZE - r) << ' ';
        for (int c = 0; c < BOARD_SIZE; ++c) {
            std::cout << chessBoard[r][c] << ' ';
        }
        std::cout << "\n";
    }
}

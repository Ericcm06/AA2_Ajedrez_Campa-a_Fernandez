#include "const.h"
#include "board.h"

int main() {
    char chessBoard[BOARD_SIZE][BOARD_SIZE];

    std::cout << "¡¡¡Bienvenido al mejor ajedrez!!!" << std::endl;

    
    initChessBoard(chessBoard); // Inicializar el tablero
    viewChessBoard(chessBoard); // Imprimir el tablero
    

    return 0;
}
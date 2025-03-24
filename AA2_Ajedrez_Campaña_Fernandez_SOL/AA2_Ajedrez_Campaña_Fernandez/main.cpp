#include "const.h"

int main() {
    char chestBoard[BOARD_SIZE][BOARD_SIZE];

    std::cout << "¡¡¡Bienvenido al mejor ajedrez!!!" << std::endl;

    // Inicializar el tablero
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            chestBoard[i][j] = CHAR_BG_BOARD;
        }
    }

    // Mostrar índices de las columnas
    std::cout << ' ' << ' ';
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i + 1 << ' ';
    }
    std::cout << std::endl;

    // Imprimir el tablero
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << BOARD_SIZE - i << ' ';

        for (int j = 0; j < BOARD_SIZE; j++) {  
            std::cout << chestBoard[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
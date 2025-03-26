#include "const.h"
#include "board.h"
#include "utils.h"

int main() {
    char chessBoard[BOARD_SIZE][BOARD_SIZE];
    bool gameOver = false;
    std::cout << "¡¡¡Bienvenido al mejor ajedrez!!!" << std::endl;

    
    initChessBoard(chessBoard); // Inicializar el tablero
    do {
        Position userGetPice, userSetPice;

        bool isGettingAPice = true;
        do {

            std::cout << "Elige una pieza: " << std::endl;
            std::cout << "X:  " << std::endl;
            std::cin >> userGetPice.x;
            std::cout << "Y:  " << std::endl;
            std::cin >> userGetPice.y;

            if (userGetPice.x < 1 || userGetPice.x > BOARD_SIZE || userGetPice.y < 1 || userGetPice.y > BOARD_SIZE)
            {
                std::cout << "INPUT INVALIDO"
                    isGettingAPice = false;
            }
            else {


            }

            } while ();


        printChessBoard(chessBoard); // Imprimir el tablero

        system("cls");
    } while (!gameOver);
    

    return 0;
}
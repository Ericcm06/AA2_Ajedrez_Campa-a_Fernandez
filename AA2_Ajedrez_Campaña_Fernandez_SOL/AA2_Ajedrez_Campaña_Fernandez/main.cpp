// main.cpp
#include "const.h"
#include "Board.h"
#include "game.h"
#include <iostream>

int main() {
    // 1) Mostrar panel de ayuda para el usuario :)
    std::cout << "\n\tPanel de ayuda e instrucciones de funcionamiento\n\n";

    std::cout << "\n\n\t\t\t [¡] Ayuda:\n\n";
    std::cout << "\t\t[+] Introducir posiciones en formato: columna fila (1..8)\n";
    std::cout << "\t\t[+] Ejemplo: \"2 7\" para origen, luego \"2 5\" para destino\n";
    std::cout << "\t\t[+] Capturar el rey enemigo finaliza la partida\n";
    std::cout << "\t\t[+] Los peones se promocionan automaticamente al llegar al extremo contrario\n";
    std::cout << "\t\t[+] No hay enroque ni movimiento \"al paso\"\n";
    std::cout << "\t\t[+] Sin acentos ni caracteres especiales en las entradas\n\n";

    // 2) Limpiar pantalla antes de empezar jeje
    system("timeout /t 6 >nul");
	system("cls");
     


    // 3) Inicializar tablero y lanzar bucle de juego
    char chessBoard[BOARD_SIZE][BOARD_SIZE];
    initChessBoard(chessBoard);
    gameLoop(chessBoard);

    return 0;
}

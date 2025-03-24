#include "const.h"

int main() {
	char chestBoard[BOARD_SIZE][BOARD_SIZE];
	std::cout << "¡¡¡Bienbenido al mejor ajedrez!!!" << std::endl;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			chestBoard[i][j] = 'CHAR_BG';
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << i++ << ' ';
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			std::cout << chestBoard[i][j];
		}
	}

	return 0;
}
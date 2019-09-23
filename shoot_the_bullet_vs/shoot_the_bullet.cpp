#include "GameField.h"
#include "windows.h"
#include <iostream>
#include <conio.h>
//..
const int LCD_WIDTH = 84;
const int LCD_HEIGHT = 48;

void PrintDestructBlock(int width, int height)
{
	std::cout << "{}";
}
void PrintUnDestructBlock(int width, int height)
{
	std::cout << "[]";
}



int main() {
	Player player;
	int i = 0;
	char input;
	std::cout << "WARNING! fullscreen for correct displaying" << std::endl;
	std::cout << " press w to move up;" << std::endl;
	std::cout << " press a to move right;" << std::endl;
	std::cout << " press s to move left;" << std::endl;
	std::cout << " press d to move right;" << std::endl;
	std::cout << " press q to move quit;" << std::endl;
	std::cout << " press f to shoot;" << std::endl;
	std::cout << "******************" << std::endl;
	std::cout << "[] - undestruct block" << std::endl;
	std::cout << "{} - destruct block" << std::endl;
	std::cout << "<> - player" << std::endl;
	system("pause");

	while (!player.field.isGameOver) {

		player.field.CreateNewLine(i);
		for (int action_idx = 0; action_idx < 10; action_idx++) {
			if (!player.field.isGameOver) {
				player.field.PrintField();
				input =_getch();

				if (input == 'w') player.moveUp();
				else if (input == 'a') player.moveLeft();
				else if (input == 's') player.moveDown();
				else if (input == 'd') player.moveRight();
				else if (input == 'f') player.shoot();
				else std::cout << "incorrect input!";
				if (player.field.isGameOver) {
					std::cout << "Game over! your score: "
						<< player.field.getScore() << std::endl;
					std::cout << "Press any key to exit: " << std::endl;
					player.field.setHiscore(player.field.getScore());
					system("pause");
				}
			}
		}
		
		//print player
		player.field.PrintField();

		i++;
		if (i>=LCD_WIDTH)i = 0;

	}
	return 0;
}
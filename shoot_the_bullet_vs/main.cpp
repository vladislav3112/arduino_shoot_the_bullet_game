#include "GameField.h"
#include "Player.h"
#include  <iostream>
#include "windows.h"

//..
const int LCD_WIDTH = 84;
const int LCD_HEIGHT = 48;
void GameField::PrintField()
{
	for (int i = 0; i < LCD_WIDTH;i++) {
		{
			for (int j = 0; j < LCD_HEIGHT;j++)
				if(game_field[i][j] == 0)std::cout << "  ";
				else if(game_field[i][j] == 1)std::cout << "[]";
				else if (game_field[i][j] == 2)std::cout << "{}";
				else if (game_field[i][j] == 3)std::cout << "<>";
		}
	}
}
void GameField::PrintDestructBlock(int width, int height)
{
	std::cout << "{}";
}
void GameField::PrintUnDestructBlock(int width, int height)
{
	std::cout << "[]";
}



int main() {
	GameField field;
	Player player(field);
	int i = 0;
	char input;
	std::cout << " press w to move up;" << std::endl;
	std::cout << " press a to move right;" << std::endl;
	std::cout << " press s to move left;" << std::endl;
	std::cout << " press d to move right;" << std::endl;
	std::cout << " press q to move quit;" << std::endl;
	std::cout << " press f to shoot;" << std::endl;

	while (!field.isGameOver) {

		field.CreateNewLine(i);
		for (int action_idx = 0; action_idx < 10; action_idx++) {
			field.PrintField();
			std::cin >> input;

			if (input == 'w') player.moveUp(field);
			else if (input == 'a') player.moveLeft(field);
			else if (input == 's') player.moveDown(field);
			else if (input == 'd') player.moveRight(field);
			else if (input == 'f') player.shoot(field);
			else std::cout << "incorrect input!";
			if (!field.isGameOver) {
				std::cout << "Game over! your score: "
					<< field.getScore() << std::endl;
			}
		}
		
		//print player
		field.PrintField();

		i++;
		if (i >= GameField::LCD_WIDTH)i = 0;

	}
	return 0;
}
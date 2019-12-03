#include "GameField.h"
#include <iostream>
#include <time.h>
GameField::GameField()
{
	score = 0;
	hiscore = 0;
	for (int i = 0; i < LCD_HEIGHT; i++) {
		for (int j = 0; j < LCD_WIDTH ; j++)
			game_field[i][j] = 0;
	}
}
int  GameField::getFieldAt(int w, int h) const
{
	return game_field[h][w];
}

void GameField::setFieldAt(int w, int h, int val)
{
	game_field[h][w] = val;
}

void GameField::CreateNewLine(int line_num) {
	srand(time(NULL));
	int randNum;

	for (int i = LCD_HEIGHT - 2; i > 0; i--) {
		for (int j = 0; j < LCD_WIDTH; j++) {
			if (game_field[i-1][j] != 3 & game_field[i][j] != 3)game_field[i][j] = game_field[i - 1][j];
		}
	}
	for (int i = 0; i < LCD_WIDTH; i++) {
		randNum = 1 + rand() % 10;//check randomizer
		if (randNum <= 2)game_field[line_num][i] = 1;
		else if ((randNum <= 6) and (randNum >= 3))
		game_field[line_num][i] = 2;
	}	
	//
	for (int j = 0; j < LCD_WIDTH; j++) {
		if((game_field[LCD_HEIGHT - 1][j]==3)&(game_field[LCD_HEIGHT - 2][j] != 0))isGameOver=true;
		if(game_field[LCD_HEIGHT - 1][j] != 3 & game_field[LCD_HEIGHT - 2][j]!=3)game_field[LCD_HEIGHT -1][j] = game_field[LCD_HEIGHT - 2][j];
	}
}


void GameField::PrintField()
{
	system("cls");
	std::cout << "your score = " << score << std::endl;
	for (int i = 0; i < LCD_HEIGHT; i++) {
		
		std::cout << LCD_HEIGHT - i;
			for (int j = 0; j < LCD_WIDTH; j++){
				
				if (game_field[i][j] == 0)std::cout << "  ";
				else if (game_field[i][j] == 1)std::cout << "[]";
				else if (game_field[i][j] == 2)std::cout << "{}";
				else if (game_field[i][j] == 3)std::cout << "<>";
		}
		std::cout << '\n';
	}
}



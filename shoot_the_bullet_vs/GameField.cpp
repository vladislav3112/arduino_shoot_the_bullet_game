#include "GameField.h"
#include <iostream>
#include <time.h>
GameField::GameField()
{
	score = 0;
	hiscore = 0;
	for (int i = 0; i < LCD_WIDTH; i++) {
		for (int j = 0; j < LCD_HEIGHT; j++)
			game_field[i][j] = 0;;
	}
}
int  GameField::getFieldAt(int w, int h) const
{
	return game_field[w][h];
}

void GameField::setFieldAt(int w, int h, int val)
{
	game_field[w][h] = val;
}

void GameField::CreateNewLine(int line_num) {
	srand(time(NULL));
	for (int i = 0; i < LCD_WIDTH; i++) {
		int randNum = 1 + rand() % 10;//check randomizer
		if (randNum <= 2)
		{
			//PrintUnDestructBlock(i, line_num);
			game_field[i][line_num] = 1;
		}
		else if ((randNum <= 6) and (randNum >= 3))
		{
			//PrintDestructBlock(i, line_num);
			game_field[i][line_num] = 2;
		}else game_field[i][line_num] = 0;
	}
}




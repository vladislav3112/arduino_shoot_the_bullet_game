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
	for (int i = 0; i < LCD_WIDTH; i++) {
		randNum = 1 + rand() % 10;//check randomizer
		if (randNum <= 2)
		{
			if (game_field[line_num][i] == 3)isGameOver = true;
			//PrintUnDestructBlock(i, line_num);
			game_field[line_num][i] = 1;
		}
		else if ((randNum <= 6) and (randNum >= 3))
		{
			if (game_field[line_num][i] == 3)isGameOver = true;
			//PrintDestructBlock(i, line_num);
			game_field[line_num][i] = 2;
		}
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


Player::Player()
{
	width = 42;
	height = LCD_HEIGHT - 1;
	field.setFieldAt(42, LCD_HEIGHT - 1, 3);//does not work
}
Player::Player(int w, int h)
{
	width = w;
	height = h;
	field.setFieldAt(w, h, 3);
}
void Player::moveLeft()
{
	if (width != 0) {
		width--;
		int pos_idx = field.getFieldAt(width, height);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
		field.setFieldAt(width+1, height, 0);
	}
}
void Player::moveRight()
{
	if (width != LCD_WIDTH - 1) {
		width++;
		int pos_idx = field.getFieldAt(width, height);
		if ((pos_idx == 1) | (pos_idx == 2)) field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
		field.setFieldAt(width-1, height, 0);
	}
}
void Player::moveUp()
{
	if (height != 0) {
		height--;
		int pos_idx = field.getFieldAt(width,height);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
		field.setFieldAt(width, height+1, 0);
	}
}
void Player::moveDown()
{

	if (height != LCD_HEIGHT - 1) {
		height++;
		int pos_idx = field.getFieldAt(width, height);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
		field.setFieldAt(width, height-1, 0);
	}
}
void Player::shoot()
{
	for (int i = height + 1; i >= 0; i--) {
		if (field.getFieldAt(width, i) == 1)break;
		if (field.getFieldAt(width,i) == 2) {
			std::cout << "You destroyed block!  +100 points" << std::endl;
			field.setScore(field.getScore() + 100);
			field.setFieldAt(width,i,0);
			break;
		}
	}
}
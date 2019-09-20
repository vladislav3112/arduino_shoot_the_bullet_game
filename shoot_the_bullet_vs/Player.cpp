#include "Player.h";
#include<iostream>
Player::Player(GameField field)
{
	width = 0;
	height = 20;
	field.setFieldAt(0, 20, 3);
}
Player::Player(GameField field, int w, int h)
{
	width = w;
	height = h;
	field.setFieldAt(w, h, 3);
}
void Player::moveLeft(GameField field)
{
	if (width != 0) {
		width--;
		int pos_idx = field.getFieldAt(height, width);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
	}
}

void Player::moveRight(GameField field)
{
	if (width != LCD_WIDTH - 1) {
		width++;
		int pos_idx = field.getFieldAt(height, width);
		if ((pos_idx == 1) | (pos_idx == 2)) field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
	}
}

void Player::moveUp(GameField field)
{
	if (height != LCD_HEIGHT - 1) {
		height++;
		int pos_idx = field.getFieldAt(height, width);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
	}
}

void Player::moveDown(GameField field)
{
	
	if (height != 0) {
		height--;
		int pos_idx = field.getFieldAt(height, width);
		if((pos_idx == 1)| (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
	}
}

void Player::shoot(GameField field)
{
	for (int i = LCD_HEIGHT - 1; i >= 0; i--) {
		if (field.getFieldAt(i, height) == 2) {
			std::cout << "You destroyed block!  +100 points" << std::endl;
			field.setScore(field.getScore() + 100);
		}
	}
}

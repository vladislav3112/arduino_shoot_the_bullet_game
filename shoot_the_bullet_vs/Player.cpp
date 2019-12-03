#include "Player.h"
#include <iostream>
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
	field.setFieldAt(width, height, 0);
	if (width != 0)width--;
	else width = LCD_WIDTH - 1;

	int pos_idx = field.getFieldAt(width, height);
	if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
	field.setFieldAt(width, height, 3);
}

void Player::moveRight()
{
	field.setFieldAt(width, height, 0);
	if (width != LCD_WIDTH - 1)width++;
	else width = 0;

	int pos_idx = field.getFieldAt(width, height);
	if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
	field.setFieldAt(width, height, 3);
}
void Player::moveUp()
{
	if (height != 0) {
		height--;
		int pos_idx = field.getFieldAt(width, height);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
		field.setFieldAt(width, height + 1, 0);
	}
}
void Player::moveDown()
{
	if (height != LCD_HEIGHT - 1) {
		height++;
		int pos_idx = field.getFieldAt(width, height);
		if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
		field.setFieldAt(width, height, 3);
		field.setFieldAt(width, height - 1, 0);
	}
}
void Player::shoot()
{
	for (int i = height + 1; i >= 0; i--) {
		if (field.getFieldAt(width, i) == 1)break;
		if (field.getFieldAt(width, i) == 2) {
			std::cout << "You destroyed block!  +100 points" << std::endl;
			field.setScore(field.getScore() + 100);
			field.setFieldAt(width, i, 0);
			break;
		}
	}
}
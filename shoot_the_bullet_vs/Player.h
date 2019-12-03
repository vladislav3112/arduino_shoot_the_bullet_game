#pragma once
#include "GameField.h"
class Player :public GameField {
public:
	GameField field;
	Player();
	Player(GameField& field);
	Player(int w, int h);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void shoot();
	int  getWeight() { return width; }
	int getHeight() { return height; }
	int SetHeight(int h) { h = height; }
	int SetWidth(int h) { h = width; }
private:
	int width;
	int height;
};
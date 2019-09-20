#include "GameField.h"
#include <exception>
class Player:public GameField {
public:
	Player(GameField field);
	Player(GameField field, int w, int h);
	void moveLeft(GameField field);
	void moveRight(GameField field);
	void moveUp(GameField field);
	void moveDown(GameField field);
	void shoot(GameField field);
	int  getWeight() { return width; }
	int getHeight() { return height; }
	int SetHeight(int h) { h = height; }
	int SetWidth(int h) { h = width; }
private:
	int width;
	int height;
};


class GameField {
public:
	GameField();
	enum size{ LCD_WIDTH = 84, LCD_HEIGHT = 48};
	bool isGameOver = false;
	void CreateNewLine(int line_num);
	void ChangeLines();
	void PrintField();
	void PrintDestructBlock(int width, int height);
	void PrintUnDestructBlock(int width, int height);
	int getScore() { return score; }
	int getHighscore() { return hiscore; }
	int getWtdth() { return LCD_HEIGHT; }
	int getHeight() { return LCD_WIDTH; }
	int getFieldAt(int w,int h) const;
	void setFieldAt(int w, int h, int val);
	void setScore(int s) { score = s; };
private:
	int score;
	int hiscore;
	int game_field[LCD_HEIGHT][LCD_WIDTH];
};

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
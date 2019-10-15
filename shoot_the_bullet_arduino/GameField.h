class GameField {
public:
  GameField();
  static const int FIELD_SIZE = 16;
  bool isGameOver = false;
  void CreateNewLine(int line_num);
  void ChangeLines();
  void PrintField();
  void PrintDestructBlock(int width, int height);
  void PrintUnDestructBlock(int width, int height);
  int getScore() { return score; }
  int getHighscore() { return hiscore; }
  int getFieldAt(int w,int h) const;
  void setFieldAt(int w, int h, int val);
  void setScore(int s) { score = s; };
  void setHiscore(int s) { hiscore = s; };
private:
  int score;
  int hiscore;
  int game_field[FIELD_SIZE][FIELD_SIZE];
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
  int shoot_check(int w, int h);
  int getWidth() { return width; }
  int getHeight() { return height; }
  int SetHeight(int h) { h = height; }
  int SetWidth(int h) { h = width; }
private:
  int width;
  int height;
};

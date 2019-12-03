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

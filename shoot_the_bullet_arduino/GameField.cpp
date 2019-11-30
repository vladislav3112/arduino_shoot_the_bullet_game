#include "GameField.h"
#include <time.h>
GameField::GameField()
{
  score = 0;
  hiscore = 0;
  for (int i = 0; i < FIELD_SIZE; i++) {
    for (int j = 0; j < FIELD_SIZE ; j++)
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
  
  int randNum;
  for (int j = 0; j < FIELD_SIZE; j++) {
    if((game_field[FIELD_SIZE - 1][j]==3)&(game_field[FIELD_SIZE - 2][j] != 0))isGameOver = true;
    if(game_field[FIELD_SIZE - 1][j] != 3 & game_field[FIELD_SIZE - 2][j]!=3)game_field[FIELD_SIZE -1][j] = game_field[FIELD_SIZE - 2][j];
  }
  for (int i = FIELD_SIZE - 2; i > 0; i--) {
    for (int j = 0; j < FIELD_SIZE; j++) {
      if (game_field[i-1][j] != 3 & game_field[i][j] != 3)game_field[i][j] = game_field[i - 1][j];
    }
  }
  for (int i = 0; i < FIELD_SIZE; i++) {
    randNum = 1 + rand() % 14;//check randomizer
    if (randNum <= 2)game_field[line_num][i] = 1;
    else if ((randNum <= 7) and (randNum >= 3))game_field[line_num][i] = 2;
    else game_field[line_num][i] = 0;
  } 
  
}

Player::Player()
{
  width = 8;
  height = FIELD_SIZE - 1;
  field.setFieldAt(8, FIELD_SIZE - 1, 3);//does not work
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
    else width = FIELD_SIZE-1;
    
    int pos_idx = field.getFieldAt(width, height);
    if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
    field.setFieldAt(width, height, 3);  
}

void Player::moveRight()
{
    field.setFieldAt(width, height, 0);
    if (width != FIELD_SIZE - 1)width++;
    else width = 0;
    
    int pos_idx = field.getFieldAt(width, height);
    if ((pos_idx == 1) | (pos_idx == 2))field.isGameOver = true;//game over
    field.setFieldAt(width, height, 3);  
}



int Player::shoot_check(int w, int h)
{
    if (field.getFieldAt(w, h) == 1)return 1;
    if (field.getFieldAt(w, h) == 2) {
      //std::cout << "You destroyed block!  +100 points" << std::endl;
      field.setScore(field.getScore() + 100);
      field.setFieldAt(w,h,0);
      //ClrBullet(width,i);//??
      return 2;
    }
    return 0;
}

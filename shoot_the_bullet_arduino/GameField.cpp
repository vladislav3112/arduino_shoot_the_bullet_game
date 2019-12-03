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

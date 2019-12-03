#include "Player.h"
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

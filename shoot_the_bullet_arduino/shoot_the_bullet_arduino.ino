const byte LCD_WIDTH = 84;
const byte LCD_HEIGHT = 48;
const byte FIELD_SIZE = 16;
const byte SCORE_WIDTH = 32;
unsigned int prev_time;
unsigned int curr_time;
int local_score = 0;

#define RIGHT_pin 3
#define LEFT_pin 5
#define FIRE_pin 6


#include "Player.h"
#include <LCD5110_Graph.h>
#include <avr/pgmspace.h>
LCD5110 lcd(9,10,11,12,13); // LCD5110(SCK, MOSI, DC, RST, CS);

extern unsigned char SmallFont[];


void DrawPlayer(int height, int width){// h, w: left_top of object 
    lcd.setPixel(width*3,height*3);       // ...
    lcd.setPixel(width*3+1,height*3+1);   //  .
    lcd.setPixel(width*3+2,height*3+2);   // ...
    lcd.setPixel(width*3+2,height*3);     //-player display
    lcd.setPixel(width*3,height*3+2);
    lcd.setPixel(width*3+1,height*3+2);
    lcd.setPixel(width*3+1,height*3);
}
void DrawBullet(int height, int width){// improve
    lcd.drawRect(width*3,height*3,width*3+2,height*3+2);
    lcd.drawLine(width*3+1,height*3,width*3+1,height*3+2); // to fill square
    lcd.drawLine(width*3,height*3+1,width*3+2,height*3+1);
}
void DrawUndestructBlock(int height, int width){// h, w: left_top of object 
    lcd.setPixel(width*3,height*3);       // . .
    lcd.setPixel(width*3+1,height*3+1);   //  .
    lcd.setPixel(width*3+2,height*3+2);   // . .
    lcd.setPixel(width*3+2,height*3);     //-display
    lcd.setPixel(width*3,height*3+2);
}
void ClrBullet(int height, int width){
    lcd.clrPixel(width*3,height*3);
    lcd.clrPixel(width*3,height*3+1);
    lcd.clrPixel(width*3,height*3+2);
    lcd.clrPixel(width*3+1,height*3);
    lcd.clrPixel(width*3+1,height*3+1);
    lcd.clrPixel(width*3+1,height*3+2);
    lcd.clrPixel(width*3+2,height*3);
    lcd.clrPixel(width*3+2,height*3+1);
    lcd.clrPixel(width*3+2,height*3+2);
}
void DrawBlock(int height, int width){
  lcd.drawRect(width*3,height*3,width*3+2,height*3+2);
}
void GameField::PrintField()
{
  lcd.clrScr();
  lcd.print("SCORE",RIGHT,8);
  lcd.printNumI(local_score,RIGHT, 16);
  for (int i = 0; i < FIELD_SIZE; i++) {
    //std::cout << LCD_HEIGHT - i
      for (int j = 0; j < FIELD_SIZE; j++){
        if (game_field[i][j] == 1)DrawUndestructBlock(i,j); //undestructBlock
        else if (game_field[i][j] == 2)DrawBlock(i,j); //destructBlock
        else if (game_field[i][j] == 3)DrawPlayer(i,j); //player
        }
      }
   lcd.update();
}



void setup() {
  srand(analogRead(A2));
      pinMode(RIGHT_pin, INPUT_PULLUP);
      pinMode(LEFT_pin, INPUT_PULLUP);
      pinMode(FIRE_pin, INPUT_PULLUP);
      pinMode(7,OUTPUT);
      digitalWrite(7,LOW);
  lcd.InitLCD(70);
  lcd.setFont(SmallFont);
  Serial.begin(115200);
  prev_time = millis();
}

int curr_line;
bool bullet_flag = false;

void loop() {
Player player;
curr_line = 0;//start trigger

  while (!player.field.isGameOver) {
      curr_time = millis();
      
      if(curr_time - prev_time > 5000 | curr_line == 0) {//if 5 seconds passed
          player.field.CreateNewLine(0);
          player.field.PrintField();
          prev_time = millis();
          curr_line = 1;
      }
      
        else if(digitalRead(RIGHT_pin) == LOW){ 
            ClrBullet(player.getHeight(),player.getWidth());
            player.moveRight();
            //Serial.println("RIGHT!");
            DrawPlayer(player.getHeight(),player.getWidth());
            lcd.update();
        }
        
        else if(digitalRead(LEFT_pin) == LOW){ 
            ClrBullet(player.getHeight(),player.getWidth());
            player.moveLeft();//delay(50);
            //Serial.println("LEFT!");
            DrawPlayer(player.getHeight(),player.getWidth());
            lcd.update();
        }
        
        else if(digitalRead(FIRE_pin) == LOW){
          //Serial.println("FIRE!");
            bullet_flag = false;
            for (int i=1; i <= FIELD_SIZE; i++){
                          
              if(i>2)ClrBullet(FIELD_SIZE - i+1,player.getWidth()); 
              if(bullet_flag){
                DrawUndestructBlock(FIELD_SIZE - i+1,player.getWidth());
                lcd.update();
                break;
              }
              if(i!=1)DrawBullet(FIELD_SIZE - i,player.getWidth());             
              
              if(i==FIELD_SIZE)ClrBullet(0,player.getWidth());
              
              if(player.shoot_check(player.getWidth(),FIELD_SIZE - i) == 1){//bullet on undestruct block situation
                DrawUndestructBlock(FIELD_SIZE - i,player.getWidth());
                bullet_flag=true;
              }
              if(player.shoot_check(player.getWidth(),FIELD_SIZE - i) == 2){//bullet on destruct block situation
                ClrBullet(FIELD_SIZE - i+1,player.getWidth());
                break;
              }
              delay(60);
            local_score = player.field.getScore();
          //button F       
            lcd.update();  
          }
        }

      
        if (player.field.isGameOver) {
          lcd.clrScr();         
          player.field.getScore();
          lcd.print("GAME OVER",CENTER,16);
          lcd.print("your score",CENTER, 24);
          lcd.printNumI(local_score,CENTER,32);
          lcd.update();
          local_score = 0;
          prev_time = millis();
          player.field.setHiscore(player.field.getScore());
          ///display score;
        }
        delay(50);   
    
    
    //print player
     if(curr_line == FIELD_SIZE)curr_line = 1;
  }
  
  player.field.isGameOver = false;
  delay(5000);
}

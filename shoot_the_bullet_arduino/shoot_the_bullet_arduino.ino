/*
  LiquidCrystal Library - Hello World

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include "GameField.h"
const byte LCD_WIDTH = 84;
const byte LCD_HEIGHT = 48;
const byte FIELD_SIZE = 16;
const byte SCORE_WIDTH = 32;
#define RIGHT_pin 3
#define LEFT_pin 5
#define UP_pin 2
#define DOWN_pin 4
#define FIRE_pin 6

#include <LCD5110_Graph.h>
#include <avr/pgmspace.h>
LCD5110 lcd(9,10,11,12,13); // LCD5110(SCK, MOSI, DC, RST, CS);

// initialize the library with the numbers of the interface pins


void PrintDestructBlock(int width, int height){//в файл вывода на дисплей
      lcd.print("o",width,height);//только 1 раз нужно
}
void PrintUndestructBlock(int width, int height){
      lcd.print("O",width,height);
}
void DrawPlayer(int width, int height){// h, w: left_top of object 
    lcd.drawRect(width*3,height*3,width*3+2,height*3+2);
    lcd.drawLine(width*3+1,height*3,width*3+1,height*3+2); // to fill square
    lcd.drawLine(width*3,height*3+1,width*3+2,height*3+1);
    lcd.update();
}
void DrawBullet(int width, int height){// improve
    lcd.setPixel(width*3+1,height*3+1);
    lcd.update();
}
void DrawBlock(int width, int height){
  //
}
void GameField::PrintField()//modify
{
  //system("cls");
  //std::cout << "your score = " << score << std::endl;
  for (int i = 0; i < FIELD_SIZE; i++) {
    
    //std::cout << LCD_HEIGHT - i
      for (int j = 0; j < FIELD_SIZE; j++){
        if (game_field[i][j] == 1)lcd.print("O",i,j); //undestructBlock
        else if (game_field[i][j] == 2)lcd.print("o",i,j); //destructBlock
        else if (game_field[i][j] == 3)lcd.print("p",i,j); //player
        
    }
  }
}



void setup() {
      pinMode(UP_pin, INPUT_PULLUP);
      pinMode(DOWN_pin, INPUT_PULLUP);
      pinMode(RIGHT_pin, INPUT_PULLUP);
      pinMode(LEFT_pin, INPUT_PULLUP);
      pinMode(FIRE_pin, INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  //lcd.begin(LCD_WIDTH,LCD_HEIGHT);
  // Print a message to the LCD.
  lcd.InitLCD();
  lcd.print("p",20,LCD_HEIGHT);
  Serial.begin(115200);
}
int curr_line;
unsigned int prev_time = millis();
unsigned int curr_time;

void loop() {
Player player;
curr_line = 0;
curr_time = 0;
curr_time = millis();
    while (!player.field.isGameOver) {
      player.field.CreateNewLine(curr_line);
      while(curr_time - prev_time < 6000) {
      if (!player.field.isGameOver) { 
        player.field.PrintField();    
        if(digitalRead(UP)==LOW) { player.moveUp(); //синхронизация движений player'а и Changeline() метода
            Serial.println("UP!");
        }
        else if(digitalRead(DOWN)==LOW) {player.moveDown();
            Serial.println("DOWN!");
        }
        else if(digitalRead(RIGHT)==LOW){ player.moveRight();
            Serial.println("RIGHT!");
        }
        else if(digitalRead(LEFT)==LOW){ player.moveLeft();//delay(50);
            Serial.println("LEFT!");
        }
        else if(digitalRead(6)==LOW){
          Serial.println("FIRE!");
          for (int i=1; i<FIELD_SIZE; i++){
            DrawBullet(player.getWidth(),i);
            if(player.shoot_check(player.getWidth(),i)==1)DrawBlock(player.getWidth(),i);    //bullet on block situation
            if(player.shoot_check(player.getWidth(),i)!=0) break;
            
          //button F         
          }
        }
        if (player.field.isGameOver) {
          player.field.getScore();
          player.field.setHiscore(player.field.getScore());
          ///display score;
        }
        delay(50);
      }
    }
    
    //print player
     curr_line++;
     if(curr_line == FIELD_SIZE)curr_line = 0;
  }
  prev_time = millis();
  
  player.field.isGameOver = false;
  delay(10000);
}

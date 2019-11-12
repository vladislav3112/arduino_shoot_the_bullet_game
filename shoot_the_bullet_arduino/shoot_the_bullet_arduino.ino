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
unsigned int prev_time;
unsigned int curr_time;
#define RIGHT_pin 3
#define LEFT_pin 5
#define UP_pin 2
#define DOWN_pin 4
#define FIRE_pin 6

#include <LCD5110_Graph.h>
#include <avr/pgmspace.h>
LCD5110 lcd(9,10,11,13,12); // LCD5110(SCK, MOSI, DC, RST, CS);

// initialize the library with the numbers of the interface pins


void DrawPlayer(int height, int width){// h, w: left_top of object 
    lcd.setPixel(width*3,height*3);       // . .
    lcd.setPixel(width*3+1,height*3+1);   //  .
    lcd.setPixel(width*3+2,height*3+2);   // . .
    lcd.setPixel(width*3+2,height*3);     //-player display
    lcd.setPixel(width*3,height*3+2);
    lcd.update();
}
void DrawBullet(int height, int width){// improve
    lcd.drawRect(width*3,height*3,width*3+2,height*3+2);
    lcd.drawLine(width*3+1,height*3,width*3+1,height*3+2); // to fill square
    lcd.drawLine(width*3,height*3+1,width*3+2,height*3+1);
    lcd.update();
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
    lcd.update();
}
void DrawBlock(int height, int width){
  lcd.drawRect(width*3,height*3,width*3+2,height*3+2);
  lcd.update();
}
void GameField::PrintField()//modify
{
  lcd.clrScr();
  //system("cls");
  //std::cout << "your score = " << score << std::endl;
  Serial.println("draw field");
  for (int i = 0; i < FIELD_SIZE; i++) {
    //std::cout << LCD_HEIGHT - i
      for (int j = 0; j < FIELD_SIZE; j++){
        if (game_field[i][j] == 1)DrawPlayer(i,j); //undestructBlock
        else if (game_field[i][j] == 2)DrawBlock(i,j); //destructBlock
        else if (game_field[i][j] == 3){
          DrawPlayer(i,j); //player
          Serial.print(i);
          Serial.print(" ");
          Serial.print(j);
        }
        
    }
  }
}



void setup() {
  srand(analogRead(A2));
      pinMode(UP_pin, INPUT_PULLUP);
      pinMode(DOWN_pin, INPUT_PULLUP);
      pinMode(RIGHT_pin, INPUT_PULLUP);
      pinMode(LEFT_pin, INPUT_PULLUP);
      pinMode(FIRE_pin, INPUT_PULLUP);
      pinMode(7,OUTPUT);
      digitalWrite(7,LOW);
  // set up the LCD's number of columns and rows:
  //lcd.begin(LCD_WIDTH,LCD_HEIGHT);
  // Print a message to the LCD.
  lcd.InitLCD();
  //DrawPlayer(15,8);
  Serial.begin(115200);
  prev_time=millis();
}
int curr_line;



void loop() {
Player player;
curr_line = 0;

if(curr_line == 0) {
    player.field.CreateNewLine(curr_line);
    player.field.PrintField();
}  while (!player.field.isGameOver) {
      curr_time = millis();
      if(curr_time-prev_time>2000) {//time-millis()
        Serial.print("new line created");
          player.field.CreateNewLine(++curr_line);
          player.field.PrintField();
          prev_time = millis();
      }
        if(digitalRead(UP_pin)==LOW) { 
            ClrBullet(player.getHeight(),player.getWidth());
            player.moveUp(); //синхронизация движений player'а и Changeline() метода
            Serial.println("UP!");
            DrawPlayer(player.getHeight(),player.getWidth());
            
        }
        else if(digitalRead(DOWN_pin)==LOW) {
            ClrBullet(player.getHeight(),player.getWidth());
            player.moveDown();
            Serial.println("DOWN!");
            player.field.PrintField();
        }
        else if(digitalRead(RIGHT_pin)==LOW){ 
            ClrBullet(player.getHeight(),player.getWidth());
            player.moveRight();
            Serial.println("RIGHT!");
            DrawPlayer(player.getHeight(),player.getWidth());
        }
        else if(digitalRead(LEFT_pin)==LOW){ 
            ClrBullet(player.getHeight(),player.getWidth());
            player.moveLeft();//delay(50);
            Serial.println("LEFT!");
            DrawPlayer(player.getHeight(),player.getWidth());
        }
        else if(digitalRead(FIRE_pin)==LOW){
           Serial.println("FIRE!");
            for (int i=1; i<=FIELD_SIZE; i++){
            DrawBullet(FIELD_SIZE-i,player.getWidth());
            if(i>1)ClrBullet(FIELD_SIZE-i+1,player.getWidth());
            if(player.shoot_check(player.getWidth(),i)==1){
              DrawBlock(player.getWidth(),i);
              break;
            }//bullet on block situation
            if(player.shoot_check(player.getWidth(),i)!=0) {
              Serial.println("log_shoot_check_=  ");
              Serial.print(player.shoot_check(player.getWidth(),i));
              Serial.println("coordinates");
              Serial.print(player.getWidth());
              Serial.print(" ");
              Serial.print(i);
              Serial.println("score=  ");
              Serial.println(player.field.getScore());
              Serial.println("log_shoot_check_=");
              break;
            }
          //button F         
          }
        }

      
        if (player.field.isGameOver) {
          player.field.getScore();
          lcd.print("GAME OVER",RIGHT,24);
          player.field.setHiscore(player.field.getScore());
          ///display score;
        }
        delay(50);
      
    
    
    //print player
     if(curr_line == FIELD_SIZE)curr_line = 0;
  }
  
  player.field.isGameOver = false;
  delay(10000);
}

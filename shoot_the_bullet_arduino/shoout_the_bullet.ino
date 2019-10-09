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
const byte FIELD_SIZE = 12;
const byte SCORE_WIDTH = 32;
const byte UP = 2;
const byte RIGHT = 3;
const byte DOWN = 4;
const byte LEFT = 5;

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

void GameField::PrintField()
{
  //system("cls");
  //std::cout << "your score = " << score << std::endl;
  for (int i = 0; i < LCD_HEIGHT; i++) {
    
    //std::cout << LCD_HEIGHT - i;
      for (int j = 0; j < LCD_WIDTH; j++){
        //if (game_field[i][j] != 0)lcd.drawRect(, y1, x2, y2);
        if (game_field[i][j] == 1)lcd.print("O",i,j);//undestructBlock
        else if (game_field[i][j] == 2)lcd.print("o",i,j);//destructBlock
        else if (game_field[i][j] == 3)lcd.print("p",i,j);//player
        
    }
  }
}



void setup() {
      pinMode(UP, INPUT_PULLUP);
      pinMode(DOWN, INPUT_PULLUP);
      pinMode(RIGHT, INPUT_PULLUP);
      pinMode(LEFT, INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  //lcd.begin(LCD_WIDTH,LCD_HEIGHT);
  // Print a message to the LCD.
  
  lcd.print("p",20,LCD_HEIGHT);
  Serial.begin(115200);
}

int curr_line;


void loop() {
  lcd.InitLCD();
  Serial.println("UP");
Player player;
curr_line = 0;

    while (!player.field.isGameOver) {
      player.field.CreateNewLine(curr_line);
      for (int action_idx = 0; action_idx < 20; action_idx++) {
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
        else if(digitalRead(6)==LOW){player.shoot();//button F
          Serial.println("FIRE!");
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
     if(curr_line == LCD_HEIGHT)curr_line = 0;
  }
  player.field.isGameOver = false;
  delay(10000);
}

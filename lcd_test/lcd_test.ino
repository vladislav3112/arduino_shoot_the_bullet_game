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
#define RIGHT_pin 3
#define LEFT_pin 5
#define UP_pin 2
#define DOWN_pin 4
#define FIRE_pin 6
// include the library code:
const byte LCD_WIDTH = 84;
const byte LCD_HEIGHT = 48;
const byte FIELD_SIZE = 15;
const byte SCORE_WIDTH = 32;

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
void DrawBullet(int width, int height, int player_x,int player_y){
    lcd.clrScr();
    lcd.drawRect(width*3,height*3,width*3+2,height*3+2);
    lcd.drawLine(width*3+1,height*3,width*3+1,height*3+2); // to fill square
    lcd.drawLine(width*3,height*3+1,width*3+2,height*3+1);

    lcd.drawRect(player_x*3,player_y*3,player_x*3+2,player_y*3+2);
    lcd.drawLine(player_x*3+1,player_y*3,player_x*3+1,player_y*3+2); // to fill square
    lcd.drawLine(player_x*3,player_y*3+1,player_x*3+2,player_y*3+1);
    lcd.update();
}
void ClrBullet(int width, int height){
    lcd.clrScr();
    lcd.update();
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
  //lcd.print("p",20,LCD_HEIGHT);
  Serial.begin(115200);
}

int w=0;
int h=FIELD_SIZE;


void loop() {
  //DrawBullet(0,0);
  if(digitalRead(UP_pin)==LOW)//onPress
    Serial.println("UP!");
  if(digitalRead(DOWN_pin)==LOW)//onPress
    Serial.println("DOWN!");
  if(digitalRead(RIGHT_pin)==LOW){//onPress
    Serial.println("RIGHT!");
    if(w!=FIELD_SIZE)w+=1;
    DrawBullet(w,h);
  }//onPress
   
  if(digitalRead(LEFT_pin)==LOW){//onPress
    Serial.println("LEFT!");
    if(w!=0)w-=1;
    DrawBullet(w,h);
  }
  if(digitalRead(FIRE_pin)==LOW){//onPress
    Serial.println("FIRE!");
    for(int i=FIELD_SIZE;i>=0;i--){
      DrawBullet(w,i,w,h);
      delay(50);
    }
    }
  delay(200);//perfect delay
  }
 

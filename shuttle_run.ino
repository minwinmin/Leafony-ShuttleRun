/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

/*
 NOTE_C3 , ドL 131
 NOTE_G3 , ソL 196
 NOTE_C4 , ド 262
 NOTE_D4 , レ 294
 NOTE_E4 , ミ 330
 NOTE_F4 , ファ　349
 NOTE_G4 , ソ 392
 NOTE_A4 , ラ 440
 NOTE_B4 , シ 493
 NOTE_C5 , ドH 523
 */

//加速度センサを積んでいるから、腕の動きとかをとって、何かがわかるかも
//シャトルラン、オンライン対戦（謎）

#include "pitches.h"
#include <Wire.h>                   // I2C
#include <ST7032.h>                 // LCD

#define SW1         PC7             // D2  (INT0)
#define I2C_EXPANDER_ADDR   0x1A

ST7032 lcd;

int levelcounter = 0;
int level = 0;
int result = 0;

// notes in the melody
int melody[] = {
  NOTE_C4 , NOTE_D4 , NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C4
};

int reverse_melody[] = {
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4 , NOTE_C4 , NOTE_C3
};

//intervalTime until leval 21
float intervalTime[] = {
  9, 8, 7, 7.58, 7.20, 6.86, 6.55, 6.26, 6.00, 5.76, 5.54, 5.33, 5.14, 4.97, 4.80, 4.65, 4.50, 4.36, 4.24, 4.11, 4.00, 3.89
};
//折り返し回数
int wrapNum[] = {7,8,8,9,9,10,10,11,11,11,12,12,13,13,13,14,14,15,15,16,16};


void i2c_write_byte(int device_address, int reg_address, int write_data){
  Wire.beginTransmission(device_address);
  Wire.write(reg_address);
  Wire.write(write_data);
  Wire.endTransmission();
}


void setup() {
  pinMode(SW1, INPUT);                                //LCD SW1
  Wire.begin();
  //LCD Initialize
  lcd.begin(8, 2);                                    // 8文字, 2行
  lcd.setContrast(30);
  lcd.clear();
  // iterate over the notes of the melody:
  Serial.begin(115200);
}

void loop() {
  // no need to repeat the melody.
    while(level<21){
      lcd.setCursor(0, 0);
      lcd.print("LEVEL:");
      lcd.print(level+1);
      Serial.print("level is :");
      Serial.println(level + 1);
        while(1){
          for(int i = 0; i < 9; i++){
            tone(PB4, melody[i], 1000 / 4);
            delay(intervalTime[level]/9 * 1000 * 1.30);
            
          }
          levelcounter++;
          result ++;

          lcd.setCursor(0, 1);
          lcd.print(result);
          
          if(wrapNum[level] <= levelcounter){
            break;
          }
          for(int i = 0; i < 9; i++){
            tone(PB4, reverse_melody[i], 1000 / 4);
            delay(intervalTime[level]/9 * 1000 * 1.30);
          }
          levelcounter++;
          result ++;

          lcd.setCursor(0, 1);
          lcd.print(result);
          if(wrapNum[level] <= levelcounter){
            break;
          }
        }
    levelcounter = 0;
    level++;
    //noTone(PB4);
  }
  Serial.println("Finish!");
  delay(1000);
}

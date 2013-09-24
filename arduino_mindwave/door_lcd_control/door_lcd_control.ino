 /* Zero Calories Can Dispenser

    Description: This project aims to get a zero-calories-consumed-to-get-a-can can dispenser.
    We all know it's not really zero-calories, brain also consumes energy, but it'll be
    zero-movement and very-low calories consuming dispenser.

    This is achieved by using a MindWave (tm) connected by bluetooth
    to an arduino relay board trough cooking hacks' XBee bluetooth module.
    Copyright 2013 Dlabs Hackerspace <socios@dlabs.co>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int controlonoff = 7;
int controlrele = 6;
int controlmotor = 5;
int senalapertura = 4;

void setup() {

  Serial.begin(9600);

  lcd.begin(16,2);

  pinMode(controlonoff, INPUT);
  pinMode(controlrele, OUTPUT);
  pinMode(controlmotor, OUTPUT);
  pinMode(senalapertura, INPUT);

  digitalWrite(controlrele, LOW);
  digitalWrite(controlmotor, HIGH);

  for(int i = 0; i< 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }

  lcd.backlight();
}


void loop() {

  int start = digitalRead(controlonoff);
  //Serial.println("Sistema desactivado");
  delay(1000);

  lcd.setCursor(0,0);
  lcd.print("Beer Machine");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Dlabs & CH");
  delay(5000);

  while ( start == 1){
    int senal = digitalRead(senalapertura);
    //Serial.println("Sistema activado");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("System activated");
    lcd.setCursor(0,1);
    lcd.print("Open your mind");
    delay(1000);

    if (senal == 1) {
      //Serial.println("Apertura");
      digitalWrite(controlmotor, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Beer request");
      lcd.setCursor(0,1);
      lcd.print("Opening door");
      //Serial.println("Activo 12v");
      delay(5000);
      digitalWrite(controlmotor, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Beer request");
      lcd.setCursor(0,1);
      lcd.print("Waiting Beer");
      //Serial.println("Desactivo 12v");
      delay(5000);
      digitalWrite(controlrele, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Beer request");
      lcd.setCursor(0,1);
      lcd.print("Closing door");
      //Serial.println("Activo rele");
      delay(5000);
      digitalWrite(controlrele, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Beer request");
      lcd.setCursor(0,1);
      lcd.print("Beer.beer..BEER!");
      //Serial.println("Desactivo rele");
      delay(5000);
      senal = 0;
    }
    start = digitalRead(controlonoff);
  }
}




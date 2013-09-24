/*
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

int i;
int m;

int controlonoff = 7;
int controlrele = 6;
int controlmotor = 5;
int senalapertura = 4;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
    pinMode(controlonoff, INPUT);
    pinMode(controlrele, OUTPUT);
    pinMode(controlmotor, OUTPUT);
    pinMode(senalapertura, INPUT);

    digitalWrite(controlrele, LOW);
    digitalWrite(controlmotor, HIGH);

    lcd.begin(16,2);
    lcd.backlight();

    Serial.begin(115200);
    delay(3000) ;
    sendATcommand("AT", "0K", 2000);
    delay(3000) ;
    Serial.println("SET BT AUTH * 0000");
    delay(3000) ;
    sendATcommand("CALL 74:e5:43:be:3e:a2 1101 RFCOMM", "CONNECT", 2000);
    delay(3000) ;
}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){
    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;
    memset(response, '\0', 100);    // Initialize the string
    delay(100);
    while( Serial.available() > 0) Serial.read();    // Clean the input buffer
    Serial.println(ATcommand);    // Send the AT command
    x = 0;
    previous = millis();
    do {
        if(Serial.available() != 0){
            response[x] = Serial.read();
            x++;
            if (strstr(response, expected_answer) != NULL) { answer = 1; }
        }
         // Waits for the asnwer with time out
    } while ((answer == 0) && ((millis() - previous) < timeout));
    return answer;
}

byte ReadOneByte() {
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();
  return ByteRead;
}

int print_lcd(char* line1, char* line2) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line1);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print(line2);
    delay(5000);
    return 0;
}

void do_open() {
    digitalWrite(controlmotor, LOW);
    print_lcd("Beer request", "Opening door");
    digitalWrite(controlmotor, HIGH);
    print_lcd("Beer request", "Waiting beer");
    digitalWrite(controlrele, HIGH);
    print_lcd("Beer request", "Closing door");
    digitalWrite(controlrele, HIGH);
    print_lcd("Beer request", "Beer Beer Beer!");
}

void loop() {
    print_lcd("Beer Machine", "Dlabs & CH");
    // Main switch...
    if (digitalRead(controlonoff) == HIGH) {
        print_lcd("System activated", "Open your mind");
        delay(1000);
        // Comprobación de inicio
        if(ReadOneByte() == 170) { if(ReadOneByte() == 170) {
            // Paquete de 32 b
            if(ReadOneByte() == 32) {
                for(i=0; i<32; i++) {
                    ReadOneByte();
                    // El 29 es lo que buscamos.
                    if(i==28) {
                        if(ReadOneByte() > 80) {
                            do_open();
                        }
                    }
                }
            }
        }}
    }
}

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
#define BAUDRATE 115200
#define powercontrol 10


int i;
int m;

int led = 12;
int ledm = 11;



byte generatedChecksum = 0;
byte checksum = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;
int payloadLength = 0;
long lastReceivedPacket = 0;
boolean bigPacket = false;

void setup() {
    Serial.begin(BAUDRATE);
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


void flash() {
  digitalWrite(led, HIGH);
    delay(5);
  digitalWrite(led, LOW);
}

void loop() {
  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {
      if(ReadOneByte() == 32) {
        for(i=0;i<32;i++) {
          ReadOneByte();
          if(i==28) {
            flash();
            if(ReadOneByte() > 80) {
              digitalWrite(ledm, HIGH);}
            else {
              digitalWrite(ledm, LOW);
              }
            }}}}}}



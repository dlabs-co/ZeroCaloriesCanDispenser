#define BAUDRATE 115200
#define powercontrol 10

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

void loop() {
  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {
      ReadOneByte();
      if (20 == ReadOneByte()) {
          for(int i = 0; i < 13; i++) {
            ReadOneByte();
          }
          concentracion = ReadOneByte();
          Serial.println(concentracion);
        }
      }
    }
}


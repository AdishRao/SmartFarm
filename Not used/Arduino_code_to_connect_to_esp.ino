#include <SoftwareSerial.h>

SoftwareSerial ArduinoSerial (3, 4); //RX,TX






void setup() {
  pinMode(3, INPUT);
    pinMode(4, OUTPUT);

   Serial.begin(9600);  //Start Serial //115200 or 9600
   ArduinoSerial.begin(4800);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

ArduinoSerial.print(1);
Serial.println("Sent\n");
//ArduinoSerial.print("\n");
delay(1000);


}

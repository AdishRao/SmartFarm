#include <dht.h>

dht DHT;

#define DHT11_PIN 7

void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  if(DHT.humidity>=75)
  {
    digitalWrite(9,HIGH);
  }
  else
  digitalWrite(9,LOW);
  delay(2000);
}

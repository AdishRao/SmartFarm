// constants won't change. They're used here to
// set pin numbers:
#include <Servo.h>

//defining Servos
Servo servohori;
int servoh = 103;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 63; 
int servovLimitHigh = 160;
int servovLimitLow = 35;
//Assigning LDRs
int ldrtopl = 2; //top left LDR green
int ldrtopr = 1; //top right LDR yellow
int ldrbotl = 3; // bottom left LDR blue
int ldrbotr = 0; // bottom right LDR orange

 
// variables will change:


 void setup() {
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
    servohori.attach(10);
  servohori.write(103);
  servoverti.attach(9);
  servoverti.write(63);
  delay(50);
  pinMode(3,INPUT);
  pinMode(7,INPUT);
}



void loop() {
  // read the state of the pushbutton value:

 

   if(digitalRead(3) == HIGH) { //NODEMCU HUMIDITY
     if(digitalRead(7) == LOW) // Solar Tracking
  { 
    servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs
  Serial.println("v");
  Serial.println(servov);
    Serial.println("h");
  Serial.println(servoh);
  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(50);
  }
  else if (avgbot < avgtop)
  {
        if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    else
    servoverti.write(servov -1);
    delay(50);
  }
  else 
  {
    servoverti.write(servov);
  }

  Serial.println(avgleft);
  Serial.println(avgright);
  
   if (avgleft < avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(50);
  }
  else if (avgright < avgleft){
     if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
   else
    servohori.write(servoh -1);
    delay(50);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
   }
   else{ //Water harvesting Humidity
    Serial.println("-----------------------------------");
    Serial.println("v");
    Serial.println(servov);
    Serial.println("h");
    Serial.println(servoh);
    servoverti.write(43);
    servohori.write(101);
  }

  }
   
   else{//FLOWER MODE MCU
      Serial.println("-----------------------------------");
    Serial.println("v");
  Serial.println(servov);
    Serial.println("h");  
  Serial.println(servoh);
    servoverti.write(50);
    servohori.write(85);
  }
 }




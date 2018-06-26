#include <LiquidCrystal.h>
char ch;
int Contrast=30;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 20;


//the time when the sensor outputs a low impulse
long unsigned int lowIn;

//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

int pirPin = 7;    //the digital pin connected to the PIR sensor's output
int ledPin = 10;   //led digital pin was 13, now 10

  int solenoidPin = 8;    //This is the output pin on the Arduino we are using
//int espPin = 2;


/////////////////////////////
//SETUP
void setup(){

  // put your setup code here, to run once:
  Serial.begin(9600);
  //pinMode(espPin,INPUT); //esp connection
  pinMode(A0, INPUT);
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
  digitalWrite(solenoidPin, LOW);

  Serial.begin(9600);

  pinMode(pirPin, INPUT);    //motion sensor gives input
  pinMode(ledPin, OUTPUT);   //output to led
  digitalWrite(pirPin, LOW); //pir pin to low initially

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++) //30 seconds calibration time
    {
      Serial.print(".");
      delay(1000);
    }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
    
    pinMode(13,OUTPUT);
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Dryness Level:");
  }

////////////////////////////
//LOOP
void loop(){

  // put your main code here, to run repeatedly:
  int soilValue = analogRead(A0);
  Serial.println(soilValue);


  if(soilValue < 900)
  {
    digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
    Serial.println("Moisture content high, Valve OFF");
     /*if(2 == HIGH)
       {
    digitalWrite(solenoidPin, HIGH);     //Switch Solenoid ON
     Serial.println("On");
       }*/
              digitalWrite(13,LOW);
   delay(1000);
   digitalWrite(13,HIGH);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(soilValue);
  lcd.print("Valve Off");
  }
  else
  {
      digitalWrite(solenoidPin, HIGH);     //Switch Solenoid ON
          Serial.println("Watering going on, Valve ON");
               digitalWrite(13,LOW);
   delay(1000);
   digitalWrite(13,HIGH);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(soilValue);
    lcd.print("Valve On");
  /* if(2 == LOW)
   {
       digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
       Serial.println("Off");
   }*/
  }

     if(digitalRead(pirPin) == HIGH) //if there is a siganl detected by the PIR
     {
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow)
       {
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;
         delay(1);
         }
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }


       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){
           //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;
           delay(1);
           }
       }
  }

  void serialEvent()
{
     if (Serial.available())
  {
    ch= Serial.read();
    if(ch=='A' && Contrast<255)
    {
      Contrast=Contrast+1;
    }
    if(ch=='B' && Contrast>0)
    {
      Contrast=Contrast-1;
    }
        if(ch=='N')
    {
      analogWrite(9,28836);
    }
       if(ch=='F')
    {
      analogWrite(9,0);
    }
    analogWrite(6,Contrast);
    Serial.println("Current contrast");
    Serial.println(Contrast);
  }
}

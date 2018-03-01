#include <SoftwareSerial.h>
int flowPin = 2;    //This is the input pin on the Arduino
double flowRate, total;    //This is the value we intend to calculate. 
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.  
int solenoidPin = 13;

SoftwareSerial ArduinoSerial (3, 4); //RX,TX

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);  //Sets the pin as an output

  pinMode(flowPin, INPUT);           //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);  //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"  
           
  //Serial.begin(9600);  //Start Serial
  //Arduino Serial Code
   pinMode(3, INPUT);
    pinMode(4, OUTPUT);

   Serial.begin(9600);  //Start Serial //115200 or 9600
   ArduinoSerial.begin(4800);



  
  digitalWrite(solenoidPin, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:  
  count = 0;      // Reset the counter so we start counting from 0 again
  interrupts();   //Enables interrupts on the Arduino
  delay (1000);   //Wait 1 second 
  noInterrupts(); //Disable the interrupts on the Arduino
  //digitalWrite(solenoidPin, LOW);
  delay(10000);
  //Start the math
  flowRate = (count * 2.25);        //Take counted pulses in the last second and multiply by 2.25mL 
  flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute
  flowRate = flowRate / 1000;       //Convert mL to Liters, giving you Liters / Minute
  total += flowRate ;
  if(total<20)
   {Serial.println(total);
   digitalWrite(solenoidPin, HIGH); //Switch Solenoid ON


//Arduino Serial Code
  ArduinoSerial.println(total);
Serial.println("Sent\n");
//ArduinoSerial.print("\n");
delay(1000);




  delay(5000);                      //Wait 1 Second
  //digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  //delay(5000);              //Wait 1 Second
   
   }//Print the variable flowRate to Serial
  else
    {Serial.println("Nope");
    ArduinoSerial.println(666);
     digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  delay(5000);
    }
}

void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}


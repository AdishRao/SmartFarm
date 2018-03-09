int flowPin = 3;    //This is the input pin on the Arduino
float flowRate; float total = 0.0;    //This is the value we intend to calculate. 
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.  
int solenoidPin = 13;
int i = 0;
void Flow();
void setup() {
  // put your setup code here, to run once:
   // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);  //Sets the pin as an output
  pinMode(5,INPUT);
  pinMode(flowPin, INPUT);           //Sets the pin as an input
  attachInterrupt(digitalPinToInterrupt(3), Flow, RISING);  //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"  
           
  //Serial.begin(9600);  //Start Serial
  //Arduino Serial Code
  // pinMode(3, INPUT);
  //  pinMode(4, OUTPUT);

   Serial.begin(9600);  //Start Serial //115200 or 9600
   digitalWrite(solenoidPin, HIGH);

}

void loop() 
{
      // put your main code here, to run repeatedly:
      // put your main code here, to run repeatedly:  
      count = 0;      // Reset the counter so we start counting from 0 again
      interrupts();   //Enables interrupts on the Arduino
      delay (1000);   //Wait 1 second 
      noInterrupts(); //Disable the interrupts on the Arduino
      //digitalWrite(solenoidPin, HIGH);
      delay(2000);
      //Start the math
      flowRate = (count * 2.25);        //Take counted pulses in the last second and multiply by 2.25mL 
      flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute
      flowRate = flowRate / 1000;       //Convert mL to Liters, giving you Liters / Minute
      total += flowRate ;
      //Serial.println("TOTAL:");
      Serial.println(total);
      if(digitalRead(5)== HIGH)
      {
          if(total>50){
                Serial.println("Exceeded limit so probably flooding rn");
                digitalWrite(solenoidPin, LOW); //Switch Solenoid OFF coz you exceeded
          }
          else
          {
              digitalWrite(solenoidPin, HIGH);
              Serial.println("Valve on");
          /*flowRate = (count * 2.25);  
          
          //Take counted pulses in the last second and multiply by 2.25mL 
          flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute
          flowRate = flowRate / 1000;       //Convert mL to Liters, giving you Liters / Minute
          total += flowRate;*/
              Serial.println(total);
          
          /*else{
              //digitalWrite(solenoidPin, HIGH);
              //Serial.println(total);
              //Serial.println("Valve on");
              Serial.println("Valve is off");
              digitalWrite(solenoidPin, LOW);
          */}
      }
      else
      {
            Serial.println("Valve is off");
            digitalWrite(solenoidPin, LOW); //Switch Solenoid OFF coz you exceeded
      }
}

/*void OC()
{
        
}*/


void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}

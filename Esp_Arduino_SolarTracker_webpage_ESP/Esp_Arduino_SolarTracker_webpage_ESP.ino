#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SoftwareSerial.h>
//#define EOUT D5 //Using a digital pin for sending the signal to the UNO
const char* ssid = "007";
const char* password = "adish007";

WiFiServer server(80);


void setup() {
  // put your setup code here, to run once:
    pinMode(14, OUTPUT);
    Serial.begin(115200);
    Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started at...");
  Serial.println(WiFi.localIP());

}



void loop() {
  // put your main code here, to run repeatedly:
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while (! client.available())
  {
    delay (1);
  }
  
 
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  // Match the request
  
  if (req.indexOf("/SolarTracker") != -1)  {  //FLOWER IN SUN MODE
    
    digitalWrite(14,HIGH);
    Serial.println("Tracking Sun!");
  }
  else if(req.indexOf("/RainWaterHarvesting") != -1) //water harvesting
  {
   // status_led1=1;
    digitalWrite(14,LOW);
    Serial.println("Harvesting Rain Water!");
  }
  
  
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println(""); 

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<H1> Solar Tracker and Rain Water Harvesting </H1>");
client.println("<br />");
 
 client.println("<a href=\"/SolarTracker\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> Solar Tracking </button> </a>");
 client.println("<a href=\"/RainWaterHarvesting\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> Rain Water Harvesting </button> </a>");
 //client.println("<a href=http://192.168.1.15:5000>  HOME  </a>"); //PI IP ADDRESS
 client.println("<a href=http://192.168.43.186:5000> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 250px; 126px; Z-INDEX: 0; TOP: 200px;'> Back Home </button> </a>");


 
 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

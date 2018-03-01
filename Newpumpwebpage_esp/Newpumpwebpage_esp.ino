#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SoftwareSerial.h>
//#define EOUT D5 //Using a digital pin for sending the signal to the UNO
const char* ssid = "Hariram1";
const char* password = "12a34b56c9";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
    pinMode(D5, OUTPUT);
    Serial.begin(115200);
   // NodeSerial.begin(4800);//Setting the baud rate
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
  
  if (req.indexOf("/pumpoff") != -1)  {
    
    digitalWrite(D5, LOW);
    Serial.println("Pump Off");
  }
  else if(req.indexOf("/pumpon") != -1)
  {
   // status_led1=1;
    digitalWrite(D5,HIGH);
    Serial.println("Pump ON");
  }
  
  
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println(""); 

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<H1> PUMP CONTROL </H1>");
client.println("<br />");
 
 client.println("<a href=\"/pumpon\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> PUMP ON </button> </a>");
 client.println("<a href=\"/pumpoff\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> PUMP OFF </button> </a>");
 client.println("<a href=http://192.168.1.15:5000>  HOME  </a>");

 //client.println("<a href=\"/ledon2\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED 2 ON </button> </a>");
 //client.println("<a href=\"/ledoff2\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED 2 OFF </button> </a>");

 
 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 

}

#include <ESP8266WiFi.h>
#define LED1 D1  // LED at GPIO4 D2 B
#define LED2 D2 //LED ar GPIO4 D3 R
#define LED3 D4 //led at GPIO4 D1  G DO NOT PUT
#define LED21 D0 //SECTOR 2 RED
#define LED22 D3 // SECTOR 2 YELLOW  DO NOT PUT
 
const char* ssid = "NETGEAR43";
const char* password = "manicshrub289";
unsigned char status_led1=0;
unsigned char status_led2=0;
unsigned char status_led3=0;
unsigned char status_led21=0;
unsigned char status_led22=0;



WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, LOW);
  pinMode(LED21, OUTPUT);
  digitalWrite(LED21, LOW);
  pinMode(LED22, OUTPUT);
  digitalWrite(LED22, LOW);
 
  // Connect to WiFi network
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
  
  if (req.indexOf("/led1off") != -1)  {
    status_led1=0;
    digitalWrite(LED1, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/led1on") != -1)
  {
    status_led1=1;
    digitalWrite(LED1,HIGH);
    Serial.println("LED ON");
  }

    if (req.indexOf("/led2off") != -1)  {
    status_led2=0;
    digitalWrite(LED2, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/led2on") != -1)
  {
    status_led2=1;
    digitalWrite(LED2,HIGH);
    Serial.println("LED ON");
  }

 if (req.indexOf("/led3off") != -1)  {
    status_led3=0;
    digitalWrite(LED3, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/led3on") != -1)
  {
    status_led3=1;
    digitalWrite(LED3,HIGH);
    Serial.println("LED ON");
  }

  if (req.indexOf("/led21off") != -1)  {
    status_led21=0;
    digitalWrite(LED21, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/led21on") != -1)
  {
    status_led21=1;
    digitalWrite(LED21,HIGH);
    Serial.println("LED ON");
  }
 if (req.indexOf("/led22off") != -1)  {
    status_led22=0;
    digitalWrite(LED22, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/led22on") != -1)
  {
    status_led22=1;
    digitalWrite(LED22,HIGH);
    Serial.println("LED ON");
  }
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println("");

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<H1> LED CONTROL </H1>");

client.println("<br />");
client.println("<H2> LED CONTROL - Sector 1 </H2>");
 client.println("<br />");
 client.println("<a href=\"/led1on\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Blue ON </button> </a>");
 client.println("<a href=\"/led1off\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Blue OFF </button> </a><br>");
  client.println("<a href=\"/led2on\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Red ON </button> </a>");
 client.println("<a href=\"/led2off\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Red OFF </button> </a><br>");
 //client.println("<a href=\"/led3on\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Green ON </button> </a>");
 //client.println("<a href=\"/led3off\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Green OFF </button> </a><br>");
 client.println("<H1> LED CONTROL - Sector 2 </H1>");
 client.println("<br />");
 client.println("<a href=\"/led21on\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Red ON </button> </a>");
 client.println("<a href=\"/led21off\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Red OFF </button> </a><br>");
 client.println("<a href=\"/led22on\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Yellow ON </button> </a>");
 client.println("<a href=\"/led22off\"\"> <button style='FONT-SIZE: 40px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED Yellow OFF </button> </a><br>");
 
 client.println("<a href=http://192.168.1.3:5000> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 250px; 126px; Z-INDEX: 0; TOP: 200px;'> Back Home </button> </a>");

 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 

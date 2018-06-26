#include <ESP8266WiFi.h>
const char* ssid = "NETGEAR43";
const char* password = "manicshrub289";
WiFiServer server(80);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(D2, OUTPUT);
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

   if (req.indexOf("/On") != -1)  {
    digitalWrite(D2,HIGH);
    Serial.println("Pump On");
  }
    else if(req.indexOf("/Off") != -1)
  {
    digitalWrite(D2,LOW);
    Serial.println("Pump Off");
  }
}

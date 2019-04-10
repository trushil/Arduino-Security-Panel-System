/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Samsung s9"
#define STAPSK  "tpatel401"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

String buzz_status="";
String lock_status="";
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  // prepare LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {

String IncomingString="";
 boolean StringReady = false;
 
 while (Serial.available()){
  delay(1000);
   IncomingString=Serial.readString();
   StringReady= true;
  }

 
 
  if (StringReady){
    //Serial.println("Received String: " + IncomingString);
  if(IncomingString[0]=='0')
 {
  lock_status="OPEN";
 }
 if(IncomingString[0]=='1')
 {
  lock_status="CLOSE";
 }

if(IncomingString[1]=='0')
 {
  buzz_status="ON";
 }
 if(IncomingString[1]=='1')
 {
  buzz_status="OFF";
 }
  }

  
  // Check if a client has connected

  //Serial.write("nothing");
  //delay(2000);
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  //Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  //Serial.println(F("request: "));
  //Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    val = 0;
    
  delay(500);
  Serial.write("open");
  
  } 
  if (req.indexOf(F("/gpio/2")) != -1) {
    val = 0;
    
  delay(500);
  Serial.write("buzz");
  
  }
  else if (req.indexOf(F("/gpio/1")) != -1) {
    val = 1;

  delay(500);
  Serial.write("close");
  
  } else {
    //Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  // Set LED according to the request
  digitalWrite(LED_BUILTIN, val);

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html><center><head><meta http-equiv=\"refresh\" content=\"10; url=http://192.168.43.12\"><style>table, th, td {border: 1px solid black;border-collapse: collapse;}th, td {padding: 5px;}th {text-align: center;}.button {background-color: #4CAF50;justify-content: center;border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}.button3 {background-color: #f44336;}</style></head>\r\n<h1>Door Locking System Portal</h1>\r\nControl the Lock From Here:- <br><br>"));
  
  //client.print((val) ? F("high") : F("low"));
  
//  client.print(F("<br><br>Click <a href='http://"));
//  client.print(WiFi.localIP());
//  client.print(F("/gpio/1'><button class=\"button button3\">Close</button></a> to lock the door, or <a href='http://"));
//  client.print(WiFi.localIP());
//  client.print(F("/gpio/0'><button class=\"button\">Open</button></a> to open the door."));
//
//  client.print(F("<br><br>Click<a href='http://"));
//  client.print(WiFi.localIP());
//  client.print(F("/gpio/2'><button class=\"button button3\">OFF</button></a> to turn OFF the alarm"));

client.print(F("<table style=\"width:100%\"><tr><th>Component</th><th></th><th>status</th></tr>"));
  client.print(F("<tr><td>LOCK</td><td><a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'><button class=\"button\">OPEN</button></a>"));

  client.print(F("<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'><button class=\"button button3\">CLOSE</button></a></td><td>"));

  client.print(lock_status);
  client.print(F("</td></tr>"));

  client.print(F("<tr><td>ALARM</td><td><a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/2'><button class=\"button button3\">OFF</button></a></td><td>"));

  client.print(buzz_status);
  client.print(F("</td></tr>"));
  
  //client.print(IncomingString);
  
  client.print(F("</table></center></html>"));

  
  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  
  //Serial.println(F("Disconnecting from client"));


  
}

/*
    This sketch demonstrates how to set up a simple HTTP-like server.
*/

#include <ESP8266WiFi.h>

/*Assign credentials to connect to the hotspot )*/
#define STASSID "Samsung s9" 
#define STAPSK  "tpatel401"


const char* ssid = STASSID;
const char* password = STAPSK;

/*Declare variables to read the status of system from Arduino Mega*/
String buzz_status="";
String lock_status="";

/*Create an instance of the server and specify the port*/
WiFiServer server(80);

void setup() 
{
	/*Set the baud rate of ESP8266WiFi to 9600*/
	Serial.begin(9600);


	/*Connect to hotspot*/
	Serial.print(F("Connecting to "));
	Serial.println(ssid);

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.print(F("."));
	}
	Serial.println();
	Serial.println(F("WiFi connected"));

	/*Start the server*/
	server.begin();
	Serial.println(F("Server started"));

	/* Print the IP address of the server on serial monitor */
	Serial.println(WiFi.localIP());

}

void loop() 
{

	String IncomingString="";
	boolean StringReady = false;
 
	while (Serial.available())
	{
		delay(20);
		IncomingString=Serial.readString();
		StringReady= true;
	}

 
	/*Set the status of system on webpage according to the received string from Arduino Mega*/
	if (StringReady)
	{
    
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

  
	/*Check for new client*/
	WiFiClient client = server.available();
	if (!client) 
	{
		return;
	}
	Serial.println(F("new client"));
	client.setTimeout(5000); // default is 1000

	/*Read first line of the HTTP request*/
	String req = client.readStringUntil('\r');
	Serial.println(F("request: "));
	Serial.println(req);

	/*Send values to Arduino Mega to change the state of system from webpage*/
	
	if (req.indexOf(F("/gpio/0")) != -1) 
	{
		delay(500);
		Serial.write("open");
	} 
	
	if (req.indexOf(F("/gpio/2")) != -1) 
	{
    
		delay(500);
		Serial.write("buzz");
  
	}
	if (req.indexOf(F("/gpio/1")) != -1) 
	{
		delay(500);
		Serial.write("close");
  
	} 
  
	/*Read request from the client if available*/
	while (client.available()) 
	{
		client.read();
	}

	/*Send the response to the client*/
	client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html><center><head><meta http-equiv=\"refresh\" content=\"5; url=http://192.168.43.12\"><style>table, th, td {border: 1px solid black;border-collapse: collapse;}th, td {padding: 5px;}th {text-align: center;}.button {background-color: #4CAF50;justify-content: center;border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}.button3 {background-color: #f44336;}</style></head>\r\n<h1>Door Locking System Portal</h1>\r\nControl the Lock From Here:- <br><br>"));
  

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
  
	client.print(F("</table></center></html>"));

}

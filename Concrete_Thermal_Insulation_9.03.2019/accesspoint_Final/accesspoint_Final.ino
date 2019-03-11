

#include <ESP8266WiFi.h>
#include "max6675.h"

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);


// First Termocouple
int ktcSO = 12;
int ktcCS = 10;
int ktcCLK = 14;

// Second Termocouple
int ktcCS2 = 5;

// third Termocouple
int ktcCS3 = 2;

//byte ledPin = 2;

float temp = 0.0;
float temp2 = 0.0;
float temp3 = 0.0;

#define LED_BUILTIN 5

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
MAX6675 ktc2(ktcCLK, ktcCS2, ktcSO);
MAX6675 ktc3(ktcCLK, ktcCS3, ktcSO);


void setup() {
  /*pinIO definition*/
  pinMode(LED_BUILTIN, OUTPUT);
  
  /* WIFI CONFIG*/
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Spraypirolisis", "GerardoMedina");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  //pinMode(ledPin, OUTPUT);
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  
  temp = ktc.readCelsius();
  temp2 = ktc2.readCelsius();
  temp3 = ktc3.readCelsius();
  
  WiFiClient client = server.available();
  
  if (!client) {return;}
  //digitalWrite(ledPin, LOW);
 //si recibe un string igual a lo que le diga prende el led que va al pic y prende el motor
 //Serial.println("aqui");
  String request = client.readStringUntil('\r');
  Serial.println("***************S*****************");
  Serial.println("From the station: " + request);
  client.flush();
  Serial.print("Byte sent to the station: ");
  Serial.println(client.println(request + temp + "," + temp2 + "," + temp3 + "\r"));
  //digitalWrite(ledPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(1000);

}

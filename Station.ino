
#include <ESP8266WiFi.h>
//#include "max6675.h"


#define LED_BUILTIN 5

const int reloj=13;
const int interruptPin=4;
int relojstate=0;
float temp = 0.0;

/*/ sensor max67
int ktcSO = 12;
int ktcCS = 10;
int ktcCLK = 14;
*/

int buttonstate=0;
byte ledPin = 2;
char ssid[] = "Spraypirolisis";           // SSID of your AP
char pass[] = "GerardoMedina";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

//MAX6675 ktc(ktcCLK, ktcCS, ktcSO);


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(interruptPin,INPUT_PULLUP);
}


/*
 
String answer = client.readStringUntil('\r');
*/
void loop() {
  //temp = ktc.readCelsius()*1
  client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  //aqui puedo agregar el if switch on envia byte
  //Serial.println("********************************");
  //Serial.print("Byte sent to the AP: ");
  Serial.print(client.print("\r"));
  String answer = client.readStringUntil('\r');
  Serial.println("," + answer);
  //client.flush();
  digitalWrite(ledPin, HIGH);
  client.stop();
  delay(100);
  
}

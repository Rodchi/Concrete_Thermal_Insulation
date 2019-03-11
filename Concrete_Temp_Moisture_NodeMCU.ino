// Sample Arduino MAX6675 Arduino Sketch
/*

This program uses a ESP8266 and the sensor dth11 (the blue one) and 5 type k termo couples to get ambiental temperature and moisture
as well as concrete cylinder temperatures to measure heat isolation properties


*/
#include "max6675.h"
#include "DHT.h"
#include <dht.h>

DHT dht;

/* ALL OF THESE ARE GPIOS*/


// Ambiental Temperature & Moisture
 

// First Termocouple
int ktcSO = 12;
int ktcCS = 10;
int ktcCLK = 14;

// Second Termocouple
int ktcCS2 = 5;
int ktcCS3 = 2;
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
MAX6675 ktc2(ktcCLK, ktcCS2, ktcSO);
MAX6675 ktc3(ktcCLK, ktcCS3, ktcSO);

void setup() {
  Serial.begin(9600);
  Serial.print("Date & Time ,Moisture, Ambiental Temp , T1, T2 ");
  Serial.println();
  // give the MAX a little time to settle
  dht.setup(D3);   /* D3 is used for data communication */
  delay(500);
}

void loop() {
  // basic readout test2
  
   float humidity = dht.getHumidity(); /* Get humidity value */
   float temperature = dht.getTemperature(); /* Get temperature value */

   //Serial.print(",");
   //Serial.print(humidity, 1);
   //Serial.print(",");
   //Serial.print(temperature, 1);
   Serial.print(",");
   Serial.println(ktc.readCelsius()*1);  // Serial.print(",");
   //Serial.print("\t");
   //Serial.print(ktc2.readCelsius()*1); Serial.print(",");
   //Serial.println(ktc3.readCelsius()*1);   
   
   delay(1000);
}

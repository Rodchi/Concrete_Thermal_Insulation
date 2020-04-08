#include "max6675.h"
#include <LiquidCrystal.h>
#include "DHT.h"

//***********Max6675 Configuration**************//

int ktcSO = 10; // Use same for multiple since no multythread or parallel (SYSTEM OUT) 
int ktcCS1 = 9;  //Use anther for multiple (CS stands for Chip Select)
int ktcCLK = 8; //Same Clock For Multiple  (CLOCK)

MAX6675 ktc(ktcCLK, ktcCS1, ktcSO);
//MAX6675 ktc2(ktcCLK, ktcCS2, ktcSO);

//*************End of Max6675 Configuration*****//


//***********LCD 16x2 Configuration**************//

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//*************End of LCD 16x2 Configuration*****//


//=============DTH22 or DTH11 Configuration=======//
#define DHTPIN 11     // Pin donde está conectado el sensor
//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
#define DHTTYPE DHT22   // Sensor DHT22
DHT dht(DHTPIN, DHTTYPE);

long lastDthLectureElapsedTime=0;

;float h,t,f =0;
//=============End of DTH configuration===========//

float getData(){

  if(millis()-lastDthLectureElapsedTime>2000)
  {   
      
      getMax6675Temperature();
      float h = dht.readHumidity(); //Reads the humidity from the dth sensor
      float t = dht.readTemperature(); //Reads the Temperature on Celcius from the dth sensor
      float f = dht.readTemperature(true); //Reads the Temperature on Farenheit from the dth sensor
      //-------Serial and lcd format and sending-------------
      Serial.print("Humedad "); lcd.setCursor(0,1);
      Serial.print(h); lcd.print("%H"); lcd.print(h); 
      Serial.print("% "); lcd.print(" Ta"); lcd.print(t); 
      Serial.print("Temperatura: ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print(f);
      Serial.println(" *F");
      lastDthLectureElapsedTime=millis(); //update last lecture
      
  }
  return h,t,f;
}

float getMax6675Temperature(){
    lcd.setCursor(0,0);
    lcd.print("T1:");
    lcd.print(ktc.readCelsius());
    Serial.print("T1:");
    Serial.println(ktc.readCelsius()*1);
  }

void lcdFormat(){
          lcd.begin(16, 2);
          lcd.setCursor(0,0);
          lcd.print("Max6675 Tcouple");
          lcd.setCursor(0,1);
          lcd.print("& DTH22");
          delay(2000);
          lcd.clear();
          lcd.print("initializing...");
          delay(2000);
          lcd.clear();
          
  }

void setup() {
  Serial.begin(9600);
  Serial.println("Max6675 Thermocouple & DTH22 Sensor");
  Serial.println("initializing...");
  dht.begin();
  lcdFormat();
}

void loop() {
    getData();
}

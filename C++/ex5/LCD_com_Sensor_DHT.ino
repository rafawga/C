#include "DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11

#include <LiquidCrystal.h>
LiquidCrystal lcd(19,23,18,17,16,15);
 

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(11520);
  dht.begin();
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else {
   
   Serial.print("Umidade: ");
   Serial.println(h);
   Serial.print("Temperatura: ");
   Serial.println(t);

   }
delay(100);
}

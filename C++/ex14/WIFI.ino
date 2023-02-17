

#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "https://treinamento-ets-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "CY6cvWUQPO0Dnw2jX6RZ79906ZSdBZVuBNwB1eIw"
#define WIFI_SSID "Vivo-Internet-BF17"
#define WIFI_PASSWORD "78814222"
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseJson json;
int Vresistor = A0;
int Vrdata = 0; 

void setup() {
Serial.begin (9600);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to Wi-Fi");

while (WiFi.status() !=  WL_CONNECTED){
Serial.print(".");
delay(300);
dht.begin();
}

Serial.println();
Serial.print("Connected with IP: ");
Serial.println(WiFi.localIP());
Serial.println();

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);

Firebase.setReadTimeout(firebaseData, 1000*60);
Firebase.setwriteSizeLimit(firebaseData, "tiny");

Serial.println("=========================================================");
Serial.println("Connected...");

dht.begin();
}

void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)){
  
  Serial.println("Failed to read from DHT sensor!");
  return;
} 
else {
  Serial.print("Umidade = ");
  Serial.println(h);
  Serial.print("Temperatura = ");
  Serial.println(t);
  json.set("/temperatura",t);
  json.set("/umidade",h);
  Firebase.updateNode(firebaseData, "/Gabriel",json);
  }
  delay(100);
}

#include<BLEDevice.h> 
#include<BLEServer.h> 
#include<BLEUtils.h> 
#include<BLE2902.h> 
#include "DHT.h"

BLECharacteristic *characteristicTX;
bool deviceConnected = false;

const int LED = 2;

#define SERVICE_UUID "ab8028b1-198e-4351-b779-901fa0e03715" 
#define CHARACTERISTIC_UUID_RX "4aca9682-9736-4e5d-932b-e9b314050495"
#define CHARACTERISTIC_UUID_TX "0972128C-7613-4075-AD52-756F33D4DA95"
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


class ServerCallbacks: public BLEServerCallbacks {
  void onConnect (BLEServer* pServer){
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer){
    deviceConnected = false;
  }
  
};


class CharacteristicCallbacks: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic* characteristic){

    std:: string rxValue = characteristic->getValue();

    if (rxValue.length()>0) {
      Serial.println("*******");
      Serial.print("Received Value: ");

      for (int i = 0; i < rxValue.length(); i++){
      Serial.print(rxValue[i]);
    }


      Serial.println();


      if (rxValue.find("L1") != -1){

       Serial.print("Turning Led on!");
       digitalWrite(LED, HIGH);
      }
      else if (rxValue.find("L0")!= -1){
        Serial.print("Turining LED OFF");
        digitalWrite(LED, LOW);
      }

      Serial.println();
      Serial.println("*********");
        
      }
    
  }
};








void setup() {

    Serial.begin(115200);
    dht.begin();
    pinMode(LED,OUTPUT);
    BLEDevice::init("Gabriel");

    BLEServer*server = BLEDevice::createServer();
    server -> setCallbacks (new ServerCallbacks());
    BLEService*service = server->createService(SERVICE_UUID);

    characteristicTX = service->createCharacteristic(
      CHARACTERISTIC_UUID_TX,
      BLECharacteristic::PROPERTY_NOTIFY
      );

      BLECharacteristic * characteristic = service->createCharacteristic(CHARACTERISTIC_UUID_RX,
      BLECharacteristic::PROPERTY_WRITE
      );

      characteristic ->setCallbacks(new CharacteristicCallbacks());

      service->start();
      server->getAdvertising()->start();

      Serial.println("Waiting a Client connection to notify...");  
}

void loop() {
  if (deviceConnected){
    float t = dht.readTemperature();
    char txString[8];
    dtostrf(t,1,2,txString);

    characteristicTX -> setValue(txString);
    characteristicTX ->notify();

    Serial.print("*** Sent Value: ");
    Serial.print(txString);
    Serial.println(" ***");
    }
delay(1000);
    

}

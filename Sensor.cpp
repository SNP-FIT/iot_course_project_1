#include "DHT.h"
#include "Config.h"

DHT dht(DHT_PIN, DHT11);

void beginSensor() {
  dht.begin();
}

int readHumidity(){
  return (int) dht.readHumidity();
}

int readTemperature(){
  return (int) dht.readTemperature();
}
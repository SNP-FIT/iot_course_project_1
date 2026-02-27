#include <ModbusMaster.h>
#include "Config.h"
ModbusMaster node;


void preTransmission() {
  digitalWrite(MAX485_EN, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_EN, LOW);
}

void beginSensor() {
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(MAX485_EN, OUTPUT);
  digitalWrite(MAX485_EN, 0);

  node.begin(2, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

}

int readHumidity() {
  uint8_t result;
  result = node.readInputRegisters(2, 1);
  Serial.println(result);
  if (result == node.ku8MBSuccess) {
    float humidity = node.getResponseBuffer(0) / 10.0f;
    return humidity;
  } else {
    Serial.println("Error");
    return 0;
  }
}

int readTemperature() {
  uint8_t result;
  result = node.readInputRegisters(1, 1);
  Serial.println(result);
  if (result == node.ku8MBSuccess) {
    float temp = node.getResponseBuffer(0) / 10.0f;
    return temp;
  } else {
    Serial.println("Error");
    return 0;
  }
}
#include "Config.h"
#include <BlynkSimpleEsp32.h>
#include "Sensor.h"

BlynkTimer timer;

BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(RELAY_1_PIN, value);
}


BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(RELAY_2_PIN, value);
}

BLYNK_CONNECTED() {
  Blynk.virtualWrite(V0,0);
  Blynk.virtualWrite(V1,0);
}

void readSensorEvent(){
  int temperature = readTemperature();
  int humidity = readHumidity();
  Serial.println(temperature);
  Serial.println(humidity);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RELAY_1_PIN,OUTPUT);
  pinMode(RELAY_2_PIN,OUTPUT);
  beginSensor();
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  timer.setInterval(60000L, readSensorEvent);
}

void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();
  timer.run();
}

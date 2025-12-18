#include "Config.h"
#include <BlynkSimpleEsp32.h>
#include "Sensor.h"

BlynkTimer timer;

bool lastButton1State = 1;
bool lastButton2State = 1;

unsigned long lastButton1Pressed = 0;
unsigned long lastButton2Pressed = 0;

bool relay1State = 0;
bool relay2State = 0;

BLYNK_WRITE(V0) {
  relay1State = param.asInt();
}


BLYNK_WRITE(V1) {
  relay2State = param.asInt();
}

BLYNK_CONNECTED() {
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
}

void readSensorEvent() {
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
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
  beginSensor();
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  timer.setInterval(60000L, readSensorEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  bool currentButton1State = digitalRead(BUTTON_1_PIN);
  if (currentButton1State == 0 && lastButton1State == 1 && currentTime - lastButton1Pressed > 100) {
    Serial.println("Button1 Pressed");
    relay1State = !relay1State;
    Blynk.virtualWrite(V0, relay1State);
    lastButton1Pressed = currentTime;
  }
  bool currentButton2State = digitalRead(BUTTON_2_PIN);
  if (currentButton2State == 0 && lastButton2State == 1 && currentTime - lastButton2Pressed > 100) {
    Serial.println("Button2 Pressed");
    relay2State = !relay2State;
    Blynk.virtualWrite(V1, relay2State);
    lastButton2Pressed = currentTime;
  }

  lastButton1State = currentButton1State;
  lastButton2State = currentButton2State;

  digitalWrite(RELAY_1_PIN, relay1State);
  digitalWrite(RELAY_2_PIN, relay2State);
  Blynk.run();
  timer.run();
}

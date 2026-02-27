#include <Wire.h>
#include <RtcDS1307.h>
#include "time.h"
#include "Global.h"

RtcDS1307<TwoWire> Rtc(Wire);

void syncTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return;
  }

  Serial.println("Syncing RTC Time");
  RtcDateTime ntpTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  Rtc.SetDateTime(ntpTime);
}

void initRTC() {
  Rtc.Begin();
  configTime(25200, 0, "pool.ntp.org");
  syncTime();
}

void readFromRTC() {
  now = Rtc.GetDateTime();
}
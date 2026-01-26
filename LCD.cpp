#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "Image.h"
#include "Global.h"

Adafruit_ST7789 tft = Adafruit_ST7789(25, 4, 5);


void beginLCD() {
  tft.init(172, 320);
  tft.setRotation(1);
  tft.fillScreen(0x0000);
}

void drawMainScreen() {
  tft.drawRGBBitmap(265, 5, logo_bitmap, 50, 50);
  tft.drawRGBBitmap(10, 70, temperature_bitmap, 40, 40);
  tft.drawRGBBitmap(10, 115, humidity_bitmap, 40, 40);

  tft.setCursor(150, 78);
  tft.setTextSize(3);
  tft.setTextColor(0xFFFF);
  tft.print("R1:");

  tft.setCursor(150, 123);
  tft.setTextSize(3);
  tft.setTextColor(0xFFFF);
  tft.print("R2:");

  tft.setCursor(15, 10);
  tft.setTextSize(2);
  tft.setTextColor(0xFFFF);
  tft.print("20/01/2026");

  tft.setCursor(15, 30);
  tft.setTextSize(3);
  tft.setTextColor(0xFFFF);
  tft.print("22:40:23");
}


void updateSensorUI() {
  tft.setCursor(55, 78);
  tft.setTextSize(3);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.print("    ");
  tft.setCursor(55, 78);
  tft.print(temperature);
  tft.write(0xF7);
  tft.print("C");

  tft.setCursor(55, 123);
  tft.setTextSize(3);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.print("    ");
  tft.setCursor(55, 123);
  tft.print(humidity);
  tft.print("%");
}

void updateRelayUI() {
  if (relay1State == 1) {
    tft.fillRoundRect(210, 70, 80, 40, 10, 0x4ef0);
    tft.setCursor(232, 78);
    tft.setTextColor(0xFFFF);
    tft.print("ON");
  } else {
    tft.fillRoundRect(210, 70, 80, 40, 10, 0x630c);
    tft.setCursor(225, 78);
    tft.setTextColor(0xFFFF);
    tft.print("OFF");
  }

  if (relay2State == 1) {
    tft.fillRoundRect(210, 115, 80, 40, 10, 0x4ef0);
    tft.setCursor(232, 123);
    tft.setTextColor(0xFFFF);
    tft.print("ON");
  } else {
    tft.fillRoundRect(210, 115, 80, 40, 10, 0x630c);
    tft.setCursor(225, 123);
    tft.setTextColor(0xFFFF);
    tft.print("OFF");
  }
}

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "Image.h"

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
/*
 * Project PapaDuck
 * Author: Jamie Gavina
 * Date: 10-29-2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */
// demensions of box 4 long X2.5 tall inch,3 inch wide hole for plug

#include "Particle.h"
#include "Colors.h"
#include "math.h"
#include "neopixel.h"
#include "Adafruit_ssd1306.h"
#include "Adafruit_BME280.h"
#include "Wire.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

const int PIXELCOUNT = 3;
const int OLED_RESET = -1;
const int HEXADDRESS = 0X76;
bool status;
int nDevices;
const int SEALEVELPRESSURE_HPA = 1013.25;
const int DEG = 0XB0;
const int PERCENT = 0X25;
int currentTime = millis();
int lastSecond = 500;

Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_BME280 bme; // I2C

void setup()
{
  Serial.begin(9600);
  waitFor(Serial.isConnected, 1000);
  Wire.begin();
  Serial.printf("Ready to go\n");
  status = bme.begin(HEXADDRESS);
  if (status == false)
  {
    Serial.printf("BME at address %i failed to start\n", HEXADDRESS);
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.display(); // show splashscreen
  if ((currentTime - lastSecond) > 500)
  {
    display.clearDisplay();
  }

  pixel.begin();
  pixel.setBrightness(10);
  pixel.show();
}

void loop()
{
  for (int i = 0; i < PIXELCOUNT; i++)
  {
    if ((currentTime - lastSecond) > 500)
    {
      pixel.setPixelColor(i, yellow);
      pixel.show();
    }
  }
  pixel.clear();
  pixel.show();
}
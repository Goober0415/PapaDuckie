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
#include "Button.h"
#include "wemo.h"
#include "Encoder.h"
#include "hue.h"

SYSTEM_MODE(MANUAL);

const int PIXELCOUNT = 12;
const int OLED_RESET = -1;
const int HEXADDRESS = 0X76;
const int SEALEVELPRESSURE_HPA = 1013.25;
const int DEG = 0XB0;
const int PERCENT = 0X25;
int color = rainbow[0];
const int MYWEMO = 3;
const int THATWEMO = 2;
bool wemowrite;
bool buttonState;
unsigned long lastUpdateTime = 0;
float temp = 0.0;
const int PINA = D4;
const int PINB = D5;
const int HUE4 = 4;
const int HUE3 = 3;
const int HUE2 = 2;
const int HUE1 = 1;
int hue = HueRainbow[color % 7];
bool switchState;

Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_BME280 bme; // I2C
Button pushButton(D3);
Button encoderSwitch(D15);
Encoder encoder(PINA, PINB);

void onOff();
void hueOnOff();

void setup()
{
  Serial.begin(9600);
  waitFor(Serial.isConnected, 1000);
  Wire.begin();
  Serial.println("Ready to go");

  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");

  WiFi.connect();
  while (WiFi.connecting())
  {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

  pixel.begin();
  pixel.setBrightness(10);
  pixel.show();

  bool status = bme.begin(HEXADDRESS);
  if (!status)
  {
    Serial.printf("BME at address %i failed to start\n", HEXADDRESS);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
  unsigned long currentMillis = millis();

  // Update temperature every minute
  if (currentMillis - lastUpdateTime >= 60000)
  {
    lastUpdateTime = currentMillis;
    temp = bme.readTemperature();

    display.clearDisplay();
    display.setCursor(10, 0);
    display.print("Temp: ");
    display.print(temp);
    display.write(DEG);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(12, 28);
    display.println("Papa Duck");
    display.display();
  }

  // Cycle through colors on NeoPixels

  for (int i = 0; i < PIXELCOUNT; i++)
  {
    pixel.setPixelColor(i, color);
    color++;
    pixel.show();
  }
  delay(50); // Adjust speed of color change

  if (pushButton.isClicked())
  {
    buttonState = !buttonState;
  }
  onOff();

  if (encoderSwitch.isClicked())
  {
    switchState = !switchState;
  }
  hueOnOff();
}

void onOff()
{
  if (buttonState == TRUE)
  {
    wemoWrite(MYWEMO, LOW);
    wemoWrite(THATWEMO, LOW);
  }
  else
  {
    wemoWrite(MYWEMO, HIGH);
    wemoWrite(MYWEMO, HIGH);
  }
}

void hueOnOff()
{
  if (switchState == TRUE)
  {
    setHue(HUE1, false, HueRainbow[color % 7], random(32, 255), 160);
    setHue(HUE2, false, HueRainbow[color % 7], random(32, 255), 160);
    setHue(HUE3, false, HueRainbow[color % 7], random(32, 255), 160);
    setHue(HUE4, false, HueRainbow[color % 7], random(32, 255), 160);
  }
  else
  {
    setHue(HUE1, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE2, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE3, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE4, true, HueRainbow[color % 7], random(32, 255), 255);
    hue++;
  }
}
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
#include "DFRobotDFPlayerMini.h"

SYSTEM_MODE(MANUAL);

const int PIXELCOUNT = 12;
const int OLED_RESET = -1;
const int HEXADDRESS = 0X76;
const int SEALEVELPRESSURE_HPA = 1013.25;
const int DEG = 0XB0;
const int PERCENT = 0X25;
int color = rainbow[0];
const int WEMO5 = 5;
const int WEMO4 = 4;
const int WEMO3 = 3;
const int WEMO2 = 2;
const int WEMO1 = 1;
const int WEMO0 = 0;
bool wemowrite;
bool buttonState;
unsigned long lastUpdateTime = 0;
float temp = 0.0;
const int PINA = D4;
const int PINB = D5;
const int HUE6 = 6;
const int HUE5 = 5;
const int HUE4 = 4;
const int HUE3 = 3;
const int HUE2 = 2;
const int HUE1 = 1;
int hue = HueRainbow[color % 7];
bool switchState;
int i, timer;
bool player, status;

Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_BME280 bme; // I2C
Button pushButton(D3);
Button encoderSwitch(D15);
Encoder encoder(PINA, PINB);
DFRobotDFPlayerMini myMp3Player;

void onOff();
void hueOnOff();

void setup()
{
  Serial.begin(9600);
  waitFor(Serial.isConnected, 1000);
  Serial1.begin(9600);
  delay(1000);

  Serial.printf("DFRobot DFPlayer Mini Demo\n");
  Serial.printf("Initializing DFPlayer ... (May take 3~5 seconds)\n");

  if (!myMp3Player.begin(Serial1))
  { // Use softwareSerial to communicate with mp3.
    Serial.printf("Unable to begin:\n");
    Serial.printf("1.Please recheck the connection!\n");
    Serial.printf("2.Please insert the SD card!\n");
    while (true)
      ;
  }

  Serial.printf("DFPlayer Mini online.\n");

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

  Serial.printf("DFRobot DFPlayer Mini Demo \nInitializing DFPlayer ... (May take 3~5 seconds)\n");

  status = myMp3Player.begin(Serial1, false);
  Serial.printf("Status = %i\n", status);

  if (!status)
  {
    Serial.printf("Unable to begin:\n");
    Serial.printf("1.Please recheck the connection!\n");
    Serial.printf("2.Please insert the SD card!\n");
    while (true)
      ;
  }
  Serial.printf("DFPlayer Mini online.\n");

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
    display.setTextSize(1);
    display.setTextColor(WHITE);
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
    wemoWrite(WEMO0, LOW);
    wemoWrite(WEMO1, LOW);
    wemoWrite(WEMO2, LOW);
    wemoWrite(WEMO3, LOW);
    wemoWrite(WEMO4, LOW);
    wemoWrite(WEMO5, LOW);
  }
  else
  {
    wemoWrite(WEMO0, HIGH);
    wemoWrite(WEMO1, HIGH);
    wemoWrite(WEMO2, HIGH);
    wemoWrite(WEMO3, HIGH);
    wemoWrite(WEMO4, HIGH);
    wemoWrite(WEMO5, HIGH);
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
    setHue(HUE5, false, HueRainbow[color % 7], random(32, 255), 160);
    setHue(HUE6, false, HueRainbow[color % 7], random(32, 255), 160);
    myMp3Player.stop();
    myMp3Player.volume(0);
  }
  else
  {
    setHue(HUE1, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE2, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE3, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE4, true, HueRainbow[color % 7], random(32, 255), 255);
    setHue(HUE5, true, HueRainbow[color % 7], random(32, 255), 160);
    setHue(HUE6, true, HueRainbow[color % 7], random(32, 255), 160);
    hue++;
    myMp3Player.loop(1);
    myMp3Player.volume(10);
  }
}
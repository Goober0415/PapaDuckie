/*
 * Project PapaDuckie
 * Author: Jamie Gavina
 * Date: 10-29-2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */
// demensions of box 4 long X2.5 tall inch,3 inch wide hole for plug

#include "Particle.h"
#include "hue.h"
#include "Button.h"
#include "wemo.h"
#include "Encoder.h"
#include "Colors.h"
#include "math.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Wire.h"
#include "Adafruit_BME280.h"
#include "neopixel.h"
#include "DFRobotDFPlayerMini.h"

SYSTEM_MODE(MANUAL); // connecting to wifi

// Global variables
// Button button(D15);
Button encoderButton(D15);
const int PINA = D4;
const int PINB = D5;
Encoder encoder(PINA, PINB);
bool buttonState;

const int PIXELCOUNT = 3;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);

const int HEXADDRESS = 0X76;
Adafruit_SSD1306 bme(HEXADDRESS);
int status;
float temp;
float tempF;
float DEG;
float pressure;
float humidity;

const int OLED_RESET = -1;
Adafruit_SSD1306 display(OLED_RESET);

DFRobotDFPlayerMini duckieGrooves;
// Adafruit_IO_Feed *audio_feed;

const int BULB1 = 1;
const int BULB2 = 2;
const int BULB3 = 3;
const int BULB4 = 4;
const int BULB5 = 5;
const int BULB6 = 6;
int bulbs[] = {BULB1, BULB2, BULB3, BULB4, BULB5, BULB6};
int tempColor;

const int WEMO1 = 1;
const int WEMO2 = 2;
const int WEMO3 = 3;
const int WEMO4 = 4;
const int WEMOS[] = {WEMO1, WEMO2, WEMO3, WEMO4};

bool pausePlay;

unsigned int lastUpdateTime = 0;
unsigned int currentTime = millis();
unsigned int lastSecond = millis();

int lastPosition = 0;
const int currentPosition = encoder.read();
int position;

void setup()
{
    Serial.begin(9600);

    Wire.begin();
    Serial.printf("Ready to go\n");

    // Initialize WiFi
    WiFi.on();
    WiFi.clearCredentials();
    WiFi.setCredentials("IoTNetwork");
    WiFi.connect();
    while (WiFi.connecting())
    {
        Serial.printf(".");
    }
    Serial.printf("\n\n");

    // Initialize BME280 sensor
    bme.begin(0x76);

    Serial.println("BME280 found!");

    // initialize MP3 player
    if (!duckieGrooves.begin(Serial1))
    { // Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while (true)
            ;
    }
    Serial.println(F("DFPlayer Mini online."));

    duckieGrooves.randomAll();
    duckieGrooves.pause();
    pausePlay = 0;
    duckieGrooves.volume(22);

    // Initialize pixels
    pixel.begin();
    pixel.setBrightness(10);
    pixel.show();

    // Update time variables
    lastUpdateTime = millis();
    lastSecond = millis();

    // Initialize display
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(12, 28);
    display.clearDisplay();
    display.printf("PAPA DUCKIE");
    display.display();
    display.clearDisplay();
}

void loop()
{
    if(encoderButton.isClicked()){
        Serial.printf("on/off\n");
        buttonState = !buttonState;
    }
    if (buttonState == TRUE){
        wemoWrite(WEMOS[], LOW);
    }else {
        wemoWrite(WEMOS[], HIGH);
    }
}
/* 
 * Project justFun
 * Author: Jamie Gavina
 * Date: 10/16/2025
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include <neopixel.h>
#include <Colors.h>
#include <Button.h>

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);
const int PIXELCOUNT = 12;
const int BUTTON = D5;
const int LED = D1;

bool onOff = true,state;
int color = 0,i;

Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  pixel.begin();
  pixel.setBrightness(30);
  pinMode(LED,OUTPUT);
}


void loop() {
  state = digitalRead(BUTTON);
 if(state.isClicked()){
  onOff = !onOff;
 }
 if (onOff){
  digitalWrite(LED,HIGH);
 }
 else {
  digitalWrite(LED,LOW);
 }

 for(i = 0; i <= PIXELCOUNT; i++){
  
  pixel.setPixelColor(i,rainbow[color]);
  pixel.show();
  delay(2000);
 }
 pixel.clear();

 color = i%7;
}

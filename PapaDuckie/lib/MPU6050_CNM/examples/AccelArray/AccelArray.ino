/*
 * Project AccelArray
 * Description: New function getAccArray() that returns an array with x, y, and z acceleration
 * Author: Brian Rashap
 * Date: 03-AUG-2022
 */

#include "MPU6050_CNM.h"

MPU6050_CNM myMPU;

const byte MPU_ADDR = 0x68;
const byte FS = 0;

// Declare variables     
float accelX, accelY, accelZ;
float acceleration[3];
unsigned int currentTime, lastTime;
float scalingFactor;

// Uncomment for testing on Serial Monitor and not connected to Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,5000);
  scalingFactor = myMPU.mpuBegin(MPU_ADDR,FS);
}

void loop() {
  currentTime = millis();
  if (currentTime - lastTime > 2500) {
    myMPU.getAccArray(acceleration);
    Serial.printf("Acceleration Data (in G's): x = %0.3f, y = %0.3f, z = %0.3f\n", acceleration[0],acceleration[1],acceleration[2]);
    lastTime = currentTime;
  }
}
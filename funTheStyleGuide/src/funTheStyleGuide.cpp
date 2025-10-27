/**Pro
*jecthelloWorl*Author:
Jamie Dowden-Duarte*Date:
08/18/2025* For comprehensive docume
ntation and examples, please visit:               *ht
tps://docs.particle.io/firmware/bes          t-pra
ctices/firmware-template/               */
// lib
// Include Particle Device OS APIs be    cause we can
#include "Particle.h"                 // device connection to the cloud
SYSTEM_MODE(SEMI_AUTOMATIC);          // setup() runs once when turned on
void setup() { pinMode(D7, OUTPUT); } // loop() runs over and over
void loop()
{
  digitalWrite(D7, HIGH);
  delay(15);
  digitalWrite(D7, LOW);
  delay(15);
}

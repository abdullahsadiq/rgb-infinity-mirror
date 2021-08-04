/*
Upload this to the 3D Magnetic sensor after installing the board in the Arduino IDE
*/

#include <Tle493d_w2b6.h>
const float pi = (22.0 / 7.0);
bool switchPressed;

Tle493d_w2b6 Tle493dMagnetic3DSensor = Tle493d_w2b6();
void setup() {
  Serial.begin(9600);
  Tle493dMagnetic3DSensor.begin();
  Tle493dMagnetic3DSensor.begin();
}

void loop() {
  Tle493dMagnetic3DSensor.updateData();
  delay(100);
  isSwitchPressed();

  float angle = pi + Tle493dMagnetic3DSensor.getAzimuth();
  angle = (angle * 180.0) / pi;

  if (!switchPressed) {
    Serial.println(angle);
  } else if (switchPressed) {
    //Do here whatever you want to do when the switch is pressed
  }
}

void isSwitchPressed() {
  if (Tle493dMagnetic3DSensor.getNorm() < 55) {
    switchPressed = false;
  }
  else if (Tle493dMagnetic3DSensor.getNorm() > 85) {
    switchPressed = true;
  }
}

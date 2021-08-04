/*
Upload this code to the Arduino MKR1000, and connect everything according to the connection diagram (after uploading the code to the XMC2Go)
*/

float deg;
int pinRed = 2;
int pinGreen = 3;
int pinBlue = 4;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
}

void loop() {
  if (Serial1.available() > 0) {
    deg = Serial1.parseFloat();
    setLedColorHSV(deg, 1, 1);
  }
}

void setLedColorHSV(int h, double s, double v) {
  //this is the algorithm to convert from RGB to HSV
  double r = 0;
  double g = 0;
  double b = 0;

  double hf = h / 60.0;

  int i = (int)floor(h / 60.0);
  double f = h / 60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s * f);
  double tv = v * (1 - s * (1 - f));

  switch (i) {
    case 0:
      r = v;
      g = tv;
      b = pv;
      break;
    case 1:
      r = qv;
      g = v;
      b = pv;
      break;
    case 2:
      r = pv;
      g = v;
      b = tv;
      break;
    case 3:
      r = pv;
      g = qv;
      b = v;
      break;
    case 4:
      r = tv;
      g = pv;
      b = v;
      break;
    case 5:
      r = v;
      g = pv;
      b = qv;
      break;
  }

  //set each component to a integer value between 0 and 255
  int red = constrain((int)255 * r, 0, 255);
  int green = constrain((int)255 * g, 0, 255);
  int blue = constrain((int)255 * b, 0, 255);

  Serial.print("Red: ");    Serial.print(red);
  Serial.print(" Green: "); Serial.print(green);
  Serial.print(" Blue: ");   Serial.print(blue);
  Serial.println();

  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}

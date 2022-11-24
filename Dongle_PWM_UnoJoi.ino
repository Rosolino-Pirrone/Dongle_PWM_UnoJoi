
#include "UnoJoy.h"

int channel_1;
int channel_2;
int channel_3;
int channel_4;
int channel_5;
int channel_7;

int ch1;
int ch2;
int ch3;
int ch4;
int ch5;
int ch7;

void setup() {
  setupPins();
  setupUnoJoy();
}

void loop() {
  // Always be getting fresh data
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void) {
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the
  // two serial line pins
  for (int i = 2; i <= 12; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }

}

dataForController_t getControllerData(void) {
  dataForController_t controllerData = getBlankDataForController();

  channel_1 = pulseIn(2, HIGH);
  channel_2 = pulseIn(3, HIGH);
  channel_3 = pulseIn(4, HIGH);
  channel_4 = pulseIn(5, HIGH);
  channel_5 = pulseIn(6, HIGH);
  channel_7 = pulseIn(8, HIGH);

  ch1 = map(constrain(channel_1, 1000, 2000), 1000, 2000, 0, 1023);
  ch2 = map(constrain(channel_2, 1000, 2000), 1000, 2000, 0, 1023);
  ch3 = map(constrain(channel_3, 1000, 2000), 1000, 2000, 0, 1023);
  ch4 = map(constrain(channel_4, 1000, 2000), 1000, 2000, 0, 1023);
  ch5 = map(constrain(channel_5, 1000, 2000), 1000, 2000, 0, 1023);
  ch7 = map(constrain(channel_7, 1000, 2000), 1000, 2000, 0, 1023);

  controllerData.leftStickX = ch1 >> 2;
  controllerData.leftStickY = ch2 >> 2;
  controllerData.rightStickX = ch3 >> 2;
  controllerData.rightStickY = ch4 >> 2;
  if (ch5 > 512) ch5 = 0;
  else ch5 = 1;
  if (ch7 > 512) ch7 = 0;
  else ch7 = 1;
  controllerData.crossOn = ch5;
  controllerData.circleOn = ch7;
  // And return the data!
  return controllerData;
}

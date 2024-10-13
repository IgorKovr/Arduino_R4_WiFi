#include <Secrets.h>
#include "thingProperties.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Used for Timer functinoality
unsigned long previousCO2Millis = 0;  // Stores the last time CO2 was read
const unsigned long co2Interval = 2000;  // Interval at which to read CO2 in milliseconds

void setup() {
  playLEDMatrixLoadingAnimation();
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(2000); 
  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  //  Enable Debuggin of the network, IoT Cloud connection, and errors. 4 is MAX
  setDebugMessageLevel(4);
  ArduinoCloud.printDebugInfo();

  // Wait for the loading animation to finish
  delay(3300);
  matrix.clear();
  led = true;
  isLedOn = true;
}

void loop() {
  ArduinoCloud.update();

  // Check if delay have passed since the last CO2 read
  unsigned long currentMillis = millis();
  if (currentMillis - previousCO2Millis >= co2Interval) {
    previousCO2Millis = currentMillis;  // Update the timestamp for the last CO2 read
    readAndSendCO2Value();
  }

  if (led) {
    printOnLEDMatrix(String(cO2Level, 0));
    isLedOn = true;
  } else {
    matrix.clear();
    isLedOn = false;
  }
}

void readAndSendCO2Value() {
  // TODO: Replace with SCD30 Readings
  cO2Level = analogRead(0);
  Serial.println(cO2Level);
}

// Executed every time a new value is received from IoT Cloud.
// Defined in thingProperties.h
void onLedChange()  {
  Serial.print("Led status changed:");
  Serial.println(led);
}

void playLEDMatrixLoadingAnimation() {
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.begin();
  matrix.play(false); // false == don't repeat animation
}

void printOnLEDMatrix(String displayText) {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(displayText);
  matrix.endText(NO_SCROLL);
  matrix.endDraw();
}
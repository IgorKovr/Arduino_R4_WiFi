#include <Secrets.h>
#include "thingProperties.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Used for Timer functinoality
unsigned long previousCO2Millis = 0;  // Stores the last time CO2 was read
const unsigned long co2Interval = 5000;  // Interval at which to read CO2 (5000 milliseconds = 5 seconds)

void setup() {
  playLEDMatrixLoadingAnimation();
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(2000); 
  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Wait for the loading animation to finish
  delay(4000);
  matrix.clear();
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
    matrix.loadSequence(LEDMATRIX_ANIMATION_LED_BLINK_VERTICAL);
    matrix.play(true);
    isLedOn = true;
  } else {
    matrix.clear();
    isLedOn = false;
  }
}

void readAndSendCO2Value() {
  int randomNumber = random(400, 3000);
  cO2Level = randomNumber;
  Serial.println(randomNumber);
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
  matrix.play(true);
}
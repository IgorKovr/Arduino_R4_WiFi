#include <Secrets.h>
#include "thingProperties.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
  // LED Matrix
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.begin();
  matrix.play(true); // loop == false
  
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

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

  delay(1000);
  matrix.clear();
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  
  readAndSendCO2Value();
  // delay(5000);

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

/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange()  {
  Serial.print("Led status changed:");
  Serial.println(led);
}
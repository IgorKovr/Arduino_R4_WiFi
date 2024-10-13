/*
  This sketch allows live editing of the matrix pixels using WebSerial
  To test, head to https://ledmatrix-editor.arduino.cc

  The LED Matrix editor is part of Arduino Labs (https://labs.arduino.cc/), and is therefore considered experimental software.

  Don't forget to close any serial monitor already opened.

  See the full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix  
*/

#include "Arduino_LED_Matrix.h" // Include the LED_Matrix library
#include "Animation.h"

ArduinoLEDMatrix matrix;        // Create an instance of the ArduinoLEDMatrix class

void setup() {
  matrix.begin();               // Initialize the LED matrix
}

void loop() {
    matrix.loadWrapper(animation, 0);
    matrix.play();
    delay(900);
}

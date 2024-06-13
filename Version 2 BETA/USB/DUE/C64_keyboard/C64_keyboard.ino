/*
MIT License

Copyright (c) 2024 Hartland PC LLC
Written by: Robert VanHazinga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "src/USBHost/KeyboardController.h"
#include "C64Keyboard.h"
C64keyboard ckey;
mt88xx array;

// Initialize USB Controller
USBHost usb;
// Attach keyboard controller to USB
KeyboardController keyboard(usb);

// This function intercepts key press
void keyPressed() {
  uint8_t keyCode = keyboard.getOemKey();
  uint8_t modifier = keyboard.getModifiers();
  bool makeBreak = true;
  ckey.c64key(keyCode,modifier,makeBreak);
}

// This function intercepts key release
void keyReleased() {
  uint8_t keyCode = keyboard.getOemKey();
  uint8_t modifier = keyboard.getModifiers();
  bool makeBreak = false;
  ckey.c64key(keyCode,modifier,makeBreak);
}

void setup() {
  
  // Configure MT88XX control library
  array.setModel(8); // Chip model. MT8808 is default. MT8808 = 8  MT8812 = 12  MT8816 = 16
  array.setErrorLED(13, false); // Error led pin, enable/disable
  uint8_t axPins[3] = {8, 9, 10}; // Define AX pins
  uint8_t ayPins[3] = {5, 6, 7}; // Define AY pins
  array.setControlPins(2, 4, axPins, ayPins, 11, 12); // Data, Strobe, AX pins, AY pins, AX3, Reset
  array.begin();

  
  // Start C64 keyboard
  ckey.begin();
 if (debug) {Serial.begin( 115200 );}
}


void loop() {
  // Process USB tasks
  usb.Task();
  
}




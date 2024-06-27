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

#include <hidboot.h>
#include "CustomHIDBoot.h"
#include "C64Keyboard.h"
#include <Arduino.h>

// Initialize USB Controller
USBHost usb;
HIDBoot<HID_PROTOCOL_KEYBOARD> hidKeyboard(&usb); // Initialize HIDBoot with keyboard protocol
CustomKeyboardReportParser keyboardParser; // Instantiate custom report parser


C64keyboard ckey;
mt88xx array;

void setup() {
  
  // Configure MT88XX control library
  array.setModel(8); // Chip model. MT8808 is default. MT8808 = 8  MT8812 = 12  MT8816 = 16
  array.setErrorLED(13, false); // Error led pin, enable/disable
  uint8_t axPins[3] = {6, 7, 8}; // Define AX pins
  uint8_t ayPins[3] = {3, 4, 5}; // Define AY pins
  array.setControlPins(1, 2, axPins, ayPins, 10, 0); // Data, Strobe, AX pins, AY pins, AX3, Reset
  array.begin();
  hidKeyboard.SetReportParser(0, &keyboardParser);
  
  // Start C64 keyboard
  ckey.begin();
 if (USBHOST_MODIFIER_BUFFER_FIX) {Serial.begin (0);}
 if (debug) {Serial1.begin( 115200 );
  }
}



void loop() {
  // Process USB tasks
  usb.Task();
 
}

void keyPressed() {
    uint8_t keyCode = keyboardParser.getKey();
    uint8_t currentModifier = keyboardParser.getCurrentModifierBuffer();
    uint8_t prevModifier = keyboardParser.getPrevModifierBuffer();
    bool makeBreak = true;
    ckey.c64key(keyCode, prevModifier, currentModifier, makeBreak);
}

void keyReleased() {
    uint8_t keyCode = keyboardParser.getKey();
    uint8_t currentModifier = keyboardParser.getCurrentModifierBuffer();
    uint8_t prevModifier = keyboardParser.getPrevModifierBuffer();
    bool makeBreak = false;
    ckey.c64key(keyCode, prevModifier, currentModifier, makeBreak);
}


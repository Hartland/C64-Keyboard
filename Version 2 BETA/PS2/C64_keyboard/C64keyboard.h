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


#ifndef C64keyboard_h
#define C64keyboard_h


#include "Arduino.h"
#include <mt88xx.h>
#include <PS2KeyAdvanced.h>
#include "keymapping.h"

extern PS2KeyAdvanced keyboard;
extern mt88xx array;



#define debug           false  //Set true for serial monitor of C64 keycodes and PS/2 keycodes

//PS2 communication pins
#define DATA_PIN				12 // Data pin for PS2 keyboard. Default 12
#define IRQ_PIN					3  // Interrupt pin for PS2 keyboard. Default 3
//Scan code value to enable a key map. Default is key map 1.
#define KEY_MAP_1				105 // Default 105 F9
#define KEY_MAP_2				106 // Default 106 F10
//C64 NMI setup
#define NMI_PIN         A0 // Restore key I/O pin. Default Analog pin 0
// Key map value for capslock
#define CAPSLOCK_KEY    3 // Capslock Key. Default 3
// Key map value for array reset
#define MT_RESET        108 // Array reset key. Default 0x6c F12


class C64keyboard {
  public:

    C64keyboard();

    void c64key(uint16_t key);

    static void begin(const C64Keymap_t &map = C64Keymap_main);

};
#endif

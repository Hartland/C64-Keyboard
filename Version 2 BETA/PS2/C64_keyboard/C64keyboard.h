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

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#define C64_KEYMAP_SIZE 	   132 // Size of each array in the key maps
#include <mt88xx.h>
#include <PS2KeyAdvanced.h>
#include "keymapping.h"


extern PS2KeyAdvanced keyboard;
extern mt88xx array;

#define debug   true  //Set true for serial monitor of C64 keycodes and PS/2 keycodes


//Scan code value to enable a key map. Default is key map 1.
#define KEY_MAP_1				0x69 // (DEC 105) F9
#define KEY_MAP_2				0x6A // (DEC 106) F10


//PS2 communication pins
#define DATA_PIN				11 // Data pin for PS2 keyboard
#define IRQ_PIN					3  // Interrupt pin for PS2 keyboard

//Scan code value to enable a key map. Default is key map 1.
#define KEY_MAP_1				0x69 // (DEC 105) F9
#define KEY_MAP_2				0x6A // (DEC 106) F10


//C64 NMI setup
#define NMI_PIN           A0 //Analog pin 0
#define RESTORE_KEY       0x1D // (DEC 29) Tab acts as Restore key

// Key map value for capslock
#define CAPSLOCK_KEY    0x03 // (DEC 3) CapsLock key 

#define MT_RESET 0x6c


class C64keyboard {
  public:

    C64keyboard();

    void c64key(uint16_t key);

    static void begin(const C64Keymap_t &map = C64Keymap_main);

};
#endif

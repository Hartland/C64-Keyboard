/*
  C64keyboard - Commodore Keyboard library

  Copyright (c) 2019 Hartland PC LLC
  Written by Robert VanHazinga



    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/


#ifndef C64keyboard_h
#define C64keyboard_h



#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#define C64_KEYMAP_SIZE 	   136 // Size of each array in the key maps

#include "keymapping.h"




#define debug   false  //Set true for serial monitor of C64 keycodes and PS/2 keycodes



#define MT8808  true    // Set true if using MT8808 and false if using MT8812 ot MT8816


//Key map value to ignore key press
#define IGNORE_KEYCODE			0xAA //(DEC 170) (Must be > 128)

// Key map value to reset the MT88xx chip
#define MT_RESET        0x45 // (DEC 69) F12 activates MT88XX reset

//MT88xx control pins
#define ANALOG_SW_DATA      0 // Sets selected cross switch on/off (Default 0)
#define ANALOG_SW_STROBE    2 // Strobe timing pulse (Default 2)
#define ANALOG_SW_RESET     10 // Reset all MT88XX cross switches to off (Default 10)
#define ANALOG_SW_ARRAY_START 3 // First pin of 6 bit switch addressing. AY2-0 & AX2-0 (Default 3)
#define ANALOG_SW_ARRAY_END   8 // Last pin of 6 bit switch addressing. AY2-0 & AX2-0 (Default 8)
#define ANALOG_SW_AX3    9 // Pin that controls AX3 (MT8812 & MT8816) (Default 9)

//C64 NMI setup
#define NMI_PIN           1 // NMI (RESTORE) KEY PIN (Default 1)
#define RESTORE_KEY       0x2B // (DEC 43) Tab acts as Restore key

// Key map value for capslock
#define CAPSLOCK_KEY    0x39 // (DEC 57) CapsLock key 
#define KEYMAP_KEY      0x47 // (DEC 71) Keymap Selection key (scroll lock)

class C64keyboard {
  public:

    C64keyboard();


    static void begin(const C64Keymap_t &map = C64Keymap_main);

};
#endif

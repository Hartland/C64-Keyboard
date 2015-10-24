/*
 C64keyboard.h - Commodore Keyboard library

  Copyright (c) 2015 Hartland PC LLC
  Written by Robert VanHazinga

 
  Based off PS2 keyboard library:
  Copyright (c) 2007 Free Software Foundation.  All right reserved.
  Written by Christian Weichel <info@32leaves.net>

 

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef C64keyboard_h
#define C64keyboard_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif

#define PS2_KEYMAP_SIZE 	   132 // Size of each array in the key maps

#include "utility/int_pins.h"
#include "keymapping.h"


//MT88xx control pins
#define ANALOG_SW_DATA			13 // Sets selected cross switch on/off
#define ANALOG_SW_STROBE		4 // Strobe timing pulse
#define ANALOG_SW_RESET			2 // Reset all MT88XX cross switches to off
#define ANALOG_SW_ARRAY_START	5 // First pin of 6 bit switch addressing. AY2-0 & AX2-0
#define ANALOG_SW_ARRAY_END		10 // Last pin of 6 bit switch addressing. AY2-0 & AX2-0
#define ANALOG_SW_AX3			11 // Pin that controls AX3 
#define MT_RESET				0x07 //F12 activates MT88XX reset

//PS2 communication pins
#define DATA_PIN				12 // Data pin for PS2 keyboard
#define IRQ_PIN					3  // Interrupt pin for PS2 keyboard

//C64 NMI setup
#define NMI_PIN 				A0 //Analog pin 0
#define RESTORE_KEY				0x0D //Tab acts as Restore key

//Scan code value to enable a key map. Default is key map 1.
#define KEY_MAP_1				0x01 // F9
#define KEY_MAP_2				0x09 // F10
#define KEY_MAP_3				0x78 // F11

//Key map value to ignore key press
#define IGNORE_KEYCODE			0xAA // 170 (Must be > 128)




class C64keyboard {
  public:
 
    C64keyboard();
    
 
    static void begin(const PS2Keymap_t &map = PS2Keymap_main);
    
};

#endif

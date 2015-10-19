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

#include "utility/int_pins.h"

#define PS2_KEYMAP_SIZE 132

typedef struct {
	uint8_t noshift[PS2_KEYMAP_SIZE];
	uint8_t shift[PS2_KEYMAP_SIZE];

} PS2Keymap_t;


extern const PROGMEM PS2Keymap_t PS2Keymap_US;




class C64keyboard {
  public:
 
    C64keyboard();
    
 
    static void begin(uint8_t dataPin, uint8_t irq_pin, const PS2Keymap_t &map = PS2Keymap_US);
    
};

#endif

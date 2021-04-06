

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

#include "C64keyboard.h"


#include <KeyboardController.h>


// Initialize USB Controller
USBHost usb;

// Attach keyboard controller to USB
KeyboardController keyboard(usb);


C64keyboard ckey;
static volatile uint8_t kc,mod, modbuff;
static const C64Keymap_t *keymap = NULL;
static const uint8_t MODKEYS[8] {58,39,63,61,58,25,63,0};
static volatile bool capslock=false,kpress=false, currkeymap=false;

// This function intercepts key press
void keyPressed() {
  kc = keyboard.getOemKey();
  mod = keyboard.getModifiers();
  kpress = true;
  c64key();
}

// This function intercepts key release
void keyReleased() {
  kc = keyboard.getOemKey();
  mod = keyboard.getModifiers();
 kpress = false;
  c64key();
}


void setup() {
  ckey.begin();
  if (debug) {Serial1.begin( 9600 );
  }
   delay(200);
}

void loop() {
  // Process USB tasks
  usb.Task();
}

 

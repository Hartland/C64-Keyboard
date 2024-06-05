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
#include "C64keyboard.h"
#include <mt88xx.h>
#include <PS2KeyAdvanced.h>

bool lshift=false, rshift=false, capslock=false;
int pressedKeys = 0;
static uint8_t  currKeymap = 1, flags ;
static const C64Keymap_t *keymap = NULL;


void debugkey (uint8_t f,uint8_t keyCode,int8_t x,int8_t y,bool mb,bool ik){
    Serial.print("Scan Code: ");
    Serial.print (keyCode);
    Serial.print (" ASCII: ");
    Serial.print ((char)keyCode);
    Serial.print (" Flags: ");
    Serial.print (f,BIN);
    Serial.print (" AX: ");
    Serial.print (x);
    Serial.print (" AY: ");
    Serial.print (y);
    Serial.print(" make: ");
    Serial.print (mb);
    if (ik){Serial.print ("  Ignored Key");}
    Serial.println();
  }


  
void C64keyboard::c64key(uint16_t k) {

   flags = k >> 8;
   uint8_t keyCode= k & 0xFF;
   SwitchAddress coords = {-1,-1,true};
   SwitchAddress tempCoords;
   bool ignoreKey = false;
   bool invalidKey = false;

  if (currKeymap == 2) {
     if (bitRead(flags, 6)) { // If shifted
        coords.ax = pgm_read_byte(&keymap->shift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->shift_1[keyCode].ay);
    } else { // If not shifted
        coords.ax = pgm_read_byte(&keymap->noshift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->noshift_1[keyCode].ay);
    }
  }


   if (currKeymap == 1) {
    if (bitRead(flags, 6)) { // If shifted
        coords.ax = pgm_read_byte(&keymap->shift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->shift_1[keyCode].ay);
    } else { // If not shifted
        coords.ax = pgm_read_byte(&keymap->noshift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->noshift_1[keyCode].ay);
    }
}
// Keymap Handling
    if (keyCode == KEY_MAP_1 && !bitRead(flags,7)){
      currKeymap = 1;
      keyboard.setLock (PS2_LOCK_SCROLL && 0);
      ignoreKey = true;
      }

    if (keyCode == KEY_MAP_2 && !bitRead(flags,7)){
      currKeymap = 2;
      keyboard.setLock (PS2_LOCK_SCROLL && 1);
      ignoreKey = true;
      }

// Process ignored key codes
if (coords.ax == -1 || keyCode > C64_KEYMAP_SIZE){ignoreKey = true;
    invalidKey = true;}

// MT reset function    
    if (keyCode == MT_RESET) {
    array.resetArray(); 
    ignoreKey = true;
    } 

// Restore key function   
    if (keyCode == RESTORE_KEY){
      if (bitRead (flags,7)){pinMode (NMI_PIN,INPUT);
      
      pressedKeys --;

     }
      if (!bitRead (flags,7)) {pinMode (NMI_PIN, OUTPUT);
        digitalWrite (NMI_PIN,LOW);
        pressedKeys ++;
        }
      ignoreKey = true;
      coords.makeBreak = !bitRead(flags,7);
   }
   
// Capslock function 
    if (keyCode == CAPSLOCK_KEY) {
      capslock = !capslock;
      tempCoords = {1,7,capslock};
      array.setSwitch (tempCoords);
      ignoreKey = true; 
      }


        
 // Differential shift conversion during key press
    if (coords.ax >= 10 && !ignoreKey) {
      
        coords.ax -= 10;
        if (rshift || lshift) {
          tempCoords = {6,4,false};
          array.setSwitch(tempCoords);
          tempCoords = {1,7,false};
          array.setSwitch(tempCoords);
        }
      
      else {
        tempCoords = {1,7,true};
        array.setSwitch(tempCoords);
      }

      // Restore shift state to match keystate
       if (bitRead (flags,7)){ 
        tempCoords = {1,7,lshift};
        array.setSwitch(tempCoords);
        tempCoords= {6,4,rshift};
        array.setSwitch(tempCoords);
     }
   }
  // Process shift key flags
     if (bitRead (flags,6 && !ignoreKey)){
      if (coords.ax == 6 & coords.ay == 4) {rshift = flags,7;}
      if (coords.ax == 1 & coords.ay == 7) {lshift = flags,7;}
     }
  // Process normal keypress
    if (!ignoreKey){
        coords.makeBreak = !bitRead(flags,7);
        array.setSwitch(coords);  
       }

      if (!capslock && !invalidKey){
        if (coords.makeBreak){pressedKeys ++;}
        else {pressedKeys --;}
        if (pressedKeys <= 0 || pressedKeys > 4){
          array.resetArray();
          pressedKeys = 0;   
        } 

      }
    // Reset invalid key flag
    invalidKey = false;
    // Debug call
    if (debug) {debugkey(flags,keyCode,coords.ax,coords.ay,coords.makeBreak,ignoreKey); }
}

  

void C64keyboard::begin(const C64Keymap_t &map) {

  keymap = &map;
array.begin();

}
C64keyboard::C64keyboard() {
  // nothing to do here, begin() does it all
}

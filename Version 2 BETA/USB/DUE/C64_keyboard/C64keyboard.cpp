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
#include <stdint.h>

bool lshift=false, rshift=false, capslock=false;
int pressedKeys = 0;
bool keyMap2 = false;
static const C64Keymap_t *keymap = NULL;
uint8_t modifierBuffer = 0;
SwitchAddress modKeys[8] = {{7,2},{1,7},{7,7},{7,5},{7,2},{6,4},{7,7},{7,5}};



void debugkey (uint8_t f,uint8_t keyCode,int8_t x,int8_t y,bool mb){
     Serial.print("Scan Code: ");
     Serial.print (keyCode);
     Serial.print (" modifier: ");
     Serial.print (f,BIN);
     Serial.print (" AX: ");
     Serial.print (x);
     Serial.print (" AY: ");
     Serial.print (y);
     Serial.print(" make: ");
     Serial.print (mb);
     Serial.println();
  }

int8_t bitPos(int8_t indice){
for (int8_t i = 0; i < 8; i++) {
        if (indice & (1 << i)) {
            return i;
        }
    }
}
  
void C64keyboard::c64key(uint8_t keyCode,uint8_t modifier, bool makeBreak) {
   SwitchAddress coords = {99,99,makeBreak};
   SwitchAddress tempCoords;
   bool ignoreKey = false;
   bool manReset = false;

   // Restore key function   
    if (keyCode == RESTORE_KEY){
      if (makeBreak){digitalWrite (NMI_PIN, HIGH);}
      else {digitalWrite (NMI_PIN,LOW);}
      ignoreKey = true;
   }
 
  // MT reset function    
    if (keyCode == MT_RESET) {
      if (makeBreak){
    array.resetArray();
    lshift=false;
    rshift=false;
    pressedKeys = 0;
      } 
    manReset = true;
    ignoreKey = true;
    }


   // Capslock function 
    if (keyCode == CAPSLOCK_KEY && !manReset) {
      if (makeBreak) {
      capslock = !capslock;
      tempCoords = {1,7,capslock};
      array.setSwitch (tempCoords);
      }
      ignoreKey = true;
    }

    if (modifier != modifierBuffer && !ignoreKey) {
          //int changedBit = modifierBuffer ^ modifier;
          int indice = bitPos(modifierBuffer ^ modifier);
          if (!capslock || (capslock && indice != 1)){
          tempCoords.ax = modKeys[indice].ax;
          tempCoords.ay = modKeys[indice].ay;
          tempCoords.makeBreak = makeBreak;
          modifierBuffer = modifier;
          lshift = bitRead(modifier,1);
          rshift = bitRead(modifier,5);
          array.setSwitch (tempCoords);
          } 
          ignoreKey = true;
    }

 

  if (keyMap2) {
     if (lshift || rshift) { // If shifted
        coords.ax = pgm_read_byte(&keymap->shift_2[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->shift_2[keyCode].ay);
    } else { // If not shifted
        coords.ax = pgm_read_byte(&keymap->noshift_2[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->noshift_2[keyCode].ay);
    }
  }


   if (!keyMap2) {
    if (lshift || rshift) { // If shifted
        coords.ax = pgm_read_byte(&keymap->shift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->shift_1[keyCode].ay);
    } else { // If not shifted
        coords.ax = pgm_read_byte(&keymap->noshift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->noshift_1[keyCode].ay);
    }
}

// Keymap Handling
      if (keyCode == KEYMAP_KEY && makeBreak){
      keyMap2 = !keyMap2;
      ignoreKey = true;
      }

 // Process ignored key codes
    if (coords.ax == 99 || keyCode > C64_KEYMAP_SIZE){ignoreKey = true;}     
 // Differential shift conversion during key press
    if (!ignoreKey && coords.ay > 8) {
        coords.ay -= 10;
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
      array.setSwitch(coords);
      // Restore shift state to match keystate
       if (!makeBreak){ 
        tempCoords = {1,7,lshift};
        array.setSwitch(tempCoords);
        tempCoords= {6,4,rshift};
        array.setSwitch(tempCoords);
     }
     ignoreKey = true;
   }
 
  
  // Process normal keypress
    if (!ignoreKey){
        coords.makeBreak = makeBreak;
        array.setSwitch(coords);  
       }

      if (!capslock && !manReset){
        if (coords.makeBreak){pressedKeys ++;}
        else {pressedKeys --;}
        if (pressedKeys <= 0 || pressedKeys > 4){
          array.resetArray();
          pressedKeys = 0;  
        } 
        manReset = false;

      }
    // Debug call
    if (debug) {debugkey(modifier,keyCode,coords.ax,coords.ay,coords.makeBreak); }
}

  

void C64keyboard::begin(const C64Keymap_t &map) {

  keymap = &map;
  pinMode (NMI_PIN,OUTPUT);
  array.begin();

}
C64keyboard::C64keyboard() {
  // nothing to do here, begin() does it all
}

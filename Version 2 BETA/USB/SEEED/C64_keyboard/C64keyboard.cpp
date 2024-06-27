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
//SwitchAddress modKeys[8] = {{7,2},{1,7},{7,7},{7,5},{7,2},{6,4},{7,7},{7,5}};



void debugkey (uint8_t f,uint8_t keyCode,int8_t x,int8_t y,bool mb){
     Serial1.print("Scan Code: ");
     Serial1.print (keyCode);
     Serial1.print (" modifier: ");
     Serial1.print (f,BIN);
     Serial1.print (" AX: ");
     Serial1.print (x);
     Serial1.print (" AY: ");
     Serial1.print (y);
     Serial1.print(" make: ");
     Serial1.print (mb);
     Serial1.print(" Pressed Keys: ");
     Serial1.println (pressedKeys);
  }



// Returns bit position of first high bit
int8_t bitPos(int8_t indice){
for (int8_t i = 0; i < 8; i++) {
        if (indice & (1 << i)) {
            return i;
        }
    }
}


void processMod(uint8_t prevModifier,uint8_t currentModifier) {

    SwitchAddress tempCoords;
    const Coordinates* modKeys = keyMap2 ? modKeyMap2 : modKeyMap1;

    //Determine changed bit in modifier buffer
    int indice = bitPos(prevModifier ^ currentModifier);

    //Capslock is handled in c64Key function. To be ignored here.
    if (!capslock || (capslock && indice != 1)){
    tempCoords.ax = modKeys[indice].ax;
    tempCoords.ay = modKeys[indice].ay;
    tempCoords.makeBreak = bitRead(currentModifier, indice);
    lshift = bitRead(currentModifier,1);
    rshift = bitRead(currentModifier,5);
    array.setSwitch (tempCoords);
    //USBHOST lockup bug fix
    if (USBHOST_MODIFIER_BUFFER_FIX) {Serial.print("");}
  }
}

void C64keyboard::c64key(uint8_t keyCode,uint8_t prevModifier, uint8_t currentModifier, bool makeBreak) {
   SwitchAddress coords = {99,99,makeBreak};
   SwitchAddress tempCoords;
   bool ignoreKey = false;
   bool manReset = false;

 if (keyCode > C64_KEYMAP_SIZE){ignoreKey = true;}


 if (prevModifier != currentModifier && !ignoreKey){
    processMod(prevModifier,currentModifier);
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

// Keymap Handling
      if (keyCode == KEYMAP_KEY){
        if (makeBreak){keyMap2 = !keyMap2;}
      ignoreKey = true;
      }
 

  if (keyMap2 && !ignoreKey) {
     if (lshift || rshift) { // If shifted
        coords.ax = pgm_read_byte(&keymap->shift_2[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->shift_2[keyCode].ay);
    } else { // If not shifted
        coords.ax = pgm_read_byte(&keymap->noshift_2[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->noshift_2[keyCode].ay);
    }
  }


   if (!keyMap2 && !ignoreKey) {
    if (lshift || rshift) { // If shifted
        coords.ax = pgm_read_byte(&keymap->shift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->shift_1[keyCode].ay);
    } else { // If not shifted
        coords.ax = pgm_read_byte(&keymap->noshift_1[keyCode].ax);
        coords.ay = pgm_read_byte(&keymap->noshift_1[keyCode].ay);
    }
}
  // Ignore key flag and invaild AY value process
  if (coords.ax == 99){ignoreKey = true;}
  if (coords.ay == 8 || coords.ay == 9) {ignoreKey = true;}
    

  // Restore key function   
    if (coords.ax == 255){
      if (makeBreak){digitalWrite (NMI_PIN,HIGH);}
      else {digitalWrite (NMI_PIN,LOW);}
      ignoreKey = true;
   }

 // Differential shift conversion during key press
    if (!ignoreKey && coords.ay >= 10) {
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


  // Process pressed key count and manage MT88xx reset. This increases stability.
  // Limits concurrent key presses to a range of 0 - 5
  // If the capslock is active or a manual reset has occurred, this process is skipped.
  // When the last key processed indicates no keys are pressed, the MT88xx is reset.
  
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
    if (debug) {debugkey(currentModifier,keyCode,coords.ax,coords.ay,coords.makeBreak); }
}

  

void C64keyboard::begin(const C64Keymap_t &map) {

  keymap = &map;
  pinMode (NMI_PIN,OUTPUT);
  digitalWrite (NMI_PIN,LOW);
  array.begin();

}
C64keyboard::C64keyboard() {
  // nothing to do here, begin() does it all
}

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



void resetMT88(void) {
  digitalWrite(ANALOG_SW_DATA , LOW);
  digitalWrite(ANALOG_SW_RESET, HIGH);
  digitalWrite( ANALOG_SW_STROBE, HIGH);
  digitalWrite(ANALOG_SW_RESET, LOW);
  digitalWrite( ANALOG_SW_STROBE, LOW);
  digitalWrite(ANALOG_SW_DATA , HIGH);
  capslock = false;
  modbuff =0;
  kpress=false;
  currkeymap = false;
  }

void setswitch(uint8_t c,bool kstate){
  int bitr;
  bool state;
  digitalWrite(ANALOG_SW_DATA , kstate);
  // Fix logic table hole in MT8812/16
  // Convert x12 & x13 to x6 & x7. AX3 line control
  if ( !MT8808 &&( (c > 55 && c < 64) || (c > 23 && c < 32 ))) {
     c -= 24;
    digitalWrite(ANALOG_SW_AX3, HIGH);
  }
    
  if (c < 64) {
    for ( int currentPin = ANALOG_SW_ARRAY_START; currentPin <= ANALOG_SW_ARRAY_END; ++currentPin) {
      bitr = (currentPin - ANALOG_SW_ARRAY_START);
      state =  bitRead(c, bitr);
      digitalWrite(currentPin, state);
    }
    digitalWrite( ANALOG_SW_STROBE, HIGH);
    digitalWrite( ANALOG_SW_STROBE, LOW);
  }
  if (!MT8808){digitalWrite(ANALOG_SW_AX3, LOW);}
  
  // Reset switch state pin to default high state (Key press).
  digitalWrite(ANALOG_SW_DATA , HIGH);

}

void debugkey (uint8_t c){
    Serial1.print ("C64 Keycode: ");
    Serial1.print (c);
    Serial1.print ("  (USB Code: ");
    Serial1.print (kc);
    Serial1.print (" Hex: ");
    Serial1.print (kc, HEX);
    Serial1.print (")");
    Serial1.print ("  Modfier: ");
      for (int i = 7; i >= 0; i--)
    {
        bool b = bitRead(mod, i);
        Serial1.print(b);
    }
    Serial1.print("  Key Press: ");
    Serial1.println (kpress);
}
    
void processmod (){
  for (int i=0;i < 8; i++){
  if (bitRead(modbuff,i) != bitRead(mod,i)){
    int key = MODKEYS[i];
     setswitch(key,kpress);
    }
  }
 modbuff=mod; 
}   

  
void c64key() {
   
   uint8_t c = 0;
 
   if (mod != modbuff) {processmod();
   c = IGNORE_KEYCODE;}

 
    
// MT reset function    
    if (kc == MT_RESET) {
    resetMT88();  
    c=IGNORE_KEYCODE;
   }   
   
// Restore key function   
  if (kc == RESTORE_KEY){
      if (!kpress){pinMode (NMI_PIN,LOW);
     }
      if (kpress) {
        digitalWrite (NMI_PIN,HIGH);
        }
      c = IGNORE_KEYCODE;
   }
   
// Capslock function 
    if (kc == CAPSLOCK_KEY && kpress) {
      capslock = !capslock;
      setswitch(39, capslock);
      c = IGNORE_KEYCODE; 
     
      }

// Keymap Handling
    if (kc == KEYMAP_KEY && kpress){
      currkeymap = !currkeymap;
      c = IGNORE_KEYCODE;
      }

// Key Process      
    if (currkeymap && c != IGNORE_KEYCODE) {
    if ((mod & 0x02) || (mod & 0x20)) {
      c = pgm_read_byte(keymap->shift_2 + kc);
    }
    else {
      c = pgm_read_byte(keymap->noshift_2 + kc);
    }
  }


   if (!currkeymap && c != IGNORE_KEYCODE) {
    if ((mod & 0x02) || (mod & 0x20)) {
      c = pgm_read_byte(keymap->shift_1 + kc);
    }
    else {
      c = pgm_read_byte(keymap->noshift_1 + kc);
    }
   }

    
// Differential shift conversion
    if (c != IGNORE_KEYCODE) {
   
   if (c >= 64 ) {
      c -= 64;
      if ((mod & 0x02) || (mod & 0x20)) {
        setswitch(25,LOW);
        setswitch(39, LOW);   
      }
      
     else {
        setswitch(39,HIGH);
      }
      // Set cross switch key
      setswitch(c,kpress);
    
      // Restore shift state to match keystate
      
      if (!kpress){
      setswitch(39,(mod & 0x02));
      setswitch(25,(mod & 0x20));
      }
     c = IGNORE_KEYCODE;
   }

  }
      

  
        
  // Process normal keypress
  
    if (c != IGNORE_KEYCODE){setswitch(c,kpress);} 
           
  
  //  debug output
    if (debug){debugkey(c);}
}

  

void C64keyboard::begin(const C64Keymap_t &map) {

  keymap = &map;

  // initialize the pins

  for ( int currentPin = ANALOG_SW_ARRAY_START; currentPin <= ANALOG_SW_ARRAY_END; ++currentPin) {
    pinMode( currentPin, OUTPUT);
  }

  if (!MT8808){pinMode( ANALOG_SW_AX3, OUTPUT);}  // ANALOG_SW_AX3 (AX3) is separate as it is used only for conversion of X12/X13 into X6/X7
  pinMode( ANALOG_SW_STROBE, OUTPUT);  // MT88XX strobe
  pinMode( ANALOG_SW_DATA, OUTPUT);   // MT88XX data
  pinMode( ANALOG_SW_RESET, OUTPUT); // MT88XX reset
  pinMode(ANALOG_SW_DATA, OUTPUT);  //MT88XX data
  pinMode(NMI_PIN, OUTPUT); // C64 NMI

  resetMT88();
  

}
C64keyboard::C64keyboard() {
  // nothing to do here, begin() does it all
}

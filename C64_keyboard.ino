
/*
  C64_keyboard - Commodore Keyboard adpator

  Version 0.5
  
  Copyright (c) 2015 Hartland PC LLC
  Written by Robert VanHazinga
 

  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <C64keyboard.h>

const int DataPin = 12;

const int IRQpin =  3;

C64keyboard keyboard;

// Define the pins for the MT8812 analog switch control.
#define ANALOG_SW_DATA         13
#define ANALOG_SW_STROBE       4
#define ANALOG_SW_RESET        2
#define ANALOG_SW_ARRAY_START  5
#define ANALOG_SW_ARRAY_END    10

void setup() {

  // Pin 5 - 7  => AY0 - AY2
  // Pin 8 - 11 => AX0 - AX3
  for ( int currentPin = ANALOG_SW_ARRAY_START; currentPin <= ANALOG_SW_ARRAY_END; ++currentPin) {
    pinMode( currentPin, OUTPUT);
  }
 
  pinMode( 11, OUTPUT);  // Pin 11 (AX3) is seperate as it is used only for conversion of X12/X13 into X6/X7
  pinMode( ANALOG_SW_STROBE, OUTPUT);  // MT88XX strobe
  pinMode( ANALOG_SW_DATA, OUTPUT);   // MT88XX data
  pinMode( ANALOG_SW_RESET, OUTPUT); // MT88XX reset
  pinMode(ANALOG_SW_DATA, OUTPUT);  //MT88XX data

  // Reset the MT88XX to ensure all crosspoints are off
  digitalWrite( ANALOG_SW_STROBE, HIGH);
  digitalWrite( ANALOG_SW_RESET, HIGH);
  digitalWrite( ANALOG_SW_RESET, LOW);
  digitalWrite( ANALOG_SW_STROBE, LOW);

  pinMode(A0,INPUT);
  keyboard.begin(DataPin, IRQpin);
}

void loop() {}






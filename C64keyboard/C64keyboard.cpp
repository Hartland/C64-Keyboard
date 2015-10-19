/*
  C64keyboard.cpp - Commodore Keyboard library

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

#include "C64keyboard.h"

#define BUFFER_SIZE 45
static volatile uint8_t buffer[BUFFER_SIZE];
static volatile uint8_t head, tail,keystate;

static uint8_t DataPin;
static const PS2Keymap_t *keymap=NULL;
#define ANALOG_SW_DATA         13
#define ANALOG_SW_STROBE       4
#define ANALOG_SW_RESET        2
#define ANALOG_SW_ARRAY_START  5
#define ANALOG_SW_ARRAY_END    10
#define RESTORE_KEY            0x0D //Tab acts as Restore key
#define MT_RESET               0x07 //F12 activates MT88XX reset


const PROGMEM PS2Keymap_t PS2Keymap_US = {
  // without shift
   {  170,  170,  170,  3,  5,  1,  170,  170,
	  170,  170,  170,  170,  170, 30,  170,  170,
	  170,  170, 39,  170,  170, 59, 56,  170,
	  170,  170, 33, 37, 34, 36, 62,  170,
	  170, 17, 23, 18, 35, 38, 32,  170,
	  170, 57, 55, 21, 19, 20, 16,  170,
	  170, 15, 49, 53, 50, 52, 22,  170,
	  170,  170,  9, 10, 51, 48, 54,  170,
	  170, 47, 13, 12, 11, 14,  8,  170,
	  170, 41, 31, 42, 26, 44, 46,  170,
	  170,  170,  170,  170,  170, 29,  170,  170,
	  170, 25,  4,  170, 170,   170,  170,  170,
	  170,  170,  170,  170,  170,  170,  0,  170,
	  170, 56,  170, 38, 48,  170,  170,  170,
	  14, 41, 7, 16, 2, 54,  63,  170,
	  170, 40, 170,   170,  170,  170,  170,  170,
	  170,  170,  170,  170},
  // with shift
	{  170,  170,  170,  3,  5,  1,  170,  170,
	  170,  170,  170,  170,  170, 30,  170,  170,
	  170,  170, 39,  170,  170, 59, 56,  170,
	  170,  170, 33, 37, 34, 36, 62,  170,
	  170, 17, 23, 18, 35, 38, 32,  170,
	  170, 57, 55, 21, 19, 20, 16,  170,
	  170, 15, 49, 53, 50, 52, 22,  170,
	  170,  170,  9, 10, 51, 48, 54,  170,
	  170, 47, 13, 12, 11, 14,  8,  170,
	  170, 41, 31, 42, 26, 44, 46,  170,
	  170,  170,  170,  170,  170, 103,  170,  170,
	  170, 25,  4,  170, 170,   170,  170,  170,
	  170,  170,  170,  170,  170,  170,  0,  170,
	  170, 56,  170, 38, 48,  170,  170,  170,
	  14, 41, 7, 16, 2, 54,  63,  170,
	  170, 40, 170,   170,  170,  170,  170,  170,
	  170,  170,  170,  170},
	
};

static inline uint8_t get_scan_code(void)
{
	uint8_t c, i;

	i = tail;
	if (i == head) return 0;
	i++;
	if (i >= BUFFER_SIZE) i = 0;
	c = buffer[i];
	tail = i;
	return c;
}



C64keyboard::C64keyboard() {
  // nothing to do here, begin() does it all
}


void setswitch(uint8_t c){
	int bitr;
	bool state;
	// Fix logic table hole in MT88xx
	// Convert x12 & x13 to x6 & x7. Pin 11 is AX3
	if( (c > 55 && c < 64) || (c > 23 && c < 32 )){
		c -= 24;
		digitalWrite(11,HIGH);
		}
		

	if (c < 64){
		for( int currentPin = ANALOG_SW_ARRAY_START; currentPin <= ANALOG_SW_ARRAY_END; ++currentPin) {
			bitr = (currentPin - ANALOG_SW_ARRAY_START);
			state =  bitRead(c,bitr);
			digitalWrite(currentPin,state);
			}
		digitalWrite( ANALOG_SW_STROBE, HIGH);
		digitalWrite( ANALOG_SW_STROBE, LOW);
		}
	digitalWrite(11,LOW);
	delayMicroseconds(1000);
	
}


void c64key(uint8_t k,byte ks)
{
		byte c = 0;
	
		if(bitRead(ks,1) || bitRead(ks,2)){c = pgm_read_byte(keymap->shift + k);}
			
		else {c = pgm_read_byte(keymap->noshift + k);}
		
		// Keymap code 170 (0xAA) is for ignored keys
		if (c != 170){
			// Differential shift conversion
			// Add 63 to value in key-map if key needs shift not logic
			if (c > 63  && digitalRead(ANALOG_SW_DATA)){
				c -= 63;
				if bitRead(ks,2){
				digitalWrite (ANALOG_SW_DATA,LOW);
				setswitch(25);
				}
				else if bitRead(ks,1){
				digitalWrite (ANALOG_SW_DATA,LOW);
				setswitch(39);
				}
				else {
				digitalWrite (ANALOG_SW_DATA,HIGH);
				setswitch(39);
				}
				// Set cross switch key
				digitalWrite(ANALOG_SW_DATA,HIGH);
				setswitch(c);
				delayMicroseconds(16000);
				// Restore shift state to match keystate
				digitalWrite (ANALOG_SW_DATA,bitRead(ks,1));
				setswitch(39);
				digitalWrite (ANALOG_SW_DATA,bitRead(ks,2));
				setswitch(25);
				}
			
			else if (c > 63){
				c -= 63;
				setswitch(c);}
			else {setswitch(c);}
		}		
	digitalWrite(ANALOG_SW_DATA ,HIGH);

}


// The ISR for the external interrupt
void ps2interrupt(void)
{	
	static uint8_t bitcount=0;
	static uint8_t incoming=0;
	static uint32_t prev_ms=0;
	uint32_t now_ms;
	uint8_t n, val;
	val = digitalRead(DataPin);
	now_ms = millis();
	if (now_ms - prev_ms > 250) {
		bitcount = 0;
		incoming = 0;
	}
	prev_ms = now_ms;
	n = bitcount - 1;
	if (n <= 7) {
		incoming |= (val << n);
	}
	bitcount++;
	if (bitcount == 11) {
		uint8_t i = head + 1;
		if (i >= BUFFER_SIZE) i = 0;
		if (i != tail) {
			buffer[i] = incoming;
			head = i;
		}
	
	uint8_t s = get_scan_code();
		
		// Key released. Set MT data pin low for next keycode.
		if (s == 0xF0){
			digitalWrite(ANALOG_SW_DATA ,0);
			}
		
		// Restore Key. Set A0 to ground by setting output mode
		// Set A0 to float by setting input mode
		else if (s == RESTORE_KEY){
			if (digitalRead(ANALOG_SW_DATA)){pinMode(A0,OUTPUT);}
			else {pinMode(A0,INPUT);}
			}
			
		//Reset MT and keystate with MT_RESET key.
		else if (s == MT_RESET){
			digitalWrite(2,HIGH);
			digitalWrite( ANALOG_SW_STROBE, HIGH);
			digitalWrite(2,LOW);
			digitalWrite( ANALOG_SW_STROBE, LOW);
			keystate = 0;		
		}
		// PS2 Extended key code. Set keystate(bit 0) for next keycode.
		else if (s == 0xE0){
			//bitSet(keystate,0);
		}

		// Match keystate (bit 1) for left shift map to MT data pin. 
		else if (s == 0x12){
			if (digitalRead(ANALOG_SW_DATA) && !bitRead(keystate,1)){
				bitSet(keystate,1);
				c64key(s,keystate);}
			else if (!digitalRead(ANALOG_SW_DATA) && bitRead(keystate,1)){
				bitClear(keystate,1);
				c64key(s,keystate);
			}
		}
		// Match keystate (bit 2) for right shift map to MT data pin. 
		else if (s == 0x59){
			if (digitalRead(ANALOG_SW_DATA) && !bitRead(keystate,2)){
				bitSet(keystate,2);
				c64key(s,keystate);}
			else if (!digitalRead(ANALOG_SW_DATA) && bitRead(keystate,2)){
				bitClear(keystate,2);
				c64key(s,keystate);
			}
		}
		//Caps lock keystate(bit 3 & 4).
		else if (s == 0x58){
				if (bitRead(keystate,4)){
					keystate ^= 1 << 3; // Flip state of bit 3
					digitalWrite(ANALOG_SW_DATA ,bitRead(keystate,3));
					c64key(0x12,keystate);
					bitClear(keystate,4);
					}
				else {bitSet(keystate,4);}	
				}
		
		// Normal keycode
		else if (s < PS2_KEYMAP_SIZE){c64key(s,keystate);}
					
	bitcount = 0;
	incoming = 0;
	}

}
	
	
void C64keyboard::begin(uint8_t data_pin, uint8_t irq_pin, const PS2Keymap_t &map) {
  uint8_t irq_num=255;

  DataPin = data_pin;
  keymap = &map;

  // initialize the pins
#ifdef INPUT_PULLUP
  pinMode(irq_pin, INPUT_PULLUP);
  pinMode(data_pin, INPUT_PULLUP);
#else
  pinMode(irq_pin, INPUT);
  digitalWrite(irq_pin, HIGH);
  pinMode(data_pin, INPUT);
  digitalWrite(data_pin, HIGH);
#endif

#ifdef CORE_INT_EVERY_PIN
  irq_num = irq_pin;

#else
  switch(irq_pin) {
    #ifdef CORE_INT0_PIN
    case CORE_INT0_PIN:
      irq_num = 0;
      break;
    #endif
    #ifdef CORE_INT1_PIN
    case CORE_INT1_PIN:
      irq_num = 1;
      break;
    #endif
    #ifdef CORE_INT2_PIN
    case CORE_INT2_PIN:
      irq_num = 2;
      break;
    #endif
    #ifdef CORE_INT3_PIN
    case CORE_INT3_PIN:
      irq_num = 3;
      break;
    #endif
    #ifdef CORE_INT4_PIN
    case CORE_INT4_PIN:
      irq_num = 4;
      break;
    #endif
    #ifdef CORE_INT5_PIN
    case CORE_INT5_PIN:
      irq_num = 5;
      break;
    #endif
    #ifdef CORE_INT6_PIN
    case CORE_INT6_PIN:
      irq_num = 6;
      break;
    #endif
    #ifdef CORE_INT7_PIN
    case CORE_INT7_PIN:
      irq_num = 7;
      break;
    #endif
    #ifdef CORE_INT8_PIN
    case CORE_INT8_PIN:
      irq_num = 8;
      break;
    #endif
    #ifdef CORE_INT9_PIN
    case CORE_INT9_PIN:
      irq_num = 9;
      break;
    #endif
    #ifdef CORE_INT10_PIN
    case CORE_INT10_PIN:
      irq_num = 10;
      break;
    #endif
    #ifdef CORE_INT11_PIN
    case CORE_INT11_PIN:
      irq_num = 11;
      break;
    #endif
    #ifdef CORE_INT12_PIN
    case CORE_INT12_PIN:
      irq_num = 12;
      break;
    #endif
    #ifdef CORE_INT13_PIN
    case CORE_INT13_PIN:
      irq_num = 13;
      break;
    #endif
    #ifdef CORE_INT14_PIN
    case CORE_INT14_PIN:
      irq_num = 14;
      break;
    #endif
    #ifdef CORE_INT15_PIN
    case CORE_INT15_PIN:
      irq_num = 15;
      break;
    #endif
    #ifdef CORE_INT16_PIN
    case CORE_INT16_PIN:
      irq_num = 16;
      break;
    #endif
    #ifdef CORE_INT17_PIN
    case CORE_INT17_PIN:
      irq_num = 17;
      break;
    #endif
    #ifdef CORE_INT18_PIN
    case CORE_INT18_PIN:
      irq_num = 18;
      break;
    #endif
    #ifdef CORE_INT19_PIN
    case CORE_INT19_PIN:
      irq_num = 19;
      break;
    #endif
    #ifdef CORE_INT20_PIN
    case CORE_INT20_PIN:
      irq_num = 20;
      break;
    #endif
    #ifdef CORE_INT21_PIN
    case CORE_INT21_PIN:
      irq_num = 21;
      break;
    #endif
    #ifdef CORE_INT22_PIN
    case CORE_INT22_PIN:
      irq_num = 22;
      break;
    #endif
    #ifdef CORE_INT23_PIN
    case CORE_INT23_PIN:
      irq_num = 23;
      break;
    #endif
  }
#endif

  head = 0;
  tail = 0;
  if (irq_num < 255) {
    attachInterrupt(irq_num, ps2interrupt, FALLING);
  }
}



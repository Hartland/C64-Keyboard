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

#include <Arduino.h>

struct Coordinates {
    int8_t ax;
    int8_t ay;
};

#define C64_KEYMAP_SIZE 	   133 // Size of each array in the key maps

struct C64Keymap_t {
  Coordinates noshift_1[C64_KEYMAP_SIZE];
  Coordinates shift_1[C64_KEYMAP_SIZE];
  Coordinates noshift_2[C64_KEYMAP_SIZE];
  Coordinates shift_2[C64_KEYMAP_SIZE];
};





/* Maps are positional in relation to keyboard PS2KeyAdvanced codes.

****PS2KEYADVANCED KEY CODES ARE NOT STANDARD PS/2 KEY CODES*****
APLPHANUMERIC CODES ARE ASCII UPPERCASE LETTER AND NUMBER CODES
THE REMAINING KEY CODES ARE SPECIFIC TO PS2KEYADVANCED

Place C64 key coordinate (AX,AY) into the equivalent keyboard PS2KeyAdvanced code position.

Each map has a normal (without shift) and shifted (with shift) array.

In situations where there is a shift difference, add 10 to the AY coordinate. 
This is when a key is shifted on keyboard, but not shifted on the C64 or vise-versa.

Unused PS2KeyAdvanced codes need to have AX coodinate set to 99. AY is ignored but 99 value is suggested.

The Restore key (NMI) is indicated with an AX value of 255

*/

const PROGMEM C64Keymap_t C64Keymap_main = {
  // map 1 without shift
   {
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{1,7},{6,4},// PS2KeyAdvanced Codes 0x00 - 0x07 (DEC 00 - 07)
        {7,2},{7,2},{7,7},{7,7},{7,5},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x08 - 0x0F (DEC 08 - 15)
        {99,99},{6,3},{99,99},{5,0},{6,1},{7,1},{0,2},{6,6},// PS2KeyAdvanced Codes 0x10 - 0x17 (DEC 16 - 23)
        {0,7},{99,99},{0,0},{6,0},{0,0},{255,255},{0,1},{7,4},// PS2KeyAdvanced Codes 0x18 - 0x1F (DEC 24 - 31)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x20 - 0x27 (DEC 32 - 39)
        {99,99},{99,99},{99,99},{0,1}, {5,0}, {5,3}, {6,1},{6,7},// PS2KeyAdvanced Codes 0x28 - 0x2F (DEC 40 - 47)
        {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// PS2KeyAdvanced Codes 0x30 - 0x37 (DEC 48 - 55)
        {3,3},{4,0},{5,5},{5,7},{5,3},{5,4},{6,7},{99,99},// PS2KeyAdvanced Codes 0x38 - 0x3F (DEC 56 - 63)
        {5,6},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// PS2KeyAdvanced Codes 0x40 - 0x47 (DEC 64 - 71)
        {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// PS2KeyAdvanced Codes 0x48 - 0x4F (DEC 72 - 79)
        {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{1,1},// PS2KeyAdvanced Codes 0x50 - 0x57 (DEC 80 - 87)
        {2,7},{3,1},{1,4},{6,2},{6,0},{5,15},{6,12},{6,5},// PS2KeyAdvanced Codes 0x58 - 0x5F (DEC 88 - 95)
        {99,99},{0,4},{0,14},{0,5},{0,15},{0,6},{0,16},{0,3},// PS2KeyAdvanced Codes 0x60 - 0x67 (DEC 96 - 103)
        {0,13},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x68 - 0x6F (DEC 104 - 111)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x70 - 0x77 (DEC 112 - 119)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{0,0},// PS2KeyAdvanced Codes 0x78 - 0x7F (DEC 113 - 127)
        {99,99},{99,99},{99,99},{99,99},{99,99} // PS2KeyAdvanced Codes 0x80 - 0x84 (DEC 128 - 133)
    
    },
  // map 1 with shift
   {
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99}, {1,7}, {6,4},// PS2KeyAdvanced Codes 0x00 - 0x07 (DEC 00 - 07)
      {7,2},{7,2},{7,7},{7,7},{7,5},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x08 - 0x0F (DEC 08 - 15)
      {99,99},{6,3},{99,99},{5,0},{6,1},{99,99},{0,2},{6,6},// PS2KeyAdvanced Codes 0x10 - 0x17 (DEC 16 - 23)
      {0,7},{99,99},{0,0},{6,0},{0,0},{255,255},{0,1},{7,4},// PS2KeyAdvanced Codes 0x18 - 0x1F (DEC 24 - 31)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x20 - 0x27 (DEC 32 - 39)
      {99,99},{99,99},{99,99},{0,1}, {5,0}, {5,3}, {6,1},{6,7},// PS2KeyAdvanced Codes 0x28 - 0x2F (DEC 40 - 47)
      {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// PS2KeyAdvanced Codes 0x30 - 0x37 (DEC 48 - 55)
      {3,3},{4,0},{5,5},{5,7},{5,3},{5,4},{6,7},{99,99},// PS2KeyAdvanced Codes 0x38 - 0x3F (DEC 56 - 63)
      {5,6},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// PS2KeyAdvanced Codes 0x40 - 0x47 (DEC 64 - 71)
      {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// PS2KeyAdvanced Codes 0x48 - 0x4F (DEC 72 - 79)
      {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{1,1},// PS2KeyAdvanced Codes 0x50 - 0x57 (DEC 80 - 87)
      {2,7},{3,1},{1,4},{6,2},{6,0},{5,15},{6,12},{6,5},// PS2KeyAdvanced Codes 0x58 - 0x5F (DEC 88 - 95)
      {99,99},{0,4},{99,99},{0,5},{99,99},{0,6},{99,99},{0,3},// PS2KeyAdvanced Codes 0x60 - 0x67 (DEC 96 - 103)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x68 - 0x6F (DEC 104 - 111)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x70 - 0x77 (DEC 112 - 119)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{0,0},// PS2KeyAdvanced Codes 0x78 - 0x7F (DEC 113 - 127)
      {99,99},{99,99},{99,99},{99,99},{99,99}  // PS2KeyAdvanced Codes 0x80 - 0x84 (DEC 128 - 133)
    
    
    },
  
  
 // map 2 without shift
     {
      
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99}, {1,7},{6,4},// PS2KeyAdvanced Codes 0x00 - 0x07 (DEC 00 - 07)
      {7,7},{99,99},{7,5},{99,99},{7,5},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x08 - 0x0F (DEC 08 - 15)
      {99,99},{6,3},{6,5},{99,99},{99,99},{99,99},{0,2},{6,6},// PS2KeyAdvanced Codes 0x10 - 0x17 (DEC 16 - 23)
      {0,7},{99,99},{0,0},{99,99},{6,0},{7,2},{0,1},{7,4},// PS2KeyAdvanced Codes 0x18 - 0x1F (DEC 24 - 31)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},//PS2KeyAdvanced Codes 0x20 - 0x27 (DEC 32 - 39)
      {99,99},{99,99},{99,99},{99,99},{5,0},{5,3},{6,1},{99,99},// PS2KeyAdvanced Codes 0x28 - 0x2F (DEC 40 - 47)
      {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// PS2KeyAdvanced Codes 0x30 - 0x37 (DEC 48 - 55)
      {3,3},{4,0},{6,2},{5,7},{5,0},{5,4},{6,7},{99,99},// PS2KeyAdvanced Codes 0x38 - 0x3F (DEC 56 - 63)
      {7,1},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// S2KeyAdvanced Codes 0x40 - 0x47 (DEC 64 - 71)
      {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// PS2KeyAdvanced Codes 0x48 - 0x4F (DEC 72 - 79)
      {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{1,1},// PS2KeyAdvanced Codes 0x50 - 0x57 (DEC 80 - 87)
      {2,7},{3,1},{1,4},{5,5},{255,255},{5,6},{6,1},{5,3},// PS2KeyAdvanced Codes 0x58 - 0x5F (DEC 88 - 95)
      {99,99},{0,4},{99,99},{0,5},{99,99},{0,6},{99,99},{0,3},// PPS2KeyAdvanced Codes 0x60 - 0x67 (DEC 96 - 103)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x68 - 0x6F (DEC 104 - 111)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x70 - 0x77 (DEC 112 - 119)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{0,0},// PS2KeyAdvanced Codes 0x78 - 0x7F (DEC 113 - 127)
      {99,99},{99,99},{99,99},{99,99},{99,99}  // PS2KeyAdvanced Codes 0x80 - 0x84 (DEC 128 - 133)
    },
  // map 2 with shift
  {
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99}, {1,7},{6,4},// PS2KeyAdvanced Codes 0x00 - 0x07 (DEC 00 - 07)
      {7,7},{99,99},{7,5},{99,99},{7,5},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x08 - 0x0F (DEC 08 - 15)
      {99,99},{6,3},{6,5},{99,99},{99,99},{99,99},{0,2},{6,6},// PS2KeyAdvanced Codes 0x10 - 0x17 (DEC 16 - 23)
      {0,7},{99,99},{0,0},{99,99},{6,0},{7,2},{0,1},{7,4},// PS2KeyAdvanced Codes 0x18 - 0x1F (DEC 24 - 31)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},//PS2KeyAdvanced Codes 0x20 - 0x27 (DEC 32 - 39)
      {99,99},{99,99},{99,99},{99,99},{5,0},{5,3},{6,1},{99,99},// PS2KeyAdvanced Codes 0x28 - 0x2F (DEC 40 - 47)
      {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// PS2KeyAdvanced Codes 0x30 - 0x37 (DEC 48 - 55)
      {3,3},{4,0},{6,2},{5,7},{5,0},{5,4},{6,7},{99,99},// PS2KeyAdvanced Codes 0x38 - 0x3F (DEC 56 - 63)
      {7,1},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// S2KeyAdvanced Codes 0x40 - 0x47 (DEC 64 - 71)
      {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// PS2KeyAdvanced Codes 0x48 - 0x4F (DEC 72 - 79)
      {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{2,1},// PS2KeyAdvanced Codes 0x50 - 0x57 (DEC 80 - 87)
      {2,7},{3,1},{1,4},{5,5},{255,255},{5,6},{6,1},{5,3},// PS2KeyAdvanced Codes 0x58 - 0x5F (DEC 88 - 95)
      {99,99},{0,4},{99,99},{0,5},{99,99},{0,6},{99,99},{0,3},// PPS2KeyAdvanced Codes 0x60 - 0x67 (DEC 96 - 103)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x68 - 0x6F (DEC 104 - 111)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// PS2KeyAdvanced Codes 0x70 - 0x77 (DEC 112 - 119)
      {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{0,0},// PS2KeyAdvanced Codes 0x78 - 0x7F (DEC 113 - 127)
      {99,99},{99,99},{99,99},{99,99},{99,99}  // PS2KeyAdvanced Codes 0x80 - 0x84 (DEC 128 - 133)
    }
};

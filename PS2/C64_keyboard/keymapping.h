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




/* Maps are positional in relation to keyboard ASCII codes.

Place C64 key coordinate (AX,AY) into the equivalent keyboard ASCII code code position.
For C64 keyboards normally ASCII code set 2.

Each map has a normal (without shift) and shifted (with shift) array.

In situations where there is a shift difference, add 10 to the AX coordinate. 
This is when a key is shifted on keyboard, but not shifted on the C64 or vise-versa.

Unused ASCII codes need to have AX coodinate set to -1. AY is ignored but -1 value is suggested.

*/

#include <Arduino.h>

struct Coordinates {
    int8_t ax;
    int8_t ay;
};


struct C64Keymap_t {
  Coordinates noshift_1[C64_KEYMAP_SIZE];
  Coordinates shift_1[C64_KEYMAP_SIZE];
  Coordinates noshift_2[C64_KEYMAP_SIZE];
  Coordinates shift_2[C64_KEYMAP_SIZE];
};



const PROGMEM C64Keymap_t C64Keymap_main = {
  // map 1 without shift
   {
        {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{1,7},{6,4},// ASCII Codes 0x00 - 0x07 (DEC 00 - 07)
        {7,2},{-1,-1},{7,7},{-1,-1},{7,5},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x08 - 0x0F (DEC 08 - 15)
        {-1,-1},{6,3},{-1,-1},{-1,-1},{-1,-1},{7,1},{0,2},{6,6},// ASCII Codes 0x10 - 0x17 (DEC 16 - 23)
        {0,7},{-1,-1},{0,0},{-1,-1},{7,1},{-1,-1},{0,1},{7,4},// ASCII Codes 0x18 - 0x1F (DEC 24 - 31)
        {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x20 - 0x27 (DEC 32 - 39)
        {-1,-1},{-1,-1},{-1,-1},{-1,-1}, {5,0}, {5,3}, {6,1},{-1,-1},// ASCII Codes 0x28 - 0x2F (DEC 40 - 47)
        {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// ASCII Codes 0x30 - 0x37 (DEC 48 - 55)
        {3,3},{4,0},{5,5},{5,7},{5,3},{5,4},{6,7},{-1,-1},// ASCII Codes 0x38 - 0x3F (DEC 56 - 63)
        {5,6},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// ASCII Codes 0x40 - 0x47 (DEC 64 - 71)
        {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// ASCII Codes 0x48 - 0x4F (DEC 72 - 79)
        {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{1,1},// ASCII Codes 0x50 - 0x57 (DEC 80 - 87)
        {2,7},{3,1},{1,4},{6,2},{6,0},{15,5},{16,2},{6,5},// ASCII Codes 0x58 - 0x5F (DEC 88 - 95)
        {-1,-1},{0,4},{10,4},{0,5},{10,5},{0,6},{10,6},{0,3},// ASCII Codes 0x60 - 0x67 (DEC 96 - 103)
        {10,3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x68 - 0x6F (DEC 104 - 111)
        {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x70 - 0x77 (DEC 112 - 119)
        {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,0},// ASCII Codes 0x78 - 0x7F (DEC 113 - 127)
        {-1,-1},{-1,-1},{-1,-1},{-1,-1} // ASCII Codes 0x80 - 0x83 (DEC 128 - 131)
    
    },
  // map 1 with shift
   {
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}, {1,7}, {6,4},// ASCII Codes 0x00 - 0x07
      {7,2},{-1,-1},{7,7},{-1,-1},{7,5},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x08 - 0x0F
      {-1,-1},{6,3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,2},{6,6},// ASCII Codes 0x{4,2} - 0x{2,4}
      {0,7},{-1,-1},{0,0},{-1,-1},{7,1},{-1,-1},{0,1},{7,4},// ASCII Codes 0x{2,2} - 0x1F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x{2,1} - 0x27
      {-1,-1},{-1,-1},{-1,-1},{-1,-1}, {5,0}, {5,3}, {6,1},{-1,-1},// ASCII Codes 0x28 - 0x2F
      {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// ASCII Codes 0x{6,3} - 0x{1,5}
      {3,3},{4,0},{5,5},{5,7},{5,3},{5,4},{6,7},{-1,-1},// ASCII Codes 0x{1,3} - 0x3F
      {5,6},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// ASCII Codes 0x{5,0} - 0{5,7}
      {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// ASCII Codes 0x{3,0} - 0x4F
      {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{2,1},// ASCII Codes 0x{3,2} - 0x{7.4}
      {2,7},{3,1},{1,4},{6,2},{6,0},{-1,-1},{-1,-1},{6,5},// ASCII Codes 0{7,2} - 0x5F
      {-1,-1},{4,4},{-1,-1},{0,5},{-1,-1},{0,6},{-1,-1},{0,3},// ASCII Codes 0x{7,1} - 0x{{4,2},6}
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x68 - 0x6F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0{{4,2},3} - 0x77
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,0},// ASCII Codes 0x78 - 0x7F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1}  // ASCII Codes 0x80 - 0x83
    
    
    },
  
  
 // map 2 without shift
     {
      
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}, {1,7},{6,4},// ASCII Codes 0x00 - 0x07
      {7,2},{-1,-1},{7,7},{-1,-1},{7,5},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x08 - 0x0F
      {-1,-1}, {6,3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,2},{6,6},// ASCII Codes 0x{4,2} - 0x{2,4}
      {0,7},{-1,-1},{0,0},{-1,-1},{7,1},{-1,-1},{0,4},{7,4},// ASCII Codes 0x{2,2} - 0x1F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x{2,1} - 0x27
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{5,0},{5,3},{6,1},{-1,-1},// ASCII Codes 0x28 - 0x2F
      {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// ASCII Codes 0x{6,3} - 0x{1,5}
      {3,3},{4,0},{5,5},{5,7},{5,3},{5,4},{6,7},{-1,-1},// ASCII Codes 0x{1,3} - 0x3F
      {5,6},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// ASCII Codes 0x{5,0} - 0{5,7}
      {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// ASCII Codes 0x{3,0} - 0x4F
      {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{2,1},// ASCII Codes 0x{3,2} - 0x{7.4}
      {2,7},{3,1},{1,4},{6,2},{6,0},{15,5},{16,2},{6,5},// ASCII Codes 0{7,2} - 0x5F
      {-1,-1},{4,4},{10,4},{0,5},{10,5},{0,6},{10,6},{0,3},// ASCII Codes 0x{7,1} - 0x{{4,2},6}
      {10,3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x68 - 0x6F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0{{4,2},3} - 0x77
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,0},// ASCII Codes 0x78 - 0x7F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1}
    },// ASCII Codes 0x80 - 0x83
  // map 2 with shift
  {
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{1,7},{6,4},// ASCII Codes 0x00 - 0x07
      {7,2},{-1,-1},{7,7},{-1,-1},{7,5},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x08 - 0x0F
      {-1,-1}, {6,3},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,2},{6,6},// ASCII Codes 0x{4,2} - 0x{2,4}
      {0,7},{-1,-1},{0,0},{-1,-1},{7,1},{-1,-1},{0,4},{7.4},// ASCII Codes 0x{2,2} - 0x1F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x{2,1} - 0x27
      {-1,-1},{-1,-1},{-1,-1},{-1,-1}, {5,0}, {5,3}, {6,1},{-1,-1},// ASCII Codes 0x28 - 0x2F
      {4,3},{7,0},{7,3},{1,0},{1,3},{2,0},{2,3},{3,0},// ASCII Codes 0x{6,3} - 0x{1,5}
      {3,3},{4,0},{5,5},{5,7},{5,3},{5,4},{6,7},{-1,-1},// ASCII Codes 0x{1,3} - 0x3F
      {5,6},{1,2},{3,4},{2,4},{2,2},{1,6},{2,5},{3,2},// ASCII Codes 0x{5,0} - 0{5,7}
      {3,5},{4,1},{4,2},{4,5},{5,2},{4,4},{4,7},{4,6},// ASCII Codes 0x{3,0} - 0x4F
      {5,1},{7,6},{2,1},{1,5},{2,6},{3,6},{3,7},{2,1},// ASCII Codes 0x{3,2} - 0x{7.4}
      {2,7},{3,1},{1,4},{6,2},{6,0},{-1,-1},{-1,-1},{6,5},// ASCII Codes 0{7,2} - 0x5F
      {-1,-1},{4,4},{-1,-1},{0,5},{-1,-1},{0,6},{-1,-1},{0,3},// ASCII Codes 0x{7,1} - 0x{{4,2},6}
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0x68 - 0x6F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},// ASCII Codes 0{{4,2},3} - 0x77
      {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,0},// ASCII Codes 0x78 - 0x7F
      {-1,-1},{-1,-1},{-1,-1},{-1,-1}
    }// ASCII Codes 0x80 - 0x83
};

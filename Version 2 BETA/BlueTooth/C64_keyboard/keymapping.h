
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




/* Maps are positional in relation to keyboard Key codes.

Place C64 key coordinate (AX,AY) into the equivalent keyboard Key code code position.


Each map has a normal (without shift) and shifted (with shift) array.

In situations where there is a shift difference, add 10 to the AY coordinate. 
This is when a key is shifted on keyboard, but not shifted on the C64 or vise-versa.

Unused key codes need to have AX coodinate set to 99. AY is ignored but 99 is suggested.

Restore key (NMI) flagged with a 101 value in AX. AY is ignored but 101 is suggested.

modKeyMap 1 & 2 map out the modifier key buffer to coordinates.

Buffer Modifier
 Bit     Key
--------------
0     Left Ctrl
1     Left Shift
2     Left Alt
3     Left Meta (Win)
4     Right Ctrl
5     Right Shift
6     Right Alt
7     Right Meta (Win)

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

const PROGMEM Coordinates modKeyMap1[8] = {
    {7, 2}, {1, 7}, {7, 7}, {7, 5},
    {7, 2}, {6, 4}, {7, 7}, {7, 5}
};

const PROGMEM Coordinates modKeyMap2[8] = {
    {7, 7}, {1, 7}, {7, 5}, {99, 99},
    {99, 99}, {6, 4}, {99, 99}, {99, 99}
};


const PROGMEM C64Keymap_t C64Keymap_main = {
  // map 1 without shift
   {
        {99,99},{99,99},{99,99},{99,99},{1,2},{3,4},{2,4},{2,2},// Key Codes 0x00 - 0x07 (DEC 00 - 07)
        {1,6},{2,5},{3,2},{3,5},{4,1},{4,2},{4,5},{5,2},// Key Codes 0x08 - 0x0F (DEC 08 - 15)
        {4,4},{4,7},{4,6},{5,1},{7,6},{2,1},{1,5},{2,6},// Key Codes 0x10 - 0x17 (DEC 16 - 23)
        {3,6},{3,7},{1,1},{2,7},{3,1},{1,4},{7,0},{7,3},// Key Codes 0x18 - 0x1F (DEC 24 - 31)
        {1,0},{1,3},{2,0},{2,3},{3,0},{3,3},{4,0},{4,3},// Key Codes 0x20 - 0x27 (DEC 32 - 39)
        {0,1},{6,0},{0,0},{101,101},{7,4},{5,3}, {5,0},{5,6},// Key Codes 0x28 - 0x2F (DEC 40 - 47)
        {6,1},{6,5},{99,99},{6,2},{5,5},{6,0},{5,7},{5,4},// Key Codes 0x30 - 0x37 (DEC 48 - 55)
        {6,7},{99,99},{0,4},{0,14},{0,5},{0,15},{0,6},{0,16},// Key Codes 0x38 - 0x3F (DEC 56 - 63)
        {0,3},{0,13},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x40 - 0x47 (DEC 64 - 71)
        {99,99},{0,10},{6,3},{5,0},{0,0},{99,99},{6,1},{0,2},// Key Codes 0x48 - 0x4F (DEC 72 - 79)
        {7,1},{0,7},{6,6},{99,99},{6,7},{6,1},{5,3},{5,0},// Key Codes 0x50 - 0x57 (DEC 80 - 87)
        {0,1},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x58 - 0x5F (DEC 88 - 95)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x60 - 0x67 (DEC 96 - 103)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x68 - 0x6F (DEC 104 - 111)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x70 - 0x77 (DEC 112 - 119)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x78 - 0x7F (DEC 113 - 127)
        {99,99},{99,99},{99,99},{99,99},{99,99}// Key Codes 0x80 - 0x83 (DEC 128 - 132)
    
    },
  // map 1 with shift
   {
        {99,99},{99,99},{99,99},{99,99},{1,2},{3,4},{2,4},{2,2},// Key Codes 0x00 - 0x07 (DEC 00 - 07)
        {1,6},{2,5},{3,2},{3,5},{4,1},{4,2},{4,5},{5,2},// Key Codes 0x08 - 0x0F (DEC 08 - 15)
        {4,4},{4,7},{4,6},{5,1},{7,6},{2,1},{1,5},{2,6},// Key Codes 0x10 - 0x17 (DEC 16 - 23)
        {3,6},{3,7},{1,1},{2,7},{3,1},{1,4},{7,0},{7,3},// Key Codes 0x18 - 0x1F (DEC 24 - 31)
        {1,0},{1,3},{2,0},{2,3},{3,0},{3,3},{4,0},{4,3},// Key Codes 0x20 - 0x27 (DEC 32 - 39)
        {0,1},{6,0},{0,0},{101,101},{7,4},{5,3}, {5,0},{5,6},// Key Codes 0x28 - 0x2F (DEC 40 - 47)
        {6,1},{6,5},{99,99},{6,2},{5,5},{6,0},{5,7},{5,4},// Key Codes 0x30 - 0x37 (DEC 48 - 55)
        {6,7},{99,99},{0,4},{0,14},{0,5},{0,15},{0,6},{0,16},// Key Codes 0x38 - 0x3F (DEC 56 - 63)
        {0,3},{0,13},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x40 - 0x47 (DEC 64 - 71)
        {99,99},{0,10},{6,3},{5,0},{0,0},{99,99},{6,1},{0,2},// Key Codes 0x48 - 0x4F (DEC 72 - 79)
        {7,1},{0,7},{6,6},{99,99},{6,7},{6,1},{5,3},{5,0},// Key Codes 0x50 - 0x57 (DEC 80 - 87)
        {0,1},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x58 - 0x5F (DEC 88 - 95)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x60 - 0x67 (DEC 96 - 103)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x68 - 0x6F (DEC 104 - 111)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x70 - 0x77 (DEC 112 - 119)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x78 - 0x7F (DEC 113 - 127)
        {99,99},{99,99},{99,99},{99,99},{99,99}// Key Codes 0x80 - 0x83 (DEC 128 - 132)
    
    
    },
  
  
 // map 2 without shift
     {
      
        {99,99},{99,99},{99,99},{99,99},{1,2},{3,4},{2,4},{2,2},// Key Codes 0x00 - 0x07 (DEC 00 - 07)
        {1,6},{2,5},{3,2},{3,5},{4,1},{4,2},{4,5},{5,2},// Key Codes 0x08 - 0x0F (DEC 08 - 15)
        {4,4},{4,7},{4,6},{5,1},{7,6},{2,1},{1,5},{2,6},// Key Codes 0x10 - 0x17 (DEC 16 - 23)
        {3,6},{3,7},{1,1},{2,7},{3,1},{1,4},{7,0},{7,3},// Key Codes 0x18 - 0x1F (DEC 24 - 31)
        {1,0},{1,3},{2,0},{2,3},{3,0},{3,3},{4,0},{4,3},// Key Codes 0x20 - 0x27 (DEC 32 - 39)
        {0,1},{6,0},{6,0},{7,2},{7,4}, {5,0},{5,3},{5,6},// Key Codes 0x28 - 0x2F (DEC 40 - 47)
        {6,1},{101,101},{99,99},{5,5},{6,2},{7,1},{5,7},{5,4},// Key Codes 0x30 - 0x37 (DEC 48 - 55)
        {6,7},{99,99},{0,4},{99,99},{0,5},{99,99},{0,6},{99,99},// Key Codes 0x38 - 0x3F (DEC 56 - 63)
        {0,3},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x40 - 0x47 (DEC 64 - 71)
        {99,99},{99,99},{6,3},{99,99},{0,0},{6,5},{99,99},{0,2},// Key Codes 0x48 - 0x4F (DEC 72 - 79)
        {7,1},{0,7},{6,6},{99,99},{99,99},{6,1},{5,3},{5,0},// Key Codes 0x50 - 0x57 (DEC 80 - 87)
        {0,1},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x58 - 0x5F (DEC 88 - 95)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x60 - 0x67 (DEC 96 - 103)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x68 - 0x6F (DEC 104 - 111)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x70 - 0x77 (DEC 112 - 119)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x78 - 0x7F (DEC 113 - 127)
        {99,99},{99,99},{99,99},{99,99},{99,99}// Key Codes 0x80 - 0x83 (DEC 128 - 132)
     },
  // map 2 with shift
  {
        {99,99},{99,99},{99,99},{99,99},{1,2},{3,4},{2,4},{2,2},// Key Codes 0x00 - 0x07 (DEC 00 - 07)
        {1,6},{2,5},{3,2},{3,5},{4,1},{4,2},{4,5},{5,2},// Key Codes 0x08 - 0x0F (DEC 08 - 15)
        {4,4},{4,7},{4,6},{5,1},{7,6},{2,1},{1,5},{2,6},// Key Codes 0x10 - 0x17 (DEC 16 - 23)
        {3,6},{3,7},{1,1},{2,7},{3,1},{1,4},{7,0},{7,3},// Key Codes 0x18 - 0x1F (DEC 24 - 31)
        {1,0},{1,3},{2,0},{2,3},{3,0},{3,3},{4,0},{4,3},// Key Codes 0x20 - 0x27 (DEC 32 - 39)
        {0,1},{6,0},{6,0},{7,2},{7,4}, {5,0},{5,3},{5,6},// Key Codes 0x28 - 0x2F (DEC 40 - 47)
        {6,1},{101,101},{99,99},{5,5},{6,2},{7,1},{5,7},{5,4},// Key Codes 0x30 - 0x37 (DEC 48 - 55)
        {6,7},{99,99},{0,4},{99,99},{0,5},{99,99},{0,6},{99,99},// Key Codes 0x38 - 0x3F (DEC 56 - 63)
        {0,3},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x40 - 0x47 (DEC 64 - 71)
        {99,99},{99,99},{6,3},{99,99},{0,0},{6,5},{99,99},{0,2},// Key Codes 0x48 - 0x4F (DEC 72 - 79)
        {7,1},{0,7},{6,6},{99,99},{99,99},{6,1},{5,3},{5,0},// Key Codes 0x50 - 0x57 (DEC 80 - 87)
        {0,1},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x58 - 0x5F (DEC 88 - 95)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x60 - 0x67 (DEC 96 - 103)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x68 - 0x6F (DEC 104 - 111)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x70 - 0x77 (DEC 112 - 119)
        {99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},// Key Codes 0x78 - 0x7F (DEC 113 - 127)
        {99,99},{99,99},{99,99},{99,99},{99,99}// Key Codes 0x80 - 0x83 (DEC 128 - 132)
  }
};


typedef struct {
  uint8_t noshift_1[C64_KEYMAP_SIZE];
  uint8_t shift_1[C64_KEYMAP_SIZE];
  uint8_t noshift_2[C64_KEYMAP_SIZE];
  uint8_t shift_2[C64_KEYMAP_SIZE];
} C64Keymap_t;

/* Maps are positional in relation to keyboard ASCII codes.
Place C64 key byte (Chart is found in KEYBIN spreadsheet)
into the equivalent keyboard ASCII code code position.
For C64 keyboards normally ASCII code set 2.

Each map has a normal (without shift) and shifted (with shift) array.

In situations where there is a shift difference, add 64 to the C64 key byte. 
This is when a key is shifted on keyboard, but not shifted on the C64 or vise-versa.

Unused ASCII codes need to have the IGNORE_KEYCODE value in place.(Default 170)

*/


const PROGMEM C64Keymap_t C64Keymap_main = {
  // map 1 without shift
   {170,170,170,170,170,170, 39, 25,// ASCII Codes 0x00 - 0x07
     58,170, 63,170, 61,170,170,170,// ASCII Codes 0x08 - 0x0F
    170, 30,170,170,170, 60,  2, 27,// ASCII Codes 0x10 - 0x17
      7,170, 00,170,  0,170,  4, 57,// ASCII Codes 0x18 - 0x1F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x20 - 0x27
    170,170,170,170, 40, 46, 28,170,// ASCII Codes 0x28 - 0x2F
     14, 56, 62, 32, 38, 16, 22, 48,// ASCII Codes 0x30 - 0x37
     54,  8, 45, 47, 46, 41, 31,170,// ASCII Codes 0x38 - 0x3F
     43, 34, 49, 17, 18, 35, 21, 50,// ASCII Codes 0x40 - 0x47
     53, 12, 10, 13, 42,  9, 15, 11,// ASCII Codes 0x48 - 0x4F
     44, 59, 20, 37, 19, 51, 55, 36,// ASCII Codes 0x50 - 0x57
     23, 52, 33, 26, 24,109, 90, 29,// ASCII Codes 0x58 - 0x5F
    170, 1,  65,  5, 69,  3, 67,  6,// ASCII Codes 0x60 - 0x67
     70,170,170,170,170,170,170,170,// ASCII Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x70 - 0x77
    170,170,170,170,170,170,170,  0,// ASCII Codes 0x78 - 0x7F
    170,170,170,170},// ASCII Codes 0x80 - 0x83
  // map 1 with shift
   {170,170,170,170,170,170, 39, 25,// ASCII Codes 0x00 - 0x07
     58,170, 63,170, 61,170,170,170,// ASCII Codes 0x08 - 0x0F
    170, 30,170,170,170,170,  2, 27,// ASCII Codes 0x10 - 0x17
      7,170,  0,170, 60,170,  4, 57,// ASCII Codes 0x18 - 0x1F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x20 - 0x27
    170,170,170,170, 40, 46, 28,170,// ASCII Codes 0x28 - 0x2F
     14, 56, 62, 32, 38, 16, 22, 48,// ASCII Codes 0x30 - 0x37
     54,  8, 45, 47, 46, 41, 31,170,// ASCII Codes 0x38 - 0x3F
     43, 34, 49, 17, 18, 35, 21, 50,// ASCII Codes 0x40 - 0x47
     53, 12, 10, 13, 42,  9, 15, 11,// ASCII Codes 0x48 - 0x4F
     44, 59, 20, 37, 19, 51, 55, 36,// ASCII Codes 0x50 - 0x57
     23, 52, 33, 26, 24,170,170, 29,// ASCII Codes 0x58 - 0x5F
    170,  1,170,  5,170,  3, 170,  6,// ASCII Codes 0x60 - 0x67
    170,170,170,170,170,170,170,170,// ASCII Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x70 - 0x77
    170,170,170,170,170,170,170,  0,// ASCII Codes 0x78 - 0x7F
    170,170,170,170},// ASCII Codes 0x80 - 0x83
  
  
 // map 2 without shift
     {170,170,170,170,170,170, 39, 25,// ASCII Codes 0x00 - 0x07
     58,170, 63,170, 61,170,170,170,// ASCII Codes 0x08 - 0x0F
    170, 30,170,170,170,170,  2, 27,// ASCII Codes 0x10 - 0x17
      7,170, 00,170, 60,170,  4, 57,// ASCII Codes 0x18 - 0x1F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x20 - 0x27
    170,170,170,170, 40, 46, 28,170,// ASCII Codes 0x28 - 0x2F
     14, 56, 62, 32, 38, 16, 22, 48,// ASCII Codes 0x30 - 0x37
     54,  8, 45, 47, 46, 41, 31,170,// ASCII Codes 0x38 - 0x3F
     43, 34, 49, 17, 18, 35, 21, 50,// ASCII Codes 0x40 - 0x47
     53, 12, 10, 13, 42,  9, 15, 11,// ASCII Codes 0x48 - 0x4F
     44, 59, 20, 37, 19, 51, 55, 36,// ASCII Codes 0x50 - 0x57
     23, 52, 33, 26, 24,109, 90, 29,// ASCII Codes 0x58 - 0x5F
    170, 1,  65,  5, 69,  3, 67,  6,// ASCII Codes 0x60 - 0x67
     70,170,170,170,170,170,170,170,// ASCII Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x70 - 0x77
    170,170,170,170,170,170,170,  0,// ASCII Codes 0x78 - 0x7F
    170,170,170,170},// ASCII Codes 0x80 - 0x83
  // map 2 with shift
  {170,170,170,170,170,170, 39, 25,// ASCII Codes 0x00 - 0x07
     58,170, 63,170, 61,170,170,170,// ASCII Codes 0x08 - 0x0F
    170, 30,170,170,170,170,  2, 27,// ASCII Codes 0x10 - 0x17
      7,170,  0,170, 60,170,  4, 57,// ASCII Codes 0x18 - 0x1F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x20 - 0x27
    170,170,170,170, 40, 46, 28,170,// ASCII Codes 0x28 - 0x2F
     14, 56, 62, 32, 38, 16, 22, 48,// ASCII Codes 0x30 - 0x37
     54,  8, 45, 47, 46, 41, 31,170,// ASCII Codes 0x38 - 0x3F
     43, 34, 49, 17, 18, 35, 21, 50,// ASCII Codes 0x40 - 0x47
     53, 12, 10, 13, 42,  9, 15, 11,// ASCII Codes 0x48 - 0x4F
     44, 59, 20, 37, 19, 51, 55, 36,// ASCII Codes 0x50 - 0x57
     23, 52, 33, 26, 24,170,170, 29,// ASCII Codes 0x58 - 0x5F
    170,  1,170,  5,170,  3,170,  6,// ASCII Codes 0x60 - 0x67
    170,170,170,170,170,170,170,170,// ASCII Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// ASCII Codes 0x70 - 0x77
    170,170,170,170,170,170,170,  0,// ASCII Codes 0x78 - 0x7F
    170,170,170,170},// ASCII Codes 0x80 - 0x83

    
  
};

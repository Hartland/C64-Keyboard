
typedef struct {
  uint8_t noshift_1[C64_KEYMAP_SIZE];
  uint8_t shift_1[C64_KEYMAP_SIZE];
  uint8_t noshift_2[C64_KEYMAP_SIZE];
  uint8_t shift_2[C64_KEYMAP_SIZE];
} C64Keymap_t;

/* Maps are positional in relation to keyboard USB codes.
Place C64 key byte (Chart is found in KEYBIN spreadsheet)
into the equivalent keyboard USB code code position.
For C64 keyboards normally USB code set 2.

Each map has a normal (without shift) and shifted (with shift) array.

In situations where there is a shift difference, add 64 to the C64 key byte. 
This is when a key is shifted on keyboard, but not shifted on the C64 or vise-versa.

Unused USB codes need to have the IGNORE_KEYCODE value in place.(Default 170)

*/


const PROGMEM C64Keymap_t C64Keymap_main = {
  // map 1 without shift
   {170,170,170,170, 34, 49, 17, 18,// USB Codes 0x00 - 0x07
     35, 21, 50, 53, 12, 10, 13, 42,// USB Codes 0x08 - 0x0F
      9, 15, 11, 44, 59, 20, 37, 19,// USB Codes 0x10 - 0x17
     51, 55, 36, 23, 52, 33, 56, 62,// USB Codes 0x18 - 0x1F
     32, 38, 16, 22, 48, 54,  8, 14,// USB Codes 0x20 - 0x27
      4,170,  0,170, 57,170, 29,170,// USB Codes 0x28 - 0x2F
    170, 24, 43, 26, 45, 43, 47, 41,// USB Codes 0x30 - 0x37
     31,170,  1,170,  5,170,  3,170,// USB Codes 0x38 - 0x3F
      6,170,170,170,170,170,170,170,// USB Codes 0x40 - 0x47
    170,170, 30,170,  0,170,170,  2,// USB Codes 0x48 - 0x4F
     60,  7, 27,170,170, 28, 46, 40,// USB Codes 0x50 - 0x57
    170,170,170,170, 60,170,170,170,// USB Codes 0x58 - 0x5F
    170,170,170,170,170,170,170,170,// USB Codes 0x60 - 0x67
    170,170,170,170,170,170,170,170,// USB Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// USB Codes 0x70 - 0x77
    170,170,170,170,170,170,170,170,// USB Codes 0x78 - 0x7F
    170,170,170,170,170,170,170,170},// USB Codes 0x80 - 0x83
  // map 1 with shift
   {170,170,170,170, 34, 49, 17, 18,// USB Codes 0x00 - 0x07
     35, 21, 50, 53, 12, 10, 13, 42,// USB Codes 0x08 - 0x0F
      9, 15, 11, 44, 59, 20, 37, 19,// USB Codes 0x10 - 0x17
     51, 55, 36, 23, 52, 33, 56, 62,// USB Codes 0x18 - 0x1F
     32, 38, 16, 22, 48, 54,  8, 14,// USB Codes 0x20 - 0x27
      4,170,  0,170, 57,170, 29,170,// USB Codes 0x28 - 0x2F
    170, 24, 43, 26, 45, 43, 47, 41,// USB Codes 0x30 - 0x37
     31,170,  1,170,  5,170,  3,170,// USB Codes 0x38 - 0x3F
      6,170,170,170,170,170,170,170,// USB Codes 0x40 - 0x47
    170,170, 30,170,  0,170,170,  2,// USB Codes 0x48 - 0x4F
     60,  7, 27,170,170, 28, 46, 40,// USB Codes 0x50 - 0x57
    170,170,170,170, 60,170,170,170,// USB Codes 0x58 - 0x5F
    170,170,170,170,170,170,170,170,// USB Codes 0x60 - 0x67
    170,170,170,170,170,170,170,170,// USB Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// USB Codes 0x70 - 0x77
    170,170,170,170,170,170,170,170,// USB Codes 0x78 - 0x7F
    170,170,170,170,170,170,170,170},// USB Codes 0x80 - 0x83
  
  
 // map 2 without shift
   {170,170,170,170, 34, 49, 17, 18,// USB Codes 0x00 - 0x07
     35, 21, 50, 53, 12, 10, 13, 42,// USB Codes 0x08 - 0x0F
      9, 15, 11, 44, 59, 20, 37, 19,// USB Codes 0x10 - 0x17
     51, 55, 36, 23, 52, 33, 56, 62,// USB Codes 0x18 - 0x1F
     32, 38, 16, 22, 48, 54,  8, 14,// USB Codes 0x20 - 0x27
      4,170, 60,170, 57,170, 29,170,// USB Codes 0x28 - 0x2F
    170, 24, 43, 26, 45, 43, 47, 41,// USB Codes 0x30 - 0x37
     31,170,  1,170,  5,170,  3,170,// USB Codes 0x38 - 0x3F
      6,170,170,170,170,170,170,170,// USB Codes 0x40 - 0x47
    170,170, 30, 27,  0,170,170,  2,// USB Codes 0x48 - 0x4F
     66,  7, 71,170,170, 28, 46, 40,// USB Codes 0x50 - 0x57
    170,170,170,170, 60,170,170,170,// USB Codes 0x58 - 0x5F
    170,170,170,170,170,170,170,170,// USB Codes 0x60 - 0x67
    170,170,170,170,170,170,170,170,// USB Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// USB Codes 0x70 - 0x77
    170,170,170,170,170,170,170,170,// USB Codes 0x78 - 0x7F
    170,170,170,170,170,170,170,170},// USB Codes 0x80 - 0x83
  // map 2 with shift
   {170,170,170,170, 34, 49, 17, 18,// USB Codes 0x00 - 0x07
     35, 21, 50, 53, 12, 10, 13, 42,// USB Codes 0x08 - 0x0F
      9, 15, 11, 44, 59, 20, 37, 19,// USB Codes 0x10 - 0x17
     51, 55, 36, 23, 52, 33, 56, 62,// USB Codes 0x18 - 0x1F
     32, 38, 16, 22, 48, 54,  8, 14,// USB Codes 0x20 - 0x27
      4,170, 60,170, 57,170, 29,170,// USB Codes 0x28 - 0x2F
    170, 24, 43, 26, 45, 43, 47, 41,// USB Codes 0x30 - 0x37
     31,170,  1,170,  5,170,  3,170,// USB Codes 0x38 - 0x3F
      6,170,170,170,170,170,170,170,// USB Codes 0x40 - 0x47
    170,170, 30, 27,  0,170,170,  2,// USB Codes 0x48 - 0x4F
    170,  7, 27,170,170, 28, 46, 40,// USB Codes 0x50 - 0x57
    170,170,170,170, 60,170,170,170,// USB Codes 0x58 - 0x5F
    170,170,170,170,170,170,170,170,// USB Codes 0x60 - 0x67
    170,170,170,170,170,170,170,170,// USB Codes 0x68 - 0x6F
    170,170,170,170,170,170,170,170,// USB Codes 0x70 - 0x77
    170,170,170,170,170,170,170,170,// USB Codes 0x78 - 0x7F
    170,170,170,170,170,170,170,170},// USB Codes 0x80 - 0x83

    
  
};

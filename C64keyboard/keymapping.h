
typedef struct {
	uint8_t noshift_1[PS2_KEYMAP_SIZE];
	uint8_t shift_1[PS2_KEYMAP_SIZE];
	uint8_t noshift_2[PS2_KEYMAP_SIZE];
	uint8_t shift_2[PS2_KEYMAP_SIZE];
	uint8_t noshift_3[PS2_KEYMAP_SIZE];
	uint8_t shift_3[PS2_KEYMAP_SIZE];
} PS2Keymap_t;

/* Maps are positional in relation to keyboard scan codes.
Place C64 key byte (Chart is found in KEYBIN spreadsheet)
into the equivalent keyboard scan code code position.
For PS2 keyboards normally scan code set 2.

Each map has a normal (without shift) and shifted (with shift) array.

In situations where there is a shift difference, add 64 to the C64 key byte. 
This is when a key is shifted on keyboard, but not shifted on the C64 or vise-versa.

Unused scan codes need to have the IGNORE_KEYCODE value in place.(Default 170)

*/


const PROGMEM PS2Keymap_t PS2Keymap_main = {
  // map 1 without shift
   {  170,170,170,  3,  5,  1,170,170,// Scan Codes 0x00 - 0x07
	  170,170,170,170,170, 30, 27,170,// Scan Codes 0x08 - 0x0F
	  170, 61, 39,170, 58, 59, 56,170,// Scan Codes 0x10 - 0x17
	  170,170, 33, 37, 34, 36, 62,170,// Scan Codes 0x18 - 0x1F
	  170, 17, 23, 18, 35, 38, 32,170,// Scan Codes 0x20 - 0x27
	  170, 57, 55, 21, 19, 20, 16,170,// Scan Codes 0x28 - 0x2F
	  170, 15, 49, 53, 50, 52, 22,170,// Scan Codes 0x30 - 0x37
	  170,170,  9, 10, 51, 48, 54,170,// Scan Codes 0x38 - 0x3F
	  170, 47, 13, 12, 11, 14,  8,170,// Scan Codes 0x40 - 0x47
	  170, 41, 31, 42, 26, 44, 24,170,// Scan Codes 0x48 - 0x4F
	  170,170,112,170,109, 29,170,170,// Scan Codes 0x50 - 0x57
	  170, 25,  4, 90,170, 45,170,170,// Scan Codes 0x58 - 0x5F
	  170,170,170,170,170,170, 60,170,// Scan Codes 0x60 - 0x67
	  170, 94,170, 66, 30,170,170,170,// Scan Codes 0x68 - 0x6F
	  170,  0,  7,170,  2, 71, 63,170,// Scan Codes 0x70 - 0x77
	  170, 40,170, 46, 28,170,170,170,// Scan Codes 0x78 - 0x7F
	  170,170,170,170},// Scan Codes 0x80 - 0x83
  // map 1 with shift
   {  170,170,170,  3,  5,  1,170,170,// Scan Codes 0x00 - 0x07
	  170,170,170,170,170, 30, 27,170,// Scan Codes 0x08 - 0x0F
	  170, 61, 39,170, 58, 59, 56,170,// Scan Codes 0x10 - 0x17
	  170,170, 33, 37, 34, 36, 107,170,// Scan Codes 0x18 - 0x1F
	  170, 17, 23, 18, 35, 38, 32,170,// Scan Codes 0x20 - 0x27
	  170, 57, 55, 21, 19, 20, 16,170,// Scan Codes 0x28 - 0x2F
	  170, 15, 49, 53, 50, 52, 22,170,// Scan Codes 0x30 - 0x37
	  170,170,  9, 10, 51, 22, 92,170,// Scan Codes 0x38 - 0x3F
	  170, 47, 13, 12, 11,  8, 54,170,// Scan Codes 0x40 - 0x47
	  170, 41, 31, 42, 26, 44, 24,170,// Scan Codes 0x48 - 0x4F
	  170,170, 62,170,170, 29,170,170,// Scan Codes 0x50 - 0x57
	  170, 25,  4,170,170, 45,170,170,// Scan Codes 0x58 - 0x5F
	  170,170,170,170,170,170, 60,170,// Scan Codes 0x60 - 0x67
	  170,170,170,170, 30,170,170,170,// Scan Codes 0x68 - 0x6F
	  170,170,170,170,170,170, 63,170,// Scan Codes 0x70 - 0x77
	  170, 40,170, 46, 28,170,170,170,// Scan Codes 0x78 - 0x7F
	  170,170,170,170},// Scan Codes 0x80 - 0x83
	
	
 // map 2 without shift
   {  170,170,170,  3,  5,  1,170,170,// Scan Codes 0x00 - 0x07
	  170,170,170,170,170, 30, 27,170,// Scan Codes 0x08 - 0x0F
	  170, 61, 39,170, 58, 59, 56,170,// Scan Codes 0x10 - 0x17
	  170,170, 33, 37, 34, 36, 62,170,// Scan Codes 0x18 - 0x1F
	  170, 17, 23, 18, 35, 38, 32,170,// Scan Codes 0x20 - 0x27
	  170, 57, 55, 21, 19, 20, 16,170,// Scan Codes 0x28 - 0x2F
	  170, 15, 49, 53, 50, 52, 22,170,// Scan Codes 0x30 - 0x37
	  170,170,  9, 10, 51, 48, 54,170,// Scan Codes 0x38 - 0x3F
	  170, 47, 13, 12, 11, 14,  8,170,// Scan Codes 0x40 - 0x47
	  170, 41, 31, 42, 26, 44, 24,170,// Scan Codes 0x48 - 0x4F
	  170,170,112,170,109, 29,170,170,// Scan Codes 0x50 - 0x57
	  170, 25,  4, 90,170, 45,170,170,// Scan Codes 0x58 - 0x5F
	  170,170,170,170,170,170, 60,170,// Scan Codes 0x60 - 0x67
	  170, 94,170, 66, 30,170,170,170,// Scan Codes 0x68 - 0x6F
	  170,  0,  7,170,  2, 71, 63,170,// Scan Codes 0x70 - 0x77
	  170, 40,170, 46, 28,170,170,170,// Scan Codes 0x78 - 0x7F
	  170,170,170,170},// Scan Codes 0x80 - 0x83
  // map 2 with shift
   {  170,170,170,  3,  5,  1,170,170,// Scan Codes 0x00 - 0x07
	  170,170,170,170,170, 30, 27,170,// Scan Codes 0x08 - 0x0F
	  170, 61, 39,170, 58, 59, 56,170,// Scan Codes 0x10 - 0x17
	  170,170, 33, 37, 34, 36, 107,170,// Scan Codes 0x18 - 0x1F
	  170, 17, 23, 18, 35, 38, 32,170,// Scan Codes 0x20 - 0x27
	  170, 57, 55, 21, 19, 20, 16,170,// Scan Codes 0x28 - 0x2F
	  170, 15, 49, 53, 50, 52, 22,170,// Scan Codes 0x30 - 0x37
	  170,170,  9, 10, 51, 22, 92,170,// Scan Codes 0x38 - 0x3F
	  170, 47, 13, 12, 11,  8, 54,170,// Scan Codes 0x40 - 0x47
	  170, 41, 31, 42, 26, 44, 24,170,// Scan Codes 0x48 - 0x4F
	  170,170, 62,170,170, 29,170,170,// Scan Codes 0x50 - 0x57
	  170, 25,  4,170,170, 45,170,170,// Scan Codes 0x58 - 0x5F
	  170,170,170,170,170,170, 60,170,// Scan Codes 0x60 - 0x67
	  170,170,170,170, 30,170,170,170,// Scan Codes 0x68 - 0x6F
	  170,170,170,170,170,170, 63,170,// Scan Codes 0x70 - 0x77
	  170, 40,170, 46, 28,170,170,170,// Scan Codes 0x78 - 0x7F
	  170,170,170,170},// Scan Codes 0x80 - 0x83

	  
 // map 3 without shift
   {  170,170,170,  3,  5,  1,170,170,// Scan Codes 0x00 - 0x07
	  170,170,170,170,170, 30, 27,170,// Scan Codes 0x08 - 0x0F
	  170, 61, 39,170, 58, 59, 56,170,// Scan Codes 0x10 - 0x17
	  170,170, 33, 37, 34, 36, 62,170,// Scan Codes 0x18 - 0x1F
	  170, 17, 23, 18, 35, 38, 32,170,// Scan Codes 0x20 - 0x27
	  170, 57, 55, 21, 19, 20, 16,170,// Scan Codes 0x28 - 0x2F
	  170, 15, 49, 53, 50, 52, 22,170,// Scan Codes 0x30 - 0x37
	  170,170,  9, 10, 51, 48, 54,170,// Scan Codes 0x38 - 0x3F
	  170, 47, 13, 12, 11, 14,  8,170,// Scan Codes 0x40 - 0x47
	  170, 41, 31, 42, 26, 44, 24,170,// Scan Codes 0x48 - 0x4F
	  170,170,112,170,109, 29,170,170,// Scan Codes 0x50 - 0x57
	  170, 25,  4, 90,170, 45,170,170,// Scan Codes 0x58 - 0x5F
	  170,170,170,170,170,170, 60,170,// Scan Codes 0x60 - 0x67
	  170, 94,170, 66, 30,170,170,170,// Scan Codes 0x68 - 0x6F
	  170,  0,  7,170,  2, 71, 63,170,// Scan Codes 0x70 - 0x77
	  170, 40,170, 46, 28,170,170,170,// Scan Codes 0x78 - 0x7F
	  170,170,170,170},// Scan Codes 0x80 - 0x83
  // map 3 with shift
   {  170,170,170,  3,  5,  1,170,170,// Scan Codes 0x00 - 0x07
	  170,170,170,170,170, 30, 27,170,// Scan Codes 0x08 - 0x0F
	  170, 61, 39,170, 58, 59, 56,170,// Scan Codes 0x10 - 0x17
	  170,170, 33, 37, 34, 36, 107,170,// Scan Codes 0x18 - 0x1F
	  170, 17, 23, 18, 35, 38, 32,170,// Scan Codes 0x20 - 0x27
	  170, 57, 55, 21, 19, 20, 16,170,// Scan Codes 0x28 - 0x2F
	  170, 15, 49, 53, 50, 52, 22,170,// Scan Codes 0x30 - 0x37
	  170,170,  9, 10, 51, 22, 92,170,// Scan Codes 0x38 - 0x3F
	  170, 47, 13, 12, 11,  8, 54,170,// Scan Codes 0x40 - 0x47
	  170, 41, 31, 42, 26, 44, 24,170,// Scan Codes 0x48 - 0x4F
	  170,170, 62,170,170, 29,170,170,// Scan Codes 0x50 - 0x57
	  170, 25,  4,170,170, 45,170,170,// Scan Codes 0x58 - 0x5F
	  170,170,170,170,170,170, 60,170,// Scan Codes 0x60 - 0x67
	  170,170,170,170, 30,170,170,170,// Scan Codes 0x68 - 0x6F
	  170,170,170,170,170,170, 63,170,// Scan Codes 0x70 - 0x77
	  170, 40,170, 46, 28,170,170,170,// Scan Codes 0x78 - 0x7F
	  170,170,170,170},// Scan Codes 0x80 - 0x83
	
};
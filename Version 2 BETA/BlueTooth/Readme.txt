The blue tooth project is based and tested on SEEED nRF52840.
 Libraries needed:
Seeed board drivers
MT88XX_Controller library
Adafruit Bluefruit nRF52 library

Wiring is the same as the SMD USB Keyboard

*****************************************************************************

***The nRF52840 is a BLE (Blue tooth low energy) microcontroller.***
***It will only work with a BLE compatible keyboards***
***Make sure the keyboard you are using is BLE compatible****
***I used and tested with an Emetok EM001 BLE keyboard***

*****************************************************************************

*****************************************************************************
CAUTION: SPEICAL FUNCTION KEYS CAN CAUSE COMMUCATION TO FAIL AND LOCK
         THIS IS DUE TO ISSUES WITHIN THE BLUEFRUIT DRIVER ITSELF
         MOST OF THE TIME SIMPLY REPARING THE KEYBOARD WILL CLEAR THE ISSUE
         OTHERWISE A POWER CYCLE AND PARING WILL BE NEEDED
*****************************************************************************
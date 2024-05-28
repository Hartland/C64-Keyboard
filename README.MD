


# !!! VERSION 2 IS CURRENTLY BEING DEVELOPED. VERSION 1 IS IN THE ARCHIVE FOLDER
# !!! PLEASE USE VERSION 1 FOR MAINSTREAM USE
# !!! EVENTUALLY VERSION 2 WILL WORK WITH VERSION 1 HARDWARE



## C64 PS2/USB Keyboard (VERSION 1)


This project is designed to allow a PS2/USB keyboard to be used with a Commodore 64 in place of the original Commodore keyboard.


Dependencies
------------
* PS2KeyAdvanced Arduino library for use with PS2 keyboard. Install through the IDE library manager

* SEEED XIAO uses slightly modified USBHOST Arduino library (C64_USB_Host_Library_SAMD). This directory will need to be copied into the Arduino library directory.

* SEEED XIAO will need its board driver installed into the Arduino IDE. See manufacturers instructions.

* DUE also uses a modified USBHOST library but it is included with the source and does not need to be installed in the library directory.


Hardware
--------
* Arduino Uno, Nano, DUE, or SEEED XIAO. SEEED XIAO or DUE required for USB keyboard

* MT8808, MT8812 or MT8816 Analog Switch Array

* 20 pin female header or male header with cable (PATA cable will work)

* Arduino shield PCB. 
	- Any universal PCB that will line up correctly

* PS2 keyboard 
	- matching socket or cut/strip and directly wire
	
* USB keyboard - **SEEED XIAO is highly recommended as the DUE is overkill for this project** 
	- Requires SEEED XIAO or DUE. In most cases, the SEED requires USB Type C to USB A or Micro Type B cable/adapter
	- Keyboards that connect through internal USB hubs are not supported.This is a limitation of the USBHost library
	- Restore (NMI) key requires a NPN transistor (2n3904 suggested) and resistor (10K)

 
Documents
---------
	
* KEYBIN.PDF
	- MT88XX AY/AX. These are the hard wired Commodore keyboard header position values used in keyboard mapping.
	- The position values are placed on the keymap where the PS2/USB keyboard value matches the Commodore key desired.
	- The AX2-1-0 AY2-1-0 and logic hole hole columns are for reference and not needed to make keymaps.
	- The logic hole column only applies to the MT8812-16.
	
* DEFAULTKEY.TXT
	- Key map of special function keys (EX. C= key mapped to Windows key)
	
* USB_KEY_CODES.TXT
	- Public Domain copy of USB HID scan codes.
	
* Schematic PDF files
	- Include wiring charts and are located in the PS2 and USB folders under the appropriate board type
	- MT8808 and MT8812-16 are separate due to a different MT88xx pinouts 


Usage
-----

* PS2 keyboards use the PS2KeyAdvanced library.
	-Use Manage Library to search for and install PS2KeyAdvanced.

* USB Keyboards use the included modified USBHOST.

* Using the Arduino IDE upload the sketch: *C64_keyboard.ino* into your Arduino.

* **SYSTEM OPTIONS ARE LOCATED IN THE *C64KEYBOARD.H* HEADER FILE. THE MT8808 DEFINITION IS VERY IMPORTANT. SET TO TRUE IF USING A MT8808 OR FALSE IF USING MT8812-16.**


!!!POWER REQUIREMENTS!!!!
-------------------------

* The Arduino UNO, Nano, and SEEED can be powered from the C64 keyboard header Pin 4

* **The Arduino DUE CANNOT BE POWERED FROM PIN 4!! Use the + side of C10 (+10V) connected to the DUE barrel power connector instead.**


TODO
----

* Create spreadsheet/program to automatically create key maps

* Publish pre-compiled binary files
 

Version 1.00
-------------
* Updated and cleaned up all schematics and documents. All wiring charts are now on the schematics.

* DUE has been brought out of archive status and will be part of future updates.


Version 0.920
-------------
* Add SEEED XIAO board for USB keyboards

* Document DUE is for archive only

Version 0.911
-------------
* USB IDE library requirement removed

Version 0.91
------------
* USB module published
 


Version 0.9
------------
* Code rewrite using PS2KeyAdvanced library

* Several bugs have been fixed

* Speed and reliability have been greatly improved

* Up to 2 key maps can be stored and hot swapped with assigned keys (Default F9-F10)


	


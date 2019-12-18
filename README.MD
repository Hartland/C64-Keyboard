## C64 PS2/USB Keyboard




This project is designed to allow a PS2/USB keyboard to be used with a Commodore 64 in place of the original Commodore keyboard.


Dependencies
------------
* PS2KeyAdvanced Arduino library for use with PS2 keyboard. Install through the IDE library manager.

* A slightly modified USBHOST Arduino library is included for use with USB keyboard.


Hardware
--------
* Arduino Uno, Nano, or DUE. DUE required for USB keyboard.

* **It is strongly recommended to use DUE for USB only. The cost of the DUE and its required level shifters for PS2 connections make it impractical for PS2 implementation.** 

* MT8808, MT8812 or MT8816 Analog Switch Array.

* 20 pin female header or male header with cable (PATA cable will work)

* Arduino shield PCB. 
	- Any universal PCB that will line up correctly.

* PS2 keyboard 
	- matching socket or cut/strip and directly wire.
	
* USB keyboard 
	- Requires DUE and in most cases, USB Type A to USB Micro Type B cable/adapter.
	- Keyboards that connect through internal USB hubs are not supported.This is a limitation of the USBHost library.
	- Restore (NMI) key requires a NPN transistor (2n3904 suggested) and resistor (10K).


Documents
---------
* MT88XX.xml
	- Basic wiring charts. Separate tabs for MT8808 and MT8812/MT8816. Wiring charts are also on the schematics.

* MT8808.pdf and MT8812-16.pdf MT8808 is separate due to a different IC pinout to MT8812-16
	- PDF versions for the wiring charts
	
* KEYBIN.xml
	- MT88XX AY/AX. These are the hard wired Commodore keyboard header position values used in keyboard mapping.
	- The position values are placed on the keymap where the PS2/USB keyboard value matches the Commodore key desired.
	- The AX2-1-0 AY2-1-0 and logic hole hole columns are for reference and not needed to make keymaps. 
	
* DEFAULTKEY
	- Included key map document
	
* Schematic_MT8812-16.pdf and Schematic_MT8808.PDF.These are located in the PS2/doc and USB/doc folders.
	-Schematic diagrams. MT8808 is separate due to a different IC pinout to MT8812-16



Usage
-----

* PS2 keyboards use the PS2KeyAdvanced library.
	-Use Manage Library to search for and install PS2KeyAdvanced.

* USB Keyboards use the included modified USBHOST.

* Using the Arduino IDE upload the sketch: *C64_keyboard.ino* into your Arduino.

* **SYSTEM OPTIONS ARE LOCATED IN THE *C64KEYBOARD.H* HEADER FILE. THE MT8808 DEFINITION IS VERY IMPORTANT. SET TO TRUE IF USING A MT8808 OR FLASE IF USING MT8812-16.**


!!!POWER REQUIREMENTS!!!!
-------------------------

* The Arduino UNO and Nano can be powered from the C64 keyboard header Pin 4

* **The Arduino DUE CANNOT BE POWERED FROM PIN 4!! Use the + side of C10 (+10V) connected to the DUE barrel power connector instead.**


TODO
----
* Code cleanup

* Write spreadsheet/program to ease creation of keymaps


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


	


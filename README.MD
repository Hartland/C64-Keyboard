C64 PS2/USB Keyboard
--------------------



This project is designed to allow a PS2/USB keyboard to be used
with a Commodore 64/128 in place of the original Commodore keyboard.

Dependencies
------------
PS2KeyAdvanced Arduino IDE library
USBHOST Arduino IDE library (USB NOT IMPLEMENTED YET)


Hardware
--------
* Arduino Uno, Nano, or DUE. DUE required for USB keyboard (USB NOT IMPLEMENTED YET).

* MT8808, MT8812 or MT8816 Analog Cross switch

* 20 pin female header or male header with cable (PATA cable will work)

* Arduino shield PCB. 
	- Any universal PCB that will line up correctly.

* PS2 keyboard 
	- matching socket or cut/strip and directly wire.
	
* USB keyboard (USB NOT IMPLEMENTED YET)
	- Requires DUE and in most cases USB to microUSB adaptor.


Documents
---------
* MT88XX.xml
	- Basic wiring charts. Separate tabs for MT8808 and MT8812/MT8816.

* MT8808.pdf and MT8812-16.pdf ( MT8808 is separate due to a different IC pinout to MT8812-16)
	- PDF versions for the wiring charts
	
* KEYBIN.xml
	- MT88XX AY/AX - Commodore header table.
	
* DEFAULTKEY
	- Included key map document
	
* Schematic_MT8812-16.pdf and Schematic_MT8808.PDF
	-Schematic diagrams ( MT8808 is separate due to a different IC pinout to MT8812-16)



Usage
-----

* PS2 keyboards need PS2KeyAdvanced library to be installed into Arduino IDE library. Use Include Library - Manage Library to search for and install PS2KeyAdvanced.

* USB Keyboards need USBHOST library to be installed into Arduino IDE library(USB NOT IMPLEMTED YET)

* Using the Arduino IDE upload the sketch: C64_keyboard.ino : into your Arduino.

** Systems options are located in the C64keyboard.h header file. The MT8808 definition is very important. Set to true if using a MT8808 or flase if using MT8812-16.**


!!!POWER REQUIREMENTS!!!!
-------------------------

* The Arduino UNO and Nano can be powered from the C64 keyboard header Pin 4

* **The Arduino DUE CANNOT BE POWERED FROM PIN 4!! Use the + side of C10 (+10V) connected to the DUE barrel power connector instead.**


	
Version 0.9
-----------
* Code rewrite using PS2KeyAdvanced library

* Several bugs have been fixed

* Speed and reliability have been greatly improved

* Up to 2 key maps can be stored and hot swapped with assigned keys (Default F9-F10)


	


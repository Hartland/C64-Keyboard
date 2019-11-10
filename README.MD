============================
C64 PS2 Keyboard
============================


This project is designed to allow a PS2 keyboard to be used
with a Commodore 64/128 in place of the original Commodore keyboard.

Dependencies
------------
PS2KeyAdvanced Arduino IDE library


Hardware
--------
* Arduino Uno or Nano

* MT8808, MT8812 or MT8816 Analog Cross switch

* 20 pin female header or male header with cable (PATA cable will work)

* Arduino shield PCB. 
	- Any universal PCB that will line up correctly.

* PS2 keyboard 
	- matching socket or cut/strip and directly wire.


Documents
---------
* MT88XX.xml
	- Basic wiring chart.
	
* KEYBIN.xml
	- MT88XX AY/AX - Commodore header table.
	
* DEFAULTKEY
	- Included key map document


Usage
-----

* PS2KeyAdvanced library needs to be installed into Arduino IDE library. Use Include Library - Manage lLibrary to search for and install  PS2KeyAdvanced.
* Using the Arduino IDE upload the sketch: C64_keyboard.ino : into your Arduino.




!!!POWER REQUIREMENTS!!!!
-------------------------

* The Arduino UNO and Nano can be powered from the C64 keyboard header Pin 4


	
Version 0.9
-----------
* Code rewrite using PS2KeyAdvanced library

* Several bugs have been fixed

* Speed and reliability have been greatly improved

* Up to 2 key maps can be stored and hot swapped with assigned keys (Default F9-F10)


	


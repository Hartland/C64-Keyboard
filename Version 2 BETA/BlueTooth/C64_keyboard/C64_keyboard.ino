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


Modified Adafruit HID example used. MIT Licence below.
*/


/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 
*********************************************************************/



#include <Arduino.h>
#include "C64Keyboard.h"
#include <bluefruit.h>

// Polling or callback implementation
#define POLLING 1
BLEClientHidAdafruit hid;

// Last checked report, to detect if there are changes between reports
hid_keyboard_report_t last_kbd_report = { 0 };
C64keyboard ckey;
mt88xx array;
void setup() {
  // *****THE DATA PIN NEEDS TO BE SET LOW ASAP TO PREVENT RUN/STOP GHOST KEY PRESS DURING POWER UP*****
  pinMode(D1, OUTPUT);
  digitalWrite(D1,LOW);
  //*****THE DATA PIN NEEDS TO BE SET LOW ASAP TO PREVENT RUN/STOP GHOST KEY PRESS DURING POWER*****


  // Configure MT88XX control library
  array.setModel(8); // Chip model. MT8808 is default. MT8808 = 8  MT8812 = 12  MT8816 = 16
  array.setErrorLED(13, false); // Error led pin, enable/disable
  uint8_t axPins[3] = {6, 7, 8}; // Define AX pins
  uint8_t ayPins[3] = {3, 4, 5}; // Define AY pins
  array.setControlPins(1, 2, axPins, ayPins, 10, 0); // Data, Strobe, AX pins, AY pins, AX3, Reset
  array.begin();

  
  // Start C64 keyboard
  ckey.begin();
 if (debug) {Serial.begin( 115200 );}
 

 // Initialize Bluefruit with maximum connections as Peripheral = 0, Central = 1
  Bluefruit.begin(0, 1);
  Bluefruit.setName("C64 Keyboard");
  // Init BLE Central Hid Service
  hid.begin();
  #if POLLING == 0
  hid.setKeyboardReportCallback(keyboard_report_callback);
  #endif

  // Increase Blink rate to differentiate from PrPh advertising mode
  Bluefruit.setConnLedInterval(250);

  // Callbacks for Central
  Bluefruit.Central.setConnectCallback(connect_callback);
  Bluefruit.Central.setDisconnectCallback(disconnect_callback);

  // Set connection secured callback, invoked when connection is encrypted
  Bluefruit.Security.setSecuredCallback(connection_secured_callback);

  // Start Central Scanning
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.filterService(hid);   // only report HID service
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0);             // 0 = Don't stop scanning after n seconds

}

/**
 * Callback invoked when scanner picks up advertising data
 * @param report Structural advertising data
 */
void scan_callback(ble_gap_evt_adv_report_t* report) {
  // Connect to the device with HID service in advertising packet
  Bluefruit.Central.connect(report);
}

/**
 * Callback invoked when a connection is established
 * @param conn_handle
 */
void connect_callback(uint16_t conn_handle) {
  BLEConnection* conn = Bluefruit.Connection(conn_handle);

  Serial.println("Connected");

  //Serial.print("Discovering HID Service ... ");

  if (hid.discover(conn_handle)) {
    //Serial.println("Found it");

    // HID device mostly requires pairing/bonding
    conn->requestPairing();
  } else {
   // Serial.println("Found NONE");
    
    // Disconnect since we couldn't find the HID service
    conn->disconnect();
  }
}

void connection_secured_callback(uint16_t conn_handle) {
  BLEConnection* conn = Bluefruit.Connection(conn_handle);

  if (!conn->secured()) {
    // If connection is still not secured, request pairing again
    conn->requestPairing();
  } else {
    //Serial.println("Secured");
    uint8_t hidInfo[4];
    hid.getHidInfo(hidInfo);

    //Serial.printf("HID version: %d.%d\n", hidInfo[0], hidInfo[1]);
    //Serial.print("Country code: "); Serial.println(hidInfo[2]);
    //Serial.printf("HID Flags  : 0x%02X\n", hidInfo[3]);

    // BLEClientHidAdafruit currently only supports Boot Protocol Mode
    // for Keyboard. Let's set the protocol mode on the peripheral to Boot Mode
    hid.setBootMode(true);

    // Enable Keyboard report notification if present on the peripheral
    if (hid.keyboardPresent()) hid.enableKeyboard();

    //Serial.println("Ready to receive from peripheral");
  }
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  //Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
  // Restart scanning
  Bluefruit.Scanner.start(0);
}

void loop() {
  #if POLLING == 1
  // Nothing to do if HID is not discovered
  if (!hid.discovered()) return;

  // Polling Keyboard
  hid_keyboard_report_t kbd_report;

  // Get the latest report
  hid.getKeyboardReport(&kbd_report);

  processKeyboardReport(&kbd_report);

  // Polling interval is 5 ms
  delay(5);
  #endif
}

void keyboard_report_callback(hid_keyboard_report_t* report) {
  processKeyboardReport(report);
}

void processKeyboardReport(hid_keyboard_report_t* report) {

  // Check if there are any changes in the report
  if (memcmp(&last_kbd_report, report, sizeof(hid_keyboard_report_t)) != 0) {
    // Process modifier keys
    if (report->modifier != last_kbd_report.modifier) {
      // Pass the current and previous modifier buffers to the C64 keyboard module
      ckey.c64key(0, last_kbd_report.modifier, report->modifier, true);
    }

    // Process keycodes
    for (uint8_t i = 0; i < 6; i++) {
      uint8_t oldKeyCode = last_kbd_report.keycode[i];
      uint8_t newKeyCode = report->keycode[i];

      if (oldKeyCode != newKeyCode) {
        if (newKeyCode != 0) {
          // Key pressed (make)
          ckey.c64key(newKeyCode, last_kbd_report.modifier, report->modifier, true);
        }
        if (oldKeyCode != 0) {
          // Key released (break)
          ckey.c64key(oldKeyCode, last_kbd_report.modifier, report->modifier, false);
        }
      }
    }

    // Update the last report
    memcpy(&last_kbd_report, report, sizeof(hid_keyboard_report_t));
  }
}

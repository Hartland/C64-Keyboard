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

#include "CustomHIDBoot.h"
#include <hidboot.h>

// Function prototypes
void keyPressed();
void keyReleased();

void CustomKeyboardReportParser::Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf) {
    prevModifierBuffer = currentModifierBuffer;
    currentModifierBuffer = buf[0];

    if (prevState.bInfo[0x00] != buf[0x00]) {
        OnControlKeysChanged(prevState.bInfo[0x00], buf[0x00]);
    }

    for (uint32_t i = 0; i < 8; i++) {
        bool down = false;
        bool up = false;

        for (uint8_t j = 0; j < 8; j++) {
            if (buf[i] == prevState.bInfo[j] && buf[i] != 1)
                down = true;
            if (buf[j] == prevState.bInfo[i] && prevState.bInfo[i] != 1)
                up = true;
        }
        if (!down) {
            HandleLockingKeys(hid, buf[i]);
            OnKeyDown(buf[0], buf[i]);
        }
        if (!up) {
            OnKeyUp(buf[0], prevState.bInfo[i]);
        }
    }
    for (uint32_t i = 0; i < 8; i++)
        prevState.bInfo[i] = buf[i];
}

void CustomKeyboardReportParser::OnKeyDown(uint8_t mod, uint8_t key) {
    this->key = key;
    keyPressed();
}

void CustomKeyboardReportParser::OnKeyUp(uint8_t mod, uint8_t key) {
    this->key = key;
    keyReleased();
}

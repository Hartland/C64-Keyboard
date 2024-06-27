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







#ifndef CUSTOM_HID_BOOT_H
#define CUSTOM_HID_BOOT_H

#include <hidboot.h>

class CustomKeyboardReportParser : public KeyboardReportParser {
public:
    void Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf) override;
    uint8_t getKey() const { return key; }
    uint8_t getPrevModifierBuffer() const { return prevModifierBuffer; }
    uint8_t getCurrentModifierBuffer() const { return currentModifierBuffer; }

protected:
    void OnKeyDown(uint8_t mod, uint8_t key) override;
    void OnKeyUp(uint8_t mod, uint8_t key) override;

private:
    uint8_t key;
    uint8_t prevModifierBuffer;
    uint8_t currentModifierBuffer;
};

#endif // CUSTOM_HID_BOOT_H

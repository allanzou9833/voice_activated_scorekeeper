#include "mbed.h"
#include "7SegSRDriver.h"

/* mbed 7-Segment Display Driver Library (via an 8bit Shift Register)
 * Copyright (c) 2011 Paul Law
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Display should be hooked up to shift register as follows:
// Q0 : Decimal Point, Q1-Q7 : Segments a-g

SSegSRDriver::SSegSRDriver(PinName srData, PinName srClock, PinName srLatch, bool disp_type): _srData(srData), _srClock(srClock), _srLatch(srLatch) {
    _disp_type = disp_type;
    write_raw(0, false);
    write_raw(0, true);
}

void SSegSRDriver::set_type(bool disp_type) {
    _disp_type = disp_type;
}

void SSegSRDriver::clear() {
    write_raw(0, false);
    write_raw(0, true);
}

void SSegSRDriver::write(unsigned char number) {
    write(number,0);
}

void SSegSRDriver::write(unsigned char number, bool dp) {
    // if (number<16) {
        // Find the definition of the number in chardefs, shift left, set dp (LSB)
        uint8_t digits[2];
        split_digits(number, digits);
        write_raw((SSegSRDriver_chardefs[digits[0]] << 1) | dp, false);
        write_raw((SSegSRDriver_chardefs[digits[1]] << 1) | dp, true);
    // }
}

void SSegSRDriver::write_raw(unsigned char bValue, bool latch) {

    if (!_disp_type) bValue = ~bValue;  // Reverse value for Common Anode

    if (bValue<=0xFF) {
        // Push value to shift register and latch
        _srLatch = 0;
        for (int i=7;i>=0;i--) {    // Output MSB to LSB
            _srClock = 0;
            _srData = (bValue & (1<<i));
            _srClock = 1;
        }
        if(latch){
            _srLatch = 1;
            _srData = 0;
        }
    }
}

void SSegSRDriver::split_digits(int score, uint8_t* digits) {
    if(score < 10) {
        digits[0] = 0;
        digits[1] = score;
    } else {
        digits[0] = (score / 10) % 10;
        digits[1] = score % 10;
    }
}
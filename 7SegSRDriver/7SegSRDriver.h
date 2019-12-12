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

#ifndef LIB_SSEGSRDRIVER_H
#define LIB_SSEGSRDRIVER_H

#include "mbed.h"

#define SSegSRDriver_COMN_ANODE 0
#define SSegSRDriver_COMN_CATHODE 1

//Char defs: 0123456789AbCdEF
const unsigned char SSegSRDriver_chardefs[16] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

/** 7-Segment Display Driver class, via a 8-bit shift register (such as the 74HC595)
 *
 * Display should be hooked up to shift register as follows:
 * Q0 : Decimal Point, Q1-Q7 : Segments a-g
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "7SegSRDriver.h"
 *
 * SSegSRDriver display(p27,p25,p26, SSegSRDriver_COMN_ANODE);
 *
 * int main() {
 *     while (1) {
 *         // Show the chars 0-9 then A-F, flashing the decimal point on and off
 *         for (int i=0; i<16; i++) {
 *             display.write(i,i%2 == 0);
 *             wait(1);
 *         }
 *     }
 * }
 * @endcode
 */
class SSegSRDriver {

public:

    /** Create a 7-Segment Display Driver object connected to a 8-bit shift register on the given DigitalOut pins
     *
     * @param srData Shift Register Data pin (DigitalOut)
     * @param srClock Shift Register Clock pin (DigitalOut)
     * @param srLatch Shift Register Latch pin (DigitalOut)
     * @param disp_type Display Type: Common Anode/Cathode (SSegSRDriver_COMN_ANODE (0) or SSegSRDriver_COMN_CATHODE (1))
     */
    SSegSRDriver(PinName srData, PinName srClock, PinName srLatch, bool disp_type);

    /** Change the type of 7-Segment Display
     *
     * @param disp_type Display Type: Common Anode/Cathode (SSegSRDriver_COMN_ANODE (0) or SSegSRDriver_COMN_CATHODE (1))
     */
    void set_type(bool disp_type);
    
    /** Sets the currently shown digit on the display
     *
     * @param number The digit to display (0-15) to show numbers 0-9 and letters A-F
     */
    void write(unsigned char number); 
    
    /** Sets the currently shown digit on the display along with the decimal place
     *
     * @param number The digit to display (0-15) to show numbers 0-9 and letters A-F
     * @param dp If the decimal place should be lit (0:Off, 1:On)
     */
    void write(unsigned char number, bool dp);   
    
    /** Sets the segments of the display directly
     * Segments are lit by binary flags where LSB is the decimal point, then segments a-g up to the MSB
     * e.g. to light segments e, f and the decimal place = 01100001
     *
     * @param bValue The segments to light
     */
    void write_raw(unsigned char number, bool latch);   // Write directly to the display - Q0/Q1-Q7
    
    /** Turn all segments of the display off
     */
    void clear();   // Clears the display

    void split_digits(int score, uint8_t* digits);
    
private:

    DigitalOut _srData;
    DigitalOut _srClock;
    DigitalOut _srLatch;
    bool _disp_type;
};

#endif
#ifndef TEAM_H
#define TEAM_H

#include "mbed.h"
#include "7SegSRDriver/7SegSRDriver.h"

class Team {

public:
    Team(   PinName inc_pin, 
            PinName dec_pin, 
            PinName voice_pin,
            PinName srData,
            PinName srClock,
            PinName srLatch
        );
    
    void increment_score();
    void decrement_score();
    void reset_score();
    int read_score();
    
private:
    InterruptIn _inc_button;
    InterruptIn _dec_button;
    volatile int _score;
    // SSegSRDriver _display_tens;
    // SSegSRDriver _display_ones;
    InterruptIn _voice;
    SSegSRDriver _display;
    
    void update_display();
    void split_score_digits(int score, uint8_t* digits);
};

#endif
#include "mbed.h"
#include "Team.h"

Team::Team (   
    PinName inc_pin, 
    PinName dec_pin,
    PinName voice_pin, 
    PinName srData,
    PinName srClock,
    PinName srLatch
) : _inc_button(inc_pin), 
    _dec_button(dec_pin), 
    _voice(voice_pin),
    _display(srData, srClock, srLatch, SSegSRDriver_COMN_ANODE)
    // _display_tens(d_one[0], d_one[1], d_one[2], SSegSRDriver_COMN_ANODE), 
    // _display_ones(d_two[0], d_two[1], d_two[2], SSegSRDriver_COMN_ANODE)
{
    _inc_button.rise(callback(this, &Team::increment_score));
    _dec_button.rise(callback(this, &Team::decrement_score));
    _voice.rise(callback(this, &Team::increment_score));
    reset_score();
}

void Team::increment_score()
{
    if (_score >= 99)
        _score = 0;
    else
        _score++;
        
    update_display();
}

void Team::decrement_score()
{
    if (_score <= 0)
        _score = 99;
    else
        _score--;
        
    update_display();
}

void Team::reset_score()
{
    _score = 0;
    update_display();
}

int Team::read_score()
{
    return _score;
}

void Team::update_display()
{
    _display.write(_score);
    // uint8_t digits[2];
    // split_score_digits(_score, digits);
    // _display.write(digits[1]);
    // _display.write(digits[0]);
    
}

void Team::split_score_digits(int score, uint8_t* digits)
{
    if(score < 10) {
        digits[0] = 0;
        digits[1] = score;
    } else {
        digits[0] = (score / 10) % 10;
        digits[1] = score % 10;
    }
}
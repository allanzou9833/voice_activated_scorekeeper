#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "mbed.h"

#define BLOCK_SIZE

class Microphone {
 
public:
    Microphone (
        PinName mic_output,
        float sampling_frequency
    );
    
    float* get_audio();
private:
    AnalogIn _audio;
    Ticker _sampler;
//    arm_fir_instance_f32 _S;
    //CircularBuffer<float, FILTER_TAP_NUM> _src;
//    CircularBuffer<float, FILTER_TAP_NUM> _out;
    
    void dsp();
};

#endif
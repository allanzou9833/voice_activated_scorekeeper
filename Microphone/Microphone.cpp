#include "mbed.h"
#include "Microphone.h"

Microphone::Microphone (
    PinName mic_output,
    float sampling_frequency
) : _audio(mic_output)
{
    _sampler.attach(callback(this, &Microphone::dsp), 1.0 / sampling_frequency);
//    arm_fir_init_f32(_S, FILTER_TAP_NUM, filter_taps, _state, BLOCK_SIZE);
//    for(int i = 0; i < FILTER_TAP_NUM; i++) _src.push(0);
}

void Microphone::dsp()
{
//    _src.push(_audio.read());
    
}

float* Microphone::get_audio()
{
//    return _out;
}
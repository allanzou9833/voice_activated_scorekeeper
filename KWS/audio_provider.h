#ifndef KWS_AUDIO_PROVIDER_H_
#define KWS_AUDIO_PROVIDER_H_

#include "tensorflow/tensorflow/lite/c/c_api_internal.h"
#include "tensorflow/tensorflow/lite/experimental/micro/micro_error_reporter.h"

void SampleAudio(int16_t sample);

// Returns 16-bit PCM sample data for a given point in time
TfLiteStatus GetAudioSamples(tflite::ErrorReporter* error_reporter,
                             int start_ms, int duration_ms,
                             int* audio_samples_size, int16_t** audio_samples);

// Returns the time that audio data was last captured in milliseconds
int32_t LatestAudioTimestamp();

#endif
#include "mbed.h"
#include "KWS/audio_provider.h"
#include "tensorflow/tensorflow/lite/experimental/micro/examples/micro_speech/micro_features/micro_model_settings.h"

// Adafruit Micro Speech Demo
// https://learn.adafruit.com/tensorflow-lite-for-edgebadge-kit-quickstart/micro-speech-demo

Ticker sampleAudioTicker;
AnalogIn micout(A0);
EventQueue q;
Thread eventThread(osPriorityRealtime);
namespace {
  bool g_is_audio_initialized = false;
  constexpr int kAudioCaptureBufferSize = kMaxAudioSampleSize * 16;
  int16_t g_audio_capture_buffer[kAudioCaptureBufferSize];
  int16_t g_audio_output_buffer[kMaxAudioSampleSize];
  int32_t g_latest_audio_timestamp = 0;
  int16_t g_audio_capture_in[kMaxAudioSampleSize]; // 512 samples
}

void CaptureSamples() {
  // This is how many bytes of new data we have each time this is called
  const int number_of_samples = kMaxAudioSampleSize;
  // Calculate what timestamp the last audio sample represents
  const int32_t time_in_ms =
      g_latest_audio_timestamp +
      (number_of_samples / (kAudioSampleFrequency / 1000));
  // Determine the index, in the history of all samples, of the last sample
  const int32_t start_sample_offset =
      g_latest_audio_timestamp * (kAudioSampleFrequency / 1000);
  // Determine the index of this sample in our ring buffer
  const int capture_index = start_sample_offset % kAudioCaptureBufferSize;
  // Read the data to the correct place in our buffer, note 2 bytes per buffer entry
  memcpy(g_audio_capture_buffer + capture_index, (void *)g_audio_capture_in, kMaxAudioSampleSize*2);
  // This is how we let the outside world know that new audio data has arrived.
  g_latest_audio_timestamp = time_in_ms;
}

void TIMER_CALLBACK() {
  static uint32_t audio_idx = 0;
  int32_t sample = (int16_t)micout.read_u16();
  
  if (audio_idx >= kMaxAudioSampleSize) {
    CaptureSamples();
    audio_idx = 0;
  }
 
  g_audio_capture_in[audio_idx] = sample;
  audio_idx++;
}

TfLiteStatus InitAudioRecording(tflite::ErrorReporter* error_reporter) {
  float period = 1.0f/(float)kAudioSampleFrequency;
  eventThread.start(callback(&q, &EventQueue::dispatch_forever));
  sampleAudioTicker.attach(q.event(&TIMER_CALLBACK), period);

  // Block until we have our first audio sample
  // while (!g_latest_audio_timestamp) {
  // }
 
  return kTfLiteOk;
}

TfLiteStatus GetAudioSamples(tflite::ErrorReporter* error_reporter,
                             int start_ms, int duration_ms,
                             int* audio_samples_size, int16_t** audio_samples) {
  if (!g_is_audio_initialized) {
    TfLiteStatus init_status = InitAudioRecording(error_reporter);
    if (init_status != kTfLiteOk) {
      return init_status;
    }
    g_is_audio_initialized = true;
  }

  const int start_offset = start_ms * (kAudioSampleFrequency / 1000);
  // Determine how many samples we want in total
  const int duration_sample_count =
      duration_ms * (kAudioSampleFrequency / 1000);
  for (int i = 0; i < duration_sample_count; ++i) {
    // For each sample, transform its index in the history of all samples into
    // its index in g_audio_capture_buffer
    const int capture_index = (start_offset + i) % kAudioCaptureBufferSize;
    // Write the sample to the output buffer
    g_audio_output_buffer[i] = g_audio_capture_buffer[capture_index];
  }
 
  // Set pointers to provide access to the audio
  *audio_samples_size = kMaxAudioSampleSize;
  *audio_samples = g_audio_output_buffer;
 
  return kTfLiteOk;
}
 
int32_t LatestAudioTimestamp() { return g_latest_audio_timestamp; }

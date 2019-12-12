#ifndef KWS_COMMAND_RESPONDER_H_
#define KWS_COMMAND_RESPONDER_H_

#include "tensorflow/tensorflow/lite/c/c_api_internal.h"
#include "tensorflow/tensorflow/lite/experimental/micro/micro_error_reporter.h"

// Called every time the results of an audio recognition run are available. The
// human-readable name of any recognized command is in the `found_command`
// argument, `score` has the numerical confidence, and `is_new_command` is set
// if the previous command was different to this one.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command);

#endif
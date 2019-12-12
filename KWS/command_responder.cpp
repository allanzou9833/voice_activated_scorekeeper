#include "mbed.h"
#include "KWS/command_responder.h"

// Serial pc(SERIAL_TX, SERIAL_RX);

void RespondToCommand(tflite::ErrorReporter *error_reporter,
                      int32_t current_time, const char *found_command,
                      uint8_t score, bool is_new_command) {
  // pc.printf("Heard %s (%d) @%dms\n", found_command, score, current_time);
  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score, current_time);
    
    // pc.printf("Heard %s (%d) @%dms", found_command, score, current_time);
    
    if (*found_command == 'o') {
      // do something for command
    } else if (found_command[1] == 'w') {
      // do something for command
    } else if (found_command[1] == 'h') {
      // do something for command
    } else if (*found_command == 'u') {
      // do something for command
    } else if (*found_command == 'd') {
      // do something for command
    } else if (*found_command == 's') {
      // do something for command
    } else if (*found_command == 'm') {
      // do something for command
    } else if (*found_command == 'u') {
      // do nothing
    } else {
      // do nothing
    }
  }
}
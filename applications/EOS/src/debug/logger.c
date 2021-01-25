#include "logger.h"

void logMessage(LOG_SEVERITY severity, const char* message) {
  const char* head = "";
  switch (severity) {
    case BOOT: head = concat(concat("[" , long_to_string(millis())) , "ms] "); break; //Use boot time notation to print
    case DEBUG: head = "[DEBUG] "; break;
    case INFO: head = "[INFO] "; break;
    case WARN: head = "[WARN] "; break;
    case ERROR: head = "[ERROR] "; break;
    case CRITICAL: head = "[CRITICAL] "; break;
    case SEVERE: head = "[SEVERE] "; break;
    case FATAL: head = "[FATAL] "; break;
    default: break;
  }
  const char* printed = concat(head , message);
  if(severity == DEBUG) {
    if(getDebug()) {
      HAL_serial_putstring(printed);
    }
    //TODO store to debug log
  } else {
    if(severity == CONSOLE || severity == BOOT) { //If a boot log or console output, print to serial terminal
      HAL_serial_putstring(printed);
    } else { //Else, store in log buffer
      //TODO implement log buffer for logs
    }
  }
}
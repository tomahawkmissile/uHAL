#ifndef LOGGER_H
#define LOGGER_H

#include "hal/serial/serial.h"
#include "hal/time/systime.h"
#include "debug.h"
#include "../utils/string/strings.h"

typedef enum LOG_SEVERITY {
  BOOT,
  CONSOLE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  CRITICAL,
  SEVERE,
  FATAL
} LOG_SEVERITY;

void logMessage(LOG_SEVERITY severity, const char* message);

#endif
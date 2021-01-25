#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "../utils/string/strings.h"
#include "../debug/debug.h"
#include "../debug/logger.h"
#include "hal/serial/serial.h"

bool argsEqual(const char* input,const char* test);
void printConsole(const char* message);
void trimCmdLineArgs(const char** input);
void smartSpaceSplit(const char* line, char** output, unsigned int* outputLength);
void parseCmdLineArgs(const char** input);
void cli_init(void);
void cli_run(void);

#endif
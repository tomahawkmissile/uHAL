#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "../utils/string/strings.h"
#include "../utils/string/args.h"
#include "../debug/debug.h"
#include "../debug/logger.h"
#include "hal/serial/serial.h"

#ifndef MAX_INPUT_LENGTH
#define MAX_INPUT_LENGTH 64 //Default max buffer length
#endif

bool argsEqual(const char* input,const char* test);
void printConsole(const char* message);
void trimCmdLineArgs(char** input);
void parseCmdLineArgs(const char* input);
void cli_init(void);
void cli_run(void);

#endif
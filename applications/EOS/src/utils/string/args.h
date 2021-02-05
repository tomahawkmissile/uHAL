#ifndef ARGS_H
#define ARGS_H

#include "stdbool.h"
#include "string.h"

typedef struct ArgsList {
    const char* base;
    Arg* args;
} ArgsList;
typedef struct Arg {
    const char* key;
    const char* value;
} Arg;

Arg* getArgs(const char** input);
ArgsList getArgsList(const char** input);

#endif
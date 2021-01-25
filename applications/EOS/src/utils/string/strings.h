#ifndef STRINGS_H
#define STRINGS_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char* concat(const char* a, const char* b);
const char* combine_list(const char** list, unsigned int len);
const char* substring(const char* input, unsigned int start, unsigned int end);
char* nonconst_substring(const char* input, unsigned int start, unsigned int end);
const char* long_to_string(long input);

#endif
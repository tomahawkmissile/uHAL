#ifndef STRINGS_H
#define STRINGS_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* nonconst_add_strlen(const char* a, unsigned int aLen);
const char* add_strlen(const char* a, unsigned int aLen);
const char* concat(const char* a, const char* b);
char* nonconst_append_char_strlen(const char* a, unsigned int aLen, char b);
const char* append_char_strlen(const char* a, unsigned int aLen, char b);
char* nonconst_append_char(const char* a, char b);
const char* append_char(const char* a, char b);
const char* combine_list(const char** list, unsigned int len);
char* nonconst_substring(const char* input, unsigned int start, unsigned int end);
const char* substring(const char* input, unsigned int start, unsigned int end);
const char* long_to_string(long input);

#endif
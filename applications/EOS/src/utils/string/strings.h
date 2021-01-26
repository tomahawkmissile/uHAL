#ifndef STRINGS_H
#define STRINGS_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void add_strlen(char** a, unsigned int aLen);

const char* concat_strlen(const char* a, unsigned int aLen, const char* b, unsigned int bLen);
const char* concat(const char* a, const char* b);

void append_char_strlen(char** a, unsigned int aLen, char b);
void append_char(char** a, char b);

const char* combine_list(const char** list, unsigned int len);

char* nonconst_substring(const char* input, unsigned int start, unsigned int end);
const char* substring(const char* input, unsigned int start, unsigned int end);

const char* long_to_string(long input);

#endif
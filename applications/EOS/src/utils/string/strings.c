#include "strings.h"

char* nonconst_add_strlen(const char* a, unsigned int aLen) {
    char* b = (char*)realloc(a,sizeof(char)*(aLen+1));
    b[aLen]='\0';
    return b;
}
const char* add_strlen(const char* a, unsigned int aLen) {
    return (const char*)nonconst_add_strlen(a,aLen);
}

const char* concat_strlen(const char* a, unsigned int aLen, const char* b, unsigned int bLen) {
    char* ret = (char*)malloc(sizeof(char)*(aLen+bLen+1));
    for(unsigned int i=0;i<aLen+bLen;i++) {
        if(i<aLen) ret[i]=a[i];
        else ret[i]=b[i-aLen];
    }
    ret[aLen+bLen]='\0';
    return (const char*)ret;
}
const char* concat(const char* a, const char* b) {
    concat_strlen(a,strlen(a),b,strlen(b));
}

char* nonconst_append_char_strlen(const char* a, unsigned int aLen, char b) {
    char* c = (char*)malloc(sizeof(char)*(aLen+2));
    if(aLen==0) {
        c[0]=b;
        c[1]='\0';
    } else {
        c[strlen(a)]=b;
        c[strlen(a)+1]='\0';
    }
    return c;
}
const char* append_char_strlen(const char* a, unsigned int aLen, char b) {
    return (const char*)nonconst_append_char_strlen(a,aLen,b);
}
char* nonconst_append_char(const char* a, char b) {
    nonconst_append_char_strlen(a,strlen(a),b);
}
const char* append_char(const char* a, char b) {
    return (const char*)nonconst_append_char(a,b);
}

const char* combine_list(const char** list, unsigned int len) {
    if(len < 1) {
        return NULL;
    } else if(len == 1) {
        return list[0];
    } else {
        unsigned int total=0;
        for(unsigned int i=0;i<len;i++) total+=strlen(list[i]);
        const char* ret = list[0];
        for(unsigned int i=1;i<len;i++) {
            ret = concat(ret,list[i]);
        }
        return ret;
    }
}
char* nonconst_substring(const char* input, unsigned int start, unsigned int end) {
    if(start<0 || end-1>strlen(input)) return NULL;
    char* ret = (char*)malloc(sizeof(char)*(end-start+1));
    for(unsigned int i=start;i<end;i++) {
        ret[i-start]=input[i];
    }
    ret[end-start]='\0';
    return ret;
}
const char* substring(const char* input, unsigned int start, unsigned int end) {
    return (const char*)nonconst_substring(input,start,end);
}
const char* long_to_string(long input) {
    if(input==0) return "0";
    //int nDigits = floor(log10(abs(input)))+1;
    const int n = snprintf(NULL, 0, "%lu", input);
    //char buf[n+1];
    char* buf = (char*)malloc(sizeof(char)*(n+1));
    int c = snprintf(buf, n+1, "%lu", input);
    return (const char*)buf;
}
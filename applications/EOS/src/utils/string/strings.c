#include "strings.h"

const char* concat(const char* a, const char* b) {
    unsigned int len1=strlen(a),len2=strlen(b);
    char* ret = (char*)malloc(sizeof(char)*(len1+len2+1));
    for(unsigned int i=0;i<len1+len2;i++) {
        if(i<len1) ret[i]=a[i];
        else ret[i]=b[i-len1];
    }
    return (const char*)ret;
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
const char* substring(const char* input, unsigned int start, unsigned int end) {
    if(start<0 || end-1>strlen(input)) return NULL;
    char* ret = (char*)malloc(sizeof(char)*(end-start+1));
    for(unsigned int i=start;i<end;i++) {
        ret[i-start]=input[i];
    }
    return (const char*)ret;
}

char* nonconst_substring(const char* input, unsigned int start, unsigned int end) {
    if(start<0 || end-1>strlen(input)) return NULL;
    char* ret = (char*)malloc(sizeof(char)*(end-start+1));
    for(unsigned int i=start;i<end;i++) {
        ret[i-start]=input[i];
    }
    return ret;
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
#include "args.h"

Arg* getArgs(const char** input) {
    const char* str = *input;
    char** output; //List of key-value pairs together as a string, delimited by = and spaces
    unsigned int outputLength=0;
    smartCharSplit(str,' ',&output,&outputLength); //Spit by spaces to get key,value pairs
    Arg* args = (Arg*)malloc(sizeof(Arg)*outputLength);
    for(unsigned int i=0;i<outputLength;i++) {
        bool inQuotes=false;
        for(unsigned int j=0;j<strlen(output[i]);j++) {
            char c = output[i][j];
            switch(c) { //Switch on character of current pair
                case '"':
                    inQuotes=!inQuotes;
                    break;
                case '=':
                    if(!inQuotes) {
                        args[i].key=substring(output[i],0,j);
                        args[i].value=substring(output[i],j,strlen(output[i]));
                        j=strlen(output[i]); //Prevent another iteration
                    }
                    break;
                default: break;
            }
        }
    }
    free(output);
    return args;
}

ArgsList getArgsList(const char** input) {
    ArgsList list;
    bool inQuotes=false;
    unsigned int baseEndIndex=-1;
    for(unsigned int i=0;i<strlen(*input);i++) {
        char c = (*input)[i];
        switch(c) {
            case '"':
                inQuotes=!inQuotes;
                break;
            case ' ':
                if(!inQuotes) baseEndIndex=i;
                break;
            default: break;
        }
    }
    list.base=substring(*input,0,baseEndIndex);
    const char* theRest = substring(*input,baseEndIndex,strlen(*input));
    list.args=getArgs(&theRest);
    return list;
}
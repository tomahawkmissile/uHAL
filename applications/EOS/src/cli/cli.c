#include "cli.h"

const char* CONSOLE_HEADER = "[SYSTEM] > ";
const char* COMMAND_RESEND = "[RESEND]";
const char* COMMAND_WATCHDOG = "[WATCHDOG]";

bool argsEqual(const char* input,const char* test) {
  return strcmp(input,test)==0;
}

void printConsole(const char* message) {
  serial_println(concat(CONSOLE_HEADER,message));
}

void trimCmdLineArgs(const char** input) {
  unsigned int firstValidChar=-1, lastValidChar=-1;
  for(unsigned int i=0;i<strlen(*input);i++) { //Get start index
    if((*input)[i]!=' ') { //If not a space
      if(firstValidChar==-1) {
        firstValidChar=i; //If we hit first non space character, set it to start index
        break;
      }
    }
  }
  for(unsigned int i=strlen(*input)-1;i>=0;i--) { //Get end index
    if((*input)[i]!=' ') {
      if(lastValidChar==-1) {
        lastValidChar=i;
        break;
      }
    }
  }
  const char* output = substring(*input,firstValidChar,lastValidChar+1);
  *input = output;
}
void smartSpaceSplit(const char* line, char** output, unsigned int* outputLength) {
  bool inQuotes=false;
  int last=0;
  for(unsigned int i=0;i<strlen(line);i++) {
    char c = line[i];
    switch(c) {
      case '"':
        inQuotes=!inQuotes;
        break;
      case ' ':
        if(!inQuotes && i>0) {
          char* newOutput;
          (*outputLength)++;
          if((*outputLength)>0) newOutput=(char*)realloc(*output,sizeof(char*)*((*outputLength)+1));
          else newOutput=(char*)malloc(sizeof(char)*((*outputLength)+1));
          *output=newOutput;
          output[(*outputLength)-1]=nonconst_substring(line,last,i);
          last=i+1;
          break;
        }
      default: 
        if(i==strlen(line)-2) {
          char* newOutput;
          (*outputLength)++;
          if((*outputLength)>0) newOutput=(char*)realloc(*output,sizeof(char)*((*outputLength)+1));
          else newOutput=(char*)malloc(sizeof(char)*((*outputLength)+1));
          *output=newOutput;
          output[(*outputLength)-1]=nonconst_substring(line,last,i+2);
          return;
        }
      break;
    }
  }
  return;
}
void parseCmdLineArgs(const char** input) {
  trimCmdLineArgs(input);
  
  unsigned int outputLength=0;
  char** output = NULL;
  smartSpaceSplit(*input,output,&outputLength);
  for(int i=0;i<outputLength;i++) {
    serial_println(output[i]);
  }
  
  serial_linebreak();

  if(argsEqual(*input,"help")) {
    serial_println("<--- Available commands --->");
    serial_println("help                                            - show this page");
  } else if(argsEqual(*input,"")) {
    serial_println("");
  } else {
    serial_println("Unknown command. Type \'help\' for a help page.");
  }
  serial_println(CONSOLE_HEADER);
}

void cli_init(void) { //Serial already initialized

    serial_linebreak(); //Spacer before prompt
    serial_println(CONSOLE_HEADER); //Initial console characters on boot
}

char* current_input="";
void cli_run(void) {
    //Console input
  if(serial_available()) {
    char c = serial_read();
    if(c != '\n' && c != '\r') {
      current_input += c;
      serial_printChar(c); //Print back to console to see what you're typing
    }
    if(c=='\n' || c=='\r') { //If incoming data is newline
      parseCmdLineArgs((const char**)&current_input); //Send input to be parsed
      current_input=""; //Reset input
    }
  }
}
#include "cli.h"

const char* CONSOLE_HEADER = "[SYSTEM] > ";
//const char CONSOLE_HEADER[] = {0x5B,0x53,0x59,0x53,0x54,0x45,0x4D,0x5D,0x20,0x3E,0x20};
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
  free((void*)*input);
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
          (*outputLength)++;
          if((*outputLength)>0) *output=(char*)realloc(*output,sizeof(char)*((*outputLength)+1));
          else *output=(char*)malloc(sizeof(char)*((*outputLength)+1));
          output[(*outputLength)-1]=nonconst_substring(line,last,i);
          last=i+1;
          break;
        }
      default: 
        if(i==strlen(line)-2) {
          (*outputLength)++;
          if((*outputLength)>0) *output=(char*)realloc(*output,sizeof(char)*((*outputLength)+1));
          else *output=(char*)malloc(sizeof(char)*((*outputLength)+1));
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

  if(argsEqual(*input,"help")) {
    serial_println("<--- Available commands --->");
    serial_println("help                                            - show this page");
  } else if(argsEqual(*input,"") || strlen(*input)==0) { //Empty input string
    serial_linebreak();
  } else {
    serial_println("Unknown command. Type \'help\' for a help page.");
  }
}

void cli_init(void) { //Serial already initialized

    serial_linebreak(); //Spacer before prompt
    serial_print(CONSOLE_HEADER); //Initial console characters on boot
}

char* current_input;
unsigned int typed_length=0;
void cli_run(void) {
    //Console input
    if(serial_available()) {
        char c = serial_read();
        switch(c) {
          case 0x08:
          case 0x7F:
            if(typed_length>0) {
              serial_printChar(8); serial_printChar(' '); serial_printChar(8);
              --typed_length;
            } else {
              serial_printChar(7); //bell
            }
            break;
          case '\r':
          case '\n':
            //parseCmdLineArgs((const char**)&current_input); //Send input to be parsed
            if(current_input==NULL) {
              serial_linebreak();
            } else {
              serial_println(current_input);
              free((char*)current_input);
            }
            typed_length=0;
            serial_print(CONSOLE_HEADER); //Print new header
              break;
          case 0x03: //Control-C

            break;
          default:
            ++typed_length;
            char* newInput = nonconst_append_char(current_input, c);
            if(current_input != NULL) free((char*)current_input);
            current_input = newInput;
            serial_printChar(c); //Print back to console to see what you're typing
            break;
        }
    }
}
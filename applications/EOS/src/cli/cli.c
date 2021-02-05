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

void trimCmdLineArgs(char** input) {
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
  cut(input,firstValidChar,lastValidChar+1);
}

void parseCmdLineArgs(const char* input) {
  char* output = strdup(input);
  trimCmdLineArgs(&output);
  
  if(argsEqual(output,"help")) {
    serial_println("<--- Available commands --->");
    serial_println("help                                            - show this page");
  } else {
    serial_println("Unknown command. Type \'help\' for a help page.");
  }
}

char current_input[MAX_INPUT_LENGTH+1]; //Input buffer + null terminator
unsigned int typed_length=0; //Length of current input

void cli_init(void) { //Serial already initialized
    serial_linebreak(); //Spacer before prompt
    serial_print(CONSOLE_HEADER); //Initial console characters on boot
}
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
              for(unsigned int i=typed_length;i<MAX_INPUT_LENGTH;i++) current_input[i]='\0'; //Fill with null terminators
            } else {
              serial_printChar(7); //bell
            }
            break;
          case '\r':
          case '\n':
            if(typed_length==0) {
              serial_linebreak();
            } else {
              serial_linebreak();
              parseCmdLineArgs((const char*)current_input); //Send input to be parsed
              for(unsigned int i=0;i<MAX_INPUT_LENGTH;i++) current_input[i]='\0';
            }
            typed_length=0;
            serial_print(CONSOLE_HEADER); //Print new header
            break;
          case 0x03: //Control-C

            break;
          default:
            if(typed_length>=MAX_INPUT_LENGTH) break;
            current_input[typed_length]=c;
            current_input[typed_length+1]='\0';
            ++typed_length;
            serial_printChar(c); //Print back to console to see what you're typing
            break;
        }
    }
}
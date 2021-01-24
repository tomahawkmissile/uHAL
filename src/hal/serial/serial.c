#include "serial.h"

void serial_putstring(const char* str) {
    unsigned int len=strlen(str);
    for(unsigned int i=0;i<len;i++) {
        serial_putchar((char)str[i]);
    }
}

void serial_println(const char* line) {
    serial_putstring(line);
    serial_putchar('\n');
}
void serial_print(const char* line) {
    serial_putstring(line);
}
void serial_printChar(char c) {
    serial_putchar(c);
}
void serial_linebreak(void) {
    serial_putchar('\n');
}
char serial_read(void) {
    return serial_getchar();
}
#include "serial.h"

void serial_putstring(const char* str) {
    unsigned int len=strlen(str);
    for(unsigned int i=0;i<len;i++) {
        hal_uart_putchar((char)str[i]);
    }
}

void serial_println(const char* line) {
    hal_uart_putstring(line);
    hal_uart_putchar('\n');
}
void serial_print(const char* line) {
    hal_uart_putstring(line);
}
void serial_printChar(char c) {
    hal_uart_putchar(c);
}
void serial_linebreak(void) {
    hal_uart_putchar('\n');
}
char serial_read(void) {
    return hal_uart_getchar();
}
#ifndef UHAL_SERIAL_H
#define UHAL_SERIAL_H

#include <stdbool.h>
#include <string.h>

//#ifdef FRONTEND

#include "../../system.h"

#if BACKEND == 1 //If atmega2560
    #include "../../backends/atmega2560/serial/serial.h"
#elif BACKEND == 2 //If atmega328p
    #include "../../backends/atmega328p/serial/serial.h"
#endif


#define serial_init() hal_uart_init()
#define serial_putchar(c) hal_uart_putchar(c)
#define serial_getchar() hal_uart_getchar()
#define serial_available() hal_uart_rxbuffer_ready()

void serial_putstring(const char* str);
void serial_println(const char* line);
void serial_print(const char* line);
void serial_printChar(char c);
void serial_linebreak(void);
char serial_read(void);

//#endif

#endif
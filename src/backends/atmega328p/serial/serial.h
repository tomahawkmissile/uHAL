#ifndef ATMEGA328P_SERIAL_H
#define ATMEGA328P_SERIAL_H

#include <stdbool.h>
#include <stdio.h>
#include <util/setbaud.h>
#include <avr/io.h>

void hal_uart_init(void);
void hal_uart_putchar(char c);
char hal_uart_getchar();
bool hal_uart_rxbuffer_ready(void);

#endif
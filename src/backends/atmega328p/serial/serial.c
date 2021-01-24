#include "serial.h"

void hal_uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    #if USE_2X
    UCSR0A |= _BV(U2X0);
    #else
    UCSR0A &= ~(_BV(U2X0));
    #endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); //8-bit data
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); //Enable RX and TX
}
/*
void atmega328p_uart_setbaud(uint32_t newBaud) {
    
}
*/
void hal_uart_putchar(char c) {
    if(c == '\n') {
        hal_uart_putchar('\r');
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}
char hal_uart_getchar() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
bool hal_uart_rxbuffer_ready(void) {
    if(bit_is_set(UCSR0B,RXC0)) {
        return true;
    } else {
        return false;
    }
}
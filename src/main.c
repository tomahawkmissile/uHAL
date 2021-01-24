#include "hal/serial/serial.h"
#include "hal/time/delay.h"
#include "hal/time/systime.h"

#include <stdio.h>
#include <stdlib.h>

const char* long_to_string(long input) {
    if(input==0) return "0";
    //int nDigits = floor(log10(abs(input)))+1;
    const int n = snprintf(NULL, 0, "%lu", input);
    //char buf[n+1];
    char* buf = (char*)malloc(sizeof(char)*(n+1));
    int c = snprintf(buf, n+1, "%lu", input);
    return (const char*)buf;
}

void main(void) {
    millis_init();
    delay(50);
    serial_init();
    delay(50);

    while(1) {
        unsigned long t1 = millis();
        delay(750);
        unsigned long t2 = millis();
        serial_println(long_to_string(t2-t1));
    }
}
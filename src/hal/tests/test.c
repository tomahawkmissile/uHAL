#include "test.h"

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

void init_hal_test(void) {
    millis_init();
    delay(50);
    serial_init();
    delay(50);

}

void run_hal_test(void) {
    init_hal_test(); //Don't include in header! Will be called upon run.

    
}

void main(void) {
    run_hal_test();

    while(1);
}
#include "hal/time/systime.h"

#include "eos.h"

int main(void) {
    millis_init();

    // Arduino style setup and loop functions, because I like them :)
    setup();
    while(1) loop();

    return -1; //Should not get here
}
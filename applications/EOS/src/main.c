#include "hal/time/systime.h"

#include "eos.h"

#include "utils/string/strings.h"

int main(void) {
    millis_init();

    // Arduino style setup and loop functions, because I like them :)
    setup();

    char* aTest = "Hello, ";
    char* bTest = "World!";
    char cTest = 'y';

    /*
    serial_println(concat(aTest,bTest));
    append_char(&aTest,cTest);
    serial_println(aTest);
    serial_println(substring(aTest,1,4));
    serial_linebreak();
    */

    while(1) loop();

    return -1; //Should not get here
}
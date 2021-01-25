#include "test.h"

const char* long_to_string(uint32_t input) {
    if(input==0) return "0";
    //int nDigits = floor(log10(abs(input)))+1;
    const int n = snprintf(NULL, 0, "%lu", (unsigned long)input);
    //char buf[n+1];
    char* buf = (char*)malloc(sizeof(char)*(n+1));
    int c = snprintf(buf, n+1, "%lu", (unsigned long)input);
    return (const char*)buf;
}

void init_hal_test(void) {
    millis_init();
    delay(50);
    serial_init();
    delay(50);
}

bool run_hal_test(void) {
    init_hal_test(); //Don't include in header! Will be called upon run.
    delay(100);
    
    bool passed=true; //Start off with passing
    serial_println("Initiating HAL system test...");

    uint32_t delay_test = 1; //Start off testing 1ms delays
    for(int i=0;i<4;i++) {
        uint32_t t1 = millis();
        delay(delay_test);
        uint32_t t2 = millis();
        uint32_t diff = (t1>t2 ? t1-t2 : t2-t1);
        uint32_t error = (delay_test > diff ? delay_test-diff : diff-delay_test);
        const char* delay_test_str = long_to_string(delay_test);
        const char* error_str = long_to_string(error);
        serial_print("Delay with t="); serial_print(delay_test_str); serial_print("ms yielded time mismatch of "); serial_println(error_str);
        free((void*)delay_test_str);
        //free((void*)error_str);

        if((double)error/delay_test > 0.05) passed = false; //If delay mismatch greater than 5% test fails
        delay_test *= 10; //Multiply by 10 for next iteration
    }
    if(passed) serial_println("Testing passed.");
    else serial_println("Testing failed.");

    return passed;
}

void main(void) {
    if(run_hal_test()) {
        //Test passed, all good!
    } else {
        //Test failed, handle...
    }

    while(1) {
        const char* ms_str = long_to_string(millis());
        serial_println(ms_str);
        free((void*)ms_str);
        delay(500);
    }
}
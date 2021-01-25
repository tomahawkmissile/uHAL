#include "eos.h"

void setup() {
    serial_init();
    delay(100);
    cli_init();
}
void loop() {
    cli_run();
}
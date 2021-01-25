#include "debug.h"

bool eos_debug = false;

bool getDebug() {
    return eos_debug;
}
void setDebug(bool val) {
    eos_debug = val;
}
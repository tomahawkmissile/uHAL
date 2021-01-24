#ifndef UHAL_DELAY_H
#define UHAL_DELAY_H

#include "../../system.h"

#if BACKEND == 1 //If atmega2560
    #include "../hal/frontends/ATMEGA/2560/time/delay.h"
    #define delay(ms) atmega2560_delay_ms(ms)
#elif BACKEND == 2 //If atmega328p
    #include "../hal/frontends/ATMEGA/328p/time/delay.h"
    #define delay(ms) atmega328p_delay_ms(ms)
#endif

#endif
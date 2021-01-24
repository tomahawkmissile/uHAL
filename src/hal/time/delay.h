#ifndef UHAL_DELAY_H
#define UHAL_DELAY_H

#include "../../system.h"

#if BACKEND == 1 //If atmega2560
    #include "../../backends/atmega2560/time/delay.h"
#elif BACKEND == 2 //If atmega328p
    #include "../../backends/atmega328p/time/delay.h"
#endif

#define delay(ms) hal_delay_ms(ms)

#endif
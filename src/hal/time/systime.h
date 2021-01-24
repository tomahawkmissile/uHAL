#ifndef UHAL_SYSTIME_H
#define UHAL_SYSTIME_H

#include "../../system.h"

#if BACKEND == 1 //If atmega2560
    #include "../../backends/atmega2560/time/systime.h"
#elif BACKEND == 2 //If atmega328p
    #include "../../backends/atmega328p/time/systime.h"
#endif


#define millis() hal_millis_get()
#define millis_init() hal_millis_init()

#endif
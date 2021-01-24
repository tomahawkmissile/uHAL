#ifndef UHAL_SYSTIME_H
#define UHAL_SYSTIME_H

#include "../../system.h"

#if BACKEND == 1 //If atmega2560
    #include "../hal/frontends/ATMEGA/2560/time/systime.h"
    #define millis() atmega2560_millis_get()
#elif BACKEND == 2 //If atmega328p
    #include "../hal/frontends/ATMEGA/328p/time/systime.h"
    #define millis() atmega328p_millis_get()
    #define millis_init() atmega328p_millis_init()
#endif

#endif
#ifndef ATMEGA328P_DELAY_H
#define ATMEGA328P_DELAY_H

#include "../../../../../core/system.h"

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void hal_delay_ms(int ms);

#endif
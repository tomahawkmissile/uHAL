#include "systime.h"

static volatile unsigned long milliseconds;

void hal_millis_init(void) {
    power_timer0_enable();
    
    TCCR1A = 0;
    TCCR1B = _BV(WGM12 | _BV(CS10));
    TIMSK1 = _BV(OCIE1A);
    OCR1A = (((F_CPU)/PRESCALER)/1000);
}

unsigned long hal_millis_get(void) {
    unsigned long ms;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ms = milliseconds;
    }
    return ms;
}
void hal_millis_resume(void) {
    power_timer0_enable();
    TIMSK1 |= _BV(OCIE1A);
}
void hal_millis_pause(void) {
    TIMSK1 &= ~_BV(OCIE1A);
    power_timer0_disable();
}
void hal_millis_reset(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        milliseconds = 0;
    }
}
void hal_millis_add(unsigned long ms) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		milliseconds += ms;
	}
}
void hal_millis_subtract(unsigned long ms) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		milliseconds -= ms;
	}
}
ISR(ISR_VECT) {
    ++milliseconds;
}
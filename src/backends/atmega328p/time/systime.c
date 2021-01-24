#include "systime.h"

volatile uint32_t milliseconds, fraction, overflow;

void hal_millis_init(void) {
    sei();
    TCCR0A = _BV(WGM01);
    TCCR0B = CLOCKSEL;
    TIMSK0 = _BV(OCIE0A);
    OCR0A = (((F_CPU)/PRESCALER)/1000);
}

uint32_t hal_millis_get(void) {
    uint32_t ms;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ms = milliseconds;
    }
    return ms;
}
void hal_millis_resume(void) {
    power_timer0_enable();
    TIMSK0 |= _BV(OCIE0A);
}
void hal_millis_pause(void) {
    TIMSK0 &= ~_BV(OCIE0A);
    power_timer0_disable();
}
void hal_millis_reset(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        milliseconds = 0;
    }
}
void hal_millis_add(uint32_t ms) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		milliseconds += ms;
	}
}
void hal_millis_subtract(uint32_t ms) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		milliseconds -= ms;
	}
}
ISR(ISR_VECT) {
    uint32_t m = milliseconds;
    uint32_t f = fraction;

    m += MS_INC;
    f += FRAC_INC;
    if(f >= FRAC_MAX) {
        f -= FRAC_MAX;
        m+=1;
    }
    fraction = f;
    milliseconds = m;
    ++overflow;
}
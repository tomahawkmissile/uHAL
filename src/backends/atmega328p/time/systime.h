#ifndef ATMEGA328P_SYSTIME_H
#define ATMEGA328P_SYSTIME_H

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>

#include <stdint.h>

#if F_CPU > 16320000 // 16.32MHz - 65.28MHz
	#define CLOCKSEL (_BV(CS20))
	#define PRESCALER 256
#elif F_CPU > 2040000 // 2.04MHz - 16.32MHz
	#define CLOCKSEL (_BV(CS01)|_BV(CS00))
	#define PRESCALER 64
#elif F_CPU > 255 // 256Hz - 2.04MHz
	#define CLOCKSEL (_BV(CS01))
	#define PRESCALER 8
#endif
#ifdef TIMER0_COMPA_vect
	#define ISR_VECT		TIMER0_COMPA_vect
#else
	#define ISR_VECT		TIM0_COMPA_vect
#endif

#define CLOCKS_PER_MS() ( F_CPU / 1000000L )
#define CLOCKS_TO_MS(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define MS_PER_TIMER0_OVERFLOW (CLOCKS_TO_MS(64 * 256))
#define MS_INC (MS_PER_TIMER0_OVERFLOW / 1000)
#define FRAC_INC ((MS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRAC_MAX (1000 >> 3)

void hal_millis_init(void);
uint32_t hal_millis_get(void);
void hal_millis_resume(void);
void hal_millis_pause(void);
void hal_millis_reset(void);
void hal_millis_add(uint32_t ms);
void hal_millis_subtract(uint32_t ms);


#endif

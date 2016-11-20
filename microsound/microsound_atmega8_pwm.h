/**
 * Implementation of microsound library for Atmel AtMega8 microcontroller with sound output via.
 * Output is PB1. PB0 shows calculation length.
 */

#define MICROSOUND_FREQUENCY (F_CPU / 256 / 8)

#include "microsound.h"


void initSound() {
	// prescale timer to 1/1st the clock rate
//	TCCR0 |= (1<<CS00);
	// prescale timer to 1/8th the clock rate
	TCCR0 |= (1<<CS01);
	// enable timer overflow interrupt
	TIMSK |= (1<<TOIE0);

	TCCR1A=(1<<COM1A1)|(1<<WGM10);
	TCCR1B=(1<<CS10);

	OCR1A=0x40;
	DDRB=0x02 | 0x01;

	sei();

	playSound(silence);
}

// Timer interrupt
ISR(TIMER0_OVF_vect) {
	PORTB |= 0x01;

	uint16_t val = getNextSample();

	OCR1A = (val >> 9) & 0xFF;

	PORTB &= ~0x01;
}
